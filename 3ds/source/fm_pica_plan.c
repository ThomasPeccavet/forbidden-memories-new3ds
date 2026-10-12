#include "fm_pica_plan.h"
static int coordinate(unsigned v,int offset)
{unsigned p=(v+(unsigned)offset)&2047;return (int)(p^1024)-1024;}
static void vertex(FMPicaVertex *v,uint32_t xy,uint32_t uv,uint32_t color,int ox,int oy)
{v->x=(float)coordinate(xy&65535,ox);v->y=(float)coordinate(xy>>16,oy);
 v->u=(float)(uv&255);v->v=(float)((uv>>8)&255);
 v->r=(float)(color&255)/255;v->g=(float)((color>>8)&255)/255;
 v->b=(float)((color>>16)&255)/255;v->a=0.5f;}
int fm_pica_plan(FMPicaPlan *out,const uint32_t *p,unsigned words,uint16_t page,
 uint32_t window,int mask_set,int mask_check,int left,int top,int right,int bottom,int ox,int oy)
{
 if(!out||!p||!words||mask_set||mask_check||(window&0xfffffu)||left<0||top<0||right>1023||bottom>511||left>right||top>bottom)return 0;
 unsigned op=p[0]>>24;if(op&2)return 0;FMPicaPlan q;memset(&q,0,sizeof q);
 q.left=left;q.top=top;q.right=right;q.bottom=bottom;q.raw=op&1;
 if(op>=0x20&&op<=0x3f){
  int shaded=(op&16)!=0; q.textured=(op&4)!=0;q.count=(op&8)?4:3;
  unsigned stride=1+(unsigned)shaded+(unsigned)q.textured;
  unsigned need=1+q.count*stride-(unsigned)shaded;if(words!=need)return 0;
  for(unsigned i=0;i<q.count;i++){
   unsigned xy=1+i*stride;vertex(&q.vertex[i],p[xy],q.textured?p[xy+1]:0,shaded?p[xy-1]:p[0],ox,oy);
  }
  if(q.textured){q.clut=p[2]>>16;page=p[shaded?5:4]>>16;}
  for(unsigned i=0;i<q.count;i++)for(unsigned j=0;j<i;j++)
   if(q.vertex[i].x-q.vertex[j].x>1023||q.vertex[j].x-q.vertex[i].x>1023||q.vertex[i].y-q.vertex[j].y>511||q.vertex[j].y-q.vertex[i].y>511)return 0;
 }else if(op>=0x60&&op<=0x7f){
  q.textured=(op&4)!=0;unsigned fixed=(op>>3)&3;
  unsigned need=2+(unsigned)q.textured+!fixed;if(words!=need)return 0;
  if(page&0x3000)return 0;
  unsigned w,h;
  if(fixed)w=h=fixed==1?1:fixed==2?8:16;
  else{w=p[need-1]&1023;h=(p[need-1]>>16)&511;}
  if(!w||!h)return 0;
  vertex(&q.vertex[0],p[1],q.textured?p[2]:0,p[0],ox,oy);
  q.count=4;for(unsigned i=1;i<4;i++)q.vertex[i]=q.vertex[0];
  q.vertex[1].x+=w;q.vertex[1].u+=w;q.vertex[2].y+=h;q.vertex[2].v+=h;
  q.vertex[3].x+=w;q.vertex[3].y+=h;q.vertex[3].u+=w;q.vertex[3].v+=h;
  if(q.textured)q.clut=p[2]>>16;
 }else return 0;
 q.page=page;if(q.textured&&(((page>>7)&3)==3||(page&0x800)))return 0;
 *out=q;return 1;
}
