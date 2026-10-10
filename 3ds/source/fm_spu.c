/* First SPU voice mixer. Register/ADPCM/envelope semantics follow PSX-SPX.
 * Linear interpolation; reverb, capture RAM and SPU IRQ are not synthesized.
 * Transfers remain synchronous; the memory bus owns DMA completion/IRQ. */
#include "fm_spu.h"
#include <string.h>
#define RAM_BYTES 0x80000u
#define RAM_MASK (RAM_BYTES-1u)
#define BASE 0x1f801c00u
#define REG(a) s.reg[((a)-BASE)/2u]
typedef struct {
    uint32_t address, phase, counter;
    int32_t hist1, hist2, envelope;
    int16_t decoded[28], previous, following;
    uint8_t index, stage, active, flags, primed, padding[3];
    int32_t volume[2];
    uint32_t volume_counter[2];
} Voice;
typedef struct {
    uint32_t magic, bytes, transfer;
    uint16_t reg[320];
    uint8_t ram[RAM_BYTES];
    Voice voice[24];
    int32_t main_volume[2];
    uint32_t main_counter[2], noise_counter, noise;
} SPUState;
static SPUState s;
static int16_t clip(int32_t x) { return x < -32768 ? -32768 : x > 32767 ? 32767 : (int16_t)x; }
static int32_t direct_volume(uint16_t r) { return (int16_t)(r*2u); }
void fm_spu_reset(void) { memset(&s,0,sizeof(s)); s.magic=0x31555053u; s.bytes=sizeof(s); s.noise=1; }
uint16_t fm_spu_transfer_read(void) {
    uint16_t v=s.ram[s.transfer] | ((uint16_t)s.ram[(s.transfer+1u)&RAM_MASK]<<8);
    s.transfer=(s.transfer+2u)&RAM_MASK; return v;
}
void fm_spu_transfer_write(uint16_t v) {
    s.ram[s.transfer]=(uint8_t)v; s.ram[(s.transfer+1u)&RAM_MASK]=(uint8_t)(v>>8);
    s.transfer=(s.transfer+2u)&RAM_MASK;
}
static void key(unsigned i, int on) {
    Voice *v=&s.voice[i];
    if (!on) { if(v->active) {v->stage=3;v->counter=0;} return; }
    v->address=(uint32_t)s.reg[i*8u+3u]*8u;
    v->phase=v->counter=0; v->hist1=v->hist2=v->envelope=0;
    v->previous=v->following=0; v->primed=0; v->index=28; v->stage=0; v->active=1;v->flags=0;
    s.reg[i*8u+6u]=0;
    unsigned r=0x19cu/2u+(i/16u); s.reg[r]&=(uint16_t)~(1u<<(i%16u));
}
uint16_t fm_spu_reg_read(uint32_t a) {
    if(a<BASE || a>=BASE+sizeof(s.reg)) return 0;
    if(a==0x1f801da8u) return fm_spu_transfer_read();
    if(a==0x1f801daeu) return REG(0x1f801daau)&0x3fu;
    if(a==0x1f801db8u || a==0x1f801dbau) return (uint16_t)s.main_volume[(a-0x1f801db8u)/2u];
    if(a>=0x1f801e00u && a<0x1f801e60u) return (uint16_t)s.voice[(a-0x1f801e00u)/4u].volume[(a&2u)/2u];
    return s.reg[(a-BASE)/2u];
}
void fm_spu_reg_write(uint32_t a,uint16_t value) {
    if(a<BASE || a>=BASE+sizeof(s.reg) || a==0x1f801daeu || a==0x1f801d9cu || a==0x1f801d9eu) return;
    if(a==0x1f801d92u || a==0x1f801d96u || a==0x1f801d9au || a==0x1f801d8au || a==0x1f801d8eu) value&=0xffu;
    unsigned r=(a-BASE)/2u; s.reg[r]=value;
    if(a==0x1f801da6u) s.transfer=(uint32_t)value*8u;
    if(a==0x1f801da8u) fm_spu_transfer_write(value);
    if(a>=0x1f801d88u && a<=0x1f801d8eu) {
        unsigned first=(a&2u)?16u:0u; int on=a<0x1f801d8cu;
        for(unsigned i=first;i<24u && i<first+16u;++i) if(value&(1u<<(i-first))) key(i,on);
    }
    if(a<BASE+0x180u) {
        unsigned i=r/8u, reg=r%8u;
        if(reg<2u && !(value&0x8000u)) {s.voice[i].volume[reg]=direct_volume(value);s.voice[i].volume_counter[reg]=0;}
        if(reg==6u) s.voice[i].envelope=value&0x7fffu;
    }
    if((a==0x1f801d80u || a==0x1f801d82u) && !(value&0x8000u)) {
        unsigned i=(a-0x1f801d80u)/2u;s.main_volume[i]=direct_volume(value);s.main_counter[i]=0;
    }
}
/* Counter form preserves the very slow rates and stopped all-ones rate. */
static int32_t envelope_step(int32_t level,uint32_t *counter,unsigned shift,unsigned step,int down,int exponential,unsigned all_bits) {
    int32_t delta=7-(int32_t)step;if(down) delta=~delta;
    if(shift<11u) delta*=1<<(11u-shift);
    uint32_t increment=0x8000u>>(shift>11u?shift-11u:0u);
    if(exponential && !down && level>0x6000) {
        if(shift<10u) delta/=4;
        else if(shift>=11u) increment/=4u;
        else {delta/=2;increment/=2u;}
    } else if(exponential && down) delta=(int32_t)(((int64_t)delta*level)>>15);
    if((step|(shift<<2))!=all_bits && !increment) increment=1;
    *counter+=increment;
    if(!(*counter&0x8000u)) return level;
    *counter=0;
    level+=delta;return level<0?0:level>0x7fff?0x7fff:level;
}
static void adsr(unsigned i) {
    Voice *v=&s.voice[i]; unsigned a=s.reg[i*8u+4u],b=s.reg[i*8u+5u];
    unsigned shift,step=0,all=127;int down=0,exp=0;
    switch(v->stage) {
      case 0:shift=(a>>10)&31;step=(a>>8)&3;exp=a>>15;break;
      case 1:shift=(a>>4)&15;down=exp=1;all=63;break;
      case 2:shift=(b>>8)&31;step=(b>>6)&3;down=(b>>14)&1;exp=b>>15;break;
      default:shift=b&31;down=1;exp=(b>>5)&1;all=124;break;
    }
    v->envelope=envelope_step(v->envelope,&v->counter,shift,step,down,exp,all);
    if(v->stage==0 && v->envelope==0x7fff) {v->stage=1;v->counter=0;}
    if(v->stage==1 && v->envelope<=(int32_t)(((a&15u)+1u)*0x800u)) {v->stage=2;v->counter=0;}
    if(v->stage==3 && !v->envelope) v->active=0;
    s.reg[i*8u+6u]=(uint16_t)v->envelope;
}
static void volume(uint16_t reg,int32_t *level,uint32_t *counter) {
    if(!(reg&0x8000u)) {*level=direct_volume(reg);return;}
    int negative=(reg>>12)&1;
    int32_t magnitude=*level<0?-*level:*level;
    magnitude=envelope_step(magnitude,counter,(reg>>2)&31,reg&3,(reg>>13)&1,(reg>>14)&1,127);
    *level=negative?-magnitude:magnitude;
}
static void decode(unsigned i) {
    static const int coef[5][2]={{0,0},{60,0},{115,-52},{98,-55},{122,-60}};
    Voice *v=&s.voice[i];uint32_t address=v->address&RAM_MASK;
    unsigned h=s.ram[address],shift=h&15u,filter=h>>4;
    if(shift>12u) shift=9;
    if(filter>4u) filter=0;
    v->flags=s.ram[(address+1u)&RAM_MASK];
    if(v->flags&4u) s.reg[i*8u+7u]=(uint16_t)(address/8u);
    for(unsigned n=0;n<28u;++n) {
        unsigned byte=s.ram[(address+2u+n/2u)&RAM_MASK];
        int nibble=(byte>>((n&1u)*4u))&15;if(nibble&8) nibble-=16;
        int32_t sample=((nibble*4096)>>shift)+((v->hist1*coef[filter][0]+v->hist2*coef[filter][1]+32)>>6);
        int16_t value=clip(sample);v->decoded[n]=value;v->hist2=v->hist1;v->hist1=value;
    }
    v->address=(address+16u)&RAM_MASK;v->index=0;
}
static int16_t next(unsigned i) {
    Voice *v=&s.voice[i];
    if(v->index==28u) {
        if(v->flags&1u) {
            s.reg[0x19cu/2u+i/16u]|=(uint16_t)(1u<<(i%16u));
            v->address=(uint32_t)s.reg[i*8u+7u]*8u;
            if(!(v->flags&2u)) {v->active=0;v->envelope=0;s.reg[i*8u+6u]=0;return 0;}
        }
        decode(i);
    }
    return v->decoded[v->index++];
}
void fm_spu_render(int16_t *out,unsigned frames) {
    uint32_t modulation=REG(0x1f801d90u)|((uint32_t)REG(0x1f801d92u)<<16);
    uint32_t noise_mask=REG(0x1f801d94u)|((uint32_t)REG(0x1f801d96u)<<16);
    for(unsigned n=0;n<frames;++n) {
        int32_t left=0,right=0,previous_output=0;
        unsigned control=REG(0x1f801daau);
        unsigned noise_shift=(control>>10)&15u,noise_step=4u+((control>>8)&3u);
        s.noise_counter+=noise_step;
        if(s.noise_counter>=(1u<<noise_shift)) {
            s.noise_counter=0;unsigned feedback=((s.noise>>15)^(s.noise>>12)^(s.noise>>11)^(s.noise>>10)^1u)&1u;
            s.noise=((s.noise<<1)|feedback)&0xffffu;
        }
        for(unsigned i=0;i<24u;++i) {
            Voice *v=&s.voice[i];int32_t sample=0;
            if(v->active && (control&0x8000u)) {
                adsr(i);
                if(!v->primed) {v->previous=next(i);v->following=next(i);v->primed=1;}
                sample=v->previous+(((int32_t)(v->following-v->previous)*(int32_t)v->phase)>>12);
                if(noise_mask&(1u<<i)) sample=(int16_t)s.noise;
                unsigned pitch=s.reg[i*8u+2u];
                if(i && (modulation&(1u<<i))) pitch=(uint16_t)(((int32_t)(int16_t)pitch*(previous_output+32768))>>15);
                if(pitch>0x4000u) pitch=0x4000u;
                v->phase+=pitch;
                while(v->phase>=0x1000u) {v->phase-=0x1000u;v->previous=v->following;v->following=next(i);}
                sample=(sample*v->envelope)>>15;
                for(unsigned ch=0;ch<2u;++ch) volume(s.reg[i*8u+ch],&v->volume[ch],&v->volume_counter[ch]);
                left+=(sample*v->volume[0])>>15;right+=(sample*v->volume[1])>>15;
            }
            previous_output=sample;
        }
        for(unsigned ch=0;ch<2u;++ch) volume(s.reg[0x180u/2u+ch],&s.main_volume[ch],&s.main_counter[ch]);
        if(!(control&0x4000u)) left=right=0;
        out[n*2u]=clip((int32_t)(((int64_t)left*s.main_volume[0])>>15));
        out[n*2u+1u]=clip((int32_t)(((int64_t)right*s.main_volume[1])>>15));
    }
}
unsigned fm_spu_snapshot_bytes(void) {return sizeof(s);}
void fm_spu_snapshot_write(void *out) {memcpy(out,&s,sizeof(s));}
int fm_spu_snapshot_valid(const void *in,unsigned bytes) {
    if(!in || bytes!=sizeof(s)) return 0;
    const SPUState *p=in;if(p->magic!=0x31555053u || p->bytes!=sizeof(s) || p->transfer>=RAM_BYTES || (p->transfer&1u)) return 0;
    for(unsigned i=0;i<24u;++i) {const Voice *v=&p->voice[i];
        if(v->address>=RAM_BYTES || v->phase>=0x1000u || v->index>28u || v->stage>3u || v->active>1u || v->primed>1u || v->envelope<0 || v->envelope>0x7fff || v->hist1<-32768 || v->hist1>32767 || v->hist2<-32768 || v->hist2>32767) return 0;
        for(unsigned ch=0;ch<2u;++ch) if(v->volume[ch]<-32768 || v->volume[ch]>32767 || v->volume_counter[ch]>0x7fffu) return 0;
        if(v->counter>0x7fffu) return 0;
    }
    for(unsigned ch=0;ch<2u;++ch) if(p->main_volume[ch]<-32768 || p->main_volume[ch]>32767 || p->main_counter[ch]>0x7fffu) return 0;
    return 1;
}
void fm_spu_snapshot_load(const void *in) {memcpy(&s,in,sizeof(s));}
