"""Differential sprite rendering against B136.38, including live VRAM aliasing."""
from pathlib import Path
import os,re,subprocess,tempfile,unittest
from test_gpu_perf_window_host import function
ROOT=Path(__file__).resolve().parents[1]
class SpriteFastTests(unittest.TestCase):
 def test_pixels(self):
  s=(ROOT/'3ds/source/fm_gpu.c').read_text()
  ctx=s[s.index('typedef struct B13512TexCtx'):s.index('} B13512TexCtx;')+len('} B13512TexCtx;')]
  funcs='\n'.join(function(s,n) for n in ('b124_vram_get','b13512_texctx','b13512_fetch_texel_ctx','b124_blend','b13639_sprite_span','b124_try_textured_rect'))
  baseline=(ROOT/'tests/host/sprite_b13638_reference.c').read_text()
  decl=[]
  for name in sorted(set(re.findall(r'\bg_[a-zA-Z0-9_]+',funcs+baseline))):
   if name=='g_vram':continue
   m=re.search(r'static\s+(\w+)\s+(?:[^;\n]*,\s*)?'+name+r'(\[[^\]]+\])?',s);assert m,name
   decl.append('static __attribute__((unused)) '+m[1]+' '+name+(m[2] or '')+';')
  code='''#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <assert.h>
static uint16_t ram[524288],initial[524288],expected[524288];
static uint16_t *g_vram=ram;
static int sw_renderer_scale(void){return 1;}
static int sw_wide_width(void){return 0;}
static int sw_texture_filter(void){return 0;}
'''+ '\n'.join(decl)+'\n'+(ROOT/'3ds/include/fm_modulate_lut.h').read_text()+ctx+'\n'+funcs+'\n'+baseline+'''
static uint32_t rng=13639;
static uint32_t rnd(void){rng=rng*1664525u+1013904223u;return rng;}
int main(int argc,char **argv){(void)argv;
 for(unsigned j=0;j<524288;++j)initial[j]=(uint16_t)rnd();
 for(unsigned j=0;j<1024;++j){initial[256*1024+j]=j%3==0?0:j%3==1?0x8000:(uint16_t)rnd();}
 for(unsigned i=0;i<700;++i){
  int x=(int)(rnd()%400)-40,y=(int)(rnd()%300)-20;
  int w=rnd()%330,h=rnd()%270,u=rnd()%256,v=rnd()%256;
  int clx=rnd()%1024,cly=(i%3==0)?y&511:rnd()%512;
  uint16_t page=(uint16_t)((i%4)<<7 | (rnd()&31));
  uint8_t op=(uint8_t)(0x64+(i%4));int raw=i%4==1;
  uint32_t color=i%5==0?0x808080:rnd()&0xffffff;
  g_draw_x1=0;g_draw_y1=0;g_draw_x2=319;g_draw_y2=255;
  g_mask_set=i%11==0;g_mask_check=i%13==0;
  g_texture_window=i%17==0?rnd()&0xfffff:0;
  memcpy(ram,initial,sizeof(ram));g_b124_rect_pixels=g_b124_rect_texels=0;
  reference_rect(op,x,y,w,h,u,v,clx,cly,page,color,raw);
  uint64_t pixels=g_b124_rect_pixels,texels=g_b124_rect_texels;
  memcpy(expected,ram,sizeof(ram));memcpy(ram,initial,sizeof(ram));
  g_b124_rect_pixels=g_b124_rect_texels=0;
  b124_try_textured_rect(op,x,y,w,h,u,v,clx,cly,page,color,raw);
  assert(!memcmp(ram,expected,sizeof(ram)));
  assert(pixels==g_b124_rect_pixels && texels==g_b124_rect_texels);
 }
 if(argc>1){
  g_texture_window=g_mask_check=g_mask_set=0;
  for(unsigned depth=0;depth<3;++depth)for(unsigned neutral=0;neutral<2;++neutral){
   uint32_t color=neutral?0x808080:0xC09060;
   clock_t a=clock();for(unsigned n=0;n<500;++n)reference_rect(0x64,0,0,200,100,0,0,512,300,(uint16_t)(16|(depth<<7)),color,0);
   clock_t b=clock();for(unsigned n=0;n<500;++n)b124_try_textured_rect(0x64,0,0,200,100,0,0,512,300,(uint16_t)(16|(depth<<7)),color,0);
   clock_t c=clock();printf("sprite depth=%u neutral=%u before_ms=%.2f after_ms=%.2f ratio=%.2f\\n",depth,neutral,(b-a)*1000.0/CLOCKS_PER_SEC,(c-b)*1000.0/CLOCKS_PER_SEC,(double)(b-a)/(c-b));
  }
 }
 return 0;
}
'''
  with tempfile.TemporaryDirectory() as tmp:
   p=Path(tmp)/'sprite.c';p.write_text(code)
   for profile in (0,1):
    exe=Path(tmp)/str(profile)
    subprocess.run(['cc','-O2','-std=c11','-Wall','-Werror',f'-DFM_PERF_PROFILE={profile}',str(p),'-o',str(exe)],check=True)
    subprocess.run([str(exe)]+(['bench'] if profile==0 and os.getenv('FM_GPU_HOST_BENCHMARK') else []),check=True)
