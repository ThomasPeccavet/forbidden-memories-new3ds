"""Compare B136.36 against the frozen production textured raster."""
from pathlib import Path
import os
import subprocess
import tempfile
import unittest
from test_gpu_perf_window_host import function
ROOT=Path(__file__).resolve().parents[1]

class TexturedNeutralTests(unittest.TestCase):
    def test_pixels_and_guards(self):
        s=(ROOT/'3ds/source/fm_gpu.c').read_text()
        ctx=s[s.index('typedef struct B13512TexCtx'):s.index('} B13512TexCtx;')+len('} B13512TexCtx;')]
        funcs='\n'.join(function(s,n) for n in ('b124_vram_get',
            'b13512_texctx','b13512_fetch_texel_ctx','b124_blend',
            'b125_put_textured','b13513_grad_fp16','b13513_edge_fp16',
            'b13636_neutral_span','b13511_shaded_textured_triangle'))
        baseline=(ROOT/'tests/host/textured_b13635_reference.c').read_text()
        # Prevent call-site constant propagation only in this harness/benchmark.
        funcs=funcs.replace('static void b13511_shaded_textured_triangle(',
            'static __attribute__((noinline,noclone)) void b13511_shaded_textured_triangle(')
        baseline=baseline.replace('static void reference_textured_triangle(',
            'static __attribute__((noinline,noclone)) void reference_textured_triangle(')
        code=r'''#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <time.h>
static uint16_t ram[1024*512],initial[1024*512],reference[1024*512];
static uint16_t *g_vram=ram;
static int g_draw_x1,g_draw_y1,g_draw_x2=319,g_draw_y2=255,g_mask_set,g_mask_check;
static uint32_t g_texture_window;
static uint64_t g_b125_pixels,g_b13533_34_fast_pixels;
static uint32_t g_b13533_34_fast_hits;
#if FM_PERF_PROFILE
static uint64_t g_b13534_setup_ticks,g_b13534_raster_ticks;
static uint32_t g_b13534_samples,g_b13534_tri_calls,g_b13535_depth_hits[3];
static int g_b13534_sample_active;
static uint64_t g_window_fast_tex_pixels,g_window_neutral_pixels;
static uint32_t g_window_fast_tex_triangles,g_window_neutral_triangles;
static uint64_t svcGetSystemTick(void) { static uint64_t t; return ++t; }
#endif
''' + ctx + '\n' + funcs + '\n' + baseline + r'''
static uint32_t rng=13636;
static uint32_t random32(void) { rng=rng*1664525u+1013904223u;return rng; }
int main(int argc,char **argv) {
    (void)argv;
    for(unsigned i=0;i<1024*512;++i) initial[i]=(uint16_t)random32();
    /* Explicit transparent and opaque-black palette entries. */
    for(unsigned y=0;y<512;++y) {
        initial[y*1024+512]=0;
        initial[y*1024+513]=0x8000;
    }
    unsigned neutral_covered=0;
    for(unsigned i=0;i<640;++i) {
        int x[3],y[3],u[3],v[3];uint32_t c[3];
        for(unsigned j=0;j<3;++j) {
            x[j]=(int)(random32()%480)-80; y[j]=(int)(random32()%360)-60;
            u[j]=random32()%256;v[j]=random32()%256;
            c[j]=i%5 ? 0x808080 | (random32()&0x070707) : random32()&0xffffff;
        }
        if(i%16==0)y[1]=y[0];
        if(i%16==1)y[2]=y[1];
        if(i%16==2)x[2]=x[1],y[2]=y[1];
        unsigned depth=(i/16)%4;
        uint16_t page=(uint16_t)(8 | 0x10 | depth<<7);
        int clx=i%2 ? 512 : 1008, cly=i%7 ? 480 : 80;
        int raw=i%11==0,semi=i%13==0;
        g_mask_set=i%17==0; g_mask_check=i%19==0;
        g_texture_window=i%23==0 ? 0x010203 : 0;
        g_draw_x1=i%13;g_draw_y1=i%7;
#if FM_PERF_PROFILE
        g_b13534_sample_active=i%9==0;
        g_window_neutral_pixels=0;g_window_neutral_triangles=0;
#endif
        memcpy(ram,initial,sizeof(ram));g_b125_pixels=g_b13533_34_fast_pixels=0;
        reference_textured_triangle(x[0],y[0],u[0],v[0],c[0],
            x[1],y[1],u[1],v[1],c[1],x[2],y[2],u[2],v[2],c[2],
            clx,cly,page,raw,semi);
        memcpy(reference,ram,sizeof(ram));
        uint64_t pixels=g_b125_pixels,fast_pixels=g_b13533_34_fast_pixels;
        memcpy(ram,initial,sizeof(ram));g_b125_pixels=g_b13533_34_fast_pixels=0;
        b13511_shaded_textured_triangle(x[0],y[0],u[0],v[0],c[0],
            x[1],y[1],u[1],v[1],c[1],x[2],y[2],u[2],v[2],c[2],
            clx,cly,page,raw,semi);
        assert(!memcmp(reference,ram,sizeof(ram)));
        assert(pixels==g_b125_pixels && fast_pixels==g_b13533_34_fast_pixels);
#if FM_PERF_PROFILE
        if(raw || semi || g_mask_set || g_mask_check || g_texture_window)
            assert(g_window_neutral_pixels==0 && g_window_neutral_triangles==0);
        neutral_covered+=g_window_neutral_pixels>0;
#endif
    }
#if FM_PERF_PROFILE
    assert(neutral_covered>100);
#else
    (void)neutral_covered;
#endif
    /* 8000h texels must overwrite a nonblack target with opaque black. */
    for(unsigned i=0;i<1024*512;++i)ram[i]=0xffff;
    for(unsigned i=0;i<16;++i)ram[480*1024+512+i]=0x8000;
    g_mask_set=g_mask_check=0;g_texture_window=0;g_draw_x1=g_draw_y1=0;
    b13511_shaded_textured_triangle(8,8,0,0,0x808080,
        60,8,40,0,0x808080,8,60,0,40,0x808080,512,480,0x18,0,0);
    assert(ram[16*1024+16]==0);
    if(argc>1) {
        /* Optional x86 host timing: never interpret this as ARM11 FPS. */
        for(unsigned depth=0;depth<3;++depth) {
            memcpy(ram,initial,sizeof(ram));
            clock_t begin=clock();
            for(unsigned i=0;i<700;++i)
                reference_textured_triangle(8,8,0,0,0x808080,300,8,128,0,0x808080,
                    8,240,0,128,0x808080,512,480,0x18|(depth<<7),0,0);
            double before=(double)(clock()-begin)/CLOCKS_PER_SEC;
            memcpy(ram,initial,sizeof(ram));begin=clock();
            for(unsigned i=0;i<700;++i)
                b13511_shaded_textured_triangle(8,8,0,0,0x808080,300,8,128,0,0x808080,
                    8,240,0,128,0x808080,512,480,0x18|(depth<<7),0,0);
            double after=(double)(clock()-begin)/CLOCKS_PER_SEC;
            printf("host depth=%u before_ms=%.2f after_ms=%.2f ratio=%.3f\n",
                depth,before*1000,after*1000,before/after);
        }
    }
    return 0;
}
'''
        with tempfile.TemporaryDirectory() as tmp:
            p=Path(tmp)/'gpu.c';p.write_text(code)
            for profile in (0,1):
                exe=Path(tmp)/f'gpu{profile}'
                subprocess.run(['cc','-std=gnu11','-O3','-fwrapv','-Wall','-Werror',
                    f'-DFM_PERF_PROFILE={profile}',str(p),'-o',str(exe)],check=True)
                subprocess.run([str(exe)],check=True)
                if profile==0 and os.environ.get("FM_GPU_HOST_BENCHMARK")=="1":
                    result=subprocess.run([str(exe),'benchmark'],check=True,text=True,capture_output=True)
                    print(result.stdout, end='')
