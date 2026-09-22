#pragma once

#include <stdint.h>

#include "cpu_state.h"

/*
 * Initialise le bridge GPU PS1 -> software renderer.
 *
 * vram doit pointer sur une VRAM 1024 x 512 en RGB555.
 */
void fm_gpu_init(
    uint16_t *vram
);

/*
 * Port GP0 :
 *
 * 0x1F801810 en écriture.
 */
void fm_gpu_gp0_write(
    uint32_t value
);

/*
 * Port GP1 :
 *
 * 0x1F801814 en écriture.
 */
void fm_gpu_gp1_write(
    uint32_t value
);

/*
 * GPUSTAT.
 */
uint32_t fm_gpu_status(void);

/*
 * Nombre total de mots GP0 reçus.
 *
 * C'est un compteur cumulatif depuis fm_gpu_init().
 */
uint64_t fm_gpu_gp0_count(void);

/*
 * Au moins une primitive / image a réellement
 * écrit dans la VRAM.
 */
int fm_gpu_has_frame(void);

/*
 * Position de début du framebuffer PS1 actuellement affiché.
 */
unsigned fm_gpu_display_x(void);
unsigned fm_gpu_display_y(void);


/*
 * B135 - etat fonctionnel minimal du GPU pour le quick-state de debug.
 * La VRAM 1024x512 est sauvegardee separement par main.c.
 */
typedef struct FMGpuQuickState
{
    uint32_t parser_state;
    uint32_t cmd[16];
    uint32_t cmd_have;
    uint32_t cmd_need;

    uint32_t has_frame;

    uint16_t texpage;
    uint16_t reserved0;
    uint32_t texture_window;

    int32_t draw_x1;
    int32_t draw_y1;
    int32_t draw_x2;
    int32_t draw_y2;

    int32_t offset_x;
    int32_t offset_y;

    int32_t mask_set;
    int32_t mask_check;

    uint32_t display_x;
    uint32_t display_y;
    int32_t display_disabled;
    uint32_t display_mode;

    uint32_t upload_x;
    uint32_t upload_y;
    uint32_t upload_w;
    uint32_t upload_h;
    uint32_t upload_index;
    uint32_t upload_pixels;
} FMGpuQuickState;

void fm_gpu_quick_save(FMGpuQuickState *out);
void fm_gpu_quick_load(const FMGpuQuickState *in);


/*
 * B122 - high-resolution GP0 opcode profiler.
 */
typedef struct FMGpuOpcodePerf
{
    uint8_t opcode;
    uint32_t calls;
    uint64_t total_us;
    uint32_t max_us;
} FMGpuOpcodePerf;

void fm_gpu_b122_rank(
    unsigned rank,
    FMGpuOpcodePerf *out
);

void fm_gpu_b122_totals(
    uint64_t *exec_us,
    uint64_t *upload_us,
    uint64_t *upload_words
);


/*
 * ============================================================
 * Diagnostic GPU bring-up
 * ============================================================
 *
 * Les compteurs packets_* comptent les paquets GP0 terminés,
 * pas les mots GP0.
 *
 * nonzero_* compte les pixels RGB555 non noirs dans une fenêtre
 * 320x256 :
 *
 *  page0   : x=0
 *  page320 : x=320
 *  display : à partir de GP1(05h) display start
 *
 * Le bit masque RGB555 n'est pas considéré comme une couleur.
 */
typedef struct FMGpuDebugStats
{
    uint64_t gp0_words;

    uint64_t packets_total;
    uint64_t packets_nop;
    uint64_t packets_fill;
    uint64_t packets_draw;
    uint64_t packets_copy;
    uint64_t packets_upload;
    uint64_t packets_readback;
    uint64_t packets_env;
    uint64_t packets_other;

    uint64_t upload_data_words;

    uint32_t nonzero_page0;
    uint32_t nonzero_page320;
    uint32_t nonzero_display;
    uint32_t nonzero_vram;

    int draw_x1;
    int draw_y1;
    int draw_x2;
    int draw_y2;

    int offset_x;
    int offset_y;

    unsigned display_x;
    unsigned display_y;

    int display_disabled;

    uint32_t b124_rect_hits;
    uint32_t b124_rect_fallbacks;
    uint64_t b124_rect_pixels;
    uint64_t b124_rect_texels;

    uint32_t b125_texquad_hits;
    uint32_t b125_gouraud_hits;
    uint32_t b125_fallbacks;
    uint64_t b125_pixels;

    uint32_t b126_seen_2c;
    uint32_t b126_seen_2e;
    uint32_t b126_seen_3a;
    uint32_t b126_try_t;
    uint32_t b126_try_g;
    uint32_t b126_reject_mask;
    int b126_scale;
    int b126_wide;
    int b126_filter;

    uint32_t b129_fill_hits;
    uint32_t b129_fill_fallbacks;
    uint64_t b129_fill_pixels;
    uint64_t b129_fill_zero_pixels;
    uint32_t b129_fill_max_pixels;
} FMGpuDebugStats;

uint32_t fm_gpu_b126_build_tag(void);

/*
 * B127: lightweight hot-path snapshot.
 * Unlike fm_gpu_debug_stats(), this does NOT scan the 1024x512 VRAM.
 */
void fm_gpu_b127_perf_snapshot(
    FMGpuDebugStats *out
);


/*
 * Remplit un snapshot de diagnostic.
 *
 * Cette fonction parcourt la VRAM : l'appeler uniquement pour
 * l'écran de debug, pas à chaque primitive.
 */
void fm_gpu_debug_stats(
    FMGpuDebugStats *out
);


/*
 * HLE des appels BIOS GPU A0:46..4E.
 *
 * Retour :
 *
 * 1 = appel reconnu
 * 0 = appel non reconnu
 */
int fm_gpu_bios_call(
    CPUState *cpu,
    uint32_t fn
);
