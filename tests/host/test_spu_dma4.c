#include "fm_memory.h"
#include "fm_gpu.h"
#include "fm_interp.h"
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
void gte_execute(CPUState *c, uint32_t v) { (void)c; (void)v; assert(0); }
uint32_t gte_read_data(CPUState *c, uint8_t r) { (void)c; (void)r; assert(0); return 0; }
uint32_t gte_read_ctrl(CPUState *c, uint8_t r) { (void)c; (void)r; assert(0); return 0; }
void gte_write_data(CPUState *c, uint8_t r, uint32_t v)
{ (void)c; (void)r; (void)v; assert(0); }
void gte_write_ctrl(CPUState *c, uint8_t r, uint32_t v)
{ (void)c; (void)r; (void)v; assert(0); }

#define ADDR 0x1F801DA6u
#define DATA 0x1F801DA8u
#define CTRL 0x1F801DAAu
#define STAT 0x1F801DAEu
#define MADR 0x1F8010C0u
#define BCR  0x1F8010C4u
#define CHCR 0x1F8010C8u
#define DICR 0x1F8010F4u
#define REVERB 0x1F801D98u
static unsigned char ram[2 * 1024 * 1024];

static void ram_fast(void)
{
    const uint32_t aliases[] = {0, 0x00200000u, 0x00400000u,
        0x00600000u, 0x80000000u, 0x80200000u, 0xA0000000u};
    const unsigned offsets[] = {0, 1, 2, 3, 4, 0x12340, 0x12341,
        0x1FFFF8, 0x1FFFFB, 0x1FFFFC};
    for (unsigned base_shift = 0; base_shift < 4; ++base_shift) {
        /* Host storage can itself be unaligned, even for a guest SW/LW. */
        fm_memory_init(ram + base_shift, sizeof(ram) - base_shift);
        for (unsigned a = 0; a < sizeof(aliases) / sizeof(aliases[0]); ++a) {
            for (unsigned o = 0; o < sizeof(offsets) / sizeof(offsets[0]); ++o) {
                unsigned offset = offsets[o];
                if (offset + 4 > sizeof(ram) - base_shift) continue;
                uint32_t address = aliases[a] + offset;
                uint32_t value = 0xBADC0000u + offset + a;
                fm_memory_write_word(address, value);
                assert(fm_memory_read_word(address) == value);
                assert(fm_memory_read_word(0x80000000u + offset) == value);
                for (unsigned b = 0; b < 4; ++b)
                    assert(ram[base_shift + offset + b] == (uint8_t)(value >> (8 * b)));
                fm_memory_write_half(address, 0xC581);
                assert(fm_memory_read_half(address) == 0xC581);
                assert(ram[base_shift + offset] == 0x81);
                assert(ram[base_shift + offset + 1] == 0xC5);
                assert(fm_memory_read_word(address) == ((value & 0xFFFF0000u) | 0xC581));
                fm_memory_write_byte(address + 1, 0x12);
                assert(fm_memory_read_half(address) == 0x1281);
            }
        }
        assert(fm_memory_unmapped_count() == 0);
    }
    fm_memory_init(ram, sizeof ram);
    /* All watch bytes, plus stores overlapping the range from below. */
    for (unsigned i = 0; i < 9; ++i) {
        fm_memory_write_byte(0x800EB248u + i, (uint8_t)(i + 1));
        assert(fm_memory_read_byte(0x800EB248u + i) == i + 1);
    }
    fm_memory_write_word(0x8009C4B5, 0x56781234);
    assert(fm_memory_read_byte(0x8009C4B8) == 0x56);
    fm_memory_write_word(0x800EB245, 0x78ABCDEF);
    assert(fm_memory_read_byte(0x800EB248) == 0x78);
}

static void timer2_clock(void)
{
    const uint32_t count = 0x1F801120u, mode = 0x1F801124u, target = 0x1F801128u;
    /* Both source choices accumulate a full second of hardware clock.
     * COUNT polling itself must not change it. */
    for (unsigned divided = 0; divided < 2; ++divided) {
        fm_memory_write_half(mode, divided ? 0x200 : 0);
        for (unsigned frame = 0; frame < 60; ++frame) fm_memory_vblank_tick();
        unsigned hz = divided ? 4233600u : 33868800u;
        assert(fm_memory_read_half(count) == (hz & 0xFFFFu));
        assert(fm_memory_read_half(count) == (hz & 0xFFFFu));
    }
    /* The actual SEQ configuration must produce pending timer2 IRQs every
     * host interval, rather than once every 14 intervals as in B136.29. */
    fm_memory_write_half(target, 0xE000);
    fm_memory_write_half(mode, 0x258);
    for (unsigned frame = 0; frame < 60; ++frame) {
        fm_memory_write_half(0x1F801070u, (uint16_t)~0x40u);
        fm_memory_vblank_tick();
        assert(fm_memory_i_stat() & 0x40);
    }
    assert(fm_memory_read_half(count) == 4233600u % 0xE001u);
    /* Without reset-on-target, a large delta crosses any target even when
     * its final modulo count falls short of it. Only one IRQ bit is latched. */
    fm_memory_write_half(target, 20000);
    fm_memory_write_half(mode, 0x250);
    fm_memory_write_half(count, 65000);
    fm_memory_write_half(0x1F801070u, (uint16_t)~0x40u);
    fm_memory_vblank_tick();
    assert(fm_memory_i_stat() & 0x40);
    assert(fm_memory_read_half(count) == ((65000u + 70560u) & 0xFFFFu));
}

static void reverb_mask(void)
{
    fm_memory_write_half(REVERB | 0xA0000000u, 0x8001);
    fm_memory_write_half(REVERB + 2, 0xFF80);
    assert(fm_memory_read_word(REVERB) == 0x00808001);
    assert(fm_memory_read_half(REVERB + 2) == 0x80);
    fm_memory_write_word(REVERB, 0xFFAB1234);
    assert(fm_memory_read_half(REVERB) == 0x1234);
    assert(fm_memory_read_half(REVERB + 2) == 0xAB);
    fm_memory_write_byte(REVERB + 1, 0x56);
    fm_memory_write_byte(REVERB + 3, 0xFF);
    assert(fm_memory_read_word(REVERB) == 0x00AB5634);
    assert(fm_memory_read_byte(REVERB + 2) == 0xAB);
    assert(fm_memory_read_byte(REVERB + 3) == 0);
    FMMemoryQuickState state;
    fm_memory_quick_save(&state);
    fm_memory_write_word(REVERB, 0);
    fm_memory_quick_load(&state);
    assert(fm_memory_read_word(REVERB) == 0x00AB5634);
    assert(fm_memory_unmapped_count() == 0);
    fm_memory_init(ram, sizeof ram);
    assert(fm_memory_read_word(REVERB) == 0);
}

static void native_reverb_poll(void)
{
    /* Synthetic native MIPS set/clear + readback polling. On B136.28 the
     * set path never returns: SH is ignored and LHU keeps returning zero.
     * This uses the interpreter and real MMIO, not a zero-filled IO array. */
    static const uint32_t code[] = {
        0x3C081F80, /* lui t0, 1f80 */
        0x35081D98, /* ori t0, t0, 1d98 */
        0x95090000, /* lhu t1, 0(t0) */
        0x35290001, /* ori t1, t1, 1 (clear case replaces this instruction) */
        0xA5090000, /* sh t1, 0(t0) */
        0x95020000, /* poll: lhu v0, 0(t0) */
        0x30420001, /* andi v0, v0, 1 */
        0x1040FFFD, /* beq v0, zero, poll (clear case uses bne) */
        0x00000000, /* nop */
        0x03E00008, /* jr ra */
        0x00000000,
    };
    fm_interp_bind_ram(ram, sizeof ram);
    for (unsigned clear = 0; clear < 2; ++clear) {
        for (unsigned i = 0; i < sizeof(code) / sizeof(code[0]); ++i)
            fm_memory_write_word(0x80010000u + 4u * i, code[i]);
        if (clear) {
            fm_memory_write_word(0x8001000Cu, 0x3129FFFE); /* andi t1,t1,fffe */
            fm_memory_write_word(0x8001001Cu, 0x1440FFFD); /* bne v0,zero,poll */
        }
        CPUState cpu = {0};
        cpu.pc = 0x80010000; cpu.gpr[31] = 0x8000FFD0;
        cpu.read_byte = fm_memory_read_byte; cpu.read_half = fm_memory_read_half;
        cpu.read_word = fm_memory_read_word; cpu.write_byte = fm_memory_write_byte;
        cpu.write_half = fm_memory_write_half; cpu.write_word = fm_memory_write_word;
        unsigned blocks = 0;
        while (cpu.pc != 0x8000FFD0 && blocks++ < 100) {
            FMInterpResult r = fm_interp_run_block(&cpu, 512);
            assert(r.reason == FM_INTERP_BLOCK_DONE || r.reason == FM_INTERP_BUDGET);
        }
        assert(cpu.pc == 0x8000FFD0 && cpu.gpr[2] == !clear);
    }
    assert(fm_memory_unmapped_count() == 0);
}

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
    if (!strcmp(argv[1], "ram_fast")) ram_fast();
    else if (!strcmp(argv[1], "spu_half")) spu_half();
    else if (!strcmp(argv[1], "spu_word")) spu_word();
    else if (!strcmp(argv[1], "reverb_mask")) reverb_mask();
    else if (!strcmp(argv[1], "native_reverb_poll")) native_reverb_poll();
    else if (!strcmp(argv[1], "timer2_clock")) timer2_clock();
    else if (!strcmp(argv[1], "dma_partial")) dma_partial();
    else if (!strcmp(argv[1], "dma_completion")) dma_completion();
    else if (!strcmp(argv[1], "reset")) reset();
    else return 2;
    puts(argv[1]);
    return 0;
}
