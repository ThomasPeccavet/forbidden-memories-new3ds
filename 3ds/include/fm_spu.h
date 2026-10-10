#ifndef FM_SPU_H
#define FM_SPU_H
#include <stdint.h>
#define FM_SPU_FRAME_SAMPLES 735u
void fm_spu_reset(void);
uint16_t fm_spu_reg_read(uint32_t address);
void fm_spu_reg_write(uint32_t address, uint16_t value);
uint16_t fm_spu_transfer_read(void);
void fm_spu_transfer_write(uint16_t value);
void fm_spu_render(int16_t *stereo, unsigned frames);
unsigned fm_spu_snapshot_bytes(void);
void fm_spu_snapshot_write(void *out);
int fm_spu_snapshot_valid(const void *in, unsigned bytes);
void fm_spu_snapshot_load(const void *in);
#endif
