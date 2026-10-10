"""Pixel differential against frozen B136.34, and exact quotient checks."""
from pathlib import Path
import subprocess
import tempfile
import unittest
ROOT=Path(__file__).resolve().parents[1]

def function(source, name):
    start=source.index(name+'(')
    start=source.rfind('\n',0,start)+1
    brace=source.index('{',start); end=brace+1; depth=1
    while depth:
        depth+=(source[end]=='{')-(source[end]=='}'); end+=1
    return source[start:end]

class GouraudExactTests(unittest.TestCase):
    def test_exact_gradients_and_pixels(self):
        source=(ROOT/'3ds/source/fm_gpu.c').read_text()
        funcs='\n'.join(function(source,n) for n in ('b124_blend',
            'b125_put_gouraud','b128_div_fp16','b13635_gradient','b125_gouraud_triangle'))
        code=r'''#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <assert.h>
#define FM_GPU_EXACT_GRADIENTS 1
static uint16_t ram[1024*512], initial[1024*512], reference[1024*512];
static uint16_t *g_vram=ram;
static int g_draw_x1,g_draw_y1,g_draw_x2,g_draw_y2,g_mask_check,g_mask_set;
static uint64_t g_b125_pixels;
''' + funcs + '\n' + (ROOT/'tests/host/gouraud_b13634_reference.c').read_text()+r'''
static uint32_t rng=13635;
static uint32_t random32(void) { rng=rng*1664525u+1013904223u; return rng; }
int main(void) {
    for(unsigned i=0;i<250000;++i) {
        int32_t n=(int32_t)random32();
        if(i&1) n=n%130000;
        int64_t d=(int32_t)random32();
        if(i%3) d=d%8400000;
        if(!d)d=1;
        float inv=65536.0f/(float)(d<0?-d:d);
        assert(b13635_gradient(n,d,inv)==(int32_t)(((int64_t)n*65536)/d));
    }
    assert(b13635_gradient(3,0,0)==0);
    /* Force a bad estimate: integer residual check must select fallback. */
    assert(b13635_gradient(100,7,0)==(int32_t)((100LL*65536)/7));
    for(unsigned i=0;i<1024*512;++i) initial[i]=(uint16_t)random32();
    for(unsigned i=0;i<600;++i) {
        int x[3],y[3]; uint16_t c[3];
        for(unsigned j=0;j<3;++j) {
            x[j]=(int)(random32()%640)-128;
            y[j]=(int)(random32()%448)-96; c[j]=(uint16_t)random32();
        }
        if(i%8==0)y[1]=y[0];
        if(i%8==1)y[2]=y[1];
        if(i%8==2)x[2]=x[1],y[2]=y[1];
        g_draw_x1=i%31; g_draw_y1=i%19; g_draw_x2=319; g_draw_y2=255;
        g_mask_check=(i>>1)&1; g_mask_set=i&1;
        int semi=(i>>2)&1,mode=(i>>3)&3;
        memcpy(ram,initial,sizeof(ram)); g_b125_pixels=0;
        reference_gouraud_triangle(x[0],y[0],c[0],x[1],y[1],c[1],x[2],y[2],c[2],semi,mode);
        memcpy(reference,ram,sizeof(ram)); uint64_t pixels=g_b125_pixels;
        memcpy(ram,initial,sizeof(ram)); g_b125_pixels=0;
        b125_gouraud_triangle(x[0],y[0],c[0],x[1],y[1],c[1],x[2],y[2],c[2],semi,mode);
        assert(pixels==g_b125_pixels);
        assert(!memcmp(reference,ram,sizeof(ram)));
    }
    return 0;
}
'''
        with tempfile.TemporaryDirectory() as tmp:
            p=Path(tmp)/'gpu.c'; p.write_text(code); exe=Path(tmp)/'gpu'
            subprocess.run(['cc','-std=c11','-O3','-fwrapv','-Wall','-Werror',str(p),'-o',str(exe)],check=True)
            subprocess.run([str(exe)],check=True)
