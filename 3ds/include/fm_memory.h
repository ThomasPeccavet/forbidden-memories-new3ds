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
 * B135 - etat MMIO minimal pour le quick-state de debug.
 * La RAM principale est sauvegardee separement par main.c.
 */
typedef struct FMMemoryQuickState
{
    uint8_t scratch[0x400];

    uint16_t i_stat;
    uint16_t i_mask;

    struct
    {
        uint16_t count;
        uint16_t mode;
        uint16_t target;
        uint8_t irq_fired_once;
        uint8_t reserved;
    } timers[3];

    uint32_t dma2_madr;
    uint32_t dma2_bcr;
    uint32_t dma2_chcr;

    uint32_t dma6_madr;
    uint32_t dma6_bcr;
    uint32_t dma6_chcr;

    uint32_t dma_dpcr;
    uint32_t dma_dicr;
} FMMemoryQuickState;

void fm_memory_quick_save(FMMemoryQuickState *out);
void fm_memory_quick_load(const FMMemoryQuickState *in);


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

    uint32_t dma2_cycle_abort_count;
    uint32_t dma2_last_cycle_addr;
    uint32_t dma2_max_nodes;
    uint32_t dma2_max_words;

    uint32_t dma2_visit_wrap_clears;
    uint32_t dma2_last_empty_ot_nodes;
    uint32_t dma2_max_empty_ot_nodes;

    uint32_t dma2_linked_last_ms;
    uint32_t dma2_linked_max_ms;
    uint64_t dma2_linked_total_ms;
    uint32_t dma2_linked_over20;
    uint32_t dma2_linked_over33;

    uint32_t dma2_empty_fast_runs;
    uint64_t dma2_empty_fast_nodes;
    uint32_t dma2_empty_fast_last;
    uint32_t dma2_empty_fast_max;

    uint32_t dma6_transfer_count;
    uint64_t dma6_word_count;

    uint32_t dma6_madr;
    uint32_t dma6_bcr;
    uint32_t dma6_chcr;
} FMDmaDebugStats;

void fm_memory_dma_debug(
    FMDmaDebugStats *out
);
