"""Production Unai adapter: pixel comparisons, fallback atomicity and restore.

The x86 C++ implementation is tested here; ARM assembly is compile/link checked
by the devkitARM workflow. These timings are not New3DS or Azahar FPS.
"""
from pathlib import Path
import os, re, subprocess, tempfile, unittest
from test_gpu_perf_window_host import function
ROOT=Path(__file__).resolve().parents[1]

class UnaiHostTests(unittest.TestCase):
 def test_render_and_fallback(self):
  s=(ROOT/'3ds/source/fm_gpu.c').read_text()
  ctx=s[s.index('typedef struct B13512TexCtx'):s.index('} B13512TexCtx;')+len('} B13512TexCtx;')]
  funcs='\n'.join(function(s,n) for n in ('b124_vram_get','b13512_texctx',
   'b13512_fetch_texel_ctx','b124_blend','b13639_sprite_span','b124_try_textured_rect',
   'b125_put_textured','b13513_grad_fp16','b13513_edge_fp16',
   'b13636_neutral_span','b13637_shaded_span','b13511_shaded_textured_triangle'))
  decl=[]
  for name in sorted(set(re.findall(r'\bg_[a-zA-Z0-9_]+',funcs))):
   if name=='g_vram':continue
   m=re.search(r'static\s+(\w+)\s+(?:[^;\n]*,\s*)?'+name+r'(\[[^\]]+\])?',s)
   if not m:continue # Local gradient variables, not file-scope counters.
   decl.append('static '+m[1]+' '+name+(m[2] or '')+';')
  code=r'''#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <assert.h>
#include "fm_unai.h"
static uint16_t ram[524288],initial[524288],expected[524288],restored[524288];
static uint16_t *g_vram=ram;
static int sw_renderer_scale(void){return 1;}
static int sw_wide_width(void){return 0;}
static int sw_texture_filter(void){return 0;}
'''+'\n'.join(decl)+'\n'+(ROOT/'3ds/include/fm_modulate_lut.h').read_text()+ctx+'\n'+funcs+r'''
static uint32_t rng=13644;
static uint32_t rnd(void){rng=rng*1664525u+1013904223u;return rng;}
static uint32_t xy(int x,int y){return (uint16_t)x|((uint32_t)(uint16_t)y<<16);}
static int draw(uint32_t *p,unsigned n,uint16_t page){
 return fm_unai_draw(ram,p,n,page,0,0,0,0,0,319,255,0,0);
}
int main(int argc,char **argv){(void)argv;
 for(unsigned j=0;j<524288;++j)initial[j]=(uint16_t)rnd();
 for(unsigned j=0;j<256;++j)initial[300*1024+512+j]=j%5==0?0:(uint16_t)rnd();
 g_draw_x1=0;g_draw_y1=0;g_draw_x2=319;g_draw_y2=255;
 /* No aliasing: texture at x=640, CLUT y=300. Exercise UV wrapping,
    clipping, raw/neutral/modulated sprites and all three bit depths. */
 for(unsigned i=0;i<240;++i){
  int x=(int)(rnd()%340)-20,y=(int)(rnd()%275)-20;
  int w=rnd()%280,h=rnd()%200,u=rnd()%256,v=rnd()%256;
  uint16_t page=10|((i%3)<<7);
  uint32_t color=i%5==0?0x808080:rnd()&0xffffff;
  unsigned op=0x64+(i%2),clut=(300<<6)|(512>>4);
  uint32_t p[]={op<<24|color,xy(x,y),u|(v<<8)|(clut<<16),xy(w,h)};
  memcpy(ram,initial,sizeof(ram));
  assert(b124_try_textured_rect(op,x,y,w,h,u,v,512,300,page,color,i%2));
  memcpy(expected,ram,sizeof(ram)); memcpy(ram,initial,sizeof(ram));
  assert(draw(p,4,page));
  for(unsigned j=0;j<524288;++j) {
   /* Unai preserves source bit15; current native opaque path clears it.
      RGB555 and every untouched pixel must otherwise match exactly. */
   assert((ram[j]&0x7fff)==(expected[j]&0x7fff));
   if(j/1024>255 || j%1024>319) assert(ram[j]==initial[j]);
  }
 }
 /* Every rejected case must leave all VRAM unchanged. */
 uint32_t p[]={0x64808080,xy(0,0),(300u<<22)|(32u<<16),xy(32,32)};
 memcpy(ram,initial,sizeof(ram));
 assert(!fm_unai_draw(ram,p,4,10,1,0,0,0,0,319,255,0,0));
 assert(!fm_unai_draw(ram,p,4,10,0,1,0,0,0,319,255,0,0));
 assert(!fm_unai_draw(ram,p,4,10,0,0,1,0,0,319,255,0,0));
 assert(!draw(p,3,10)); assert(!draw(p,4,0)); // aliases framebuffer
 assert(!draw(p,4,15|(2<<7))); // horizontal texture wrapping
 assert(!draw(p,4,10|(3<<7))); // reserved texture depth
 assert(!memcmp(ram,initial,sizeof(ram)));
 /* Environment is rebound on every call, including a restored VRAM pointer
    and second framebuffer at x=320. */
 memset(restored,0,sizeof(restored));
 memcpy(restored,initial,sizeof(initial));
 assert(fm_unai_draw(restored,p,4,10,0,0,0,320,0,639,255,320,0));
 assert(!memcmp(ram,initial,sizeof(ram)));
 assert(restored[320]!=initial[320]);
 /* Raw textured quad, constant source: both triangles, exact clip bounds. */
 for(unsigned j=0;j<524288;++j)ram[j]=0;
 for(unsigned y=256;y<512;++y)for(unsigned x=640;x<896;++x)ram[y*1024+x]=0x1234;
 uint16_t page=10|16|(2<<7);
 uint32_t q[]={0x3d808080,xy(10,10),0,0x808080,xy(50,10),(uint32_t)page<<16,
  0x808080,xy(10,50),0,0x808080,xy(50,50),0};
 assert(draw(q,12,page));
 unsigned written=0;
 for(unsigned y=0;y<256;++y)for(unsigned x=0;x<320;++x){
  if(ram[y*1024+x]){assert(x>=10&&x<50&&y>=10&&y<50);assert(ram[y*1024+x]==0x1234);++written;}
 }
 assert(written==1600);
 /* Gouraud and transparency paths: no writes outside drawing area. */
 q[0]=0x3c404040;q[3]=0xffffff;q[6]=0x808080;q[9]=0xc0c0c0;
 assert(draw(q,12,page));q[0]=0x3e808080;assert(draw(q,12,page));
 q[0]=0x34808080;assert(draw(q,9,page));
 q[0]=0x36808080;assert(draw(q,9,page));
 if(argc>1){
  memcpy(ram,initial,sizeof(ram));
  for(unsigned depth=0;depth<3;++depth){
   uint16_t pg=10|16|(depth<<7);
   uint32_t sp[]={0x64c09060,0,((300<<6)|32)<<16,xy(200,100)};
   clock_t a=clock();for(unsigned n=0;n<500;++n)b124_try_textured_rect(0x64,0,0,200,100,0,0,512,300,pg,0xc09060,0);
   clock_t b=clock();for(unsigned n=0;n<500;++n)draw(sp,4,pg);
   clock_t c=clock();printf("unai sprite depth=%u native_ms=%.2f unai_ms=%.2f ratio=%.2f\n",depth,(b-a)*1000.0/CLOCKS_PER_SEC,(c-b)*1000.0/CLOCKS_PER_SEC,(double)(b-a)/(c-b));
  }
  for(unsigned depth=0;depth<3;++depth){
   uint16_t pg=10|16|(depth<<7); unsigned cl=(300<<6)|32;
   uint32_t qp[]={0x3c404060,xy(0,0),cl<<16,0xe0a080,xy(128,0),(uint32_t)pg<<16|127,
    0x60d040,xy(0,128),127<<8,0xc080d0,xy(128,128),127<<8|127};
   clock_t a=clock();for(unsigned n=0;n<300;++n){
    b13511_shaded_textured_triangle(0,0,0,0,0x404060,128,0,127,0,0xe0a080,0,128,0,127,0x60d040,512,300,pg,0,0);
    b13511_shaded_textured_triangle(128,0,127,0,0xe0a080,0,128,0,127,0x60d040,128,128,127,127,0xc080d0,512,300,pg,0,0);
   }
   clock_t b=clock();for(unsigned n=0;n<300;++n)draw(qp,12,pg);
   clock_t c=clock();printf("unai quad depth=%u native_ms=%.2f unai_ms=%.2f ratio=%.2f\n",depth,(b-a)*1000.0/CLOCKS_PER_SEC,(c-b)*1000.0/CLOCKS_PER_SEC,(double)(b-a)/(c-b));
  }
 }
 return 0;
}
'''
  with tempfile.TemporaryDirectory() as tmp:
   p=Path(tmp)/'harness.c';p.write_text(code);obj=Path(tmp)/'harness.o';exe=Path(tmp)/'unai'
   subprocess.run(['cc','-O2','-DFM_PERF_PROFILE=0','-I'+str(ROOT/'3ds/include'),'-c',str(p),'-o',str(obj)],check=True)
   subprocess.run(['g++','-O3','-DNDEBUG','-std=gnu++11','-fno-strict-aliasing',
    '-I'+str(ROOT/'3ds/include'),'-I'+str(ROOT/'3ds/source/unai'),str(ROOT/'3ds/source/fm_unai.cpp'),str(obj),'-o',str(exe)],check=True)
   subprocess.run([str(exe)]+(['bench'] if os.getenv('FM_GPU_HOST_BENCHMARK') else []),check=True)
