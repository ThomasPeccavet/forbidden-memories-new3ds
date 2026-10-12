#ifndef FM_PICA_H
#define FM_PICA_H
#include <stdint.h>
#ifndef FM_GPU_PICA
#define FM_GPU_PICA 0
#endif
#if FM_GPU_PICA
int fm_pica_init(uint16_t *vram);
void fm_pica_exit(void);
/* Finish all queued rasterization before any CPU VRAM observation. */
void fm_pica_sync(void);
/* Also invalidate GPU copies before a CPU VRAM mutation or snapshot restore. */
void fm_pica_cpu_write(void);
int fm_pica_draw(const uint32_t *p,unsigned words,uint16_t page,uint32_t window,
 int mask_set,int mask_check,int left,int top,int right,int bottom,int ox,int oy);
void fm_pica_status_dump(void);
#else
static inline int fm_pica_init(uint16_t *vram){(void)vram;return 0;}
static inline void fm_pica_exit(void){}
static inline void fm_pica_sync(void){}
static inline void fm_pica_cpu_write(void){}
static inline void fm_pica_status_dump(void){}
#endif
#endif
