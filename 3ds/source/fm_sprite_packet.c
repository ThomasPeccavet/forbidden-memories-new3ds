#include "fm_sprite_packet.h"
#include "fm_native_memory.h"
#include "fm_sprite_packet_code.h"
#include <string.h>

/* B136.65: bounded 95-instruction leaf, no guest callback or host continuation.
 * Validate once, calculate using local registers, publish complete guest state.
 * Unusual mappings/aliasing and interior resumptions retain the original core. */
static int overlaps(uint32_t a,unsigned an,uint32_t b,unsigned bn)
{ return a < b+bn && b < a+an; }
int fm_sprite_packet_try(CPUState *c,uint32_t address)
{
    if (!c || (address&0x1fffffffu)!=0x84978u) return 0;
#ifdef PSX_ENABLE_BLOCK_CYCLES
    return 0;
#endif
    if (!g_fm_native_ram.base || g_fm_native_ram.size<0x200000u
        || c->gpr[0] || c->read_word!=fm_memory_read_word
        || c->read_half!=fm_memory_read_half || c->read_byte!=fm_memory_read_byte
        || c->write_word!=fm_memory_write_word) return 0;
    uint8_t *ram=g_fm_native_ram.base;
    if (memcmp(ram+0x84978,sprite_packet_code,sizeof sprite_packet_code)) return 0;
    uint32_t object=c->gpr[4],context=c->gpr[5],depth=c->gpr[6];
    uint8_t *o=fm_native_ram_ptr(object,24);
    if (!o) return 0;
    uint32_t flags=fm_ram_load32(o),v0=c->gpr[2];
    unsigned exit_stage=0;
    if (flags&0x80000000u) exit_stage=1;
    else if (!(v0=fm_ram_load16(o+8))) exit_stage=2;
    else if (!(v0=fm_ram_load16(o+10))) exit_stage=3;
    if (exit_stage) {
        c->gpr[11]=object; c->gpr[13]=context; c->gpr[12]=flags;c->gpr[14]=depth;
        if(exit_stage>=2)c->gpr[2]=v0;
        if(exit_stage==3)c->gpr[4]=0xe1000000u;
        c->pc=c->gpr[31]; return 1;
    }
    uint8_t *ctx=fm_native_ram_ptr(context,12);
    uint32_t packet=fm_ram_load32(ram+0xff5c4);
    uint8_t *out=fm_native_ram_ptr(packet,24);
    if(!ctx || !out) return 0;
    uint32_t ot=fm_ram_load32(ctx+4)+(depth&0xffffu)*4u-fm_ram_load32(ctx+8)*4u;
    uint8_t *link=fm_native_ram_ptr(ot,4);
    if(!link) return 0;
    uint32_t po=(uint32_t)(out-ram),lo=(uint32_t)(link-ram);
    uint32_t oo=(uint32_t)(o-ram),co=(uint32_t)(ctx-ram);
    /* Preloaded values are safe only when writes cannot change subsequent
     * reads. Reject all aliases, including physical mirrors and code writes. */
    const uint32_t spans[][2]={{oo,24},{co,12},{0xff444,4},{0xff5c4,4},{0x84978,sizeof sprite_packet_code}};
    for(unsigned i=0;i<sizeof spans/sizeof spans[0];i++)
        if(overlaps(po,24,spans[i][0],spans[i][1]) || overlaps(lo,4,spans[i][0],spans[i][1]))return 0;
    if(overlaps(po,24,lo,4) || overlaps(oo,24,0xff5c4,4) || overlaps(co,12,0xff5c4,4)
       || fm_native_watched(packet,24) || fm_native_watched(ot,4))return 0;
    uint32_t x=(fm_ram_load16(o+4)+fm_ram_load16(ram+0xff444))&0xffffu;
    uint32_t y=((uint32_t)fm_ram_load16(o+6)+fm_ram_load16(ram+0xff446))<<16;
    uint32_t color=((flags>>5)&0x02000000u)|((flags<<18)&0x01000000u)|0x64000000u;
    uint32_t uv=fm_ram_load16(o+14)|((uint32_t)fm_ram_load16(o+18)<<22)
        |(((uint32_t)fm_ram_load16(o+16)<<12)&0x003f0000u);
    uint32_t height=(uint32_t)fm_ram_load16(o+10)<<16;
    uint32_t size=fm_ram_load16(o+8)|height;
    uint32_t tag=fm_ram_load32(link)+0x05000000u;
    fm_ram_store32(out+4,(fm_ram_load16(o+12)&31u)|((flags>>17)&0x180u)|0xe1000200u|((flags>>23)&0x60u));
    fm_ram_store32(out+12,x|y);
    fm_ram_store32(out+8,color|((uint32_t)o[22]<<16)|((uint32_t)o[21]<<8)|o[20]);
    fm_ram_store32(out+16,uv);fm_ram_store32(out+20,size);
    fm_ram_store32(out,tag);fm_ram_store32(link,packet&0xffffffu);
    fm_ram_store32(ram+0xff5c4,packet+24u);
    c->gpr[1]=0x80100000u;c->gpr[2]=tag;c->gpr[3]=0x05000000u;
    c->gpr[4]=ot;c->gpr[5]=y;c->gpr[6]=(uint32_t)o[22]<<16;c->gpr[7]=packet+24u;
    c->gpr[8]=(uint32_t)o[21]<<8;c->gpr[9]=o[20];c->gpr[10]=packet&0xffffffu;
    c->gpr[11]=object;c->gpr[12]=flags;c->gpr[13]=context;c->gpr[14]=depth;
    c->pc=c->gpr[31];return 1;
}
