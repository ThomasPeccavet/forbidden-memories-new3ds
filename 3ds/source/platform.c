#include <3ds.h>
#include <string.h>
#include "fm_platform.h"

uint16_t fm_pad_bits(uint32_t held) {
    uint16_t bits = 0xffff;
    const uint32_t keys[] = {KEY_SELECT, 0, 0, KEY_START, KEY_DUP, KEY_DRIGHT,
        KEY_DDOWN, KEY_DLEFT, KEY_ZL, KEY_ZR, KEY_L, KEY_R,
        KEY_X, KEY_A, KEY_B, KEY_Y};
    for (unsigned i = 0; i < 16; ++i)
        if (held & keys[i]) bits &= ~(1u << i);
    return bits;
}

/* PSX BGR555 -> rotated libctru BGR8 framebuffer. 4:3 320x240 viewport.
 * Fit mode resamples all 256 source rows; crop mode keeps 1:1 pixels.
 * No stereo duplication: gfxSet3D(false) is required by the caller. */
void fm_present_rgb555(const uint16_t *pixels, unsigned pitch, int crop) {
    uint8_t *fb = gfxGetFramebuffer(GFX_TOP, GFX_LEFT, NULL, NULL);
    memset(fb, 0, 400 * 240 * 3);
    for (unsigned y = 0; y < 240; ++y) {
        unsigned sy = crop ? y + 8 : y * 256 / 240;
        for (unsigned x = 0; x < 320; ++x) {
            uint16_t p = pixels[sy * pitch + x];
            uint8_t *d = fb + ((x + 40) * 240 + 239 - y) * 3;
            unsigned r = p & 31, g = (p >> 5) & 31, b = (p >> 10) & 31;
            d[0] = (b << 3) | (b >> 2);
            d[1] = (g << 3) | (g >> 2);
            d[2] = (r << 3) | (r >> 2);
        }
    }
}
