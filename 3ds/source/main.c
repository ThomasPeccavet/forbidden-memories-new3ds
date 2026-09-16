#include <3ds.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fm_platform.h"
#include "gpu_sw_renderer.h"

/* Native-wide desktop compositing is deliberately disabled on this target. */
int g_ws_bd_stretch_on = 0;
int g_ws_bd_stretch_pct = 100;
int psx_ws_prim_in_backdrop(void) { return 0; }

static int load_preview(uint16_t *pixels) {
    FILE *f = fopen("sdmc:/3ds/fm-new3ds/preview.rgb555", "rb");
    if (!f) return 0;
    int ok = fread(pixels, 2, 320 * 256, f) == 320 * 256 && fgetc(f) == EOF;
    fclose(f);
    return ok;
}
int main(void) {
    gfxInitDefault();
    gfxSet3D(false);
    consoleInit(GFX_BOTTOM, NULL);
    bool is_new = false;
    APT_CheckNew3DS(&is_new);
    osSetSpeedupEnable(true);
    uint16_t *vram = calloc(1024 * 512, 2);
    uint16_t *preview = malloc(320 * 256 * 2);
    uint8_t *ram = malloc(2 * 1024 * 1024);
    if (!vram || !preview || !ram) {
        printf("Memoire insuffisante. START: quitter\n");
        while (aptMainLoop()) {
            hidScanInput(); if (hidKeysDown() & KEY_START) break;
            gspWaitForVBlank();
        }
        free(vram); free(preview); free(ram); gfxExit(); return 1;
    }
    int have_preview = load_preview(preview);
    int show_preview = have_preview, crop = 0, x = 160, y = 128;
    uint32_t entry = 0;
    printf("Chargement SD...\n");
    int disc_status = fm_disc_open("sdmc:/3ds/fm-new3ds/disc.bin");
    int exe_status = disc_status ? -99 : fm_disc_load_exe(ram, &entry);
    sw_renderer_init(vram);
    sw_renderer_set_scale(1);
    unsigned frame = 0;
    uint16_t old_pad = 0;
    uint64_t render_ticks = 0;
    unsigned render_count = 0;
    while (aptMainLoop()) {
        hidScanInput();
        uint32_t held = hidKeysHeld(), down = hidKeysDown();
        if ((held & (KEY_START | KEY_SELECT)) == (KEY_START | KEY_SELECT)) break;
        if ((down & KEY_X) && have_preview) show_preview = !show_preview;
        if (down & KEY_Y) crop = !crop;
        x += (held & KEY_DRIGHT ? 2 : 0) - (held & KEY_DLEFT ? 2 : 0);
        y += (held & KEY_DDOWN ? 2 : 0) - (held & KEY_DUP ? 2 : 0);
        if (x < 32) x = 32;
        if (x > 288) x = 288;
        if (y < 32) y = 32;
        if (y > 224) y = 224;
        uint64_t start = svcGetSystemTick();
        if (show_preview) {
            fm_present_rgb555(preview, 320, crop);
        } else {
            sw_fill_rect(0, 0, 320, 256, 0x1842);
            int pulse = (frame / 2) % 32;
            sw_draw_gouraud_triangle(x, y - 30, 31, x - 30, y + 30,
                31 << 5, x + 30, y + 30, (uint16_t)(pulse << 10));
            fm_present_rgb555(vram, 1024, crop);
        }
        render_ticks += svcGetSystemTick() - start;
        ++render_count;
        uint16_t pad = fm_pad_bits(held);
        if (frame % 30 == 0 || pad != old_pad || down) {
            printf("\x1b[2J\x1b[HForbidden Memories / New 3DS\n\n");
            printf("Prototype plateforme - non jouable\n");
            printf("Console : %s\n", is_new ? "New 3DS" : "3DS (non cible)");
            printf("Vue : %s\n", show_preview ? "CAPTURE PC FIXE" : "RASTER PSX NATIF ARM");
            printf("Format : %s\n", crop ? "1:1, 8 lignes coupees en haut/bas" : "4:3, image complete");
            printf("\nX : capture / raster\nY : format image\nCroix : deplacer triangle\nSTART + SELECT : quitter\n");
            printf("\nPad PSX : %04X\n", (unsigned)pad);
            printf("Disque SD : %d (0 = ouvert)\n", disc_status);
            printf("EXE charge : %d (0 = oui)\n", exe_status);
            printf("Entree : %08lX (non executee)\n", (unsigned long)entry);
            if (frame % 30 == 0 && frame) {
                printf("Rendu moyen : %.2f ms\n", (double)render_ticks * 1000.0 / SYSCLOCK_ARM11 / render_count);
                render_ticks = 0;
                render_count = 0;
            }
            printf("\nCPU/CD/XA/SPU : pas raccordes\n");
        }
        old_pad = pad;
        ++frame;
        gfxFlushBuffers(); gfxSwapBuffers(); gspWaitForVBlank();
    }
    fm_disc_close();
    free(vram); free(preview); free(ram);
    gfxExit(); return 0;
}
