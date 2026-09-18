#include "fm_gpu.h"

#include "gpu_sw_renderer.h"

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

static int g_has_frame = 0;


/*
 * ============================================================
 * Draw environment
 * ============================================================
 */

static uint16_t g_texpage = 0;

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


        sw_fill_rect(
            x,
            y,
            w,
            h,
            rgb24_to_555(
                g_cmd[0]
            )
        );


        g_has_frame =
            1;


        return;
    }


    /*
     * ========================================================
     * Polygons
     * ========================================================
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
                coord_x(g_cmd[1]);

            int y0 =
                coord_y(g_cmd[1]);

            int x1 =
                coord_x(g_cmd[2]);

            int y1 =
                coord_y(g_cmd[2]);

            int x2 =
                coord_x(g_cmd[3]);

            int y2 =
                coord_y(g_cmd[3]);


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
                    coord_x(g_cmd[4]);

                int y3 =
                    coord_y(g_cmd[4]);


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
                coord_x(g_cmd[1]);

            int y0 =
                coord_y(g_cmd[1]);

            int u0 =
                tex_u(g_cmd[2]);

            int v0 =
                tex_v(g_cmd[2]);


            uint16_t clut =
                packet_clut(
                    g_cmd[2]
                );


            int x1 =
                coord_x(g_cmd[3]);

            int y1 =
                coord_y(g_cmd[3]);

            int u1 =
                tex_u(g_cmd[4]);

            int v1 =
                tex_v(g_cmd[4]);


            g_texpage =
                packet_texpage(
                    g_cmd[4]
                );


            int x2 =
                coord_x(g_cmd[5]);

            int y2 =
                coord_y(g_cmd[5]);

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
                    coord_x(g_cmd[7]);

                int y3 =
                    coord_y(g_cmd[7]);

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
                coord_x(g_cmd[1]);

            int y0 =
                coord_y(g_cmd[1]);


            uint16_t c1 =
                rgb24_to_555(
                    g_cmd[2]
                );


            int x1 =
                coord_x(g_cmd[3]);

            int y1 =
                coord_y(g_cmd[3]);


            uint16_t c2 =
                rgb24_to_555(
                    g_cmd[4]
                );


            int x2 =
                coord_x(g_cmd[5]);

            int y2 =
                coord_y(g_cmd[5]);


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
                    coord_x(g_cmd[7]);

                int y3 =
                    coord_y(g_cmd[7]);


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
                coord_x(g_cmd[1]);

            int y0 =
                coord_y(g_cmd[1]);

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
                coord_x(g_cmd[4]);

            int y1 =
                coord_y(g_cmd[4]);

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
                coord_x(g_cmd[7]);

            int y2 =
                coord_y(g_cmd[7]);

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
                    coord_x(g_cmd[10]);

                int y3 =
                    coord_y(g_cmd[10]);

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
            coord_x(g_cmd[1]),
            coord_y(g_cmd[1]),

            coord_x(g_cmd[2]),
            coord_y(g_cmd[2]),

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
            coord_x(g_cmd[1]),
            coord_y(g_cmd[1]),

            coord_x(g_cmd[2]),
            coord_y(g_cmd[2]),

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
            coord_x(g_cmd[1]),
            coord_y(g_cmd[1]),
            rgb24_to_555(g_cmd[0]),

            coord_x(g_cmd[3]),
            coord_y(g_cmd[3]),
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
            coord_x(g_cmd[1]),
            coord_y(g_cmd[1]),
            rgb24_to_555(g_cmd[0]),

            coord_x(g_cmd[3]),
            coord_y(g_cmd[3]),
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
            coord_x(g_cmd[1]);

        int y =
            coord_y(g_cmd[1]);


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
        sw_set_texture_window(
            g_cmd[0]
        );


        return;
    }


    if (opcode == 0xE3)
    {
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


    g_has_frame =
        0;


    g_texpage =
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


            sw_vram_write(
                (
                    g_upload_x
                    +
                    px
                )
                &
                1023u,

                (
                    g_upload_y
                    +
                    py
                )
                &
                511u,

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
        execute_command();


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