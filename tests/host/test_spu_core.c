#include "fm_spu.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define BASE 0x1f801c00u
static void write(unsigned offset,unsigned value) {fm_spu_reg_write(BASE+offset,value);}
static void sample(void) {
    write(0x1a6,0xffff); /* transfer wraps at the 512KB boundary */
    for(unsigned n=0;n<8;++n) fm_spu_transfer_write(0x1000u+n);
    write(0x1a6,0xffff);for(unsigned n=0;n<8;++n) assert(fm_spu_transfer_read()==0x1000u+n);
    write(0x1a6,0x101);fm_spu_transfer_write(0x0700); /* loop + end + loop-start */
    for(unsigned n=0;n<7;++n) fm_spu_transfer_write(0x7777);
    write(0,0x3fff);write(2,0x2000);write(4,0x1000);write(6,0x101);
    write(8,0x00ff);write(10,0x1fc0);write(0x180,0x3fff);write(0x182,0x3fff);
    write(0x1aa,0xc000);write(0x188,1);
}
static int16_t transient[200];
static void sync_transient(void) {fm_spu_render(transient,100);}
int main(void) {
    fm_spu_reset();sample();int16_t pcm[200],expected[200],actual[200];
    fm_spu_render(pcm,100);assert(pcm[12]>20000 && pcm[13]>10000 && pcm[13]<pcm[12]);
    assert(fm_spu_reg_read(BASE+0x19c)&1);assert(fm_spu_reg_read(BASE+14)==0x101);
    unsigned bytes=fm_spu_snapshot_bytes();void *snap=malloc(bytes);assert(snap);
    fm_spu_snapshot_write(snap);assert(fm_spu_snapshot_valid(snap,bytes));
    assert(!fm_spu_snapshot_valid(snap,bytes-1));
    fm_spu_render(expected,100);fm_spu_reset();fm_spu_snapshot_load(snap);fm_spu_render(actual,100);
    assert(!memcmp(expected,actual,sizeof(actual)));
    write(0x18c,1);write(10,0);fm_spu_render(pcm,100);assert(fm_spu_reg_read(BASE+12)==0);
    for(unsigned n=90;n<100;++n) assert(!pcm[n*2] && !pcm[n*2+1]);
    fm_spu_reset();sample();write(0x1aa,0x8000);fm_spu_render(pcm,100);
    for(unsigned n=0;n<200;++n) assert(!pcm[n]);
    /* A short effect contributes samples before its KEY OFF changes state. */
    fm_spu_reset();sample();fm_spu_set_sync(sync_transient);
    write(0x18c,1);fm_spu_set_sync(NULL);
    assert(transient[12]>20000);
    free(snap);puts("SPU: wrapped transfer, voices, loop, ADSR, stereo, mute and exact resume passed");
}
