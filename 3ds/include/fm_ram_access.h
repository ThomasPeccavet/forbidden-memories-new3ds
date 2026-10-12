#ifndef FM_RAM_ACCESS_H
#define FM_RAM_ACCESS_H
#include <stdint.h>
#include <string.h>

/* B136.48: RAM callbacks are used by the recompiled core as well as HLE.
 * ARM11 must not perform unaligned LDR/STR: retain byte assembly there.
 * memcpy keeps aliasing valid; assume_aligned is used only after checking
 * the actual host pointer (fm_memory_init accepts arbitrary RAM storage). */
static inline uint32_t fm_ram_load32(const uint8_t *p)
{
    if (((uintptr_t)p & 3u) == 0u) {
        uint32_t value;
        memcpy(&value, __builtin_assume_aligned(p, 4), sizeof(value));
        return value;
    }
    return (uint32_t)p[0] | ((uint32_t)p[1] << 8)
        | ((uint32_t)p[2] << 16) | ((uint32_t)p[3] << 24);
}
static inline void fm_ram_store32(uint8_t *p, uint32_t value)
{
    if (((uintptr_t)p & 3u) == 0u) {
        memcpy(__builtin_assume_aligned(p, 4), &value, sizeof(value));
        return;
    }
    p[0] = (uint8_t)value; p[1] = (uint8_t)(value >> 8);
    p[2] = (uint8_t)(value >> 16); p[3] = (uint8_t)(value >> 24);
}
static inline uint16_t fm_ram_load16(const uint8_t *p)
{
    if (((uintptr_t)p & 1u) == 0u) {
        uint16_t value;
        memcpy(&value, __builtin_assume_aligned(p, 2), sizeof(value));
        return value;
    }
    return (uint16_t)p[0] | ((uint16_t)p[1] << 8);
}
static inline void fm_ram_store16(uint8_t *p, uint16_t value)
{
    if (((uintptr_t)p & 1u) == 0u) {
        memcpy(__builtin_assume_aligned(p, 2), &value, sizeof(value));
        return;
    }
    p[0] = (uint8_t)value; p[1] = (uint8_t)(value >> 8);
}


#endif
