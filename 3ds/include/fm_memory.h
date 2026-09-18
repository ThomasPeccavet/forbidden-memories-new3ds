#pragma once

#include <stddef.h>
#include <stdint.h>

void fm_memory_init(
    uint8_t *ram,
    size_t ram_size
);

uint32_t fm_memory_read_word(uint32_t addr);
void     fm_memory_write_word(uint32_t addr, uint32_t value);

uint16_t fm_memory_read_half(uint32_t addr);
void     fm_memory_write_half(uint32_t addr, uint16_t value);

uint8_t  fm_memory_read_byte(uint32_t addr);
void     fm_memory_write_byte(uint32_t addr, uint8_t value);

int fm_memory_self_test(void);

uint32_t fm_memory_last_unmapped(void);
unsigned fm_memory_unmapped_count(void);

void fm_memory_vblank_tick(void);

uint16_t fm_memory_i_stat(void);
uint16_t fm_memory_i_mask(void);


/*
 * ============================================================
 * Diagnostic DMA bring-up
 * ============================================================
 */

typedef struct FMDmaDebugStats
{
    uint32_t dma2_transfer_count;
    uint64_t dma2_word_count;

    uint32_t dma2_linked_transfer_count;

    uint32_t dma2_madr;
    uint32_t dma2_bcr;
    uint32_t dma2_chcr;

    uint32_t dma2_last_start_madr;
    uint32_t dma2_last_chcr;

    uint32_t dma2_last_nodes;
    uint32_t dma2_last_words;
    uint32_t dma2_last_first_header;

    uint32_t dma6_transfer_count;
    uint64_t dma6_word_count;

    uint32_t dma6_madr;
    uint32_t dma6_bcr;
    uint32_t dma6_chcr;
} FMDmaDebugStats;

void fm_memory_dma_debug(
    FMDmaDebugStats *out
);
