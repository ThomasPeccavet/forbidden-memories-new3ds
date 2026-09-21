#include <3ds.h>
#include <string.h>
#include <stdint.h>

#include "fm_platform.h"


uint16_t fm_pad_bits(uint32_t held)
{
    uint16_t bits = 0xffff;

    const uint32_t keys[] =
    {
        KEY_SELECT, 0, 0, KEY_START,
        KEY_DUP, KEY_DRIGHT, KEY_DDOWN, KEY_DLEFT,
        KEY_ZL, KEY_ZR, KEY_L, KEY_R,
        KEY_X, KEY_A, KEY_B, KEY_Y
    };

    for (unsigned i = 0; i < 16; ++i)
    {
        if (held & keys[i])
        {
            bits &= ~(1u << i);
        }
    }

    return bits;
}


/*
 * ============================================================
 * B105 - present RGB555 optimise
 * ============================================================
 *
 * Ancien chemin :
 *   - memset 400*240*3 = 288000 octets a CHAQUE frame ;
 *   - extraction/expansion R/G/B pour les 76800 pixels.
 *
 * Nouveau chemin :
 *   - chaque framebuffer 3DS est nettoye une seule fois ;
 *   - les bandes noires restent noires, le viewport central est
 *     totalement reecrit a chaque present ;
 *   - LUT 32768 entrees pour supprimer les conversions RGB555
 *     repetitives.
 */
static uint32_t g_rgb555_to_bgr888[32768];
static int g_rgb555_lut_ready = 0;

static uint8_t *g_seen_fb[4] = { NULL, NULL, NULL, NULL };
static unsigned g_seen_fb_count = 0;


static void fm_prepare_rgb555_lut(void)
{
    if (g_rgb555_lut_ready)
    {
        return;
    }

    for (unsigned p = 0; p < 32768u; ++p)
    {
        unsigned r5 = p & 31u;
        unsigned g5 = (p >> 5) & 31u;
        unsigned b5 = (p >> 10) & 31u;

        unsigned r8 = (r5 << 3) | (r5 >> 2);
        unsigned g8 = (g5 << 3) | (g5 >> 2);
        unsigned b8 = (b5 << 3) | (b5 >> 2);

        g_rgb555_to_bgr888[p] =
            (uint32_t)b8
            |
            ((uint32_t)g8 << 8)
            |
            ((uint32_t)r8 << 16);
    }

    g_rgb555_lut_ready = 1;
}


static void fm_clear_framebuffer_once(uint8_t *fb)
{
    for (unsigned i = 0; i < g_seen_fb_count; ++i)
    {
        if (g_seen_fb[i] == fb)
        {
            return;
        }
    }

    /*
     * Le top framebuffer fait 400x240 BGR8.
     * Un clear initial suffit : les bandes laterales ne sont jamais
     * reutilisees pour l'image 320x240.
     */
    memset(
        fb,
        0,
        400u * 240u * 3u
    );

    if (g_seen_fb_count < 4u)
    {
        g_seen_fb[g_seen_fb_count++] = fb;
    }
}


/*
 * PSX BGR555 -> framebuffer libctru BGR8 tourne.
 * 4:3, viewport 320x240 centre.
 */
void fm_present_rgb555(
    const uint16_t *pixels,
    unsigned pitch,
    int crop
)
{
    fm_prepare_rgb555_lut();

    uint8_t *fb =
        gfxGetFramebuffer(
            GFX_TOP,
            GFX_LEFT,
            NULL,
            NULL
        );

    fm_clear_framebuffer_once(fb);

    /*
     * Source en lignes : meilleur acces cache pour la VRAM/composite.
     * La destination 3DS est tournee, donc x avance par colonnes.
     */
    for (unsigned y = 0; y < 240u; ++y)
    {
        unsigned sy =
            crop
                ? y + 8u
                : (y * 256u) / 240u;

        const uint16_t *src =
            pixels
            +
            sy * pitch;

        uint8_t *d =
            fb
            +
            (40u * 240u + 239u - y) * 3u;

        for (unsigned x = 0; x < 320u; ++x)
        {
            uint32_t c =
                g_rgb555_to_bgr888[
                    src[x] & 0x7FFFu
                ];

            d[0] = (uint8_t)c;
            d[1] = (uint8_t)(c >> 8);
            d[2] = (uint8_t)(c >> 16);

            /*
             * Colonne suivante du framebuffer tourne :
             * 240 pixels * 3 octets.
             */
            d += 240u * 3u;
        }
    }
}
