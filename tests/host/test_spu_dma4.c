#include "fm_memory.h"
#include "fm_gpu.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

/* GPU is outside this test: unexpected calls must fail, not silently pass. */
uint32_t g_debug_last_store_pc;
uint64_t fm_mdec_host_frame, fm_mdec_host_cycles;
uint8_t fm_media_cd_read(uint32_t addr) { (void)addr; return 0; }
void fm_media_cd_write(uint32_t addr, uint8_t value) { (void)addr; (void)value; }
void fm_gpu_gp0_write(uint32_t value) { (void)value; assert(0); }
void fm_gpu_gp0_words(const uint32_t *v, uint32_t n) { (void)v; (void)n; assert(0); }
void fm_gpu_gp1_write(uint32_t value) { (void)value; assert(0); }
uint32_t fm_gpu_status(void) { assert(0); return 0; }
void fm_gpu_b13532_profile_reset(void) { assert(0); }

#define ADDR 0x1F801DA6u
#define DATA 0x1F801DA8u
#define CTRL 0x1F801DAAu
#define STAT 0x1F801DAEu
#define MADR 0x1F8010C0u
#define BCR  0x1F8010C4u
#define CHCR 0x1F8010C8u
#define DICR 0x1F8010F4u
static unsigned char ram[2 * 1024 * 1024];

static void spu_half(void)
{
    /* Psy-Q's transfer-mode polling must see a preceding SH store. */
    fm_memory_write_half(ADDR, 0x1234);
    fm_memory_write_half(DATA, 0x5678);
    fm_memory_write_half(CTRL | 0xA0000000u, 0x0020);
    assert(fm_memory_read_half(ADDR) == 0x1234);
    assert(fm_memory_read_half(DATA) == 0x5678);
    assert((fm_memory_read_half(CTRL) & 0x30) == 0x20);
    assert((fm_memory_read_half(STAT) & 0x30) == 0x20);
    assert(fm_memory_read_word(DATA) == 0x00205678);
    fm_memory_write_half(STAT, 0xFFFF);
    assert(fm_memory_read_half(STAT) == 0x20);
    assert(fm_memory_unmapped_count() == 0);
}

static void spu_word(void)
{
    fm_memory_write_word(ADDR - 2, 0x12340000);
    fm_memory_write_word(DATA, 0x0030ABCD);
    assert(fm_memory_read_half(ADDR) == 0x1234);
    assert(fm_memory_read_half(DATA) == 0xABCD);
    assert(fm_memory_read_half(CTRL) == 0x30);
    assert(fm_memory_read_word(STAT - 2) == 0x00300000);
    fm_memory_write_word(STAT - 2, 0xFFFFFFFF);
    assert(fm_memory_read_half(STAT) == 0x30);
}

static void dma_partial(void)
{
    fm_memory_write_word(MADR, 0xABCDEF);
    fm_memory_write_half(MADR, 0x1234);
    assert(fm_memory_read_word(MADR) == 0xAB1234);
    fm_memory_write_byte(MADR + 2, 0x55);
    fm_memory_write_byte(MADR + 3, 0xFF);
    assert(fm_memory_read_word(MADR) == 0x551234);
    fm_memory_write_word(BCR, 0x00010080);
    fm_memory_write_half(BCR + 2, 2);
    assert(fm_memory_read_word(BCR) == 0x00020080);
    fm_memory_write_half(CHCR, 0x0201);
    assert(fm_memory_dma4_transfer_count() == 0);
    /* Setting START via upper half must use the same path as SW. */
    fm_memory_write_half(CHCR + 2, 0x0100);
    assert(fm_memory_dma4_transfer_count() == 1);
    assert(fm_memory_read_word(CHCR) == 0x0201);
    assert(fm_memory_dma4_take_completion() == 1);
    assert(fm_memory_dma4_take_completion() == 0);
    fm_memory_write_byte(CHCR + 3, 1);
    assert(fm_memory_dma4_transfer_count() == 2);
    assert(fm_memory_dma4_take_completion() == 1);
    assert(fm_memory_dma4_take_completion() == 0);
}

static void dma_completion(void)
{
    /* Exercise existing synchronous bring-up semantics, not full SPU DMA. */
    fm_memory_write_word(DICR, (1u << 20) | (1u << 23));
    fm_memory_write_word(MADR, 0x801DC000);
    fm_memory_write_word(BCR, 0x00010080);
    assert(fm_memory_dma4_take_completion() == 0);
    fm_memory_write_word(CHCR, 0x01000201);
    assert(fm_memory_read_word(MADR) == 0x1DC000);
    assert((fm_memory_read_word(CHCR) & 0x11000000) == 0);
    assert((fm_memory_read_word(DICR) & 0x90000000) == 0x90000000);
    assert(fm_memory_i_stat() & 8);
    assert(fm_memory_dma4_take_completion() == 1);
    assert(fm_memory_dma4_take_completion() == 0);
    fm_memory_write_byte(DICR + 3, 0x10);
    assert((fm_memory_read_word(DICR) & 0x90000000) == 0);
    /* Completion token is independent of the DICR write-one-to-clear flag. */
    assert(fm_memory_dma4_take_completion() == 0);
}

static void reset(void)
{
    fm_memory_write_word(DATA, 0x00201234);
    fm_memory_write_word(MADR, 0x1234);
    fm_memory_write_word(BCR, 0x10080);
    fm_memory_write_word(CHCR, 0x01000201);
    fm_memory_init(ram, sizeof ram);
    assert(fm_memory_read_half(CTRL) == 0);
    assert(fm_memory_read_half(STAT) == 0);
    assert(fm_memory_read_half(DATA) == 0);
    assert(fm_memory_read_word(MADR) == 0);
    assert(fm_memory_read_word(BCR) == 0);
    assert(fm_memory_read_word(CHCR) == 0);
    assert(fm_memory_dma4_transfer_count() == 0);
    assert(fm_memory_dma4_take_completion() == 0);
    uint32_t diag[6];
    fm_memory_dma4_write_diag(diag);
    for (unsigned i = 0; i < 6; ++i) assert(diag[i] == 0);
}

int main(int argc, char **argv)
{
    assert(argc == 2);
    fm_memory_init(ram, sizeof ram);
    if (!strcmp(argv[1], "spu_half")) spu_half();
    else if (!strcmp(argv[1], "spu_word")) spu_word();
    else if (!strcmp(argv[1], "dma_partial")) dma_partial();
    else if (!strcmp(argv[1], "dma_completion")) dma_completion();
    else if (!strcmp(argv[1], "reset")) reset();
    else return 2;
    puts(argv[1]);
    return 0;
}
