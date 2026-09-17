#ifndef FM_PLATFORM_H
#define FM_PLATFORM_H

#include <stdint.h>
#include <stdio.h>

/* All PSX addresses and pixels remain fixed-width, never host pointers. */

uint16_t fm_pad_bits(uint32_t held);

void fm_present_rgb555(
    const uint16_t *pixels,
    unsigned pitch,
    int crop
);

int fm_disc_open(
    const char *path
);

int fm_disc_read_sector(
    uint32_t lba,
    uint8_t out[2048]
);

int fm_disc_find_file(
    const char *path,
    uint32_t *lba,
    uint32_t *size
);

int fm_disc_load_exe(
    uint8_t *ram,
    uint32_t *entry
);

void fm_disc_close(void);

#endif