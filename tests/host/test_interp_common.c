#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "fm_interp.h"
void ref_bind(uint8_t*,size_t);
FMInterpResult ref_block(CPUState*,uint32_t);
FMInterpResult ref_region(CPUState*,uint32_t,uint32_t,uint32_t,uint32_t);
static uint8_t ram[65536],reference[65536];
static uint32_t rng=0x13660;
static uint32_t random32(void){rng=rng*1664525u+1013904223u;return rng;}
static uint32_t rdword(uint32_t a){return 0xA5000000u|(a&0xffff);}
static uint16_t rdhalf(uint32_t a){return (uint16_t)rdword(a);}
static uint8_t rdbyte(uint32_t a){return (uint8_t)rdword(a);}
static uint32_t stores,store_addr,store_value;
static void wrword(uint32_t a,uint32_t v){++stores;store_addr=a;store_value=v;}
static void wrhalf(uint32_t a,uint16_t v){wrword(a,v);}
static void wrbyte(uint32_t a,uint8_t v){wrword(a,v);}
void gte_execute(CPUState*c,uint32_t a){(void)c;(void)a;}
uint32_t gte_read_data(CPUState*c,uint8_t r){return c->gte_data[r];}
uint32_t gte_read_ctrl(CPUState*c,uint8_t r){return c->gte_ctrl[r];}
void gte_write_data(CPUState*c,uint8_t r,uint32_t v){c->gte_data[r]=v;}
void gte_write_ctrl(CPUState*c,uint8_t r,uint32_t v){c->gte_ctrl[r]=v;}
static CPUState cpu_init(void){CPUState c={0};c.pc=0x80001000;
 c.read_word=rdword;c.read_half=rdhalf;c.read_byte=rdbyte;
 c.write_word=wrword;c.write_half=wrhalf;c.write_byte=wrbyte;return c;}
static void equivalence(void){
 const unsigned ops[]={0,8,9,10,11,12,13,14,15,32,33,35,36,37,40,41,43};
 const unsigned funcs[]={0,2,3,4,6,7,32,33,34,35,36,37,38,39,42,43};
 for(unsigned i=0;i<16000;++i){
  CPUState a=cpu_init();for(unsigned j=1;j<32;++j)a.gpr[j]=random32();
  unsigned op=ops[i%(sizeof(ops)/sizeof(ops[0]))];
  unsigned rs=random32()%32,rt=random32()%32,rd=random32()%32;
  uint32_t ins=(op<<26)|(rs<<21)|(rt<<16)|(random32()&65535);
  if(op==0)ins=(rs<<21)|(rt<<16)|(rd<<11)|((random32()%32)<<6)|funcs[(i/17)%16];
  if(op>=32){
   // Ordinary RAM and callback/MMIO fallback, signed offsets, aligned spans.
   rs=20;a.gpr[rs]=(i&1)?0x80008000:0x1F801000;
   ins=(op<<26)|(rs<<21)|(rt<<16)|(((random32()%128)*4-256) & 65535);
  }
  memcpy(ram+4096,&ins,4);memcpy(reference,ram,sizeof ram);
  CPUState b=a;fm_interp_bind_ram(ram,sizeof ram);ref_bind(reference,sizeof reference);
  stores=0;FMInterpResult x=fm_interp_run_block(&a,1);
  uint32_t n=stores,addr=store_addr,value=store_value;
  stores=0;FMInterpResult y=ref_block(&b,1);
  assert(x.reason==y.reason&&x.pc==y.pc&&x.instruction==y.instruction&&x.instructions==y.instructions);
  assert(!memcmp(&a,&b,sizeof a));assert(!memcmp(ram,reference,sizeof ram));
  assert(stores==n);if(n)assert(store_addr==addr&&store_value==value);
 }
}
static void install_loop(void){
 // A bounded MIPS RAM/ALU loop with a real branch delay slot; resident JR exit.
 const uint32_t words[]={0x8C820000,0x00431021,0x00431026,0xAC820000,
  0x24840004,0x24A5FFFF,0x14A0FFF9,0x24630001,0x03E00008,0};
 memcpy(ram+4096,words,sizeof words);memcpy(reference,ram,sizeof ram);
}
static CPUState loop_cpu(void){CPUState c=cpu_init();c.gpr[4]=0x80002000;
 c.gpr[5]=5000;c.gpr[31]=0x80008000;return c;}
static unsigned run(CPUState*c,int fast){unsigned calls=0;
 while(c->pc!=0x80008000){FMInterpResult r=fast?
 fm_interp_run_region(c,2048,0x1000,0x2000,0xFFFFFFFF):ref_block(c,8192);
 assert(r.reason==FM_INTERP_BLOCK_DONE||r.reason==FM_INTERP_BUDGET);
 assert(++calls<10000);}
 return calls;
}
int main(void){equivalence();install_loop();CPUState a=loop_cpu(),b=a;
 fm_interp_bind_ram(ram,sizeof ram);ref_bind(reference,sizeof reference);
 unsigned fast=run(&a,1),slow=run(&b,0);
 assert(!memcmp(&a,&b,sizeof a));assert(!memcmp(ram,reference,sizeof ram));
 printf("overlay loop dispatcher calls: reference=%u fast=%u\n",slow,fast);
 assert(fast*100<slow);
 clock_t start=clock();for(unsigned i=0;i<100;++i){install_loop();a=loop_cpu();run(&a,1);}
 double fast_ms=(double)(clock()-start)*1000/CLOCKS_PER_SEC;
 start=clock();for(unsigned i=0;i<100;++i){install_loop();b=loop_cpu();run(&b,0);}
 double ref_ms=(double)(clock()-start)*1000/CLOCKS_PER_SEC;
 printf("host synthetic loop: fast=%.2fms reference=%.2fms (not 3DS FPS)\n",fast_ms,ref_ms);
 return 0;}
