#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "fm_sprite_packet.h"
#include "fm_native_memory.h"
#include "fm_interp.h"
#include "fm_sprite_packet_code.h"
FMNativeRam g_fm_native_ram;
static uint8_t ram[0x200000], ref[0x200000], scratch[1024];
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

static void run(unsigned variant) {
 memory=ram;pad=scratch;memset(ram,0,sizeof ram);
 memcpy(ram+0x84978,sprite_packet_code,sizeof sprite_packet_code);
 CPUState a={0}; for(unsigned i=1;i<32;i++)a.gpr[i]=rnd();
 a.read_word=fm_memory_read_word;a.write_word=fm_memory_write_word;
 a.read_half=fm_memory_read_half;a.write_half=fm_memory_write_half;
 a.read_byte=fm_memory_read_byte;a.write_byte=fm_memory_write_byte;
 uint32_t obj=0x1000,ctx=0x2000,pkt=0x3000,ot=0x4000;
 if(variant==4)pkt=obj;
 if(variant==5)ot=pkt;
 if(variant==6)pkt=0xff444;
 if(variant==7)pkt=0xeb248;
 if(variant==8)pkt=0x84978;
 if(variant==9)ot=0xff5c4;
 if(variant==10)pkt=0x1ffff8;
 a.gpr[4]=0x80000000u+obj;a.gpr[5]=0xa0000000u+ctx;a.gpr[6]=rnd();
 a.gpr[31]=0x80010000u;a.pc=0x80084978;
 for(unsigned i=0;i<24;i++)ram[obj+i]=(uint8_t)rnd();
 put(obj,rnd()&0x7fffffffu);fm_memory_write_half(obj+8,1+(rnd()%65535));fm_memory_write_half(obj+10,1+(rnd()%65535));
 if(variant==1)put(obj,0x80000000u|rnd());
 if(variant==2)fm_memory_write_half(obj+8,0);
 if(variant==3)fm_memory_write_half(obj+10,0);
 put(ctx+4,0x80200000u+ot);put(ctx+8,a.gpr[6]&0xffffu);
 put(ot,rnd());put(0xff444,rnd());put(0xff5c4,0x80600000u+pkt);
 if(variant==11)ram[0x84978]^=1;
 CPUState before=a,b=a;memcpy(ref,ram,sizeof ram);
 g_fm_native_ram.base=ram;g_fm_native_ram.size=sizeof ram;
 int handled=fm_sprite_packet_try(&a,a.pc);
 if(variant>=4) { assert(!handled);assert(!memcmp(&before,&a,sizeof a));assert(!memcmp(ref,ram,sizeof ram));return; }
 assert(handled);memory=ref;fm_interp_bind_ram(NULL,0);
 unsigned blocks=0;
 while(b.pc!=b.gpr[31]) {FMInterpResult result=fm_interp_run_block(&b,8192);assert(result.reason==FM_INTERP_BLOCK_DONE);assert(++blocks<20);}
 if(memcmp(&a,&b,sizeof a)) {for(unsigned i=0;i<32;i++)if(a.gpr[i]!=b.gpr[i])fprintf(stderr,"r%u: %08x != %08x\n",i,a.gpr[i],b.gpr[i]);assert(0);}
 assert(!memcmp(ram,ref,sizeof ram));
}
int main(void) {
 for(unsigned i=0;i<1000;i++)run(i%12);
 CPUState c={0},old=c;assert(!fm_sprite_packet_try(&c,0x80084990));assert(!memcmp(&c,&old,sizeof c));
 puts("sprite packet: 1000 exact MIPS/reference or unchanged fallback cases");
}
