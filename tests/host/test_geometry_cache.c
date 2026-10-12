#include "cpu_state.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
void gte_execute(CPUState *,uint32_t);
void ref_gte_execute(CPUState *,uint32_t);
void fm_runtime_geometry_cache_stats(uint64_t out[3]);
void test_force_wrap(void);
static uint32_t seed=13663;
static uint32_t rnd(void) {seed=seed*1664525u+1013904223u;return seed;}
static void random_cpu(CPUState *cpu) {
 memset(cpu,0,sizeof *cpu);
 for(unsigned j=0;j<32;++j){cpu->gpr[j]=rnd();cpu->gte_data[j]=rnd();cpu->gte_ctrl[j]=rnd();}
}
static void same(CPUState *a,CPUState *b,uint32_t cmd) {
 gte_execute(a,cmd);ref_gte_execute(b,cmd);
 assert(!memcmp(a,b,sizeof *a));
}
static void shared_vertices(CPUState *a,unsigned step) {
 for(unsigned v=0;v<3;++v){unsigned n=(step+v)%24;
  int16_t x=(int16_t)((int)(n%6)*100-250),y=(int16_t)((int)(n/6)*100-150);
  a->gte_data[v*2]=(uint16_t)x | (uint32_t)(uint16_t)y<<16;
  a->gte_data[v*2+1]=n%3*16;
 }
}
static void identity(CPUState *a) {
 memset(a->gte_ctrl,0,sizeof a->gte_ctrl);
 a->gte_ctrl[0]=4096;a->gte_ctrl[2]=4096;a->gte_ctrl[4]=4096;
 a->gte_ctrl[7]=4096;a->gte_ctrl[24]=160u<<16;a->gte_ctrl[25]=128u<<16;
 a->gte_ctrl[26]=256;a->gte_ctrl[27]=0xffff;a->gte_ctrl[28]=0x10000000;
}
int main(void) {
 CPUState a,b;random_cpu(&a);identity(&a);b=a;
 const uint32_t cmds[]={0x280030,0x180001,0x1400006,0x168002e,0x158002d,0x3d};
 for(unsigned k=0;k<40000;++k){
  /* Reuse vertices but overwrite current FIFOs and unrelated state: a hit
   * cannot reinstate the FIFO or backing registers from the original miss. */
  shared_vertices(&a,k);b=a;
  same(&a,&b,cmds[k%6]);
  if(k%7==0){for(unsigned j=8;j<32;++j)a.gte_data[j]=rnd();b=a;}
  if(k%257==0){a.gte_ctrl[5]++;b=a;}
 }
 uint64_t stats[3];fm_runtime_geometry_cache_stats(stats);
 assert(stats[0]>10000 && stats[1]>0 && stats[2]>0);
 printf("shared-vertex exact hits=%llu misses=%llu contexts=%llu\n",
  (unsigned long long)stats[0],(unsigned long long)stats[1],(unsigned long long)stats[2]);
 /* Every control can change between commands; sf/lm and pathological
  * projection/overflow cases must invalidate or produce the same result. */
 for(unsigned k=0;k<25000;++k){
  if(k%5==0)random_cpu(&a);
  a.gte_ctrl[k%32]=rnd();b=a;
  uint32_t cmd=(k&1)?1u:0x30u;
  if(k&2)cmd|=1u<<19;
  if(k&4)cmd|=1u<<10;
  same(&a,&b,cmd);
  /* Identical vertex/control key with arbitrary initial FIFO state. */
  for(unsigned j=8;j<32;++j)a.gte_data[j]=rnd();
  b=a;
  same(&a,&b,cmd);
 }
 test_force_wrap();identity(&a);b=a;same(&a,&b,0x280030);
 /* A synthetic reusable mesh benchmark is evidence for the algorithm,
  * not a prediction of end-to-end 3DS/Azahar FPS. */
 identity(&a);shared_vertices(&a,0);b=a;
 clock_t start=clock();for(unsigned k=0;k<500000;++k)gte_execute(&a,0x280030);
 double cached=(double)(clock()-start)/CLOCKS_PER_SEC;
 start=clock();for(unsigned k=0;k<500000;++k)ref_gte_execute(&b,0x280030);
 double raw=(double)(clock()-start)/CLOCKS_PER_SEC;
 assert(!memcmp(&a,&b,sizeof a));
 printf("synthetic host mesh: cached=%.4fs uncached=%.4fs (not game FPS)\n",cached,raw);
 return 0;
}
