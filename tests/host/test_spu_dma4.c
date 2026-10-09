#include "fm_memory.h"
#include "fm_native_memory.h"
#include "fm_sort_swap.h"
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


static unsigned native_cycle_calls;
uint32_t psx_cyc_load_word(CPUState *c,uint32_t a,uint32_t r,uint32_t m)
{ ++native_cycle_calls; (void)r; (void)m; return c->read_word(a); }
uint16_t psx_cyc_load_half(CPUState *c,uint32_t a,uint32_t r,uint32_t m)
{ ++native_cycle_calls; (void)r; (void)m; return c->read_half(a); }
uint8_t psx_cyc_load_byte(CPUState *c,uint32_t a,uint32_t r,uint32_t m)
{ ++native_cycle_calls; (void)r; (void)m; return c->read_byte(a); }
uint32_t native_fixture(CPUState *, uint32_t);
uint32_t native_fixture_reference(CPUState *, uint32_t);
static unsigned native_callback_reads, native_callback_writes;
static uint32_t native_custom_read(uint32_t a) {
    ++native_callback_reads; return fm_memory_read_word(a);
}
static void native_custom_write(uint32_t a, uint32_t v) {
    ++native_callback_writes; fm_memory_write_word(a, v);
}
static void native_ram_fast(void)
{
    CPUState cpu = {0};
    cpu.read_word=fm_memory_read_word; cpu.read_half=fm_memory_read_half;
    cpu.read_byte=fm_memory_read_byte; cpu.write_word=fm_memory_write_word;
    cpu.write_half=fm_memory_write_half; cpu.write_byte=fm_memory_write_byte;
    cpu.gpr[1]=0xabcd1234; cpu.gpr[2]=0x7654; cpu.gpr[3]=0x98;
    fm_memory_init(ram,sizeof ram);
    uint32_t original=native_fixture_reference(&cpu,0x80012000);
    unsigned char expected[16]; memcpy(expected,ram+0x12000,16);
    memset(ram+0x12000,0,16);
    native_cycle_calls=0;
    assert(native_fixture(&cpu,0x80012000)==original);
#ifdef PSX_ENABLE_BLOCK_CYCLES
    assert(native_cycle_calls==3);
#else
    assert(native_cycle_calls==0);
#endif
    assert(!memcmp(expected,ram+0x12000,16));
    const uint32_t bases[]={0,0x80000000u,0xa0000000u,0x00200000u,0x00600000u};
    for(unsigned shift=0;shift<4;++shift) {
        fm_memory_init(ram+shift, sizeof ram-shift);
        for(unsigned b=0;b<5;++b) for(unsigned o=0;o<128;++o) {
            uint32_t a=bases[b]+0x12000+o;
            uint32_t value=0x5a123456u+o;
            fm_native_write_word(&cpu,a,value);
            assert(fm_memory_read_word(a)==value);
            assert(fm_native_read_word(&cpu,a)==cpu.read_word(a));
            fm_native_write_half(&cpu,a,0x9876);
            assert(fm_memory_read_half(a)==0x9876);
            assert(fm_native_read_half(&cpu,a)==cpu.read_half(a));
            fm_native_write_byte(&cpu,a,0x42);
            assert(fm_memory_read_byte(a)==0x42);
            assert(fm_native_read_byte(&cpu,a)==cpu.read_byte(a));
        }
    }
    fm_memory_init(ram, sizeof ram);
    /* RAM mirror end, incomplete spans, scratchpad, BIOS and MMIO must
     * retain the original behavior, including unmapped accounting. */
    const uint32_t edge[]={0x1ffffc,0x1ffffd,0x1ffffe,0x1fffff,
        0x7fffff,0x800000,0x1f800000,0x1f8003fd,0x1fc00000,REVERB,CTRL};
    for(unsigned i=0;i<sizeof edge/sizeof edge[0];++i) {
        uint32_t a=edge[i];
        assert(fm_native_read_word(&cpu,a)==cpu.read_word(a));
        assert(fm_native_read_half(&cpu,a)==cpu.read_half(a));
        assert(fm_native_read_byte(&cpu,a)==cpu.read_byte(a));
        fm_native_write_word(&cpu,a,0x76543210);
        assert(fm_native_read_word(&cpu,a)==cpu.read_word(a));
    }
    assert(!fm_native_ram_ptr(0x1fffff,4));
    /* An overridden callback is never bypassed, including ordinary RAM. */
    cpu.read_word=native_custom_read; cpu.write_word=native_custom_write;
    fm_native_write_word(&cpu,0x80012000,0xabcdef01);
    assert(fm_native_read_word(&cpu,0x80012000)==0xabcdef01);
    assert(native_callback_reads==1 && native_callback_writes==1);
    cpu.read_word=fm_memory_read_word; cpu.write_word=fm_memory_write_word;
    /* Watched writes, including aliases/crossing stores, take the callback. */
    assert(fm_native_watched(0x8029c4b7,2));
    assert(fm_native_watched(0xa02eb247,4));
    assert(!fm_native_watched(0x80012000,4));
    fm_native_write_byte(&cpu,0x8009c4b8,1);
    fm_native_write_word(&cpu,0x800eb248,0xabcdef12);
    fm_memory_watch_dump("fm-native-watch.txt");
    /* Rebinding RAM cannot leave the generated code pointing at old data. */
    fm_memory_init(ram+1,128);
    assert(g_fm_native_ram.base==ram+1 && g_fm_native_ram.size==128);
    assert(!fm_native_ram_ptr(127,2));
    fm_native_write_word(&cpu,4,0x12345678);
    assert(fm_memory_read_word(4)==0x12345678);
    fm_memory_init(NULL,0);
    assert(!fm_native_ram_ptr(0,1));
}


static void sort_swap(void)
{
    static const uint32_t mips[]={
        0x00804021,0x00a04821,0x10c0000a,0x00003821,0x01071821,
        0x01272021,0x90650000,0x90820000,0x24e70001,0xa0620000,
        0x00e6102b,0x1440fff8,0xa0850000,0x03e00008,0x00000000
    };
    static unsigned char expected_ram[sizeof ram];
    fm_memory_init(ram,sizeof ram); fm_interp_bind_ram(ram,sizeof ram);
    memcpy(ram+0x8f6c8,mips,sizeof mips);
    CPUState initial={0};
    initial.read_word=fm_memory_read_word; initial.read_half=fm_memory_read_half;
    initial.read_byte=fm_memory_read_byte; initial.write_word=fm_memory_write_word;
    initial.write_half=fm_memory_write_half; initial.write_byte=fm_memory_write_byte;
    for(unsigned r=1;r<32;++r) initial.gpr[r]=0x12345600+r;
    initial.gpr[31]=0x80015000;
    const unsigned sizes[]={0,1,2,4,16,32,63,128,256};
    for(unsigned shift=0;shift<4;++shift) for(unsigned ni=0;ni<9;++ni)
        for(unsigned resumed=0;resumed<2;++resumed) {
        unsigned n=sizes[ni]; if(resumed && !n) continue;
        unsigned start=resumed ? (n==16 ? 13 : n/2) : 0;
        CPUState cpu=initial;
        cpu.pc=resumed ? 0x8008f6d8 : 0x8008f6c8;
        cpu.gpr[6]=n; cpu.gpr[7]=start;
        cpu.gpr[4]=0x80010000+shift; cpu.gpr[5]=0xa0012000+shift;
        if(resumed) { cpu.gpr[8]=cpu.gpr[4]; cpu.gpr[9]=cpu.gpr[5];
            cpu.gpr[4]=cpu.gpr[9]+start-1; cpu.gpr[5]=0x3f; }
        for(unsigned o=0;o<260;++o) {
            ram[0x10000+o]=(unsigned char)(o*17+3);
            ram[0x12000+o]=(unsigned char)(o*5+97);
        }
        CPUState expected=cpu;
        for(unsigned step=0;expected.pc!=expected.gpr[31];++step) {
            assert(step<1024);
            FMInterpResult result=fm_interp_run_block(&expected,32);
            assert(result.reason==FM_INTERP_BLOCK_DONE);
        }
        memcpy(expected_ram,ram,sizeof ram);
        for(unsigned o=0;o<260;++o) {
            ram[0x10000+o]=(unsigned char)(o*17+3);
            ram[0x12000+o]=(unsigned char)(o*5+97);
        }
#ifdef PSX_ENABLE_BLOCK_CYCLES
        CPUState unchanged=cpu;
        assert(!fm_sort_swap_try(&cpu,cpu.pc&0x1fffffff));
        assert(!memcmp(&cpu,&unchanged,sizeof cpu));
#else
        assert(fm_sort_swap_try(&cpu,cpu.pc&0x1fffffff));
        assert(!memcmp(&cpu,&expected,sizeof cpu));
        assert(!memcmp(ram,expected_ram,sizeof ram));
#endif
    }
    /* Fallbacks are transactional: no register or memory mutation. */
    for(unsigned guard=0;guard<6;++guard) {
        CPUState cpu=initial;
        cpu.pc=0x8008f6c8; cpu.gpr[4]=0x80010000; cpu.gpr[5]=0x80012000;
        cpu.gpr[6]=16;
        if(guard==0)cpu.gpr[5]=0xa0010004; /* mirrored overlap */
        if(guard==1)cpu.gpr[4]=0x801ffff8; /* incomplete RAM span */
        if(guard==2)cpu.gpr[4]=0x800eb248; /* write watch */
        if(guard==3)cpu.gpr[6]=257; /* bound */
        if(guard==4)cpu.write_byte=NULL; /* replacement callback */
        if(guard==5)ram[0x8f6c8]^=1; /* modified implementation */
        CPUState before=cpu; memcpy(expected_ram,ram,sizeof ram);
        assert(!fm_sort_swap_try(&cpu,0x8f6c8));
        assert(!memcmp(&cpu,&before,sizeof cpu));
        assert(!memcmp(ram,expected_ram,sizeof ram));
        if(guard==5)ram[0x8f6c8]^=1;
    }
}

static void scratch_fast(void)
{
    const uint32_t bases[] = {0x1F800000u, 0x9F800000u, 0xBF800000u};
    const unsigned offsets[] = {0, 1, 2, 3, 128, 129, 1019, 1020};
    for (unsigned i = 0; i < 3; ++i) {
        for (unsigned j = 0; j < sizeof(offsets) / sizeof(offsets[0]); ++j) {
            unsigned o = offsets[j]; uint32_t address = bases[i] + o;
            fm_memory_write_word(address, 0x56781234);
            assert(fm_memory_read_word(address) == 0x56781234);
            assert(fm_memory_read_word(0x1F800000u + o) == 0x56781234);
            fm_memory_write_half(address, 0x89AB);
            assert(fm_memory_read_half(address) == 0x89AB);
            fm_memory_write_byte(address + 1, 0xCD);
            assert(fm_memory_read_word(address) == 0x5678CDAB);
        }
    }
    fm_memory_write_half(0xBF8003FE, 0x9876);
    assert(fm_memory_read_byte(0x9F8003FF) == 0x98);
    assert(fm_memory_unmapped_count() == 0);
    /* A wider access crossing the scratchpad boundary must stay invalid. */
    assert(fm_memory_read_word(0x1F8003FD) == 0);
    assert(fm_memory_unmapped_count() == 1);
}

static void interp_ram_fast(void)
{
    const uint32_t code[] = {
        0x3C088001, 0x35082000, /* t0 = 80012000 */
        0x8D090000, 0,         /* lw t1,0(t0); nop */
        0x25290001, 0xAD090004, /* addiu t1,1; sw t1,4(t0) */
        0x950A0002, 0,         /* lhu t2,2(t0); nop */
        0xA50A0008,            /* sh t2,8(t0) */
        0x910B0001, 0,         /* lbu t3,1(t0); nop */
        0xA10B000A,            /* sb t3,10(t0) */
        0x03E00008, 0          /* jr ra; nop */
    };
    for (unsigned shift = 0; shift < 4; ++shift) {
        fm_memory_init(ram + shift, sizeof ram - shift);
        fm_interp_bind_ram(ram + shift, sizeof ram - shift);
        for (unsigned i = 0; i < sizeof code / sizeof code[0]; ++i)
            fm_memory_write_word(0x80010000u + 4 * i, code[i]);
        fm_memory_write_word(0x80012000, 0x12345678);
        CPUState cpu = {0}; cpu.pc = 0x80010000; cpu.gpr[31] = 0x8000FFD0;
        cpu.read_byte = fm_memory_read_byte; cpu.read_half = fm_memory_read_half;
        cpu.read_word = fm_memory_read_word; cpu.write_byte = fm_memory_write_byte;
        cpu.write_half = fm_memory_write_half; cpu.write_word = fm_memory_write_word;
        FMInterpResult result = fm_interp_run_block(&cpu, 128);
        assert(result.reason == FM_INTERP_BLOCK_DONE && cpu.pc == 0x8000FFD0);
        assert(cpu.gpr[9] == 0x12345679 && cpu.gpr[10] == 0x1234 && cpu.gpr[11] == 0x56);
        assert(fm_memory_read_word(0x80012004) == 0x12345679);
        assert(fm_memory_read_half(0x80012008) == 0x1234);
        assert(fm_memory_read_byte(0x8001200A) == 0x56);
        assert(fm_memory_unmapped_count() == 0);
    }
}

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
    /* B136.55: acknowledge at target boundaries, without adding VBlanks.
     * Ten seconds gives floor(42336000/57345)=738 IRQs instead of 600. */
    fm_memory_write_half(mode, 0x258);
    fm_memory_write_half(0x1F801070u, (uint16_t)~0x40u);
    unsigned delivered=0;
    for (unsigned frame=0; frame<600u; ++frame) {
        uint32_t remaining=fm_memory_vblank_begin_timer2();
        unsigned slices=0;
        do {
            remaining=fm_memory_timer2_slice(remaining,slices++ < 8u);
            if (fm_memory_i_stat() & 0x40u) {
                ++delivered;
                fm_memory_write_half(0x1F801070u,(uint16_t)~0x40u);
            }
        } while (remaining);
        assert(slices<=3u);
    }
    assert(delivered==42336000u/0xE001u);
    assert(fm_memory_read_half(count)==42336000u%0xE001u);
    /* No acknowledgement: IRQs remain one latched bit, not queued events. */
    fm_memory_write_half(mode,0x258);
    for (unsigned frame=0; frame<60u; ++frame) {
        uint32_t remaining=fm_memory_vblank_begin_timer2();
        while (remaining) remaining=fm_memory_timer2_slice(remaining,1);
    }
    assert(fm_memory_i_stat() & 0x40u);
    assert(fm_memory_read_half(count)==4233600u%0xE001u);
    /* A pathological target is bounded and still consumes every clock tick. */
    fm_memory_write_half(target,0);
    fm_memory_write_half(mode,0x258);
    uint32_t remaining=fm_memory_vblank_begin_timer2();
    unsigned slices=0;
    do { remaining=fm_memory_timer2_slice(remaining,slices++ < 8u); } while (remaining);
    assert(slices==9u && fm_memory_read_half(count)==0);
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
    if (!strcmp(argv[1], "sort_swap")) sort_swap();
    else if (!strcmp(argv[1], "native_ram_fast")) native_ram_fast();
    else if (!strcmp(argv[1], "scratch_fast")) scratch_fast();
    else if (!strcmp(argv[1], "interp_ram_fast")) interp_ram_fast();
    else if (!strcmp(argv[1], "ram_fast")) ram_fast();
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
