#include "fm_sort_swap.h"
#include "fm_native_memory.h"
#include <string.h>

extern uint32_t g_debug_last_store_pc;

int fm_sort_swap_try(CPUState *cpu, uint32_t phys)
{
    if (!cpu || (phys != 0x8f6c8u && phys != 0x8f6d8u)) return 0;
#ifdef PSX_ENABLE_BLOCK_CYCLES
    /* Do not replace detailed guest cycle/interlock accounting. */
    return 0;
#else
    static const uint32_t code[] = {
        0x00804021,0x00a04821,0x10c0000a,0x00003821,0x01071821,
        0x01272021,0x90650000,0x90820000,0x24e70001,0xa0620000,
        0x00e6102b,0x1440fff8,0xa0850000,0x03e00008,0x00000000
    };
    uint8_t *instructions = fm_native_ram_ptr(0x8008f6c8u, sizeof code);
    if (!instructions || memcmp(instructions,code,sizeof code)
        || cpu->read_byte != fm_memory_read_byte
        || cpu->write_byte != fm_memory_write_byte) return 0;
    uint32_t size=cpu->gpr[6], start=phys==0x8f6d8u ? cpu->gpr[7] : 0u;
    uint32_t a=cpu->gpr[phys==0x8f6d8u ? 8 : 4];
    uint32_t b=cpu->gpr[phys==0x8f6d8u ? 9 : 5];
    /* Bound each completion; unsupported/overlapping spans remain native.
     * A restored loop checkpoint with an inconsistent index also falls back. */
    if (size>256u || (phys==0x8f6d8u && start>=size)) return 0;
    if (!size) {
        cpu->gpr[8]=a; cpu->gpr[9]=b; cpu->gpr[7]=0;
        cpu->pc=cpu->gpr[31];
        return 1;
    }
    uint32_t remaining=size-start;
    uint8_t *pa=fm_native_ram_ptr(a+start,remaining);
    uint8_t *pb=fm_native_ram_ptr(b+start,remaining);
    if (!pa || !pb || fm_native_watched(a+start,remaining)
        || fm_native_watched(b+start,remaining)) return 0;
    /* RAM aliases can overlap even when guest addresses differ. */
    size_t oa=(size_t)(pa-g_fm_native_ram.base);
    size_t ob=(size_t)(pb-g_fm_native_ram.base);
    if (oa<ob+remaining && ob<oa+remaining) return 0;
    uint8_t last_a=pa[remaining-1];
    uint8_t temporary[256];
    memcpy(temporary,pa,remaining);
    memcpy(pa,pb,remaining);
    memcpy(pb,temporary,remaining);
    /* Match all registers clobbered by the MIPS loop, including the return
     * value (the last SLTU is false) and the two final byte addresses. */
    cpu->gpr[2]=0; cpu->gpr[3]=a+size-1; cpu->gpr[4]=b+size-1;
    cpu->gpr[5]=last_a; cpu->gpr[7]=size;
    cpu->gpr[8]=a; cpu->gpr[9]=b;
    cpu->pc=cpu->gpr[31];
    g_debug_last_store_pc=0x8008f6f8u;
    return 1;
#endif
}
