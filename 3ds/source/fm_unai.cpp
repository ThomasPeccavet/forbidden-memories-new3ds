/* B136.44: bounded Unai experiment. Rendering only; no emulated clocks,
 * CD callbacks, GP0 parser or presentation state belong to this backend.
 * Unai headers/assembly retain their original GPL-2.0-or-later notices. */
#include "fm_unai.h"
#include <stddef.h>
#include <string.h>
#include "unai/arm_features.h"
#define USE_GPULIB 1
#define GPU_UNAI_NO_OLD 1
#define GPU_UNAI_USE_FLOATMATH 1
#define GPU_UNAI_USE_FLOAT_DIV_MULTINV 1
#if __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__
#error This adapter targets little-endian New3DS and host tests
#endif
#define HTOLE16(x) (x)
#define HTOLE32(x) (x)
#define LE16TOH(x) (x)
#define LE32TOH(x) (x)
#include "unai/gpu_unai.h"
#include "unai/gpu_fixedpoint.h"
#include "unai/gpu_inner.h"
#include "unai/gpu_raster_polygon.h"
#include "unai/gpu_raster_sprite.h"
#include "unai/gpu_command.h"

#ifdef __arm__
/* gpu_arm.S reads these offsets directly. Catch ABI drift at ARM build time. */
static_assert(offsetof(gpu_unai_inner_t,u)==0x08,"Unai ARM UV ABI");
static_assert(offsetof(gpu_unai_inner_t,r5)==0x20,"Unai ARM sprite light ABI");
static_assert(offsetof(gpu_unai_inner_t,gCol)==0x28,"Unai ARM Gouraud ABI");
static_assert(offsetof(gpu_unai_inner_t,PixelData)==0x38,"Unai ARM pixel ABI");
#endif

static bool initialized;
static uint32_t sprite_calls, polygon_calls, fallbacks;
static bool overlaps(int x, int y, int w, int h,
    int left, int top, int right, int bottom)
{
    return x <= right && x+w > left && y <= bottom && y+h > top;
}

extern "C" int fm_unai_draw(uint16_t *vram, const uint32_t *p, unsigned words,
    uint16_t page, uint32_t window, int mask_set, int mask_check,
    int left, int top, int right, int bottom, int ox, int oy)
{
    if (!vram || !p || !words) return 0;
    unsigned op=p[0]>>24, family=op&0xfc;
    unsigned expected=family==0x64 ? 4 : family==0x34 ? 9 : family==0x3c ? 12 : 0;
    if (!expected) return 0;
    if (words!=expected) { ++fallbacks; return 0; }
    if (family!=0x64) page=(uint16_t)(p[5]>>16);
    unsigned depth=(page>>7)&3;
    int tx=(page&15)*64, ty=(page&16)*16;
    int tw=depth==0 ? 64 : depth==1 ? 128 : 256;
    unsigned clut=p[2]>>16;
    int cx=(clut&63)*16, cy=(clut>>6)&511;
    int cw=depth==0 ? 16 : 256;
    /* Assembly can read several source pixels before writing a destination.
     * Keep live aliasing, wrapping textures/CLUTs, windows, mask operations
     * and coordinate overflow on the established renderer for this trial. */
    bool unsafe=window || mask_set || mask_check || depth==3 || tx+tw>1024
        || (depth<2 && cx+cw>1024) || left<0 || top<0 || right>1023
        || bottom>511 || right<left || bottom<top
        || overlaps(tx,ty,tw,256,left,top,right,bottom)
        || (depth<2 && overlaps(cx,cy,cw,1,left,top,right,bottom));
    if (family==0x64)
        unsafe |= (p[3]&0xffff)>1023 || (p[3]>>16)>511;
    for (unsigned i=0; i<(family==0x64 ? 1u : family==0x34 ? 3u : 4u); ++i) {
        uint32_t xy=p[1+i*3];
        int x=GPU_EXPANDSIGN((int16_t)xy)+ox;
        int y=GPU_EXPANDSIGN((int16_t)(xy>>16))+oy;
        unsafe |= x < -1024 || x > 1023 || y < -1024 || y > 1023;
    }
    if (unsafe) { ++fallbacks; return 0; }
    if (!initialized) {
        memset(&gpu_unai,0,sizeof(gpu_unai));
        gpu_unai.config.lighting=1;
        gpu_unai.config.blending=1;
        /* Match current port's no-dither policy; no pixel/line/frame skip. */
        gpu_unai.TextureWindow[2]=gpu_unai.TextureWindow[3]=255;
        gpu_unai.inn.mask_v00u=0xff0000ff;
        SetupLightLUT();
        SetupDitheringConstants();
        initialized=true;
    }
    gpu_unai.vram=vram;
    gpu_unai.DrawingArea[0]=left; gpu_unai.DrawingArea[1]=top;
    gpu_unai.DrawingArea[2]=right+1; gpu_unai.DrawingArea[3]=bottom+1;
    gpu_unai.DrawingOffset[0]=ox; gpu_unai.DrawingOffset[1]=oy;
    gpu_unai.GPU_GP1=page;
    gpuSetTexture(page);
    gpuSetCLUT(clut);
    memcpy(gpu_unai.PacketBuffer.U4,p,words*sizeof(uint32_t));
    PtrUnion packet={.ptr=(void*)&gpu_unai.PacketBuffer};
    unsigned idx=gpu_unai.TEXT_MODE | ((op&2) ? gpu_unai.BLEND_MODE|2 : 0);
    if (family==0x64) {
        if (!(op&1) && (p[0]&0xf8f8f8)!=0x808080) idx|=1;
        s32 w=0,h=0;
        gpuDrawS(packet,gpuSpriteDrivers[idx],&w,&h);
        ++sprite_calls;
    } else {
        if (!(op&1)) {
            idx|=129; // CF_LIGHT | CF_GOURAUD
            gpuDrawPolyGT(packet,gpuPolySpanDrivers[idx],family==0x3c);
        } else gpuDrawPolyFT(packet,gpuPolySpanDrivers[idx],family==0x3c,POLYTYPE_GT);
        ++polygon_calls;
    }
    return 1;
}

extern "C" void fm_unai_counts(uint32_t *s, uint32_t *p, uint32_t *f)
{
    *s=sprite_calls; *p=polygon_calls; *f=fallbacks;
}
