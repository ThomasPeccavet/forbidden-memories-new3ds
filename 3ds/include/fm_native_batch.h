#ifndef FM_NATIVE_BATCH_H
#define FM_NATIVE_BATCH_H
#include <stdint.h>
/* Resident object/packet helpers. 85D98 is a main.c HLE boundary and
 * must not execute inside a native batch. Overlays and 81Axx waits stay out. */
static inline int fm_native_object_batch(uint32_t address) {
    uint32_t phys=address & 0x1fffffffu;
    return (phys>=0x00084018u && phys<0x00085D98u)
        || (phys>=0x00085D9Cu && phys<0x00089D60u);
}
#endif
