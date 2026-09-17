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