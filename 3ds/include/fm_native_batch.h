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
/* B136.46: resident display-object traversal, animation and packet builders.
 * Keep 42538 as an outer boundary: its return updates the existing hand
 * packet lifetime/safety tracking. No boot, overlay, CD, BIOS or VSync PCs. */
static inline int fm_native_render_batch(uint32_t address) {
    uint32_t phys=address & 0x1fffffffu;
    return phys>=0x00040350u && phys<0x00042BE0u
        && phys!=0x00042538u;
}
static inline int fm_native_batchable(uint32_t address) {
    return fm_native_object_batch(address) || fm_native_render_batch(address);
}
#endif
