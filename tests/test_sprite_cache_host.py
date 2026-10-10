"""Compare cached sprites to production Unai, including live VRAM mutations."""
from pathlib import Path
import subprocess, tempfile, unittest, os
ROOT = Path(__file__).resolve().parents[1]

class SpriteCacheTests(unittest.TestCase):
 def test_pixels_and_invalidation(self):
  source = r'''
#include "fm_unai.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
static uint16_t ram[524288], base[524288], expected[524288];
extern "C" int fm_unai_sprite_reference(uint16_t*,const uint32_t*,unsigned,
 uint16_t,int,int,int,int,int,int);
extern "C" void fm_unai_cache_counts(uint32_t*,uint32_t*);
static uint32_t seed=13653;
static uint32_t rnd(){seed=seed*1664525u+1013904223u;return seed;}
static uint32_t xy(int x,int y){return (uint16_t)x|((uint32_t)(uint16_t)y<<16);}
static void check(uint32_t *p,uint16_t pg,int ox,int oy){
 memcpy(ram,base,sizeof ram);
 assert(fm_unai_sprite_reference(ram,p,4,pg,0,0,319,255,ox,oy));
 memcpy(expected,ram,sizeof ram);memcpy(ram,base,sizeof ram);
 assert(fm_unai_draw(ram,p,4,pg,0,0,0,0,0,319,255,ox,oy));
 assert(!memcmp(ram,expected,sizeof ram));
}
int main(int argc,char**){
 for(unsigned i=0;i<524288;++i)base[i]=(uint16_t)rnd();
 for(unsigned i=0;i<256;++i)base[300*1024+512+i]=i%5?rnd():0;
 for(unsigned n=0;n<400;++n){
  unsigned depth=n%2,w=1+rnd()%128,h=1+rnd()%32;
  unsigned u=rnd()%(257-w),v=rnd()%(257-h);
  uint16_t pg=10|16|(depth<<7);unsigned cl=(300<<6)|32;
  uint32_t p[]={((n%3==0?0x65u:0x64u)<<24)|0x808080,
   xy((int)(rnd()%350)-25,(int)(rnd()%290)-25),u|(v<<8)|(cl<<16),xy(w,h)};
  int ox=(n%7)-3,oy=(n%5)-2;
  check(p,pg,ox,oy);check(p,pg,ox,oy); // exact hit
  // Palette writes and same-pointer restored content must invalidate.
  for(unsigned i=0;i<(depth?256u:16u);++i)base[300*1024+512+i]^=0x7fff;
  check(p,pg,ox,oy);check(p,pg,ox,oy);
  // GPU upload/copy or RAM snapshot restore can alter any source row.
  unsigned a=(256+v+h/2)*1024+640+((u+w/2)>>(depth?1:2));
  base[a]^=0xffff;check(p,pg,ox,oy);
 }
 // Source zero must preserve destination; source bit15 must be retained.
 for(unsigned i=0;i<16;++i)base[300*1024+512+i]=i==0?0:0x8000|i;
 uint32_t p[]={0x64808080,xy(0,0),((300<<6)|32)<<16,xy(32,32)};
 check(p,10|16,0,0);check(p,10|16,0,0);
 // Fully opaque rows use a copy, retaining bit15 and clipping exactly.
 for(unsigned i=0;i<16;++i)base[300*1024+512+i]=0x8000|i;
 check(p,10|16,-7,-9);check(p,10|16,-7,-9);
 // Nonneutral, blend and wrapping sprites keep the existing path.
 p[0]=0x64404040;check(p,10|16,0,0);
 p[0]=0x66808080;check(p,10|16,0,0);
 p[0]=0x64808080;p[2]|=250;check(p,10|16,0,0);
 uint32_t hits,misses;fm_unai_cache_counts(&hits,&misses);
 assert(hits>100 && misses>100);
 printf("sprite cache exact pixels; hits=%u misses=%u\n",hits,misses);
 if(argc>1){
  p[2]=((300<<6)|32)<<16;p[3]=xy(32,32);memcpy(ram,base,sizeof ram);
  clock_t a=clock();for(unsigned i=0;i<50000;++i)
   fm_unai_sprite_reference(ram,p,4,10|16,0,0,319,255,0,0);
  clock_t b=clock();for(unsigned i=0;i<50000;++i)
   fm_unai_draw(ram,p,4,10|16,0,0,0,0,0,319,255,0,0);
  clock_t c=clock();printf("host repeated 32x32 sprite reference_ms=%.1f cached_ms=%.1f ratio=%.2f\n",
   (b-a)*1000.0/CLOCKS_PER_SEC,(c-b)*1000.0/CLOCKS_PER_SEC,(double)(b-a)/(c-b));
 }
}
'''
  with tempfile.TemporaryDirectory() as tmp:
   src=Path(tmp)/'cache.cpp'; src.write_text(source); exe=Path(tmp)/'cache'
   subprocess.run(['g++','-O3','-DFM_UNAI_REFERENCE_TEST=1','-std=gnu++11',
    '-fno-strict-aliasing','-I'+str(ROOT/'3ds/include'),str(src),
    '-c','-o',str(Path(tmp)/'harness.o')],check=True)
   subprocess.run(['g++','-O3','-DNDEBUG','-DFM_UNAI_REFERENCE_TEST=1','-std=gnu++11',
    '-fno-strict-aliasing','-I'+str(ROOT/'3ds/include'),
    str(ROOT/'3ds/source/fm_unai.cpp'),str(Path(tmp)/'harness.o'),'-o',str(exe)],check=True)
   subprocess.run([str(exe)]+(['bench'] if os.getenv('FM_GPU_HOST_BENCHMARK') else []),check=True)
