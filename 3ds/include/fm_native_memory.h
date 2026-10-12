#ifndef FM_NATIVE_MEMORY_H
#define FM_NATIVE_MEMORY_H
#include "cpu_state.h"
#include "fm_memory.h"
#include "fm_ram_access.h"

/* B136.51: bound by fm_memory_init; never an independent RAM copy.
 * Only ordinary RAM accesses with the standard callback can be inlined.
 * Scratchpad, MMIO, BIOS and incomplete spans keep the original callback. */
typedef struct FMNativeRam {
    uint8_t *base;
    size_t size;
} FMNativeRam;
extern FMNativeRam g_fm_native_ram;

static inline uint8_t *fm_native_ram_ptr(uint32_t address, unsigned width)
{
    uint32_t phys = address & 0x1fffffffu;
    uint32_t offset = phys & 0x001fffffu;
    if (phys < 0x00800000u && g_fm_native_ram.base
        && g_fm_native_ram.size >= width
        && offset <= g_fm_native_ram.size - width)
        return g_fm_native_ram.base + offset;
    return NULL;
}

/* Retain exact write-watch events even when generated objects are shared
 * between CLEAN and PROFILE builds. Check the mirrored RAM offset. */
static inline int fm_native_watched(uint32_t address, unsigned width)
{
    uint32_t offset = address & 0x001fffffu;
    uint32_t end = offset + width;
    return (offset <= 0x0009c4b8u && end > 0x0009c4b8u)
        || (offset < 0x000eb251u && end > 0x000eb248u);
}

static inline uint32_t fm_native_read_word(CPUState *cpu, uint32_t address)
{
    uint8_t *p = fm_native_ram_ptr(address, 4u);
    if (p && cpu->read_word == fm_memory_read_word) return fm_ram_load32(p);
    return cpu->read_word(address);
}
static inline void fm_native_write_word(CPUState *cpu, uint32_t address, uint32_t value)
{
    uint8_t *p = fm_native_ram_ptr(address, 4u);
    if (p && cpu->write_word == fm_memory_write_word
        && !fm_native_watched(address, 4u)) {
        fm_ram_store32(p, value);
        return;
    }
    cpu->write_word(address, value);
}

static inline uint16_t fm_native_read_half(CPUState *cpu, uint32_t address)
{
    uint8_t *p = fm_native_ram_ptr(address, 2u);
    if (p && cpu->read_half == fm_memory_read_half) return fm_ram_load16(p);
    return cpu->read_half(address);
}
static inline void fm_native_write_half(CPUState *cpu, uint32_t address, uint16_t value)
{
    uint8_t *p = fm_native_ram_ptr(address, 2u);
    if (p && cpu->write_half == fm_memory_write_half
        && !fm_native_watched(address, 2u)) {
        fm_ram_store16(p, value);
        return;
    }
    cpu->write_half(address, value);
}

static inline uint8_t fm_native_read_byte(CPUState *cpu, uint32_t address)
{
    uint8_t *p = fm_native_ram_ptr(address, 1u);
    if (p && cpu->read_byte == fm_memory_read_byte) return *p;
    return cpu->read_byte(address);
}
static inline void fm_native_write_byte(CPUState *cpu, uint32_t address, uint8_t value)
{
    uint8_t *p = fm_native_ram_ptr(address, 1u);
    if (p && cpu->write_byte == fm_memory_write_byte
        && !fm_native_watched(address, 1u)) {
        *p = value;
        return;
    }
    cpu->write_byte(address, value);
}

/* Generated loads use cycle helpers even in a build without detailed guest
 * cycles. Never bypass their interlocks in a PSX_ENABLE_BLOCK_CYCLES build.
 * GNU expression blocks evaluate all four original arguments exactly once.
 * The original helper declaration is provided by the generated source's
 * runtime header before these macros are expanded. */
#ifdef PSX_ENABLE_BLOCK_CYCLES
#define fm_native_cyc_load_word psx_cyc_load_word
#define fm_native_cyc_load_half psx_cyc_load_half
#define fm_native_cyc_load_byte psx_cyc_load_byte
#else
#define FM_NATIVE_CYC_LOAD(kind, width, load, c, a, r, m) \
    __extension__ ({ \
        CPUState *_fm_c = (c); uint32_t _fm_a = (a); \
        uint32_t _fm_r = (r), _fm_m = (m); \
        uint8_t *_fm_p = fm_native_ram_ptr(_fm_a, width); \
        _fm_p && _fm_c->read_##kind == fm_memory_read_##kind \
            ? (load) : psx_cyc_load_##kind(_fm_c, _fm_a, _fm_r, _fm_m); \
    })
#define fm_native_cyc_load_word(c, a, r, m) \
    FM_NATIVE_CYC_LOAD(word, 4u, fm_ram_load32(_fm_p), c, a, r, m)
#define fm_native_cyc_load_half(c, a, r, m) \
    FM_NATIVE_CYC_LOAD(half, 2u, fm_ram_load16(_fm_p), c, a, r, m)
#define fm_native_cyc_load_byte(c, a, r, m) \
    FM_NATIVE_CYC_LOAD(byte, 1u, *_fm_p, c, a, r, m)
#endif

#endif
