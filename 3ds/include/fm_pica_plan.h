#ifndef FM_PICA_PLAN_H
#define FM_PICA_PLAN_H
#include <stdint.h>
#include <string.h>
typedef struct FMPicaVertex {float x,y,u,v,r,g,b,a;} FMPicaVertex;
typedef struct FMPicaPlan {
 FMPicaVertex vertex[4];unsigned count;int textured,raw;
 uint16_t page,clut;int left,top,right,bottom;
} FMPicaPlan;
int fm_pica_plan(FMPicaPlan *out,const uint32_t *p,unsigned words,uint16_t page,
 uint32_t window,int mask_set,int mask_check,int left,int top,int right,int bottom,int ox,int oy);
/* PICA RGBA8 is ABGR in little-endian memory. Alpha encodes PS1 bit15;
 * 128=opaque/unmasked, 255=opaque/masked, 0=transparent texture texel only. */
static inline uint32_t fm_pica_rgba(uint16_t p,int texture)
{ return texture && !p ? 0u : ((uint32_t)(p&31)<<27)|((uint32_t)((p>>5)&31)<<19)
 |((uint32_t)((p>>10)&31)<<11)|((p&0x8000)?255u:128u); }
static inline uint16_t fm_pica_psx(uint32_t p)
{ return (uint16_t)(((p>>27)&31)|(((p>>19)&31)<<5)|(((p>>11)&31)<<10)
 |((p&255)>=192?0x8000:0)); }
static inline unsigned fm_pica_morton(unsigned x,unsigned y,unsigned width)
{unsigned xx=x&7,yy=y&7;return ((y>>3)*(width>>3)+(x>>3))*64
 |(xx&1)|((yy&1)<<1)|((xx&2)<<1)|((yy&2)<<2)|((xx&4)<<2)|((yy&4)<<3);}
static inline uint16_t fm_pica_texel(const uint16_t *ram,uint16_t page,uint16_t clut,unsigned u,unsigned v)
{unsigned depth=(page>>7)&3,tx=(page&15)*64,ty=(page&16)*16;
 unsigned x=(tx+(u>>(2-depth)))&1023,y=(ty+v)&511;
 uint16_t p=ram[y*1024+x];if(depth==2)return p;
 unsigned index=depth==0?(p>>((u&3)*4))&15:(p>>((u&1)*8))&255;
 return ram[((clut>>6)&511)*1024+(((clut&63)*16+index)&1023)];}
#endif
