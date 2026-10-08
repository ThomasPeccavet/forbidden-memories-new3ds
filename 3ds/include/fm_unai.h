#pragma once
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif
/* Stateless frontend contract: environment is supplied for every packet,
 * including the first packet after quick-load. Return 0 without VRAM writes
 * when the bounded experimental backend cannot handle a command. */
int fm_unai_draw(uint16_t *vram, const uint32_t *packet, unsigned words,
    uint16_t page, uint32_t window, int mask_set, int mask_check,
    int left, int top, int right, int bottom, int offset_x, int offset_y);
void fm_unai_counts(uint32_t *sprites, uint32_t *polygons, uint32_t *fallbacks);
#ifdef __cplusplus
}
#endif
