/* Experimental PS1 GP0 -> PICA200 rasterizer. CPU VRAM is serialized at every
 * consumer boundary. Never submit the same primitive to both rasterizers. */
#include <3ds.h>
#include <citro3d.h>
#include <stdio.h>
#include <string.h>
#include "fm_pica.h"
#include "fm_pica_plan.h"
#include "fm_pica_shbin.h"
#include "gpu_vram_dirty.h"
#define WIDTH 1024
#define HEIGHT 512
#define IMAGE_BYTES (WIDTH*HEIGHT*4u)
#define CACHE_COUNT 8
#define BATCH_LIMIT 256
static uint16_t *ram;
static C3D_RenderTarget *target;
static DVLB_s *dvlb;
static shaderProgram_s program;
static uint32_t *seed,*readback;
static int initialized,attempted,active,target_valid;
int g_fm_pica_enabled;
static uint32_t selftest_center,selftest_mirror;
static unsigned selftest_red_pixels;
static uint32_t selftest_seed_top,selftest_seed_bottom;
static int selftest_seed_ok;
static unsigned commands;
static int selftest;
static int dx0,dy0,dx1,dy1;
static uint64_t draws,flushes,uploads,downloads,fallbacks,texture_uploads,feedback;
typedef struct Texture {C3D_Tex tex;uint16_t page,clut;int valid,allocated;} Texture;
static Texture cache[CACHE_COUNT];
static int run_selftest(void);
static void invalidate_cache(void){for(unsigned i=0;i<CACHE_COUNT;i++)cache[i].valid=0;}
void fm_pica_sync(void)
{
 if(!active)return;
 C3D_FrameEnd(GX_CMDLIST_FLUSH);C3D_FrameSync();active=0;commands=0;++flushes;invalidate_cache();
 /* Untile into top-down CPU RGBA8 without a second vertical flip. GPU finish
  * and cache invalidate precede every CPU read; no texture/vertex reuse race. */
 C3D_SyncDisplayTransfer((u32*)target->frameBuf.colorBuf,GX_BUFFER_DIM(WIDTH,HEIGHT),
  readback,GX_BUFFER_DIM(WIDTH,HEIGHT),GX_TRANSFER_FLIP_VERT(0)|GX_TRANSFER_OUT_TILED(0)
  |GX_TRANSFER_IN_FORMAT(GX_TRANSFER_FMT_RGBA8)|GX_TRANSFER_OUT_FORMAT(GX_TRANSFER_FMT_RGBA8)
  |GX_TRANSFER_SCALING(GX_TRANSFER_SCALE_NO));
 GSPGPU_InvalidateDataCache(readback,IMAGE_BYTES);downloads+=IMAGE_BYTES;
 if(dx0<=dx1&&dy0<=dy1){
  for(int y=dy0;y<=dy1;y++)for(int x=dx0;x<=dx1;x++)ram[y*WIDTH+x]=fm_pica_psx(readback[y*WIDTH+x]);
  gpu_vram_dirty_mark_rect(dx0,dy0,dx1-dx0+1,dy1-dy0+1);
 }
}
void fm_pica_cpu_write(void)
{if(!initialized)return;fm_pica_sync();target_valid=0;invalidate_cache();}
void fm_pica_exit(void)
{
 fm_pica_sync();
 if(initialized){
  for(unsigned i=0;i<CACHE_COUNT;i++)if(cache[i].allocated)C3D_TexDelete(&cache[i].tex);
  if(target)C3D_RenderTargetDelete(target);
  shaderProgramFree(&program);if(dvlb)DVLB_Free(dvlb);
  linearFree(seed);linearFree(readback);C3D_Fini();
 }
 memset(cache,0,sizeof cache);target=NULL;seed=readback=NULL;dvlb=NULL;
 initialized=attempted=active=target_valid=g_fm_pica_enabled=0;ram=NULL;
}
int fm_pica_init(uint16_t *vram)
{
 if(initialized){fm_pica_cpu_write();ram=vram;return 1;}
 if(attempted||!vram)return 0;
 attempted=1;
 if(!C3D_Init(0x100000))return 0;
 initialized=1;ram=vram;shaderProgramInit(&program);
 dvlb=DVLB_ParseFile((u32*)fm_pica_shbin,fm_pica_shbin_size);
 target=C3D_RenderTargetCreate(WIDTH,HEIGHT,GPU_RB_RGBA8,-1);
 seed=linearAlloc(IMAGE_BYTES);readback=linearAlloc(IMAGE_BYTES);
 if(!dvlb||!target||!seed||!readback){fm_pica_exit();attempted=1;return 0;}
 shaderProgramSetVsh(&program,&dvlb->DVLE[0]);
 for(unsigned i=0;i<CACHE_COUNT;i++){
  if(!C3D_TexInit(&cache[i].tex,256,256,GPU_RGBA8)){fm_pica_exit();attempted=1;return 0;}
  cache[i].allocated=1;C3D_TexSetFilter(&cache[i].tex,GPU_NEAREST,GPU_NEAREST);
  C3D_TexSetWrap(&cache[i].tex,GPU_REPEAT,GPU_REPEAT);
 }
 if(!run_selftest()){fm_pica_exit();attempted=1;return 0;}
 selftest=1;g_fm_pica_enabled=1;draws=flushes=uploads=downloads=fallbacks=texture_uploads=feedback=0;
 return 1;
}
static int begin(void)
{
 if(active)return 1;
 if(!target_valid){
  for(unsigned y=0;y<HEIGHT;y++)for(unsigned x=0;x<WIDTH;x++)
   seed[fm_pica_morton(x,y,WIDTH)]=fm_pica_rgba(ram[y*WIDTH+x],0);
  GSPGPU_FlushDataCache(seed,IMAGE_BYTES);
  C3D_SyncTextureCopy(seed,0,(u32*)target->frameBuf.colorBuf,0,IMAGE_BYTES,8);
  uploads+=IMAGE_BYTES;target_valid=1;
 }
 if(!C3D_FrameBegin(C3D_FRAME_SYNCDRAW))return 0;
 C3D_FrameDrawOn(target);C3D_BindProgram(&program);
 C3D_SetViewport(0,0,WIDTH,HEIGHT);
 C3D_AttrInfo *a=C3D_GetAttrInfo();AttrInfo_Init(a);
 AttrInfo_AddLoader(a,0,GPU_FLOAT,4);AttrInfo_AddLoader(a,1,GPU_FLOAT,4);AttrInfo_AddLoader(a,2,GPU_FLOAT,4);
 C3D_CullFace(GPU_CULL_NONE);C3D_DepthTest(false,GPU_ALWAYS,GPU_WRITE_COLOR);
 C3D_AlphaBlend(GPU_BLEND_ADD,GPU_BLEND_ADD,GPU_ONE,GPU_ZERO,GPU_ONE,GPU_ZERO);
 C3D_AlphaTest(false,GPU_ALWAYS,0);
 for(unsigned i=0;i<6;i++)C3D_TexEnvInit(C3D_GetTexEnv(i));
 dx0=WIDTH;dy0=HEIGHT;dx1=dy1=-1;commands=0;active=1;return 1;
}
static int intersects(int l,int t,int r,int b)
{return active&&l<=dx1&&r>=dx0&&t<=dy1&&b>=dy0;}
static Texture *texture(uint16_t page,uint16_t clut)
{
 unsigned tx=(page&15)*64,ty=(page&16)*16,width=64u<<((page>>7)&3);
 unsigned cx=(clut&63)*16,cy=(clut>>6)&511,colors=((page>>7)&3)==0?16:256;
 if(tx+width>1024 || cx+colors>1024){ /* wrapped reads: conservative dependency barrier */
  if(active){fm_pica_sync();invalidate_cache();++feedback;}
 }else if(intersects(tx,ty,tx+width-1,ty+255)
  || (((page>>7)&3)<2 && intersects(cx,cy,cx+colors-1,cy))){
  fm_pica_sync();invalidate_cache();++feedback;
 }
 Texture *slot=NULL;
 for(unsigned i=0;i<CACHE_COUNT;i++){
  if(cache[i].valid&&cache[i].page==page&&cache[i].clut==clut)return &cache[i];
  if(!cache[i].valid)slot=&cache[i];
 }
 if(!slot){fm_pica_sync();invalidate_cache();slot=&cache[0];}
 uint32_t *data=slot->tex.data;
 for(unsigned y=0;y<256;y++)for(unsigned x=0;x<256;x++)
  data[fm_pica_morton(x,255-y,256)]=fm_pica_rgba(fm_pica_texel(ram,page,clut,x,y),1);
 C3D_TexFlush(&slot->tex);slot->page=page;slot->clut=clut;slot->valid=1;++texture_uploads;
 return slot;
}
static void pica_send_vertex(const FMPicaVertex *v)
{
 C3D_ImmSendAttrib(v->x/512.0f-1.0f,1.0f-v->y/256.0f,-0.5f,1.0f);
 C3D_ImmSendAttrib(v->u/256.0f,1.0f-v->v/256.0f,0,1);
 C3D_ImmSendAttrib(v->r,v->g,v->b,v->a);
}
int fm_pica_draw(const uint32_t *p,unsigned words,uint16_t page,uint32_t window,
 int mask_set,int mask_check,int left,int top,int right,int bottom,int ox,int oy)
{
 if(!initialized)return 0;
 unsigned op=p[0]>>24;if(op<0x20u||op>0x7fu)return 0;
 FMPicaPlan q;
 if(!fm_pica_plan(&q,p,words,page,window,mask_set,mask_check,left,top,right,bottom,ox,oy)){
  ++fallbacks;return 0;
 }
 if(active&&(commands>=BATCH_LIMIT||C3D_GetCmdBufUsage()>0.65f))fm_pica_sync();
 Texture *tex=q.textured?texture(q.page,q.clut):NULL;
 if(!begin()){++fallbacks;return 0;}
 C3D_SetScissor(GPU_SCISSOR_NORMAL,q.left,HEIGHT-1-q.bottom,q.right+1,HEIGHT-q.top);
 C3D_TexEnv *e=C3D_GetTexEnv(0);C3D_TexEnvInit(e);
 C3D_AlphaTest(q.textured!=0,GPU_GREATER,0);
 if(q.textured){
  C3D_TexBind(0,&tex->tex);
  C3D_TexEnvSrc(e,C3D_RGB,GPU_TEXTURE0,GPU_PRIMARY_COLOR,0);
  C3D_TexEnvFunc(e,C3D_RGB,q.raw?GPU_REPLACE:GPU_MODULATE);
  C3D_TexEnvScale(e,C3D_RGB,q.raw?GPU_TEVSCALE_1:GPU_TEVSCALE_2);
  C3D_TexEnvSrc(e,C3D_Alpha,GPU_TEXTURE0,0,0);C3D_TexEnvFunc(e,C3D_Alpha,GPU_REPLACE);
 }else{
  C3D_TexEnvSrc(e,C3D_Both,GPU_PRIMARY_COLOR,0,0);C3D_TexEnvFunc(e,C3D_Both,GPU_REPLACE);
 }
 C3D_ImmDrawBegin(GPU_TRIANGLES);pica_send_vertex(&q.vertex[0]);pica_send_vertex(&q.vertex[1]);pica_send_vertex(&q.vertex[2]);
 if(q.count==4){pica_send_vertex(&q.vertex[1]);pica_send_vertex(&q.vertex[3]);pica_send_vertex(&q.vertex[2]);}
 C3D_ImmDrawEnd();
 /* Conservative dirty/dependency bound. Exact coverage is produced by PICA. */
 if(q.left<dx0)dx0=q.left;
 if(q.top<dy0)dy0=q.top;
 if(q.right>dx1)dx1=q.right;
 if(q.bottom>dy1)dy1=q.bottom;
 ++commands;++draws;return 1;
}
/* Validate shader, transfer orientation, RGBA order and alpha-bit packing on
 * the actual GPU. Restore the only CPU rectangle touched, even on failure. */
static int run_selftest(void)
{
 uint16_t saved[64];
 for(unsigned y=0;y<8;y++)memcpy(saved+y*8,ram+(16+y)*WIDTH+16,16);
 /* Asymmetric seed markers verify upload/untile row order independently of
  * the shader draw, including RGB555 bit15. Both CPU words are restored. */
 const unsigned upper=91u*WIDTH+7u,lower=433u*WIDTH+1001u;
 uint16_t old_upper=ram[upper],old_lower=ram[lower];
 ram[upper]=0x8352u;ram[lower]=0x24adu;
 uint32_t p[]={0x600000ffu,16u|(16u<<16),8u|(8u<<16)};
 int ok=fm_pica_draw(p,3,0,0,0,0,16,16,23,23,0,0);
 fm_pica_sync();
 selftest_center=readback[20*WIDTH+20];
 selftest_mirror=readback[(HEIGHT-1-20)*WIDTH+20];
 selftest_seed_top=readback[upper];selftest_seed_bottom=readback[lower];
 selftest_seed_ok=fm_pica_psx(selftest_seed_top)==0x8352u
     && fm_pica_psx(selftest_seed_bottom)==0x24adu;
 if(!selftest_seed_ok)ok=0;
 for(unsigned i=0;i<WIDTH*HEIGHT;i++)if((readback[i]&0xffffff00u)==0xff000000u)++selftest_red_pixels;
 for(unsigned y=0;y<8;y++)for(unsigned x=0;x<8;x++)
  if(ram[(16+y)*WIDTH+16+x]!=31u)ok=0;
 for(unsigned y=0;y<8;y++)memcpy(ram+(16+y)*WIDTH+16,saved+y*8,16);
 ram[upper]=old_upper;ram[lower]=old_lower;
 target_valid=0;invalidate_cache();return ok;
}
void fm_pica_status_dump(void)
{
 FILE *f=fopen("sdmc:/3ds/fm-new3ds/pica-status.txt","w");if(!f)return;
 fprintf(f,"probe=B136.68 renderer=pica200-experiment initialized=%d selftest=%d\n"
  "draws=%llu fallback=%llu batches=%llu texture_uploads=%llu feedback_barriers=%llu\n"
  "seed_bytes=%llu readback_bytes=%llu\nselftest_center=%08lX mirror=%08lX red_pixels=%u\nseed_top=%08lX seed_bottom=%08lX seed_ok=%d\n",initialized,selftest,
  (unsigned long long)draws,(unsigned long long)fallbacks,(unsigned long long)flushes,
  (unsigned long long)texture_uploads,(unsigned long long)feedback,
  (unsigned long long)uploads,(unsigned long long)downloads,
  (unsigned long)selftest_center,(unsigned long)selftest_mirror,selftest_red_pixels,
  (unsigned long)selftest_seed_top,(unsigned long)selftest_seed_bottom,selftest_seed_ok);fclose(f);
}
