#include "fm_gpu.h"

#include "gpu_sw_renderer.h"
#include "gpu_vram_dirty.h"

#include <3ds.h>
#include <stdint.h>
#include <string.h>


/*
 * ============================================================
 * État
 * ============================================================
 */

typedef enum FMGpuState
{
    FM_GPU_IDLE = 0,

    FM_GPU_VRAM_WRITE,

    FM_GPU_POLYLINE_MONO_SKIP,

    FM_GPU_POLYLINE_SHADED_SKIP

} FMGpuState;


static uint16_t *g_vram = NULL;


static FMGpuState g_state =
    FM_GPU_IDLE;


static uint32_t g_cmd[16];

static unsigned g_cmd_have = 0;

static unsigned g_cmd_need = 0;


static uint64_t g_gp0_count = 0;

/*
 * Paquets GP0 terminés.
 *
 * g_gp0_count compte les mots; ces compteurs permettent de savoir
 * si le flux est composé de vraies primitives, de copies d'image
 * ou seulement de commandes d'environnement.
 */
static uint64_t g_packet_total = 0;
static uint64_t g_packet_nop = 0;
static uint64_t g_packet_fill = 0;
static uint64_t g_packet_draw = 0;
static uint64_t g_packet_copy = 0;
static uint64_t g_packet_upload = 0;
static uint64_t g_packet_readback = 0;
static uint64_t g_packet_env = 0;
static uint64_t g_packet_other = 0;

static uint64_t g_upload_data_words = 0;

/*
 * ============================================================
 * B122 - high-resolution GP0 opcode profiler
 * ============================================================
 *
 * B121 still shows 60-230 ms DMA2 transfers after collapsing thousands
 * of empty OT buckets. Time completed GP0 commands with the ARM11 system
 * tick so we can rank the actual raster/copy/upload opcodes by cost.
 */
static uint64_t g_b122_opcode_ticks[256];
static uint32_t g_b122_opcode_calls[256];
static uint64_t g_b122_opcode_max_ticks[256];

static uint64_t g_b122_exec_ticks = 0u;
static uint64_t g_b122_upload_ticks = 0u;
static uint64_t g_b122_upload_words = 0u;

/*
 * B124 - native 3DS fast path for variable-size textured rectangles
 * (GP0 64h..67h). This bypasses the generic multi-target renderer when
 * scale=1, no wide mirror and nearest filtering are active.
 */
static uint32_t g_b124_rect_hits = 0u;
static uint32_t g_b124_rect_fallbacks = 0u;
static uint64_t g_b124_rect_pixels = 0u;
static uint64_t g_b124_rect_texels = 0u;

/*
 * B125 - fixed-point fast paths for the actual hot quads seen on 3DS:
 *   2Ch/2Eh family : flat textured quad
 *   38h..3Bh       : Gouraud untextured quad (3Ah is the hot semi-trans case)
 */
static uint32_t g_b125_texquad_hits = 0u;
static uint32_t g_b125_gouraud_hits = 0u;
static uint32_t g_b125_fallbacks = 0u;
static uint64_t g_b125_pixels = 0u;

/* B126 - direct proof of opcode flow and linked object version. */
static uint32_t g_b126_seen_2c = 0u;
static uint32_t g_b126_seen_2e = 0u;
static uint32_t g_b126_seen_3a = 0u;
static uint32_t g_b126_try_t = 0u;
static uint32_t g_b126_try_g = 0u;
static uint32_t g_b126_reject_mask = 0u;

/*
 * B129 - direct native VRAM fill for GP0(02h).
 * Keeps the current renderer semantics but removes per-pixel wrap masking.
 */
static uint32_t g_b129_fill_hits = 0u;
static uint32_t g_b129_fill_fallbacks = 0u;
static uint64_t g_b129_fill_pixels = 0u;
static uint64_t g_b129_fill_zero_pixels = 0u;
static uint32_t g_b129_fill_max_pixels = 0u;

static uint64_t b122_ticks_to_us(uint64_t ticks)
{
    return
        (ticks * 1000000ull)
        /
        (uint64_t)SYSCLOCK_ARM11;
}

static void b122_record_opcode(
    uint8_t opcode,
    uint64_t ticks
)
{
    g_b122_opcode_ticks[opcode] += ticks;
    ++g_b122_opcode_calls[opcode];

    if (ticks > g_b122_opcode_max_ticks[opcode])
    {
        g_b122_opcode_max_ticks[opcode] = ticks;
    }

    g_b122_exec_ticks += ticks;
}

/* B28: diagnostic/preservation des clears framebuffer. */
static uint64_t g_fill_suppressed = 0;

/*
 * B42 - mode video natif.
 *
 * Les anciens builds supprimaient volontairement les gros clears noirs
 * pour conserver le background WA_MRG injecte a la main. Maintenant que
 * le runtime CD/GPU avance reellement, le mode normal doit laisser le jeu
 * effacer ses propres framebuffers.
 */
static int g_preserve_background_clears = 0;
static int g_last_fill_x = 0;
static int g_last_fill_y = 0;
static int g_last_fill_w = 0;
static int g_last_fill_h = 0;
static uint16_t g_last_fill_color = 0;

/*
 * B29 - trace des trois dernieres primitives GP0 DRAW.
 * Base propre reconstruite depuis B28.
 */
typedef struct FMB29DrawTrace
{
    uint8_t opcode;
    uint8_t words;
    uint16_t texpage;
    int16_t off_x;
    int16_t off_y;
    uint16_t area_x1;
    uint16_t area_y1;
    uint16_t area_x2;
    uint16_t area_y2;
    uint32_t cmd[8];
} FMB29DrawTrace;

static FMB29DrawTrace g_b29_draw_trace[3];
static unsigned g_b29_draw_trace_head = 0u;
static unsigned g_b29_draw_trace_count = 0u;

/*
 * B38 - trace ciblee des gros rectangles/sprites.
 * Aucun changement de rendu : diagnostic uniquement.
 */
static uint32_t g_b38_bigrect_count = 0u;
static uint8_t  g_b38_bigrect_opcode = 0u;
static uint8_t  g_b38_bigrect_textured = 0u;
static uint8_t  g_b38_bigrect_raw = 0u;
static int      g_b38_bigrect_x = 0;
static int      g_b38_bigrect_y = 0;
static int      g_b38_bigrect_w = 0;
static int      g_b38_bigrect_h = 0;
static int      g_b38_bigrect_u = 0;
static int      g_b38_bigrect_v = 0;
static int      g_b38_bigrect_clut_x = 0;
static int      g_b38_bigrect_clut_y = 0;
static uint16_t g_b38_bigrect_texpage = 0u;
static uint32_t g_b38_bigrect_texwindow = 0u;
static uint32_t g_b38_bigrect_cmd[4] = {0,0,0,0};

/*
 * ============================================================
 * B44 - qui ecrit dans la zone texture du sprite 72x72 ?
 * ============================================================
 *
 * B43 a prouve qu'aucun LoadImage HLE ne couvre cette zone.
 * On observe maintenant TOUS les paquets GP0 susceptibles d'ecrire
 * dedans : fill, draw, copy et upload.
 *
 * Zone issue du sprite observe :
 *   TP=0x204, U/V=136/64, 4 bpp, 72x72
 *   -> VRAM words x=290..307, y=64..135
 */
#define B44_WX 290
#define B44_WY 64
#define B44_WW 18
#define B44_WH 72

static uint32_t g_b44_serial = 0u;
static uint32_t g_b44_hits_fill = 0u;
static uint32_t g_b44_hits_draw = 0u;
static uint32_t g_b44_hits_copy = 0u;
static uint32_t g_b44_hits_upload = 0u;

static uint32_t g_b44_last_serial = 0u;
static uint8_t  g_b44_last_type = 0u; /* F,D,C,U */
static uint8_t  g_b44_last_opcode = 0u;
static int      g_b44_last_x = 0;
static int      g_b44_last_y = 0;
static int      g_b44_last_w = 0;
static int      g_b44_last_h = 0;
static uint32_t g_b44_last_cmd[4] = {0,0,0,0};

/*
 * ============================================================
 * B46 - provenance GPU native du sprite 72x72
 * ============================================================
 *
 * B45 n'a pas vu le sprite dans fm_submit_ot_safe(). On trace donc
 * directement execute_command(), point commun de tous les paquets GP0.
 */
static uint32_t g_b46_cmd_serial = 0u;
static uint32_t g_b46_last_e1_serial = 0u;
static uint16_t g_b46_last_e1_value = 0u;
static uint32_t g_b46_last_fill_serial = 0u;

static uint32_t g_b46_sprite_hits = 0u;
static uint32_t g_b46_sprite_serial = 0u;
static uint32_t g_b46_sprite_e1_age = 0xFFFFFFFFu;
static uint32_t g_b46_sprite_fill_age = 0xFFFFFFFFu;
static uint16_t g_b46_sprite_e1 = 0u;
static uint16_t g_b46_sprite_texpage = 0u;
static int g_b46_sprite_off_x = 0;
static int g_b46_sprite_off_y = 0;
static uint32_t g_b46_sprite_cmd[4] = {0,0,0,0};

static int g_has_frame = 0;


/*
 * ============================================================
 * Draw environment
 * ============================================================
 */

static uint16_t g_texpage = 0;
static uint32_t g_texture_window = 0;

static int g_draw_x1 = 0;
static int g_draw_y1 = 0;

static int g_draw_x2 = 1023;
static int g_draw_y2 = 511;

static int g_offset_x = 0;
static int g_offset_y = 0;

static int g_mask_set = 0;
static int g_mask_check = 0;


/*
 * ============================================================
 * Display
 * ============================================================
 */

static unsigned g_display_x = 0;

static unsigned g_display_y = 0;

static int g_display_disabled = 1;

static uint32_t g_display_mode = 0u;
static uint32_t g_b104_gp1_08_count = 0u;


/*
 * ============================================================
 * B100 - trace legere des commandes de frame-buffer
 * ============================================================
 */
static uint32_t g_b100_e3_count = 0u;
static uint32_t g_b100_e4_count = 0u;
static uint32_t g_b100_e5_count = 0u;
static uint32_t g_b100_gp1_05_count = 0u;

static uint32_t g_b100_last_e3 = 0u;
static uint32_t g_b100_last_e4 = 0u;
static uint32_t g_b100_last_e5 = 0u;
static uint32_t g_b100_last_gp1_05 = 0u;

/* B101: drawable GP0 packets seen with a non-zero draw offset. */
static uint32_t g_b101_offset_draw_packets = 0u;


/*
 * ============================================================
 * CPU -> VRAM transfer
 * ============================================================
 */

static unsigned g_upload_x = 0;
static unsigned g_upload_y = 0;

static unsigned g_upload_w = 0;
static unsigned g_upload_h = 0;

static uint32_t g_upload_index = 0;
static uint32_t g_upload_pixels = 0;


/*
 * ============================================================
 * Helpers
 * ============================================================
 */

static int sign11(
    uint32_t value
)
{
    value &=
        0x7FFu;


    if (value & 0x400u)
    {
        value |=
            0xFFFFF800u;
    }


    return
        (int32_t)value;
}


static int coord_x(
    uint32_t word
)
{
    return
        (int16_t)(
            word
            &
            0xFFFFu
        );
}


static int coord_y(
    uint32_t word
)
{
    return
        (int16_t)(
            word
            >>
            16
        );
}


static int tex_u(
    uint32_t word
)
{
    return
        word
        &
        0xFFu;
}


static int tex_v(
    uint32_t word
)
{
    return
        (
            word
            >>
            8
        )
        &
        0xFFu;
}


static uint16_t packet_clut(
    uint32_t word
)
{
    return
        (uint16_t)(
            word
            >>
            16
        );
}


static uint16_t packet_texpage(
    uint32_t word
)
{
    return
        (uint16_t)(
            word
            >>
            16
        );
}


static int clut_x(
    uint16_t clut
)
{
    return
        (clut & 0x3Fu)
        *
        16;
}


static int clut_y(
    uint16_t clut
)
{
    return
        (
            clut
            >>
            6
        )
        &
        0x1FFu;
}


static uint16_t rgb24_to_555(
    uint32_t color
)
{
    unsigned r =
        color
        &
        0xFFu;


    unsigned g =
        (
            color
            >>
            8
        )
        &
        0xFFu;


    unsigned b =
        (
            color
            >>
            16
        )
        &
        0xFFu;


    return
        (uint16_t)(
            (r >> 3)
            |
            (
                (g >> 3)
                <<
                5
            )
            |
            (
                (b >> 3)
                <<
                10
            )
        );
}


static void set_texture_modulation(
    uint32_t command,
    int raw_texture
)
{
    int r =
        command
        &
        0xFFu;


    int g =
        (
            command
            >>
            8
        )
        &
        0xFFu;


    int b =
        (
            command
            >>
            16
        )
        &
        0xFFu;


    sw_set_color_modulation(
        r,
        g,
        b,
        raw_texture
    );
}


static void set_primitive_state(
    uint8_t opcode
)
{
    int semi =
        (
            opcode
            &
            0x02u
        )
        !=
        0;


    int mode =
        (
            g_texpage
            >>
            5
        )
        &
        3;


    sw_set_semi_transparency(
        semi,
        mode
    );


    sw_set_mask_bits(
        g_mask_set,
        g_mask_check
    );
}


/*
 * ============================================================
 * B124 - fast textured rectangle for native 3DS mode
 * ============================================================
 */
static inline uint16_t b124_vram_get(int x, int y)
{
    return
        g_vram[
            ((unsigned)y & 511u) * 1024u
            +
            ((unsigned)x & 1023u)
        ];
}


static inline uint16_t b124_blend(
    uint16_t back,
    uint16_t front,
    int mode
)
{
    int br = (back >> 0) & 31;
    int bg = (back >> 5) & 31;
    int bb = (back >> 10) & 31;
    int fr = (front >> 0) & 31;
    int fg = (front >> 5) & 31;
    int fb = (front >> 10) & 31;
    int r, g, b;

    switch (mode & 3)
    {
        case 0:
            r = (br + fr) >> 1;
            g = (bg + fg) >> 1;
            b = (bb + fb) >> 1;
            break;

        case 1:
            r = br + fr; if (r > 31) r = 31;
            g = bg + fg; if (g > 31) g = 31;
            b = bb + fb; if (b > 31) b = 31;
            break;

        case 2:
            r = br - fr; if (r < 0) r = 0;
            g = bg - fg; if (g < 0) g = 0;
            b = bb - fb; if (b < 0) b = 0;
            break;

        default:
            r = br + (fr >> 2); if (r > 31) r = 31;
            g = bg + (fg >> 2); if (g > 31) g = 31;
            b = bb + (fb >> 2); if (b > 31) b = 31;
            break;
    }

    return
        (uint16_t)(
            r
            |
            (g << 5)
            |
            (b << 10)
        );
}


static inline uint16_t b124_fetch_texel(
    int u,
    int v,
    int clx,
    int cly,
    uint16_t texpage
)
{
    unsigned mask_x =
        g_texture_window
        &
        0x1Fu;

    unsigned mask_y =
        (g_texture_window >> 5)
        &
        0x1Fu;

    unsigned off_x =
        (g_texture_window >> 10)
        &
        0x1Fu;

    unsigned off_y =
        (g_texture_window >> 15)
        &
        0x1Fu;

    if (mask_x | mask_y)
    {
        u =
            (u & ~(int)(mask_x * 8u))
            |
            (int)((off_x & mask_x) * 8u);

        v =
            (v & ~(int)(mask_y * 8u))
            |
            (int)((off_y & mask_y) * 8u);
    }

    u &= 0xFF;
    v &= 0xFF;

    int tpx =
        (texpage & 0x0Fu)
        *
        64;

    int tpy =
        ((texpage >> 4) & 1u)
        *
        256;

    int depth =
        (texpage >> 7)
        &
        3u;

    if (depth == 0)
    {
        uint16_t packed =
            b124_vram_get(
                tpx + (u >> 2),
                tpy + v
            );

        int index =
            (packed >> ((u & 3) * 4))
            &
            0x0F;

        return
            b124_vram_get(
                clx + index,
                cly
            );
    }

    if (depth == 1)
    {
        uint16_t packed =
            b124_vram_get(
                tpx + (u >> 1),
                tpy + v
            );

        int index =
            (packed >> ((u & 1) * 8))
            &
            0xFF;

        return
            b124_vram_get(
                clx + index,
                cly
            );
    }

    return
        b124_vram_get(
            tpx + u,
            tpy + v
        );
}


static int b124_try_textured_rect(
    uint8_t opcode,
    int x,
    int y,
    int w,
    int h,
    int u,
    int v,
    int clx,
    int cly,
    uint16_t texpage,
    uint32_t command,
    int raw_texture
)
{
    if (
        !g_vram
        ||
        sw_renderer_scale() != 1
        ||
        sw_wide_width() != 0
        ||
        sw_texture_filter() != 0
    )
    {
        ++g_b124_rect_fallbacks;
        return 0;
    }

    /*
     * First B124 intentionally targets only the measured hot family
     * 64h..67h (variable-size textured rectangle).
     */
    if ((opcode & 0xFCu) != 0x64u)
    {
        ++g_b124_rect_fallbacks;
        return 0;
    }

    ++g_b124_rect_hits;

    if (w <= 0 || h <= 0)
    {
        return 1;
    }

    int x0 = x;
    int y0 = y;
    int x1 = x + w;
    int y1 = y + h;

    if (x0 < g_draw_x1) x0 = g_draw_x1;
    if (y0 < g_draw_y1) y0 = g_draw_y1;
    if (x1 > g_draw_x2 + 1) x1 = g_draw_x2 + 1;
    if (y1 > g_draw_y2 + 1) y1 = g_draw_y2 + 1;

    if (x0 < 0) x0 = 0;
    if (y0 < 0) y0 = 0;
    if (x1 > 1024) x1 = 1024;
    if (y1 > 512) y1 = 512;

    if (x0 >= x1 || y0 >= y1)
    {
        return 1;
    }

    int mod_r =
        (command & 0xFFu)
        >>
        3;

    int mod_g =
        ((command >> 8) & 0xFFu)
        >>
        3;

    int mod_b =
        ((command >> 16) & 0xFFu)
        >>
        3;

    int semi =
        (opcode & 0x02u)
        !=
        0;

    int semi_mode =
        (texpage >> 5)
        &
        3u;

    g_b124_rect_pixels +=
        (uint64_t)(x1 - x0)
        *
        (uint64_t)(y1 - y0);

    for (int py = y0; py < y1; ++py)
    {
        int tv =
            (v + (py - y))
            &
            0xFF;

        uint16_t *dst =
            g_vram
            +
            (size_t)py * 1024u
            +
            (size_t)x0;

        int tu =
            (u + (x0 - x))
            &
            0xFF;

        for (int px = x0; px < x1; ++px, ++dst)
        {
            uint16_t texel =
                b124_fetch_texel(
                    tu,
                    tv,
                    clx,
                    cly,
                    texpage
                );

            tu =
                (tu + 1)
                &
                0xFF;

            ++g_b124_rect_texels;

            if (texel == 0u)
            {
                continue;
            }

            if (
                g_mask_check
                &&
                (*dst & 0x8000u)
            )
            {
                continue;
            }

            uint16_t color;

            if (raw_texture)
            {
                color =
                    texel
                    &
                    0x7FFFu;
            }
            else
            {
                int tr = (texel >> 0) & 31;
                int tg = (texel >> 5) & 31;
                int tb = (texel >> 10) & 31;

                int r = (tr * mod_r) >> 4;
                int g = (tg * mod_g) >> 4;
                int b = (tb * mod_b) >> 4;

                if (r > 31) r = 31;
                if (g > 31) g = 31;
                if (b > 31) b = 31;

                color =
                    (uint16_t)(
                        r
                        |
                        (g << 5)
                        |
                        (b << 10)
                    );
            }

            if (
                semi
                &&
                (texel & 0x8000u)
            )
            {
                color =
                    b124_blend(
                        *dst,
                        color,
                        semi_mode
                    );
            }

            if (g_mask_set)
            {
                color |=
                    0x8000u;
            }

            *dst =
                color;
        }
    }

    return 1;
}



/*
 * ============================================================
 * B125 - fixed-point hot-quad rasterizers
 * ============================================================
 *
 * These paths intentionally target native 1x / nearest / no-wide mode only.
 * They replace per-pixel floating-point interpolation with 16.16 fixed-point
 * increments. The generic renderer remains the fallback for every other mode.
 */

static int b125_native_mode_ready(void)
{
    uint32_t reject = 0u;

    if (!g_vram) reject |= 1u;
    if (sw_renderer_scale() != 1) reject |= 2u;
    if (sw_wide_width() != 0) reject |= 4u;
    if (sw_texture_filter() != 0) reject |= 8u;

    g_b126_reject_mask |= reject;

    return reject == 0u;
}


static inline void b125_put_textured(
    uint16_t *dst,
    uint16_t texel,
    int mod_r,
    int mod_g,
    int mod_b,
    int raw_texture,
    int semi,
    int semi_mode
)
{
    if (texel == 0u)
    {
        return;
    }

    if (
        g_mask_check
        &&
        (*dst & 0x8000u)
    )
    {
        return;
    }

    uint16_t color;

    if (raw_texture)
    {
        color =
            texel
            &
            0x7FFFu;
    }
    else
    {
        int tr = (texel >> 0) & 31;
        int tg = (texel >> 5) & 31;
        int tb = (texel >> 10) & 31;

        int r = (tr * mod_r) >> 4;
        int g = (tg * mod_g) >> 4;
        int b = (tb * mod_b) >> 4;

        if (r > 31) r = 31;
        if (g > 31) g = 31;
        if (b > 31) b = 31;

        color =
            (uint16_t)(
                r
                |
                (g << 5)
                |
                (b << 10)
            );
    }

    if (
        semi
        &&
        (texel & 0x8000u)
    )
    {
        color =
            b124_blend(
                *dst,
                color,
                semi_mode
            );
    }

    if (g_mask_set)
    {
        color |=
            0x8000u;
    }

    *dst =
        color;
}


static inline void b125_put_gouraud(
    uint16_t *dst,
    uint16_t color,
    int semi,
    int semi_mode
)
{
    if (
        g_mask_check
        &&
        (*dst & 0x8000u)
    )
    {
        return;
    }

    if (semi)
    {
        color =
            b124_blend(
                *dst,
                color,
                semi_mode
            );
    }

    if (g_mask_set)
    {
        color |=
            0x8000u;
    }

    *dst =
        color;
}


static inline int32_t b128_div_fp16(
    int64_t numerator,
    int32_t denominator
)
{
    if (denominator == 0)
    {
        return 0;
    }

    return
        (int32_t)(
            (numerator << 16)
            /
            denominator
        );
}


/*
 * B128: affine plane gradients + incremental edges.
 *
 * B125 still performed several 64-bit divisions on EVERY scanline.
 * ARM11 has no hardware integer divide, so those helpers dominated the
 * supposedly "fast" path. B128 performs all divisions once per triangle:
 *
 *   - 3 edge X slopes
 *   - 4 UV plane gradients for textured triangles
 *   - 6 RGB plane gradients for Gouraud triangles
 *
 * Raster loops then use additions only.
 */
static void b125_textured_triangle(
    int x0, int y0, int u0, int v0,
    int x1, int y1, int u1, int v1,
    int x2, int y2, int u2, int v2,
    int clx,
    int cly,
    uint16_t texpage,
    uint32_t command,
    int raw_texture,
    int semi
)
{
#define B128_SWAP_INT(a,b) do { int _t=(a); (a)=(b); (b)=_t; } while (0)

    if (y0 > y1)
    {
        B128_SWAP_INT(x0,x1);
        B128_SWAP_INT(y0,y1);
        B128_SWAP_INT(u0,u1);
        B128_SWAP_INT(v0,v1);
    }

    if (y0 > y2)
    {
        B128_SWAP_INT(x0,x2);
        B128_SWAP_INT(y0,y2);
        B128_SWAP_INT(u0,u2);
        B128_SWAP_INT(v0,v2);
    }

    if (y1 > y2)
    {
        B128_SWAP_INT(x1,x2);
        B128_SWAP_INT(y1,y2);
        B128_SWAP_INT(u1,u2);
        B128_SWAP_INT(v1,v2);
    }

    int dy02 = y2 - y0;

    if (dy02 <= 0)
    {
        return;
    }

    int64_t det =
        (int64_t)(x1 - x0) * (int64_t)(y2 - y0)
        -
        (int64_t)(x2 - x0) * (int64_t)(y1 - y0);

    if (det == 0)
    {
        return;
    }

    /*
     * 16.16 affine UV plane gradients. Only four divides per triangle.
     */
    int32_t du_dx =
        (int32_t)(
            (
                (
                    (int64_t)(u1 - u0) * (y2 - y0)
                    -
                    (int64_t)(u2 - u0) * (y1 - y0)
                )
                << 16
            )
            /
            det
        );

    int32_t du_dy =
        (int32_t)(
            (
                (
                    (int64_t)(x1 - x0) * (u2 - u0)
                    -
                    (int64_t)(x2 - x0) * (u1 - u0)
                )
                << 16
            )
            /
            det
        );

    int32_t dv_dx =
        (int32_t)(
            (
                (
                    (int64_t)(v1 - v0) * (y2 - y0)
                    -
                    (int64_t)(v2 - v0) * (y1 - y0)
                )
                << 16
            )
            /
            det
        );

    int32_t dv_dy =
        (int32_t)(
            (
                (
                    (int64_t)(x1 - x0) * (v2 - v0)
                    -
                    (int64_t)(x2 - x0) * (v1 - v0)
                )
                << 16
            )
            /
            det
        );

    int32_t dx_long =
        b128_div_fp16(
            (int64_t)(x2 - x0),
            dy02
        );

    int32_t dx_upper =
        b128_div_fp16(
            (int64_t)(x1 - x0),
            y1 - y0
        );

    int32_t dx_lower =
        b128_div_fp16(
            (int64_t)(x2 - x1),
            y2 - y1
        );

    int mod_r = (command & 0xFFu) >> 3;
    int mod_g = ((command >> 8) & 0xFFu) >> 3;
    int mod_b = ((command >> 16) & 0xFFu) >> 3;

    int semi_mode =
        (texpage >> 5)
        &
        3u;

    int ys = y0;
    int ye = y2;

    if (ys < g_draw_y1) ys = g_draw_y1;
    if (ye > g_draw_y2 + 1) ye = g_draw_y2 + 1;
    if (ys < 0) ys = 0;
    if (ye > 512) ye = 512;

    for (int y = ys; y < ye; ++y)
    {
        int32_t xl_fp =
            ((int32_t)x0 << 16)
            +
            dx_long * (y - y0);

        int32_t xs_fp;

        if (y < y1)
        {
            xs_fp =
                ((int32_t)x0 << 16)
                +
                dx_upper * (y - y0);
        }
        else
        {
            xs_fp =
                ((int32_t)x1 << 16)
                +
                dx_lower * (y - y1);
        }

        int32_t left_fp =
            xl_fp < xs_fp
                ? xl_fp
                : xs_fp;

        int32_t right_fp =
            xl_fp < xs_fp
                ? xs_fp
                : xl_fp;

        int sx = left_fp >> 16;
        int ex = right_fp >> 16;

        if (sx < g_draw_x1) sx = g_draw_x1;
        if (ex > g_draw_x2 + 1) ex = g_draw_x2 + 1;
        if (sx < 0) sx = 0;
        if (ex > 1024) ex = 1024;

        if (sx >= ex)
        {
            continue;
        }

        int32_t u_fp =
            (int32_t)(
                ((int64_t)u0 << 16)
                +
                (int64_t)du_dx * (sx - x0)
                +
                (int64_t)du_dy * (y - y0)
            );

        int32_t v_fp =
            (int32_t)(
                ((int64_t)v0 << 16)
                +
                (int64_t)dv_dx * (sx - x0)
                +
                (int64_t)dv_dy * (y - y0)
            );

        uint16_t *dst =
            g_vram
            +
            (size_t)y * 1024u
            +
            (size_t)sx;

        g_b125_pixels +=
            (uint64_t)(ex - sx);

        for (int x = sx; x < ex; ++x, ++dst)
        {
            uint16_t texel =
                b124_fetch_texel(
                    (u_fp >> 16) & 0xFF,
                    (v_fp >> 16) & 0xFF,
                    clx,
                    cly,
                    texpage
                );

            b125_put_textured(
                dst,
                texel,
                mod_r,
                mod_g,
                mod_b,
                raw_texture,
                semi,
                semi_mode
            );

            u_fp += du_dx;
            v_fp += dv_dx;
        }
    }

#undef B128_SWAP_INT
}


static void b125_gouraud_triangle(
    int x0, int y0, uint16_t c0,
    int x1, int y1, uint16_t c1,
    int x2, int y2, uint16_t c2,
    int semi,
    int semi_mode
)
{
#define B128_SWAP_INT2(a,b) do { int _t=(a); (a)=(b); (b)=_t; } while (0)
#define B128_SWAP_U16(a,b) do { uint16_t _t=(a); (a)=(b); (b)=_t; } while (0)

    if (y0 > y1)
    {
        B128_SWAP_INT2(x0,x1);
        B128_SWAP_INT2(y0,y1);
        B128_SWAP_U16(c0,c1);
    }

    if (y0 > y2)
    {
        B128_SWAP_INT2(x0,x2);
        B128_SWAP_INT2(y0,y2);
        B128_SWAP_U16(c0,c2);
    }

    if (y1 > y2)
    {
        B128_SWAP_INT2(x1,x2);
        B128_SWAP_INT2(y1,y2);
        B128_SWAP_U16(c1,c2);
    }

    int dy02 = y2 - y0;

    if (dy02 <= 0)
    {
        return;
    }

    int64_t det =
        (int64_t)(x1 - x0) * (int64_t)(y2 - y0)
        -
        (int64_t)(x2 - x0) * (int64_t)(y1 - y0);

    if (det == 0)
    {
        return;
    }

    int r0 = (c0 >> 0) & 31;
    int g0 = (c0 >> 5) & 31;
    int b0 = (c0 >> 10) & 31;

    int r1 = (c1 >> 0) & 31;
    int g1 = (c1 >> 5) & 31;
    int b1 = (c1 >> 10) & 31;

    int r2 = (c2 >> 0) & 31;
    int g2 = (c2 >> 5) & 31;
    int b2 = (c2 >> 10) & 31;

#define B128_GRAD_X(a0,a1,a2) \
    ((int32_t)(((((int64_t)((a1)-(a0)) * (y2-y0)) - \
                  ((int64_t)((a2)-(a0)) * (y1-y0))) << 16) / det))

#define B128_GRAD_Y(a0,a1,a2) \
    ((int32_t)(((((int64_t)(x1-x0) * ((a2)-(a0))) - \
                  ((int64_t)(x2-x0) * ((a1)-(a0)))) << 16) / det))

    int32_t dr_dx = B128_GRAD_X(r0,r1,r2);
    int32_t dr_dy = B128_GRAD_Y(r0,r1,r2);
    int32_t dg_dx = B128_GRAD_X(g0,g1,g2);
    int32_t dg_dy = B128_GRAD_Y(g0,g1,g2);
    int32_t db_dx = B128_GRAD_X(b0,b1,b2);
    int32_t db_dy = B128_GRAD_Y(b0,b1,b2);

#undef B128_GRAD_X
#undef B128_GRAD_Y

    int32_t dx_long =
        b128_div_fp16(
            (int64_t)(x2 - x0),
            dy02
        );

    int32_t dx_upper =
        b128_div_fp16(
            (int64_t)(x1 - x0),
            y1 - y0
        );

    int32_t dx_lower =
        b128_div_fp16(
            (int64_t)(x2 - x1),
            y2 - y1
        );

    int ys = y0;
    int ye = y2;

    if (ys < g_draw_y1) ys = g_draw_y1;
    if (ye > g_draw_y2 + 1) ye = g_draw_y2 + 1;
    if (ys < 0) ys = 0;
    if (ye > 512) ye = 512;

    for (int y = ys; y < ye; ++y)
    {
        int32_t xl_fp =
            ((int32_t)x0 << 16)
            +
            dx_long * (y - y0);

        int32_t xs_fp;

        if (y < y1)
        {
            xs_fp =
                ((int32_t)x0 << 16)
                +
                dx_upper * (y - y0);
        }
        else
        {
            xs_fp =
                ((int32_t)x1 << 16)
                +
                dx_lower * (y - y1);
        }

        int32_t left_fp =
            xl_fp < xs_fp
                ? xl_fp
                : xs_fp;

        int32_t right_fp =
            xl_fp < xs_fp
                ? xs_fp
                : xl_fp;

        int sx = left_fp >> 16;
        int ex = right_fp >> 16;

        if (sx < g_draw_x1) sx = g_draw_x1;
        if (ex > g_draw_x2 + 1) ex = g_draw_x2 + 1;
        if (sx < 0) sx = 0;
        if (ex > 1024) ex = 1024;

        if (sx >= ex)
        {
            continue;
        }

        int32_t r_fp =
            (int32_t)(
                ((int64_t)r0 << 16)
                +
                (int64_t)dr_dx * (sx - x0)
                +
                (int64_t)dr_dy * (y - y0)
            );

        int32_t g_fp =
            (int32_t)(
                ((int64_t)g0 << 16)
                +
                (int64_t)dg_dx * (sx - x0)
                +
                (int64_t)dg_dy * (y - y0)
            );

        int32_t b_fp =
            (int32_t)(
                ((int64_t)b0 << 16)
                +
                (int64_t)db_dx * (sx - x0)
                +
                (int64_t)db_dy * (y - y0)
            );

        uint16_t *dst =
            g_vram
            +
            (size_t)y * 1024u
            +
            (size_t)sx;

        g_b125_pixels +=
            (uint64_t)(ex - sx);

        for (int x = sx; x < ex; ++x, ++dst)
        {
            int r = r_fp >> 16;
            int g = g_fp >> 16;
            int b = b_fp >> 16;

            if (r < 0) r = 0; else if (r > 31) r = 31;
            if (g < 0) g = 0; else if (g > 31) g = 31;
            if (b < 0) b = 0; else if (b > 31) b = 31;

            uint16_t color =
                (uint16_t)(
                    r
                    |
                    (g << 5)
                    |
                    (b << 10)
                );

            b125_put_gouraud(
                dst,
                color,
                semi,
                semi_mode
            );

            r_fp += dr_dx;
            g_fp += dg_dx;
            b_fp += db_dx;
        }
    }

#undef B128_SWAP_INT2
#undef B128_SWAP_U16
}


static int b125_try_textured_quad(
    uint8_t opcode,
    int x0, int y0, int u0, int v0,
    int x1, int y1, int u1, int v1,
    int x2, int y2, int u2, int v2,
    int x3, int y3, int u3, int v3,
    int clx,
    int cly,
    uint16_t texpage,
    uint32_t command,
    int raw_texture
)
{
    if (
        !b125_native_mode_ready()
        ||
        (opcode & 0xFCu) != 0x2Cu
    )
    {
        ++g_b125_fallbacks;
        return 0;
    }

    ++g_b125_texquad_hits;

    int semi =
        (opcode & 0x02u)
        !=
        0;

    b125_textured_triangle(
        x0,y0,u0,v0,
        x1,y1,u1,v1,
        x2,y2,u2,v2,
        clx,cly,
        texpage,
        command,
        raw_texture,
        semi
    );

    b125_textured_triangle(
        x1,y1,u1,v1,
        x2,y2,u2,v2,
        x3,y3,u3,v3,
        clx,cly,
        texpage,
        command,
        raw_texture,
        semi
    );

    return 1;
}


static int b125_try_gouraud_quad(
    uint8_t opcode,
    int x0, int y0, uint16_t c0,
    int x1, int y1, uint16_t c1,
    int x2, int y2, uint16_t c2,
    int x3, int y3, uint16_t c3
)
{
    if (
        !b125_native_mode_ready()
        ||
        (opcode & 0xFCu) != 0x38u
    )
    {
        ++g_b125_fallbacks;
        return 0;
    }

    ++g_b125_gouraud_hits;

    int semi =
        (opcode & 0x02u)
        !=
        0;

    int semi_mode =
        (g_texpage >> 5)
        &
        3u;

    b125_gouraud_triangle(
        x0,y0,c0,
        x1,y1,c1,
        x2,y2,c2,
        semi,
        semi_mode
    );

    b125_gouraud_triangle(
        x1,y1,c1,
        x2,y2,c2,
        x3,y3,c3,
        semi,
        semi_mode
    );

    return 1;
}



/*
 * ============================================================
 * B129 - fast GP0(02h) VRAM fill
 * ============================================================
 */

static inline void b129_fill_span(
    uint16_t *dst,
    uint32_t count,
    uint16_t color
)
{
    if (count == 0u)
    {
        return;
    }

    if (color == 0u)
    {
        memset(
            dst,
            0,
            (size_t)count * sizeof(uint16_t)
        );
        return;
    }

    if (color == 0xFFFFu)
    {
        memset(
            dst,
            0xFF,
            (size_t)count * sizeof(uint16_t)
        );
        return;
    }

    if (
        ((uintptr_t)dst & 3u) != 0u
        &&
        count != 0u
    )
    {
        *dst++ = color;
        --count;
    }

    uint32_t pair =
        (uint32_t)color
        |
        ((uint32_t)color << 16);

    uint32_t pairs =
        count >> 1;

    uint32_t *dst32 =
        (uint32_t *)dst;

    while (pairs >= 4u)
    {
        dst32[0] = pair;
        dst32[1] = pair;
        dst32[2] = pair;
        dst32[3] = pair;

        dst32 += 4;
        pairs -= 4u;
    }

    while (pairs != 0u)
    {
        *dst32++ = pair;
        --pairs;
    }

    if (count & 1u)
    {
        *((uint16_t *)dst32) =
            color;
    }
}


static int b129_try_fill_rect(
    int x,
    int y,
    int w,
    int h,
    uint16_t color
)
{
    /*
     * sw_fill_rect() only maintains the supersampled shadow when scale>1.
     * In the current 3DS native mode scale is 1, so direct VRAM is exact.
     */
    if (
        !g_vram
        ||
        sw_renderer_scale() != 1
    )
    {
        ++g_b129_fill_fallbacks;
        return 0;
    }

    ++g_b129_fill_hits;

    if (w <= 0 || h <= 0)
    {
        return 1;
    }

    uint32_t area =
        (uint32_t)w
        *
        (uint32_t)h;

    g_b129_fill_pixels +=
        area;

    if (color == 0u)
    {
        g_b129_fill_zero_pixels +=
            area;
    }

    if (area > g_b129_fill_max_pixels)
    {
        g_b129_fill_max_pixels =
            area;
    }

    uint32_t x0 =
        (uint32_t)x
        &
        1023u;

    uint32_t y0 =
        (uint32_t)y
        &
        511u;

    for (int row = 0; row < h; ++row)
    {
        uint32_t py =
            (y0 + (uint32_t)row)
            &
            511u;

        uint32_t remaining =
            (uint32_t)w;

        uint32_t px =
            x0;

        while (remaining != 0u)
        {
            uint32_t span =
                1024u - px;

            if (span > remaining)
            {
                span =
                    remaining;
            }

            b129_fill_span(
                g_vram
                    +
                    (size_t)py * 1024u
                    +
                    px,
                span,
                color
            );

            remaining -=
                span;

            px =
                0u;
        }
    }

    /*
     * Preserve the same dirty-region side effect as sw_fill_rect().
     * Offline this is an inline no-op; rollback tracking remains correct.
     */
    gpu_vram_dirty_mark_rect(
        (int)x0,
        (int)y0,
        w,
        h
    );

    return 1;
}


/*
 * ============================================================
 * Longueur commande GP0
 * ============================================================
 */

static unsigned command_words(
    uint8_t opcode
)
{
    if (
        opcode == 0x00
        ||
        opcode == 0x01
    )
    {
        return 1;
    }


    if (opcode == 0x02)
    {
        return 3;
    }


    /*
     * Polygones.
     */
    if (
        opcode >= 0x20
        &&
        opcode <= 0x3F
    )
    {
        int gouraud =
            opcode
            &
            0x10;


        int quad =
            opcode
            &
            0x08;


        int textured =
            opcode
            &
            0x04;


        if (
            !gouraud
            &&
            !textured
        )
        {
            return
                quad
                    ? 5
                    : 4;
        }


        if (
            !gouraud
            &&
            textured
        )
        {
            return
                quad
                    ? 9
                    : 7;
        }


        if (
            gouraud
            &&
            !textured
        )
        {
            return
                quad
                    ? 8
                    : 6;
        }


        return
            quad
                ? 12
                : 9;
    }


    /*
     * Lignes.
     */
    if (
        opcode >= 0x40
        &&
        opcode <= 0x47
    )
    {
        return 3;
    }


    /*
     * Mono polyline.
     */
    if (
        opcode >= 0x48
        &&
        opcode <= 0x4F
    )
    {
        return 3;
    }


    /*
     * Gouraud line.
     */
    if (
        opcode >= 0x50
        &&
        opcode <= 0x57
    )
    {
        return 4;
    }


    /*
     * Gouraud polyline.
     */
    if (
        opcode >= 0x58
        &&
        opcode <= 0x5F
    )
    {
        return 4;
    }


    /*
     * Rectangles.
     */
    if (
        opcode >= 0x60
        &&
        opcode <= 0x7F
    )
    {
        int textured =
            opcode
            &
            0x04;


        unsigned size_type =
            (
                opcode
                >>
                3
            )
            &
            3u;


        /*
         * Taille variable.
         */
        if (size_type == 0)
        {
            return
                textured
                    ? 4
                    : 3;
        }


        return
            textured
                ? 3
                : 2;
    }


    /*
     * VRAM -> VRAM.
     */
    if (
        opcode >= 0x80
        &&
        opcode <= 0x9F
    )
    {
        return 4;
    }


    /*
     * CPU -> VRAM.
     */
    if (
        opcode >= 0xA0
        &&
        opcode <= 0xBF
    )
    {
        return 3;
    }


    /*
     * VRAM -> CPU.
     */
    if (
        opcode >= 0xC0
        &&
        opcode <= 0xDF
    )
    {
        return 3;
    }


    /*
     * Environment.
     */
    if (
        opcode >= 0xE0
    )
    {
        return 1;
    }


    return 1;
}


/*
 * B29 - capture une primitive DRAW juste avant son execution.
 */
static void fm_gpu_b29_capture_draw(uint8_t opcode)
{
    if (opcode < 0x20u || opcode > 0x7Fu)
    {
        return;
    }

    FMB29DrawTrace *trace =
        &g_b29_draw_trace[g_b29_draw_trace_head];

    memset(trace, 0, sizeof(*trace));

    trace->opcode = opcode;
    trace->words = (uint8_t)g_cmd_need;
    trace->texpage = g_texpage;
    trace->off_x = (int16_t)g_offset_x;
    trace->off_y = (int16_t)g_offset_y;
    trace->area_x1 = (uint16_t)g_draw_x1;
    trace->area_y1 = (uint16_t)g_draw_y1;
    trace->area_x2 = (uint16_t)g_draw_x2;
    trace->area_y2 = (uint16_t)g_draw_y2;

    unsigned copy_words = g_cmd_need;
    if (copy_words > 8u)
    {
        copy_words = 8u;
    }

    for (unsigned i = 0; i < copy_words; ++i)
    {
        trace->cmd[i] = g_cmd[i];
    }

    g_b29_draw_trace_head =
        (g_b29_draw_trace_head + 1u) % 3u;

    if (g_b29_draw_trace_count < 3u)
    {
        ++g_b29_draw_trace_count;
    }
}

/*
 * ============================================================
 * B44 writer helpers
 * ============================================================
 */
static int b44_overlap_rect(int x, int y, int w, int h)
{
    if (w <= 0 || h <= 0)
    {
        return 0;
    }

    int ax0 = x;
    int ay0 = y;
    int ax1 = x + w;
    int ay1 = y + h;

    int bx0 = B44_WX;
    int by0 = B44_WY;
    int bx1 = B44_WX + B44_WW;
    int by1 = B44_WY + B44_WH;

    return ax0 < bx1 && bx0 < ax1 && ay0 < by1 && by0 < ay1;
}

static void b44_note(
    uint8_t type,
    uint8_t opcode,
    int x,
    int y,
    int w,
    int h
)
{
    ++g_b44_serial;

    if (!b44_overlap_rect(x, y, w, h))
    {
        return;
    }

    if (type == 'F') ++g_b44_hits_fill;
    else if (type == 'D') ++g_b44_hits_draw;
    else if (type == 'C') ++g_b44_hits_copy;
    else if (type == 'U') ++g_b44_hits_upload;

    g_b44_last_serial = g_b44_serial;
    g_b44_last_type = type;
    g_b44_last_opcode = opcode;
    g_b44_last_x = x;
    g_b44_last_y = y;
    g_b44_last_w = w;
    g_b44_last_h = h;

    for (unsigned i = 0; i < 4u; ++i)
    {
        g_b44_last_cmd[i] = i < g_cmd_need ? g_cmd[i] : 0u;
    }
}

static void b44_bounds_from_points(
    const int *xs,
    const int *ys,
    unsigned n,
    int *x,
    int *y,
    int *w,
    int *h
)
{
    int minx = xs[0], maxx = xs[0];
    int miny = ys[0], maxy = ys[0];

    for (unsigned i = 1; i < n; ++i)
    {
        if (xs[i] < minx) minx = xs[i];
        if (xs[i] > maxx) maxx = xs[i];
        if (ys[i] < miny) miny = ys[i];
        if (ys[i] > maxy) maxy = ys[i];
    }

    *x = minx;
    *y = miny;
    *w = maxx - minx + 1;
    *h = maxy - miny + 1;
}

static void b44_trace_current_packet(uint8_t opcode)
{
    /* Fill */
    if (opcode == 0x02u)
    {
        int x = (int)(g_cmd[1] & 0x3FFu);
        int y = (int)((g_cmd[1] >> 16) & 0x1FFu);
        int w = (int)(g_cmd[2] & 0x3FFu);
        int h = (int)((g_cmd[2] >> 16) & 0x1FFu);
        b44_note('F', opcode, x, y, w, h);
        return;
    }

    /* Polygons */
    if (opcode >= 0x20u && opcode <= 0x3Fu)
    {
        int gouraud = (opcode & 0x10u) != 0;
        int quad = (opcode & 0x08u) != 0;
        int textured = (opcode & 0x04u) != 0;

        unsigned ci[4] = {0,0,0,0};
        unsigned n = quad ? 4u : 3u;

        if (!gouraud && !textured)
        {
            ci[0]=1; ci[1]=2; ci[2]=3; ci[3]=4;
        }
        else if (!gouraud && textured)
        {
            ci[0]=1; ci[1]=3; ci[2]=5; ci[3]=7;
        }
        else if (gouraud && !textured)
        {
            ci[0]=1; ci[1]=3; ci[2]=5; ci[3]=7;
        }
        else
        {
            ci[0]=1; ci[1]=4; ci[2]=7; ci[3]=10;
        }

        int xs[4], ys[4];
        for (unsigned i = 0; i < n; ++i)
        {
            xs[i] = coord_x(g_cmd[ci[i]]) + g_offset_x;
            ys[i] = coord_y(g_cmd[ci[i]]) + g_offset_y;
        }

        int x,y,w,h;
        b44_bounds_from_points(xs, ys, n, &x, &y, &w, &h);
        b44_note('D', opcode, x, y, w, h);
        return;
    }

    /* Lines - first segment is sufficient for our watch. */
    if (opcode >= 0x40u && opcode <= 0x4Fu)
    {
        int xs[2] = {
            coord_x(g_cmd[1]) + g_offset_x,
            coord_x(g_cmd[2]) + g_offset_x
        };
        int ys[2] = {
            coord_y(g_cmd[1]) + g_offset_y,
            coord_y(g_cmd[2]) + g_offset_y
        };
        int x,y,w,h;
        b44_bounds_from_points(xs, ys, 2u, &x, &y, &w, &h);
        b44_note('D', opcode, x, y, w, h);
        return;
    }

    if (opcode >= 0x50u && opcode <= 0x5Fu)
    {
        int xs[2] = {
            coord_x(g_cmd[1]) + g_offset_x,
            coord_x(g_cmd[3]) + g_offset_x
        };
        int ys[2] = {
            coord_y(g_cmd[1]) + g_offset_y,
            coord_y(g_cmd[3]) + g_offset_y
        };
        int x,y,w,h;
        b44_bounds_from_points(xs, ys, 2u, &x, &y, &w, &h);
        b44_note('D', opcode, x, y, w, h);
        return;
    }

    /* Rectangles / sprites. */
    if (opcode >= 0x60u && opcode <= 0x7Fu)
    {
        int textured = (opcode & 0x04u) != 0;
        unsigned size_type = (opcode >> 3) & 3u;

        int x = coord_x(g_cmd[1]) + g_offset_x;
        int y = coord_y(g_cmd[1]) + g_offset_y;
        int w = 0, h = 0;

        if (size_type == 0u)
        {
            uint32_t sw = textured ? g_cmd[3] : g_cmd[2];
            w = (int)(sw & 0xFFFFu);
            h = (int)((sw >> 16) & 0xFFFFu);
        }
        else if (size_type == 1u)
        {
            w = 1; h = 1;
        }
        else if (size_type == 2u)
        {
            w = 8; h = 8;
        }
        else
        {
            w = 16; h = 16;
        }

        b44_note('D', opcode, x, y, w, h);
        return;
    }

    /* VRAM -> VRAM copy, watch destination. */
    if (opcode >= 0x80u && opcode <= 0x9Fu)
    {
        int x = (int)(g_cmd[2] & 0x3FFu);
        int y = (int)((g_cmd[2] >> 16) & 0x1FFu);
        int w = (int)(g_cmd[3] & 0x3FFu);
        int h = (int)((g_cmd[3] >> 16) & 0x1FFu);
        b44_note('C', opcode, x, y, w, h);
        return;
    }

    /* CPU -> VRAM upload header. */
    if (opcode >= 0xA0u && opcode <= 0xBFu)
    {
        int x = (int)(g_cmd[1] & 0x3FFu);
        int y = (int)((g_cmd[1] >> 16) & 0x1FFu);
        int w = (int)(g_cmd[2] & 0xFFFFu);
        int h = (int)((g_cmd[2] >> 16) & 0xFFFFu);
        if (w == 0) w = 0x10000;
        if (h == 0) h = 0x10000;
        b44_note('U', opcode, x, y, w, h);
        return;
    }
}

/*
 * ============================================================
 * Exécution primitive
 * ============================================================
 */

static void execute_command(void)
{
    uint8_t opcode =
        (
            g_cmd[0]
            >>
            24
        )
        &
        0xFFu;

    if (opcode == 0x2Cu) ++g_b126_seen_2c;
    if (opcode == 0x2Eu) ++g_b126_seen_2e;
    if (opcode == 0x3Au) ++g_b126_seen_3a;

    ++g_b46_cmd_serial;

    if (opcode == 0xE1u)
    {
        g_b46_last_e1_serial = g_b46_cmd_serial;
        g_b46_last_e1_value = (uint16_t)(g_cmd[0] & 0x07FFu);
    }

    if (opcode == 0x02u && g_cmd_need >= 3u)
    {
        int fx = (int)(g_cmd[1] & 0x3FFu);
        int fy = (int)((g_cmd[1] >> 16) & 0x1FFu);
        int fw = (int)(g_cmd[2] & 0x3FFu);
        int fh = (int)((g_cmd[2] >> 16) & 0x1FFu);

        if (fx == 0 && fy == 0 && fw == 320 && fh == 256)
        {
            g_b46_last_fill_serial = g_b46_cmd_serial;
        }
    }

    if (opcode == 0x64u && g_cmd_need >= 4u)
    {
        int sx = coord_x(g_cmd[1]) + g_offset_x;
        int sy = coord_y(g_cmd[1]) + g_offset_y;
        int su = (int)(g_cmd[2] & 0xFFu);
        int sv = (int)((g_cmd[2] >> 8) & 0xFFu);
        int sw = (int)(g_cmd[3] & 0xFFFFu);
        int sh = (int)((g_cmd[3] >> 16) & 0xFFFFu);

        if (sx == 17 && sy == 17 && su == 136 && sv == 64 && sw == 72 && sh == 72)
        {
            ++g_b46_sprite_hits;
            g_b46_sprite_serial = g_b46_cmd_serial;
            g_b46_sprite_e1 = g_b46_last_e1_value;
            g_b46_sprite_texpage = g_texpage;
            g_b46_sprite_off_x = g_offset_x;
            g_b46_sprite_off_y = g_offset_y;

            g_b46_sprite_e1_age =
                g_b46_last_e1_serial != 0u
                    ? g_b46_cmd_serial - g_b46_last_e1_serial
                    : 0xFFFFFFFFu;

            g_b46_sprite_fill_age =
                g_b46_last_fill_serial != 0u
                    ? g_b46_cmd_serial - g_b46_last_fill_serial
                    : 0xFFFFFFFFu;

            for (unsigned i = 0; i < 4u; ++i)
            {
                g_b46_sprite_cmd[i] = g_cmd[i];
            }
        }
    }


    fm_gpu_b29_capture_draw(opcode);

    b44_trace_current_packet(opcode);

    if (
        opcode >= 0x20u
        &&
        opcode <= 0x7Fu
        &&
        (g_offset_x != 0 || g_offset_y != 0)
    )
    {
        ++g_b101_offset_draw_packets;
    }


    /*
     * --------------------------------------------------------
     * Diagnostic packet classification
     * --------------------------------------------------------
     */

    ++g_packet_total;


    if (
        opcode == 0x00u
        ||
        opcode == 0x01u
    )
    {
        ++g_packet_nop;
    }
    else if (opcode == 0x02u)
    {
        ++g_packet_fill;
    }
    else if (
        opcode >= 0x20u
        &&
        opcode <= 0x7Fu
    )
    {
        ++g_packet_draw;
    }
    else if (
        opcode >= 0x80u
        &&
        opcode <= 0x9Fu
    )
    {
        ++g_packet_copy;
    }
    else if (
        opcode >= 0xA0u
        &&
        opcode <= 0xBFu
    )
    {
        ++g_packet_upload;
    }
    else if (
        opcode >= 0xC0u
        &&
        opcode <= 0xDFu
    )
    {
        ++g_packet_readback;
    }
    else if (opcode >= 0xE0u)
    {
        ++g_packet_env;
    }
    else
    {
        ++g_packet_other;
    }


    /*
     * --------------------------------------------------------
     * NOP / clear texture cache
     * --------------------------------------------------------
     */

    if (
        opcode == 0x00
        ||
        opcode == 0x01
    )
    {
        return;
    }


    /*
     * --------------------------------------------------------
     * Fill rectangle in VRAM
     * --------------------------------------------------------
     */

    if (opcode == 0x02)
    {
        int x =
            g_cmd[1]
            &
            0x3FFu;


        int y =
            (
                g_cmd[1]
                >>
                16
            )
            &
            0x1FFu;


        int w =
            g_cmd[2]
            &
            0x3FFu;


        int h =
            (
                g_cmd[2]
                >>
                16
            )
            &
            0x1FFu;


        uint16_t fill_color =
            rgb24_to_555(
                g_cmd[0]
            );

        g_last_fill_x = x;
        g_last_fill_y = y;
        g_last_fill_w = w;
        g_last_fill_h = h;
        g_last_fill_color = fill_color;

        /*
         * B28 - PRESERVE BACKGROUND CLEAR
         *
         * B27 montre que les deux uploads A0h sont bien executes,
         * puis la VRAM retombe a zero pendant RUN. Les 13 paquets
         * Fill sont donc le suspect principal.
         *
         * Pendant le bring-up uniquement, on ignore les grands clears
         * noirs des pages framebuffer. Les primitives suivantes restent
         * executees et peuvent ainsi se dessiner au-dessus du vrai decor
         * WA_MRG deja place en VRAM.
         */
        if (
            g_preserve_background_clears
            && fill_color == 0u
            && w >= 256
            && h >= 160
            && y < 256
            && x < 640
        )
        {
            ++g_fill_suppressed;
            g_has_frame = 1;
            return;
        }

        if (
            !b129_try_fill_rect(
                x,
                y,
                w,
                h,
                fill_color
            )
        )
        {
            sw_fill_rect(
                x,
                y,
                w,
                h,
                fill_color
            );
        }


        g_has_frame =
            1;


        return;
    }


    /*
     * ========================================================
     * Polygons
     * ========================================================
     */
    /*
     * B101 - IMPORTANT:
     *
     * GP0(E5h) is the PS1 drawing offset. The software rasterizer API
     * receives final VRAM coordinates; merely calling sw_set_draw_offset()
     * does not translate the primitive coordinates in this renderer.
     *
     * B100 proved Forbidden Memories alternates:
     *   draw area/offset 0..319    <-> 320..639
     * while P320 stayed empty.
     *
     * Apply g_offset_x/g_offset_y to ALL GP0 drawing primitives here.
     */

    if (
        opcode >= 0x20
        &&
        opcode <= 0x3F
    )
    {
        int gouraud =
            (
                opcode
                &
                0x10
            )
            !=
            0;


        int quad =
            (
                opcode
                &
                0x08
            )
            !=
            0;


        int textured =
            (
                opcode
                &
                0x04
            )
            !=
            0;


        int raw =
            (
                opcode
                &
                0x01
            )
            !=
            0;


        set_primitive_state(
            opcode
        );


        /*
         * ----------------------------------------------------
         * Flat untextured
         * ----------------------------------------------------
         */

        if (
            !gouraud
            &&
            !textured
        )
        {
            uint16_t color =
                rgb24_to_555(
                    g_cmd[0]
                );


            int x0 =
                (coord_x(g_cmd[1]) + g_offset_x);

            int y0 =
                (coord_y(g_cmd[1]) + g_offset_y);

            int x1 =
                (coord_x(g_cmd[2]) + g_offset_x);

            int y1 =
                (coord_y(g_cmd[2]) + g_offset_y);

            int x2 =
                (coord_x(g_cmd[3]) + g_offset_x);

            int y2 =
                (coord_y(g_cmd[3]) + g_offset_y);


            sw_draw_flat_triangle(
                x0,
                y0,
                x1,
                y1,
                x2,
                y2,
                color
            );


            if (quad)
            {
                int x3 =
                    (coord_x(g_cmd[4]) + g_offset_x);

                int y3 =
                    (coord_y(g_cmd[4]) + g_offset_y);


                sw_draw_flat_triangle(
                    x1,
                    y1,
                    x2,
                    y2,
                    x3,
                    y3,
                    color
                );
            }


            g_has_frame =
                1;


            return;
        }


        /*
         * ----------------------------------------------------
         * Flat textured
         * ----------------------------------------------------
         */

        if (
            !gouraud
            &&
            textured
        )
        {
            int x0 =
                (coord_x(g_cmd[1]) + g_offset_x);

            int y0 =
                (coord_y(g_cmd[1]) + g_offset_y);

            int u0 =
                tex_u(g_cmd[2]);

            int v0 =
                tex_v(g_cmd[2]);


            uint16_t clut =
                packet_clut(
                    g_cmd[2]
                );


            int x1 =
                (coord_x(g_cmd[3]) + g_offset_x);

            int y1 =
                (coord_y(g_cmd[3]) + g_offset_y);

            int u1 =
                tex_u(g_cmd[4]);

            int v1 =
                tex_v(g_cmd[4]);


            g_texpage =
                packet_texpage(
                    g_cmd[4]
                );


            int x2 =
                (coord_x(g_cmd[5]) + g_offset_x);

            int y2 =
                (coord_y(g_cmd[5]) + g_offset_y);

            int u2 =
                tex_u(g_cmd[6]);

            int v2 =
                tex_v(g_cmd[6]);


            set_texture_modulation(
                g_cmd[0],
                raw
            );


            set_primitive_state(
                opcode
            );


            if (quad)
            {
                int x3 =
                    (coord_x(g_cmd[7]) + g_offset_x);

                int y3 =
                    (coord_y(g_cmd[7]) + g_offset_y);

                int u3 =
                    tex_u(g_cmd[8]);

                int v3 =
                    tex_v(g_cmd[8]);

                ++g_b126_try_t;

                if (
                    b125_try_textured_quad(
                        opcode,
                        x0,y0,u0,v0,
                        x1,y1,u1,v1,
                        x2,y2,u2,v2,
                        x3,y3,u3,v3,
                        clut_x(clut),
                        clut_y(clut),
                        g_texpage,
                        g_cmd[0],
                        raw
                    )
                )
                {
                    g_has_frame = 1;
                    return;
                }
            }

            sw_draw_textured_triangle(
                x0,
                y0,
                u0,
                v0,

                x1,
                y1,
                u1,
                v1,

                x2,
                y2,
                u2,
                v2,

                clut_x(clut),
                clut_y(clut),

                g_texpage
            );


            if (quad)
            {
                int x3 =
                    (coord_x(g_cmd[7]) + g_offset_x);

                int y3 =
                    (coord_y(g_cmd[7]) + g_offset_y);

                int u3 =
                    tex_u(g_cmd[8]);

                int v3 =
                    tex_v(g_cmd[8]);


                sw_draw_textured_triangle(
                    x1,
                    y1,
                    u1,
                    v1,

                    x2,
                    y2,
                    u2,
                    v2,

                    x3,
                    y3,
                    u3,
                    v3,

                    clut_x(clut),
                    clut_y(clut),

                    g_texpage
                );
            }


            g_has_frame =
                1;


            return;
        }


        /*
         * ----------------------------------------------------
         * Gouraud untextured
         * ----------------------------------------------------
         */

        if (
            gouraud
            &&
            !textured
        )
        {
            uint16_t c0 =
                rgb24_to_555(
                    g_cmd[0]
                );


            int x0 =
                (coord_x(g_cmd[1]) + g_offset_x);

            int y0 =
                (coord_y(g_cmd[1]) + g_offset_y);


            uint16_t c1 =
                rgb24_to_555(
                    g_cmd[2]
                );


            int x1 =
                (coord_x(g_cmd[3]) + g_offset_x);

            int y1 =
                (coord_y(g_cmd[3]) + g_offset_y);


            uint16_t c2 =
                rgb24_to_555(
                    g_cmd[4]
                );


            int x2 =
                (coord_x(g_cmd[5]) + g_offset_x);

            int y2 =
                (coord_y(g_cmd[5]) + g_offset_y);


            if (quad)
            {
                uint16_t c3 =
                    rgb24_to_555(
                        g_cmd[6]
                    );

                int x3 =
                    (coord_x(g_cmd[7]) + g_offset_x);

                int y3 =
                    (coord_y(g_cmd[7]) + g_offset_y);

                ++g_b126_try_g;

                if (
                    b125_try_gouraud_quad(
                        opcode,
                        x0,y0,c0,
                        x1,y1,c1,
                        x2,y2,c2,
                        x3,y3,c3
                    )
                )
                {
                    g_has_frame = 1;
                    return;
                }
            }

            sw_draw_gouraud_triangle(
                x0,
                y0,
                c0,

                x1,
                y1,
                c1,

                x2,
                y2,
                c2
            );


            if (quad)
            {
                uint16_t c3 =
                    rgb24_to_555(
                        g_cmd[6]
                    );


                int x3 =
                    (coord_x(g_cmd[7]) + g_offset_x);

                int y3 =
                    (coord_y(g_cmd[7]) + g_offset_y);


                sw_draw_gouraud_triangle(
                    x1,
                    y1,
                    c1,

                    x2,
                    y2,
                    c2,

                    x3,
                    y3,
                    c3
                );
            }


            g_has_frame =
                1;


            return;
        }


        /*
         * ----------------------------------------------------
         * Gouraud textured
         * ----------------------------------------------------
         */

        {
            uint32_t c0 =
                g_cmd[0]
                &
                0xFFFFFFu;


            int x0 =
                (coord_x(g_cmd[1]) + g_offset_x);

            int y0 =
                (coord_y(g_cmd[1]) + g_offset_y);

            int u0 =
                tex_u(g_cmd[2]);

            int v0 =
                tex_v(g_cmd[2]);


            uint16_t clut =
                packet_clut(
                    g_cmd[2]
                );


            uint32_t c1 =
                g_cmd[3]
                &
                0xFFFFFFu;


            int x1 =
                (coord_x(g_cmd[4]) + g_offset_x);

            int y1 =
                (coord_y(g_cmd[4]) + g_offset_y);

            int u1 =
                tex_u(g_cmd[5]);

            int v1 =
                tex_v(g_cmd[5]);


            g_texpage =
                packet_texpage(
                    g_cmd[5]
                );


            uint32_t c2 =
                g_cmd[6]
                &
                0xFFFFFFu;


            int x2 =
                (coord_x(g_cmd[7]) + g_offset_x);

            int y2 =
                (coord_y(g_cmd[7]) + g_offset_y);

            int u2 =
                tex_u(g_cmd[8]);

            int v2 =
                tex_v(g_cmd[8]);


            set_primitive_state(
                opcode
            );


            sw_draw_shaded_textured_triangle(
                x0,
                y0,
                u0,
                v0,
                c0,

                x1,
                y1,
                u1,
                v1,
                c1,

                x2,
                y2,
                u2,
                v2,
                c2,

                clut_x(clut),
                clut_y(clut),

                g_texpage,
                raw
            );


            if (quad)
            {
                uint32_t c3 =
                    g_cmd[9]
                    &
                    0xFFFFFFu;


                int x3 =
                    (coord_x(g_cmd[10]) + g_offset_x);

                int y3 =
                    (coord_y(g_cmd[10]) + g_offset_y);

                int u3 =
                    tex_u(g_cmd[11]);

                int v3 =
                    tex_v(g_cmd[11]);


                sw_draw_shaded_textured_triangle(
                    x1,
                    y1,
                    u1,
                    v1,
                    c1,

                    x2,
                    y2,
                    u2,
                    v2,
                    c2,

                    x3,
                    y3,
                    u3,
                    v3,
                    c3,

                    clut_x(clut),
                    clut_y(clut),

                    g_texpage,
                    raw
                );
            }


            g_has_frame =
                1;


            return;
        }
    }


    /*
     * ========================================================
     * Mono line
     * ========================================================
     */

    if (
        opcode >= 0x40
        &&
        opcode <= 0x47
    )
    {
        set_primitive_state(
            opcode
        );


        sw_draw_line(
            (coord_x(g_cmd[1]) + g_offset_x),
            (coord_y(g_cmd[1]) + g_offset_y),

            (coord_x(g_cmd[2]) + g_offset_x),
            (coord_y(g_cmd[2]) + g_offset_y),

            rgb24_to_555(
                g_cmd[0]
            )
        );


        g_has_frame =
            1;


        return;
    }


    /*
     * Mono polyline :
     *
     * on dessine le premier segment puis on consomme
     * la suite jusqu'au marqueur de fin.
     */
    if (
        opcode >= 0x48
        &&
        opcode <= 0x4F
    )
    {
        set_primitive_state(
            opcode
        );


        sw_draw_line(
            (coord_x(g_cmd[1]) + g_offset_x),
            (coord_y(g_cmd[1]) + g_offset_y),

            (coord_x(g_cmd[2]) + g_offset_x),
            (coord_y(g_cmd[2]) + g_offset_y),

            rgb24_to_555(
                g_cmd[0]
            )
        );


        g_state =
            FM_GPU_POLYLINE_MONO_SKIP;


        g_has_frame =
            1;


        return;
    }


    /*
     * ========================================================
     * Gouraud line
     * ========================================================
     */

    if (
        opcode >= 0x50
        &&
        opcode <= 0x57
    )
    {
        set_primitive_state(
            opcode
        );


        sw_draw_shaded_line(
            (coord_x(g_cmd[1]) + g_offset_x),
            (coord_y(g_cmd[1]) + g_offset_y),
            rgb24_to_555(g_cmd[0]),

            (coord_x(g_cmd[3]) + g_offset_x),
            (coord_y(g_cmd[3]) + g_offset_y),
            rgb24_to_555(g_cmd[2])
        );


        g_has_frame =
            1;


        return;
    }


    if (
        opcode >= 0x58
        &&
        opcode <= 0x5F
    )
    {
        set_primitive_state(
            opcode
        );


        sw_draw_shaded_line(
            (coord_x(g_cmd[1]) + g_offset_x),
            (coord_y(g_cmd[1]) + g_offset_y),
            rgb24_to_555(g_cmd[0]),

            (coord_x(g_cmd[3]) + g_offset_x),
            (coord_y(g_cmd[3]) + g_offset_y),
            rgb24_to_555(g_cmd[2])
        );


        g_state =
            FM_GPU_POLYLINE_SHADED_SKIP;


        g_has_frame =
            1;


        return;
    }


    /*
     * ========================================================
     * Rectangle / Sprite
     * ========================================================
     */

    if (
        opcode >= 0x60
        &&
        opcode <= 0x7F
    )
    {
        int textured =
            (
                opcode
                &
                0x04
            )
            !=
            0;


        int raw =
            (
                opcode
                &
                0x01
            )
            !=
            0;


        unsigned size_type =
            (
                opcode
                >>
                3
            )
            &
            3u;


        int x =
            (coord_x(g_cmd[1]) + g_offset_x);

        int y =
            (coord_y(g_cmd[1]) + g_offset_y);


        int w;
        int h;


        if (size_type == 0)
        {
            uint32_t size_word =
                textured
                    ? g_cmd[3]
                    : g_cmd[2];


            w =
                size_word
                &
                0xFFFFu;


            h =
                (
                    size_word
                    >>
                    16
                )
                &
                0xFFFFu;
        }
        else if (size_type == 1)
        {
            w = 1;
            h = 1;
        }
        else if (size_type == 2)
        {
            w = 8;
            h = 8;
        }
        else
        {
            w = 16;
            h = 16;
        }


        /*
         * B38 : conserver le dernier rectangle/sprite suffisamment gros
         * pour expliquer un bloc visuel important a l'ecran.
         */
        if (w >= 24 && h >= 24)
        {
            ++g_b38_bigrect_count;
            g_b38_bigrect_opcode = opcode;
            g_b38_bigrect_textured = textured ? 1u : 0u;
            g_b38_bigrect_raw = raw ? 1u : 0u;
            g_b38_bigrect_x = x;
            g_b38_bigrect_y = y;
            g_b38_bigrect_w = w;
            g_b38_bigrect_h = h;
            g_b38_bigrect_texpage = g_texpage;
            g_b38_bigrect_texwindow = g_texture_window;

            g_b38_bigrect_cmd[0] = g_cmd[0];
            g_b38_bigrect_cmd[1] = g_cmd[1];
            g_b38_bigrect_cmd[2] = g_cmd[2];
            g_b38_bigrect_cmd[3] = g_cmd[3];

            if (textured)
            {
                uint16_t b38_clut = packet_clut(g_cmd[2]);
                g_b38_bigrect_u = tex_u(g_cmd[2]);
                g_b38_bigrect_v = tex_v(g_cmd[2]);
                g_b38_bigrect_clut_x = clut_x(b38_clut);
                g_b38_bigrect_clut_y = clut_y(b38_clut);
            }
            else
            {
                g_b38_bigrect_u = 0;
                g_b38_bigrect_v = 0;
                g_b38_bigrect_clut_x = 0;
                g_b38_bigrect_clut_y = 0;
            }
        }

        set_primitive_state(
            opcode
        );


        if (!textured)
        {
            sw_draw_flat_rect(
                x,
                y,
                w,
                h,
                rgb24_to_555(
                    g_cmd[0]
                )
            );
        }
        else
        {
            int u =
                tex_u(g_cmd[2]);

            int v =
                tex_v(g_cmd[2]);


            uint16_t clut =
                packet_clut(
                    g_cmd[2]
                );


            set_texture_modulation(
                g_cmd[0],
                raw
            );


            if (
                !b124_try_textured_rect(
                    opcode,
                    x,
                    y,
                    w,
                    h,
                    u,
                    v,
                    clut_x(clut),
                    clut_y(clut),
                    g_texpage,
                    g_cmd[0],
                    raw
                )
            )
            {
                sw_draw_textured_rect(
                    x,
                    y,
                    w,
                    h,

                    u,
                    v,

                    clut_x(clut),
                    clut_y(clut),

                    g_texpage
                );
            }
        }


        g_has_frame =
            1;


        return;
    }


    /*
     * ========================================================
     * VRAM -> VRAM
     * ========================================================
     */

    if (
        opcode >= 0x80
        &&
        opcode <= 0x9F
    )
    {
        int sx =
            g_cmd[1]
            &
            0x3FFu;


        int sy =
            (
                g_cmd[1]
                >>
                16
            )
            &
            0x1FFu;


        int dx =
            g_cmd[2]
            &
            0x3FFu;


        int dy =
            (
                g_cmd[2]
                >>
                16
            )
            &
            0x1FFu;


        int w =
            g_cmd[3]
            &
            0x3FFu;


        int h =
            (
                g_cmd[3]
                >>
                16
            )
            &
            0x1FFu;


        sw_copy_rect(
            sx,
            sy,
            dx,
            dy,
            w,
            h
        );


        g_has_frame =
            1;


        return;
    }


    /*
     * ========================================================
     * CPU -> VRAM
     * ========================================================
     */

    if (
        opcode >= 0xA0
        &&
        opcode <= 0xBF
    )
    {
        g_upload_x =
            g_cmd[1]
            &
            0x3FFu;


        g_upload_y =
            (
                g_cmd[1]
                >>
                16
            )
            &
            0x1FFu;


        g_upload_w =
            g_cmd[2]
            &
            0xFFFFu;


        g_upload_h =
            (
                g_cmd[2]
                >>
                16
            )
            &
            0xFFFFu;


        if (g_upload_w == 0)
        {
            g_upload_w =
                0x10000u;
        }


        if (g_upload_h == 0)
        {
            g_upload_h =
                0x10000u;
        }


        g_upload_pixels =
            g_upload_w
            *
            g_upload_h;


        g_upload_index =
            0;


        g_state =
            FM_GPU_VRAM_WRITE;


        return;
    }


    /*
     * ========================================================
     * Drawing environment
     * ========================================================
     */

    if (opcode == 0xE1)
    {
        g_texpage =
            g_cmd[0]
            &
            0x7FFu;


        return;
    }


    if (opcode == 0xE2)
    {
        g_texture_window =
            g_cmd[0]
            &
            0x000FFFFFu;

        sw_set_texture_window(
            g_cmd[0]
        );


        return;
    }


    if (opcode == 0xE3)
    {
        ++g_b100_e3_count;
        g_b100_last_e3 = g_cmd[0];

        g_draw_x1 =
            g_cmd[0]
            &
            0x3FFu;


        g_draw_y1 =
            (
                g_cmd[0]
                >>
                10
            )
            &
            0x1FFu;


        sw_set_draw_area(
            g_draw_x1,
            g_draw_y1,
            g_draw_x2,
            g_draw_y2
        );


        return;
    }


    if (opcode == 0xE4)
    {
        ++g_b100_e4_count;
        g_b100_last_e4 = g_cmd[0];

        g_draw_x2 =
            g_cmd[0]
            &
            0x3FFu;


        g_draw_y2 =
            (
                g_cmd[0]
                >>
                10
            )
            &
            0x1FFu;


        sw_set_draw_area(
            g_draw_x1,
            g_draw_y1,
            g_draw_x2,
            g_draw_y2
        );


        return;
    }


    if (opcode == 0xE5)
    {
        ++g_b100_e5_count;
        g_b100_last_e5 = g_cmd[0];

        g_offset_x =
            sign11(
                g_cmd[0]
            );


        g_offset_y =
            sign11(
                g_cmd[0]
                >>
                11
            );


        sw_set_draw_offset(
            g_offset_x,
            g_offset_y
        );


        return;
    }


    if (opcode == 0xE6)
    {
        g_mask_set =
            (
                g_cmd[0]
                &
                1u
            )
            !=
            0;


        g_mask_check =
            (
                g_cmd[0]
                &
                2u
            )
            !=
            0;


        sw_set_mask_bits(
            g_mask_set,
            g_mask_check
        );


        return;
    }
}


/*
 * ============================================================
 * Init
 * ============================================================
 */

void fm_gpu_init(
    uint16_t *vram
)
{
    g_vram =
        vram;


    g_state =
        FM_GPU_IDLE;


    g_cmd_have =
        0;


    g_cmd_need =
        0;


    g_gp0_count =
        0;


    g_packet_total =
        0;

    g_packet_nop =
        0;

    g_packet_fill =
        0;

    g_packet_draw =
        0;

    g_packet_copy =
        0;

    g_packet_upload =
        0;

    g_packet_readback =
        0;

    g_packet_env =
        0;

    g_packet_other =
        0;

    g_upload_data_words =
        0;

    memset(
        g_b122_opcode_ticks,
        0,
        sizeof(g_b122_opcode_ticks)
    );

    memset(
        g_b122_opcode_calls,
        0,
        sizeof(g_b122_opcode_calls)
    );

    memset(
        g_b122_opcode_max_ticks,
        0,
        sizeof(g_b122_opcode_max_ticks)
    );

    g_b122_exec_ticks =
        0u;

    g_b122_upload_ticks =
        0u;

    g_b122_upload_words =
        0u;

    g_b124_rect_hits =
        0u;

    g_b124_rect_fallbacks =
        0u;

    g_b124_rect_pixels =
        0u;

    g_b124_rect_texels =
        0u;

    g_b125_texquad_hits =
        0u;

    g_b125_gouraud_hits =
        0u;

    g_b125_fallbacks =
        0u;

    g_b125_pixels =
        0u;

    g_b126_seen_2c =
        0u;

    g_b126_seen_2e =
        0u;

    g_b126_seen_3a =
        0u;

    g_b126_try_t =
        0u;

    g_b126_try_g =
        0u;

    g_b126_reject_mask =
        0u;

    g_b129_fill_hits =
        0u;

    g_b129_fill_fallbacks =
        0u;

    g_b129_fill_pixels =
        0u;

    g_b129_fill_zero_pixels =
        0u;

    g_b129_fill_max_pixels =
        0u;

    g_fill_suppressed = 0;
    g_last_fill_x = 0;
    g_last_fill_y = 0;
    g_last_fill_w = 0;
    g_last_fill_h = 0;
    g_last_fill_color = 0;

    memset(
        g_b29_draw_trace,
        0,
        sizeof(g_b29_draw_trace)
    );
    g_b29_draw_trace_head = 0u;
    g_b29_draw_trace_count = 0u;

    g_b38_bigrect_count = 0u;
    g_b38_bigrect_opcode = 0u;
    g_b38_bigrect_textured = 0u;
    g_b38_bigrect_raw = 0u;
    g_b38_bigrect_x = 0;
    g_b38_bigrect_y = 0;
    g_b38_bigrect_w = 0;
    g_b38_bigrect_h = 0;
    g_b38_bigrect_u = 0;
    g_b38_bigrect_v = 0;
    g_b38_bigrect_clut_x = 0;
    g_b38_bigrect_clut_y = 0;
    g_b38_bigrect_texpage = 0u;
    g_b38_bigrect_texwindow = 0u;
    memset(g_b38_bigrect_cmd, 0, sizeof(g_b38_bigrect_cmd));

    g_b44_serial = 0u;
    g_b44_hits_fill = 0u;
    g_b44_hits_draw = 0u;
    g_b44_hits_copy = 0u;
    g_b44_hits_upload = 0u;
    g_b44_last_serial = 0u;
    g_b44_last_type = 0u;
    g_b44_last_opcode = 0u;
    g_b44_last_x = 0;
    g_b44_last_y = 0;
    g_b44_last_w = 0;
    g_b44_last_h = 0;
    memset(g_b44_last_cmd, 0, sizeof(g_b44_last_cmd));

    g_b46_cmd_serial = 0u;
    g_b46_last_e1_serial = 0u;
    g_b46_last_e1_value = 0u;
    g_b46_last_fill_serial = 0u;
    g_b46_sprite_hits = 0u;
    g_b46_sprite_serial = 0u;
    g_b46_sprite_e1_age = 0xFFFFFFFFu;
    g_b46_sprite_fill_age = 0xFFFFFFFFu;
    g_b46_sprite_e1 = 0u;
    g_b46_sprite_texpage = 0u;
    g_b46_sprite_off_x = 0;
    g_b46_sprite_off_y = 0;
    memset(g_b46_sprite_cmd, 0, sizeof(g_b46_sprite_cmd));


    g_has_frame =
        0;


    g_texpage =
        0;

    g_texture_window =
        0;


    g_draw_x1 =
        0;


    g_draw_y1 =
        0;


    g_draw_x2 =
        1023;


    g_draw_y2 =
        511;


    g_offset_x =
        0;


    g_offset_y =
        0;


    g_display_x =
        0;


    g_display_y =
        0;


    g_display_disabled =
        1;

    g_display_mode = 0u;
    g_b104_gp1_08_count = 0u;

    g_b100_e3_count = 0u;
    g_b100_e4_count = 0u;
    g_b100_e5_count = 0u;
    g_b100_gp1_05_count = 0u;
    g_b100_last_e3 = 0u;
    g_b100_last_e4 = 0u;
    g_b100_last_e5 = 0u;
    g_b100_last_gp1_05 = 0u;
    g_b101_offset_draw_packets = 0u;


    g_mask_set =
        0;


    g_mask_check =
        0;


    sw_set_draw_area(
        0,
        0,
        1023,
        511
    );


    sw_set_draw_offset(
        0,
        0
    );


    sw_set_mask_bits(
        0,
        0
    );


    sw_set_texture_window(
        0
    );
}


/*
 * ============================================================
 * GP0
 * ============================================================
 */

void fm_gpu_gp0_write(
    uint32_t value
)
{
    ++g_gp0_count;


    /*
     * --------------------------------------------------------
     * CPU -> VRAM pixel data
     * --------------------------------------------------------
     */

    if (g_state == FM_GPU_VRAM_WRITE)
    {
        uint64_t b122_upload_start =
            svcGetSystemTick();

        ++g_upload_data_words;


        for (
            unsigned half = 0;
            half < 2;
            ++half
        )
        {
            if (
                g_upload_index
                >=
                g_upload_pixels
            )
            {
                break;
            }


            uint16_t pixel =
                half == 0
                    ? (uint16_t)value
                    : (uint16_t)(
                        value >> 16
                    );


            unsigned px =
                g_upload_index
                %
                g_upload_w;


            unsigned py =
                g_upload_index
                /
                g_upload_w;


            unsigned vx =
                (
                    g_upload_x
                    +
                    px
                )
                &
                1023u;


            unsigned vy =
                (
                    g_upload_y
                    +
                    py
                )
                &
                511u;


            /*
             * B27: garder la VRAM possedee par fm_gpu.c comme
             * source de verite. B26 prouvait que le parser A0h
             * recevait bien les 51200 mots mais que le buffer
             * inspecte par fm_gpu_debug_stats restait a zero.
             *
             * On ecrit donc explicitement dans g_vram, puis on
             * appelle aussi le renderer pour conserver son suivi
             * interne/dirty-state.
             */
            if (g_vram)
            {
                g_vram[
                    vy * 1024u
                    +
                    vx
                ] =
                    pixel;
            }


            sw_vram_write(
                vx,
                vy,
                pixel
            );


            ++g_upload_index;
        }


        if (
            g_upload_index
            >=
            g_upload_pixels
        )
        {
            g_state =
                FM_GPU_IDLE;


            g_has_frame =
                1;
        }

        g_b122_upload_ticks +=
            svcGetSystemTick()
            -
            b122_upload_start;

        ++g_b122_upload_words;

        return;
    }


    /*
     * --------------------------------------------------------
     * Polyline skip mode
     * --------------------------------------------------------
     */

    if (
        g_state == FM_GPU_POLYLINE_MONO_SKIP
        ||
        g_state == FM_GPU_POLYLINE_SHADED_SKIP
    )
    {
        if (
            (
                value
                &
                0xF000F000u
            )
            ==
            0x50005000u
        )
        {
            g_state =
                FM_GPU_IDLE;
        }


        return;
    }


    /*
     * --------------------------------------------------------
     * Nouvelle commande
     * --------------------------------------------------------
     */

    if (g_cmd_have == 0)
    {
        uint8_t opcode =
            (
                value
                >>
                24
            )
            &
            0xFFu;


        g_cmd_need =
            command_words(
                opcode
            );
    }


    if (
        g_cmd_have
        <
        16
    )
    {
        g_cmd[
            g_cmd_have
        ] =
            value;
    }


    ++g_cmd_have;


    if (
        g_cmd_have
        >=
        g_cmd_need
    )
    {
        uint8_t b122_opcode =
            (uint8_t)(g_cmd[0] >> 24);

        uint64_t b122_start =
            svcGetSystemTick();

        execute_command();

        b122_record_opcode(
            b122_opcode,
            svcGetSystemTick() - b122_start
        );


        g_cmd_have =
            0;


        g_cmd_need =
            0;
    }
}


/*
 * ============================================================
 * GP1
 * ============================================================
 */

void fm_gpu_gp1_write(
    uint32_t value
)
{
    uint8_t command =
        (
            value
            >>
            24
        )
        &
        0x3Fu;


    switch (command)
    {
        /*
         * Reset GPU
         */
        case 0x00:
        {
            g_state =
                FM_GPU_IDLE;


            g_cmd_have =
                0;


            g_cmd_need =
                0;


            g_display_x =
                0;


            g_display_y =
                0;


            g_display_disabled =
                1;

            g_display_mode =
                0u;


            g_texpage =
                0;


            sw_set_draw_area(
                0,
                0,
                1023,
                511
            );


            sw_set_draw_offset(
                0,
                0
            );


            break;
        }


        /*
         * Reset GP0 command buffer
         */
        case 0x01:
        {
            g_state =
                FM_GPU_IDLE;


            g_cmd_have =
                0;


            g_cmd_need =
                0;


            break;
        }


        /*
         * Display enable / disable
         */
        case 0x03:
        {
            g_display_disabled =
                value
                &
                1u;


            break;
        }


        /*
         * DMA direction.
         *
         * Pas besoin de stockage particulier pour notre HLE.
         */
        case 0x04:
        {
            break;
        }


        /*
         * Display VRAM start
         */
        case 0x05:
        {
            ++g_b100_gp1_05_count;
            g_b100_last_gp1_05 = value;

            g_display_x =
                value
                &
                0x3FFu;


            g_display_y =
                (
                    value
                    >>
                    10
                )
                &
                0x1FFu;


            break;
        }


        /*
         * Display mode.
         * bit4 = 24-bit direct display.
         */
        case 0x08:
        {
            g_display_mode =
                value
                &
                0xFFu;

            ++g_b104_gp1_08_count;
            break;
        }


        default:
        {
            break;
        }
    }
}


/*
 * ============================================================
 * Status
 * ============================================================
 */

uint32_t fm_gpu_display_mode_raw(void)
{
    return g_display_mode;
}


int fm_gpu_display_24bit(void)
{
    return
        (g_display_mode & 0x10u) != 0u;
}


unsigned fm_gpu_display_width(void)
{
    if ((g_display_mode & 0x40u) != 0u)
    {
        return 368u;
    }

    switch (g_display_mode & 3u)
    {
        case 0u: return 256u;
        case 1u: return 320u;
        case 2u: return 512u;
        default: return 640u;
    }
}


uint32_t fm_gpu_status(void)
{
    /*
     * GPU prêt à recevoir commandes et DMA.
     *
     * On expose volontairement un statut "idle/ready"
     * pour éviter de bloquer les boucles GPU_sync pendant
     * le bring-up.
     */
    uint32_t status =
        0x1C802000u;


    /*
     * GP1(08) -> GPUSTAT display-mode fields.
     */
    status &= ~(
        (1u << 16)
        | (3u << 17)
        | (1u << 19)
        | (1u << 20)
        | (1u << 21)
        | (1u << 22)
    );

    if ((g_display_mode & 0x40u) != 0u)
    {
        status |= 1u << 16;
    }

    status |= (g_display_mode & 3u) << 17;

    if ((g_display_mode & 0x04u) != 0u) status |= 1u << 19;
    if ((g_display_mode & 0x08u) != 0u) status |= 1u << 20;
    if ((g_display_mode & 0x10u) != 0u) status |= 1u << 21;
    if ((g_display_mode & 0x20u) != 0u) status |= 1u << 22;

    if (g_display_disabled)
    {
        status |=
            1u << 23;
    }


    return status;
}


uint64_t fm_gpu_gp0_count(void)
{
    return
        g_gp0_count;
}


int fm_gpu_has_frame(void)
{
    return
        g_has_frame;
}


unsigned fm_gpu_display_x(void)
{
    unsigned x =
        g_display_x;


    /*
     * Notre present 3DS lit actuellement 320 pixels.
     */
    if (x > 704)
    {
        x =
            704;
    }


    return x;
}


unsigned fm_gpu_display_y(void)
{
    unsigned y =
        g_display_y;


    /*
     * fm_present_rgb555 peut lire jusqu'à 256 lignes.
     */
    if (y > 256)
    {
        y =
            256;
    }


    return y;
}


void fm_gpu_b122_rank(
    unsigned rank,
    FMGpuOpcodePerf *out
)
{
    if (!out)
    {
        return;
    }

    memset(out, 0, sizeof(*out));

    uint8_t selected[256] = {0};

    for (unsigned pick = 0u; pick <= rank; ++pick)
    {
        int best = -1;
        uint64_t best_ticks = 0u;

        for (unsigned op = 0u; op < 256u; ++op)
        {
            if (
                selected[op]
                ||
                g_b122_opcode_calls[op] == 0u
            )
            {
                continue;
            }

            if (
                best < 0
                ||
                g_b122_opcode_ticks[op] > best_ticks
            )
            {
                best = (int)op;
                best_ticks = g_b122_opcode_ticks[op];
            }
        }

        if (best < 0)
        {
            return;
        }

        selected[best] = 1u;

        if (pick == rank)
        {
            out->opcode = (uint8_t)best;
            out->calls = g_b122_opcode_calls[best];
            out->total_us =
                b122_ticks_to_us(
                    g_b122_opcode_ticks[best]
                );
            out->max_us =
                (uint32_t)b122_ticks_to_us(
                    g_b122_opcode_max_ticks[best]
                );
            return;
        }
    }
}


void fm_gpu_b122_totals(
    uint64_t *exec_us,
    uint64_t *upload_us,
    uint64_t *upload_words
)
{
    if (exec_us)
    {
        *exec_us =
            b122_ticks_to_us(
                g_b122_exec_ticks
            );
    }

    if (upload_us)
    {
        *upload_us =
            b122_ticks_to_us(
                g_b122_upload_ticks
            );
    }

    if (upload_words)
    {
        *upload_words =
            g_b122_upload_words;
    }
}


/*
 * ============================================================
 * BIOS helpers
 * ============================================================
 */

static void bios_mem_to_vram(
    CPUState *cpu
)
{
    uint32_t x =
        cpu->gpr[4];


    uint32_t y =
        cpu->gpr[5];


    uint32_t w =
        cpu->gpr[6];


    uint32_t h =
        cpu->gpr[7];


    uint32_t source =
        cpu->read_word(
            cpu->gpr[29]
            +
            16u
        );


    fm_gpu_gp0_write(
        0xA0000000u
    );


    fm_gpu_gp0_write(
        (
            (y & 0xFFFFu)
            <<
            16
        )
        |
        (x & 0xFFFFu)
    );


    fm_gpu_gp0_write(
        (
            (h & 0xFFFFu)
            <<
            16
        )
        |
        (w & 0xFFFFu)
    );


    uint32_t words =
        (
            w
            *
            h
            +
            1u
        )
        /
        2u;


    for (
        uint32_t i = 0;
        i < words;
        ++i
    )
    {
        fm_gpu_gp0_write(
            cpu->read_word(
                source
                +
                i * 4u
            )
        );
    }
}


static void bios_send_buffer(
    CPUState *cpu
)
{
    uint32_t addr =
        cpu->gpr[4];


    uint32_t count =
        cpu->gpr[5];


    for (
        uint32_t i = 0;
        i < count;
        ++i
    )
    {
        fm_gpu_gp0_write(
            cpu->read_word(
                addr
                +
                i * 4u
            )
        );
    }
}


static void bios_send_linked_list(
    CPUState *cpu
)
{
    uint32_t addr =
        cpu->gpr[4]
        &
        0x00FFFFFCu;


    /*
     * Protection en cas de liste corrompue.
     */
    for (
        unsigned node_guard = 0;
        node_guard < 65536;
        ++node_guard
    )
    {
        uint32_t header =
            cpu->read_word(
                addr
            );


        unsigned words =
            header
            >>
            24;


        uint32_t next =
            header
            &
            0x00FFFFFFu;


        uint32_t data =
            addr
            +
            4u;


        for (
            unsigned i = 0;
            i < words;
            ++i
        )
        {
            fm_gpu_gp0_write(
                cpu->read_word(
                    data
                    +
                    i * 4u
                )
            );
        }


        if (
            next
            ==
            0x00FFFFFFu
        )
        {
            break;
        }


        addr =
            next
            &
            0x00FFFFFCu;
    }
}


/*
 * ============================================================
 * Retour BIOS GPU vers le code guest
 * ============================================================
 *
 * Tous les appels BIOS A0:46..4E passent par le vecteur A0.
 * Une fois le service HLE terminé, il faut impérativement
 * replacer le PC guest sur $ra. Sans cela le main ré-appelle
 * le même service A0 à chaque handoff (boucle infinie).
 */
static void bios_return(
    CPUState *cpu
)
{
    cpu->pc =
        cpu->gpr[31];

    cpu->gpr[0] =
        0;
}



uint32_t fm_gpu_b101_offset_draw_packets(void)
{
    return g_b101_offset_draw_packets;
}


/*
 * B100 - getter sans scan VRAM.
 */
void fm_gpu_b100_env_get(
    int *off_x, int *off_y,
    int *area_x1, int *area_y1,
    int *area_x2, int *area_y2,
    uint32_t *e3_count,
    uint32_t *e4_count,
    uint32_t *e5_count,
    uint32_t *gp1_05_count,
    uint32_t *last_e3,
    uint32_t *last_e4,
    uint32_t *last_e5,
    uint32_t *last_gp1_05
)
{
    if (off_x) *off_x = g_offset_x;
    if (off_y) *off_y = g_offset_y;

    if (area_x1) *area_x1 = g_draw_x1;
    if (area_y1) *area_y1 = g_draw_y1;
    if (area_x2) *area_x2 = g_draw_x2;
    if (area_y2) *area_y2 = g_draw_y2;

    if (e3_count) *e3_count = g_b100_e3_count;
    if (e4_count) *e4_count = g_b100_e4_count;
    if (e5_count) *e5_count = g_b100_e5_count;
    if (gp1_05_count) *gp1_05_count = g_b100_gp1_05_count;

    if (last_e3) *last_e3 = g_b100_last_e3;
    if (last_e4) *last_e4 = g_b100_last_e4;
    if (last_e5) *last_e5 = g_b100_last_e5;
    if (last_gp1_05) *last_gp1_05 = g_b100_last_gp1_05;
}


/*
 * ============================================================
 * Diagnostic VRAM
 * ============================================================
 */

static uint32_t fm_gpu_count_nonzero_rect(
    unsigned start_x,
    unsigned start_y,
    unsigned width,
    unsigned height
)
{
    if (!g_vram)
    {
        return 0;
    }


    uint32_t count =
        0;


    for (
        unsigned y = 0;
        y < height;
        ++y
    )
    {
        unsigned sy =
            (
                start_y
                +
                y
            )
            &
            511u;


        for (
            unsigned x = 0;
            x < width;
            ++x
        )
        {
            unsigned sx =
                (
                    start_x
                    +
                    x
                )
                &
                1023u;


            uint16_t pixel =
                g_vram[
                    sy * 1024u
                    +
                    sx
                ];


            /*
             * Bit15 = mask bit.
             * On ne le compte pas comme couleur visible.
             */
            if (
                pixel
                &
                0x7FFFu
            )
            {
                ++count;
            }
        }
    }


    return count;
}


void fm_gpu_b127_perf_snapshot(
    FMGpuDebugStats *out
)
{
    if (!out)
    {
        return;
    }

    /*
     * Do not memset the whole structure here. main.c already owns the
     * snapshot and may have filled cheap fields such as gp0_words.
     * Only copy counters needed by B124..B127.
     */
    out->b124_rect_hits =
        g_b124_rect_hits;

    out->b124_rect_fallbacks =
        g_b124_rect_fallbacks;

    out->b124_rect_pixels =
        g_b124_rect_pixels;

    out->b124_rect_texels =
        g_b124_rect_texels;

    out->b125_texquad_hits =
        g_b125_texquad_hits;

    out->b125_gouraud_hits =
        g_b125_gouraud_hits;

    out->b125_fallbacks =
        g_b125_fallbacks;

    out->b125_pixels =
        g_b125_pixels;

    out->b126_seen_2c =
        g_b126_seen_2c;

    out->b126_seen_2e =
        g_b126_seen_2e;

    out->b126_seen_3a =
        g_b126_seen_3a;

    out->b126_try_t =
        g_b126_try_t;

    out->b126_try_g =
        g_b126_try_g;

    out->b126_reject_mask =
        g_b126_reject_mask;

    out->b126_scale =
        sw_renderer_scale();

    out->b126_wide =
        sw_wide_width();

    out->b126_filter =
        sw_texture_filter();

    out->b129_fill_hits =
        g_b129_fill_hits;

    out->b129_fill_fallbacks =
        g_b129_fill_fallbacks;

    out->b129_fill_pixels =
        g_b129_fill_pixels;

    out->b129_fill_zero_pixels =
        g_b129_fill_zero_pixels;

    out->b129_fill_max_pixels =
        g_b129_fill_max_pixels;
}


void fm_gpu_debug_stats(
    FMGpuDebugStats *out
)
{
    if (!out)
    {
        return;
    }


    memset(
        out,
        0,
        sizeof(*out)
    );


    out->gp0_words =
        g_gp0_count;


    out->packets_total =
        g_packet_total;

    out->packets_nop =
        g_packet_nop;

    out->packets_fill =
        g_packet_fill;

    out->packets_draw =
        g_packet_draw;

    out->packets_copy =
        g_packet_copy;

    out->packets_upload =
        g_packet_upload;

    out->packets_readback =
        g_packet_readback;

    out->packets_env =
        g_packet_env;

    out->packets_other =
        g_packet_other;

    out->upload_data_words =
        g_upload_data_words;


    out->draw_x1 =
        g_draw_x1;

    out->draw_y1 =
        g_draw_y1;

    out->draw_x2 =
        g_draw_x2;

    out->draw_y2 =
        g_draw_y2;


    out->offset_x =
        g_offset_x;

    out->offset_y =
        g_offset_y;


    out->display_x =
        g_display_x;

    out->display_y =
        g_display_y;

    out->display_disabled =
        g_display_disabled;

    out->b124_rect_hits =
        g_b124_rect_hits;

    out->b124_rect_fallbacks =
        g_b124_rect_fallbacks;

    out->b124_rect_pixels =
        g_b124_rect_pixels;

    out->b124_rect_texels =
        g_b124_rect_texels;

    out->b125_texquad_hits =
        g_b125_texquad_hits;

    out->b125_gouraud_hits =
        g_b125_gouraud_hits;

    out->b125_fallbacks =
        g_b125_fallbacks;

    out->b125_pixels =
        g_b125_pixels;

    out->b126_seen_2c =
        g_b126_seen_2c;

    out->b126_seen_2e =
        g_b126_seen_2e;

    out->b126_seen_3a =
        g_b126_seen_3a;

    out->b126_try_t =
        g_b126_try_t;

    out->b126_try_g =
        g_b126_try_g;

    out->b126_reject_mask =
        g_b126_reject_mask;

    out->b126_scale =
        sw_renderer_scale();

    out->b126_wide =
        sw_wide_width();

    out->b126_filter =
        sw_texture_filter();


    /*
     * Les trois fenêtres qui nous intéressent pour Forbidden
     * Memories. Le jeu double-bufferise notamment x=0 / x=320.
     */
    out->nonzero_page0 =
        fm_gpu_count_nonzero_rect(
            0,
            0,
            320,
            256
        );


    out->nonzero_page320 =
        fm_gpu_count_nonzero_rect(
            320,
            0,
            320,
            256
        );


    out->nonzero_display =
        fm_gpu_count_nonzero_rect(
            g_display_x,
            g_display_y,
            320,
            256
        );


    out->nonzero_vram =
        fm_gpu_count_nonzero_rect(
            0,
            0,
            1024,
            512
        );
}


uint32_t fm_gpu_b126_build_tag(void)
{
    return 126u;
}


/*
 * ============================================================
 * BIOS A0 GPU family
 * ============================================================
 */

int fm_gpu_bios_call(
    CPUState *cpu,
    uint32_t fn
)
{
    if (!cpu)
    {
        return 0;
    }


    switch (
        fn
        &
        0xFFu
    )
    {
        /*
         * A0:46 GPU_dw
         */
        case 0x46:
        {
            bios_mem_to_vram(
                cpu
            );


            bios_return(
                cpu
            );


            return 1;
        }


        /*
         * A0:47 mem2vram
         */
        case 0x47:
        {
            bios_mem_to_vram(
                cpu
            );


            bios_return(
                cpu
            );


            return 1;
        }


        /*
         * A0:48 SendGPU / GP1
         */
        case 0x48:
        {
            fm_gpu_gp1_write(
                cpu->gpr[4]
            );


            bios_return(
                cpu
            );


            return 1;
        }


        /*
         * A0:49 GPU_cw / GP0
         */
        case 0x49:
        {
            fm_gpu_gp0_write(
                cpu->gpr[4]
            );


            bios_return(
                cpu
            );


            return 1;
        }


        /*
         * A0:4A GPU_cwb(buffer, count)
         */
        case 0x4A:
        {
            bios_send_buffer(
                cpu
            );


            bios_return(
                cpu
            );


            return 1;
        }


        /*
         * A0:4B GPU_SendPackets(ordering_table)
         */
        case 0x4B:
        {
            /*
             * GPU DMA linked-list mode.
             */
            fm_gpu_gp1_write(
                0x04000002u
            );


            bios_send_linked_list(
                cpu
            );


            bios_return(
                cpu
            );


            return 1;
        }


        /*
         * A0:4D GetGPUStatus
         */
        case 0x4D:
        {
            cpu->gpr[2] =
                fm_gpu_status();


            bios_return(
                cpu
            );


            return 1;
        }


        /*
         * A0:4E GPU_sync
         */
        case 0x4E:
        {
            cpu->gpr[2] =
                0;


            bios_return(
                cpu
            );


            return 1;
        }


        default:
        {
            return 0;
        }
    }
}

/* ============================================================
 * B28 debug helpers (declared locally by main.c)
 * ============================================================ */
uint64_t fm_gpu_fill_suppressed_count(void)
{
    return g_fill_suppressed;
}

void fm_gpu_last_fill_info(
    int *x, int *y, int *w, int *h, uint16_t *color
)
{
    if (x) *x = g_last_fill_x;
    if (y) *y = g_last_fill_y;
    if (w) *w = g_last_fill_w;
    if (h) *h = g_last_fill_h;
    if (color) *color = g_last_fill_color;
}

/*
 * ============================================================
 * B29 public draw trace API
 * ============================================================
 */
unsigned fm_gpu_b29_draw_trace_count(void)
{
    return g_b29_draw_trace_count;
}

int fm_gpu_b29_draw_trace_get(
    unsigned back,
    uint8_t *opcode,
    unsigned *words,
    uint16_t *texpage,
    int *off_x,
    int *off_y,
    int *area_x1,
    int *area_y1,
    int *area_x2,
    int *area_y2,
    uint32_t out_cmd[8]
)
{
    if (back >= g_b29_draw_trace_count)
    {
        return 0;
    }

    unsigned index =
        (g_b29_draw_trace_head + 3u - 1u - back) % 3u;

    const FMB29DrawTrace *trace =
        &g_b29_draw_trace[index];

    if (opcode) *opcode = trace->opcode;
    if (words) *words = trace->words;
    if (texpage) *texpage = trace->texpage;
    if (off_x) *off_x = trace->off_x;
    if (off_y) *off_y = trace->off_y;
    if (area_x1) *area_x1 = trace->area_x1;
    if (area_y1) *area_y1 = trace->area_y1;
    if (area_x2) *area_x2 = trace->area_x2;
    if (area_y2) *area_y2 = trace->area_y2;

    if (out_cmd)
    {
        for (unsigned i = 0; i < 8u; ++i)
        {
            out_cmd[i] = trace->cmd[i];
        }
    }

    return 1;
}


/*
 * ============================================================
 * B38 public big-rectangle trace API
 * ============================================================
 */
int fm_gpu_b38_bigrect_get(
    uint32_t *count,
    uint8_t *opcode,
    int *textured,
    int *raw,
    int *x, int *y, int *w, int *h,
    int *u, int *v,
    int *clut_x_out, int *clut_y_out,
    uint16_t *texpage,
    uint32_t out_cmd[4]
)
{
    if (g_b38_bigrect_count == 0u)
    {
        return 0;
    }

    if (count) *count = g_b38_bigrect_count;
    if (opcode) *opcode = g_b38_bigrect_opcode;
    if (textured) *textured = g_b38_bigrect_textured;
    if (raw) *raw = g_b38_bigrect_raw;
    if (x) *x = g_b38_bigrect_x;
    if (y) *y = g_b38_bigrect_y;
    if (w) *w = g_b38_bigrect_w;
    if (h) *h = g_b38_bigrect_h;
    if (u) *u = g_b38_bigrect_u;
    if (v) *v = g_b38_bigrect_v;
    if (clut_x_out) *clut_x_out = g_b38_bigrect_clut_x;
    if (clut_y_out) *clut_y_out = g_b38_bigrect_clut_y;
    if (texpage) *texpage = g_b38_bigrect_texpage;

    if (out_cmd)
    {
        for (unsigned i = 0; i < 4u; ++i)
        {
            out_cmd[i] = g_b38_bigrect_cmd[i];
        }
    }

    return 1;
}

/*
 * ============================================================
 * B39 texture/CLUT probe
 * ============================================================
 *
 * Sonde la VRAM possedee par fm_gpu.c avec exactement les infos du
 * dernier gros sprite B38. Le but est de separer deux cas:
 *
 *   - texture/CLUT deja mauvaises dans la VRAM -> probleme upload/data
 *   - texture/CLUT variees mais sprite uni -> probleme sampler renderer
 */
static unsigned fm_b39_apply_texwin_u(unsigned u, uint32_t tw)
{
    unsigned mask = (tw >> 0) & 0x1Fu;
    unsigned off  = (tw >> 10) & 0x1Fu;

    unsigned mask8 = mask << 3;
    unsigned off8  = (off & mask) << 3;

    return ((u & 0xFFu) & ~mask8) | off8;
}

static unsigned fm_b39_apply_texwin_v(unsigned v, uint32_t tw)
{
    unsigned mask = (tw >> 5) & 0x1Fu;
    unsigned off  = (tw >> 15) & 0x1Fu;

    unsigned mask8 = mask << 3;
    unsigned off8  = (off & mask) << 3;

    return ((v & 0xFFu) & ~mask8) | off8;
}

int fm_gpu_b39_texture_probe_get(
    uint32_t *texwindow,
    int *depth,
    int *base_x,
    int *base_y,
    uint32_t *texel_count,
    uint32_t *index_nonzero,
    uint32_t *color_nonzero,
    uint32_t *unique_indices,
    uint16_t clut16[16],
    uint8_t sample_idx[8],
    uint16_t sample_col[8]
)
{
    if (
        !g_vram
        ||
        g_b38_bigrect_count == 0u
        ||
        !g_b38_bigrect_textured
    )
    {
        return 0;
    }

    uint16_t tp = g_b38_bigrect_texpage;
    unsigned dep = (tp >> 7) & 3u;
    unsigned bx = (tp & 0x0Fu) * 64u;
    unsigned by = (tp & 0x10u) ? 256u : 0u;
    uint32_t tw = g_b38_bigrect_texwindow;

    if (dep > 2u)
    {
        dep = 2u;
    }

    if (texwindow) *texwindow = tw;
    if (depth) *depth = (int)dep;
    if (base_x) *base_x = (int)bx;
    if (base_y) *base_y = (int)by;

    uint8_t seen[256];
    memset(seen, 0, sizeof(seen));

    uint32_t total = 0u;
    uint32_t idx_nz = 0u;
    uint32_t col_nz = 0u;
    uint32_t uniq = 0u;

    /* Palette 4bpp visible pour le diagnostic. */
    for (unsigned i = 0; i < 16u; ++i)
    {
        unsigned px = ((unsigned)g_b38_bigrect_clut_x + i) & 1023u;
        unsigned py = (unsigned)g_b38_bigrect_clut_y & 511u;
        if (clut16)
        {
            clut16[i] = g_vram[py * 1024u + px];
        }
    }

    for (int yy = 0; yy < g_b38_bigrect_h; ++yy)
    {
        for (int xx = 0; xx < g_b38_bigrect_w; ++xx)
        {
            unsigned u = fm_b39_apply_texwin_u(
                (unsigned)(g_b38_bigrect_u + xx),
                tw
            ) & 0xFFu;

            unsigned v = fm_b39_apply_texwin_v(
                (unsigned)(g_b38_bigrect_v + yy),
                tw
            ) & 0xFFu;

            uint8_t idx = 0u;
            uint16_t col = 0u;

            if (dep == 0u)
            {
                unsigned vx = (bx + (u >> 2)) & 1023u;
                unsigned vy = (by + v) & 511u;
                uint16_t word = g_vram[vy * 1024u + vx];
                idx = (uint8_t)((word >> ((u & 3u) * 4u)) & 0x0Fu);

                unsigned cx = ((unsigned)g_b38_bigrect_clut_x + idx) & 1023u;
                unsigned cy = (unsigned)g_b38_bigrect_clut_y & 511u;
                col = g_vram[cy * 1024u + cx];
            }
            else if (dep == 1u)
            {
                unsigned vx = (bx + (u >> 1)) & 1023u;
                unsigned vy = (by + v) & 511u;
                uint16_t word = g_vram[vy * 1024u + vx];
                idx = (uint8_t)((word >> ((u & 1u) * 8u)) & 0xFFu);

                unsigned cx = ((unsigned)g_b38_bigrect_clut_x + idx) & 1023u;
                unsigned cy = (unsigned)g_b38_bigrect_clut_y & 511u;
                col = g_vram[cy * 1024u + cx];
            }
            else
            {
                unsigned vx = (bx + u) & 1023u;
                unsigned vy = (by + v) & 511u;
                col = g_vram[vy * 1024u + vx];
                idx = (uint8_t)(col & 0xFFu);
            }

            if (!seen[idx])
            {
                seen[idx] = 1u;
                ++uniq;
            }

            if (idx != 0u) ++idx_nz;
            if ((col & 0x7FFFu) != 0u) ++col_nz;

            if (yy == 0 && xx < 8)
            {
                if (sample_idx) sample_idx[xx] = idx;
                if (sample_col) sample_col[xx] = col;
            }

            ++total;
        }
    }

    if (texel_count) *texel_count = total;
    if (index_nonzero) *index_nonzero = idx_nz;
    if (color_nonzero) *color_nonzero = col_nz;
    if (unique_indices) *unique_indices = uniq;

    return 1;
}


/*
 * ============================================================
 * B42 public video bring-up control
 * ============================================================
 */
void fm_gpu_b42_set_preserve_background_clears(int enabled)
{
    g_preserve_background_clears = enabled ? 1 : 0;
}

int fm_gpu_b42_get_preserve_background_clears(void)
{
    return g_preserve_background_clears;
}


/*
 * ============================================================
 * B44 public writer-watch API
 * ============================================================
 */
void fm_gpu_b44_watch_get(
    uint32_t *fill_hits,
    uint32_t *draw_hits,
    uint32_t *copy_hits,
    uint32_t *upload_hits,
    uint32_t *last_serial,
    uint8_t *last_type,
    uint8_t *last_opcode,
    int *x, int *y, int *w, int *h,
    uint32_t cmd[4]
)
{
    if (fill_hits) *fill_hits = g_b44_hits_fill;
    if (draw_hits) *draw_hits = g_b44_hits_draw;
    if (copy_hits) *copy_hits = g_b44_hits_copy;
    if (upload_hits) *upload_hits = g_b44_hits_upload;
    if (last_serial) *last_serial = g_b44_last_serial;
    if (last_type) *last_type = g_b44_last_type;
    if (last_opcode) *last_opcode = g_b44_last_opcode;
    if (x) *x = g_b44_last_x;
    if (y) *y = g_b44_last_y;
    if (w) *w = g_b44_last_w;
    if (h) *h = g_b44_last_h;

    if (cmd)
    {
        for (unsigned i = 0; i < 4u; ++i)
        {
            cmd[i] = g_b44_last_cmd[i];
        }
    }
}


int fm_gpu_b46_sprite_provenance_get(
    uint32_t *hits,
    uint32_t *serial,
    uint16_t *last_e1,
    uint32_t *e1_age,
    uint32_t *fill_age,
    uint16_t *texpage,
    int *off_x,
    int *off_y,
    uint32_t cmd[4]
)
{
    if (g_b46_sprite_hits == 0u)
    {
        return 0;
    }

    if (hits) *hits = g_b46_sprite_hits;
    if (serial) *serial = g_b46_sprite_serial;
    if (last_e1) *last_e1 = g_b46_sprite_e1;
    if (e1_age) *e1_age = g_b46_sprite_e1_age;
    if (fill_age) *fill_age = g_b46_sprite_fill_age;
    if (texpage) *texpage = g_b46_sprite_texpage;
    if (off_x) *off_x = g_b46_sprite_off_x;
    if (off_y) *off_y = g_b46_sprite_off_y;

    if (cmd)
    {
        for (unsigned i = 0; i < 4u; ++i)
        {
            cmd[i] = g_b46_sprite_cmd[i];
        }
    }

    return 1;
}
