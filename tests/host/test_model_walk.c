#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "fm_model_walk.h"
#include "fm_native_memory.h"
#include "fm_interp.h"
#include "model_walk_reference.h"
FMNativeRam g_fm_native_ram;
static uint8_t ram[0x200000], ref[0x200000], scratch[1024], rscratch[1024];
static uint8_t *memory=ram,*pad=scratch;
static uint8_t *ptr(uint32_t a){a&=0x1fffffffu;
 if(a>=0x1f800000u&&a<0x1f800400u)return pad+a-0x1f800000u;
 assert(a<0x800000u);return memory+(a&0x1fffffu);}
uint32_t fm_memory_read_word(uint32_t a){uint32_t v;memcpy(&v,ptr(a),4);return v;}
void fm_memory_write_word(uint32_t a,uint32_t v){memcpy(ptr(a),&v,4);}
uint16_t fm_memory_read_half(uint32_t a){uint16_t v;memcpy(&v,ptr(a),2);return v;}
void fm_memory_write_half(uint32_t a,uint16_t v){memcpy(ptr(a),&v,2);}
uint8_t fm_memory_read_byte(uint32_t a){return *ptr(a);}
void fm_memory_write_byte(uint32_t a,uint8_t v){*ptr(a)=v;}
void gte_execute(CPUState*c,uint32_t a){(void)c;(void)a;assert(0);}
uint32_t gte_read_data(CPUState*c,uint8_t r){return c->gte_data[r];}
uint32_t gte_read_ctrl(CPUState*c,uint8_t r){return c->gte_ctrl[r];}
void gte_write_data(CPUState*c,uint8_t r,uint32_t v){c->gte_data[r]=v;}
void gte_write_ctrl(CPUState*c,uint8_t r,uint32_t v){c->gte_ctrl[r]=v;}
static uint32_t rng=64;
static uint32_t rnd(void){rng=rng*1664525u+1013904223u;return rng;}
static void put(uint32_t a,uint32_t v){fm_memory_write_word(a,v);}
static unsigned segments, callbacks;
static void compare(CPUState *a,CPUState*b){
 if(memcmp(a,b,sizeof *a)){for(unsigned i=0;i<32;i++){if(a->gpr[i]!=b->gpr[i])
 fprintf(stderr,"r%u %08x != %08x pc %08x/%08x\n",i,a->gpr[i],b->gpr[i],a->pc,b->pc);}assert(0);}
 assert(!memcmp(ram,ref,sizeof ram));assert(!memcmp(scratch,rscratch,sizeof scratch));
}
static void run(unsigned n,unsigned count,int cyclic,int fast_ram){
 memory=ram;pad=scratch;memset(ram,0,sizeof ram);memset(scratch,0,sizeof scratch);
 memcpy(ram+0x8a0d8,model_walk_code,sizeof model_walk_code);
 put(0x1004,0x80002000);put(0x1100,rnd());put(0x1108,rnd());put(0xff5c4,0x80010000);
 for(unsigned g=0;g<n;g++){
  uint32_t node=0x2000+g*256,table=0x4000+g*1024;
  put(node,g+1<n?0x80000000+node+256:cyclic?0x80002000:0xffffffffu);
  put(node+4,0x80000000+table);put(table,count);
  for(unsigned i=0;i<count;i++)put(table+4+i*4,rnd());
  unsigned cb=cyclic?0:g%4;put(node+8,cb);
  for(unsigned i=0;i<cb;i++)put(node+12+4*i,0x80153070+i*16);
 }
 CPUState a={0};for(unsigned i=1;i<32;i++)a.gpr[i]=rnd();
 a.pc=0x8008a0d8;a.gpr[4]=0x80001000;a.gpr[5]=0x80001100;
 a.gpr[6]=0x1f800000;a.gpr[29]=0x801ff000;a.gpr[31]=0x80010000;
 a.read_word=fm_memory_read_word;a.write_word=fm_memory_write_word;
 a.read_half=fm_memory_read_half;a.write_half=fm_memory_write_half;
 a.read_byte=fm_memory_read_byte;a.write_byte=fm_memory_write_byte;
 CPUState b=a;memcpy(ref,ram,sizeof ram);memcpy(rscratch,scratch,sizeof scratch);
 fm_interp_bind_ram(NULL,0);
 for(unsigned step=0;step<100;step++){
  memory=ram;pad=scratch;g_fm_native_ram.base=fast_ram?ram:NULL;g_fm_native_ram.size=sizeof ram;
  if(!fm_model_walk_try(&a,a.pc)){FMInterpResult r=fm_interp_run_block(&a,8192);assert(r.reason==FM_INTERP_BLOCK_DONE);}
  memory=ref;pad=rscratch;unsigned blocks=0;
  do{FMInterpResult r=fm_interp_run_block(&b,8192);assert(r.reason==FM_INTERP_BLOCK_DONE);assert(++blocks<10000);}while(b.pc!=a.pc || ((a.pc==0x8008a134 || a.pc==0x8008a164) && (a.gpr[19]!=b.gpr[19] || a.gpr[16]!=b.gpr[16])));
  compare(&a,&b);++segments;
  if(a.pc==0x80010000)return;
  if(a.pc>=0x80153070&&a.pc<0x80153100){
   // Simulate a primitive consuming the packet list and updating global output.
   // Compare before AND after continuation, including random caller-saved regs.
   for(unsigned i=2;i<16;i++)a.gpr[i]=b.gpr[i]=rnd();
   a.gpr[2]=b.gpr[2]=fm_memory_read_word(0x1f800000);
   uint32_t value=rnd();put(0xff5c4,value);memory=ram;pad=scratch;put(0xff5c4,value);
   a.pc=b.pc=0x8008a1c0;++callbacks;
  }
  if(cyclic&&step==4)return; // bounded native yield, no hang
 }
 assert(0);
}
int main(void){
 for(unsigned i=0;i<100;i++)run(1+rnd()%12,rnd()%24,0,i&1);
 run(12,0,1,1);run(3,140,0,1);
 // Unrecognized entry and altered code must leave CPU/memory untouched.
 memory=ram;pad=scratch;CPUState c={0};c.read_word=fm_memory_read_word;
 c.pc=0x8008a0d8;CPUState before=c;put(0x8a0d8,0);g_fm_native_ram.base=ram;
 assert(!fm_model_walk_try(&c,c.pc));assert(!memcmp(&c,&before,sizeof c));
 assert(!fm_model_walk_try(&c,0x8008a140));
 printf("model walker: %u exact continuation boundaries, %u primitive callbacks\n",segments,callbacks);
}
