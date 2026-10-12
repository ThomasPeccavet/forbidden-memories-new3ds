#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "fm_pica_plan.h"
static uint16_t ram[1024*512];
static unsigned char seen[256*256];
static uint32_t xy(int x,int y){return (uint16_t)x|((uint32_t)(uint16_t)y<<16);}
static int plan(FMPicaPlan *q,uint32_t *p,unsigned n,uint16_t pg){return fm_pica_plan(q,p,n,pg,0,0,0,0,0,639,255,0,0);}
int main(void){
 for(unsigned p=0;p<65536;p++)assert(fm_pica_psx(fm_pica_rgba((uint16_t)p,0))==p);
 assert((fm_pica_rgba(1,1)&255)==128);assert((fm_pica_rgba(0x8000,1)&255)==255);
 assert(fm_pica_rgba(0,1)==0);assert(fm_pica_rgba(0x8000,1)!=0);
 for(unsigned y=0;y<256;y++)for(unsigned x=0;x<256;x++){unsigned i=fm_pica_morton(x,y,256);assert(i<sizeof seen&&!seen[i]);seen[i]=1;}
 /* All 4/8/15-bit texels match independent packed-address calculation,
  * including page/palette wrap and source bit15. */
 for(unsigned i=0;i<1024*512;i++)ram[i]=(uint16_t)(i*379u+17);
 for(unsigned d=0;d<3;d++)for(unsigned u=0;u<256;u++)for(unsigned v=0;v<256;v++){
  uint16_t pg=15|16|(d<<7),cl=(511<<6)|63;unsigned x=(960+(u>>(2-d)))%1024,y=(256+v)%512;
  uint16_t w=ram[y*1024+x],expect=w;
  if(d<2){unsigned n=d==0?(w>>(4*(u%4)))%16:(w>>(8*(u%2)))%256;expect=ram[511*1024+(1008+n)%1024];}
  assert(fm_pica_texel(ram,pg,cl,u,v)==expect);
 }
 for(unsigned op=0x20;op<0x40;op++){
  unsigned count=(op&8)?4:3,sh=(op&16)!=0,tx=(op&4)!=0,stride=1+sh+tx;
  unsigned n=1+count*stride-sh;uint32_t p[12]={0};p[0]=(op<<24)|0x123456;
  for(unsigned i=0;i<count;i++){unsigned k=1+i*stride;p[k]=xy(10+(i&1)*30,20+(i>>1)*40);if(tx)p[k+1]=i*0x101+7;if(sh)p[k-1]=(i?0x112233:p[0]);}
  if(tx){p[2]|=0x12340000;p[sh?5:4]|=0x000a0000;}
  FMPicaPlan q,before;memset(&q,0x5a,sizeof q);before=q;int ok=plan(&q,p,n,0);
  if(op&2){assert(!ok&&!memcmp(&q,&before,sizeof q));continue;}
  if(!ok)fprintf(stderr,"rejected opcode %02x page %08x n=%u\n",op,tx?p[sh?5:4]:0,n);
  assert(ok&&q.count==count&&q.textured==(int)tx);assert(q.vertex[0].x==10&&q.vertex[0].y==20&&q.vertex[0].a==0.5f);
  if(tx)assert(q.page==10&&q.clut==0x1234);
  before=q;assert(!plan(&q,p,n-1,0)&&!memcmp(&q,&before,sizeof q));
 }
 uint32_t sprite[]={0x64808080,xy(-5,6),0x4000faf8,xy(16,8)};FMPicaPlan q;
 assert(plan(&q,sprite,4,10));assert(q.vertex[3].x==11&&q.vertex[3].y==14&&q.vertex[3].u==264&&q.vertex[3].v==258);
 assert(!fm_pica_plan(&q,sprite,4,10,0,1,0,0,0,319,255,0,0));
 assert(!fm_pica_plan(&q,sprite,4,10,1,0,0,0,0,319,255,0,0));
 assert(!plan(&q,sprite,4,0x180));assert(!plan(&q,sprite,4,0x3000));
 uint32_t line[]={0x40808080,0,0};assert(!plan(&q,line,3,0));
 puts("PICA plan: packet layouts, affine vertices, 65536 pixel roundtrips, wrapped textures and atomic fallback OK");
}
