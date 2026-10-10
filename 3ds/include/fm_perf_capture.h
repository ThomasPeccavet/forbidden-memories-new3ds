#ifndef FM_PERF_CAPTURE_H
#define FM_PERF_CAPTURE_H
#include <stdint.h>
#include <string.h>
#define FM_CAPTURE_DURATION_MS 10000u
#define FM_CAPTURE_ROWS 4096u
/* Host-only telemetry, never serialized with the guest snapshot. */
typedef struct {
 uint32_t elapsed_ms,start_pc,end_pc,frame,images,running;
 uint32_t pre_ms,render_ms,vblank_ms,gfx_ms,wait_ms,loop_ms,wait_reason;
 uint32_t dma_calls,irq_calls,vsyncs,native_probes,cd_sectors;
 uint64_t dma_us,seq_ms,overlay_instructions,clock_debt;
} FMPerfCaptureRow;
typedef struct {
 uint32_t pc,calls,max_us;
 uint64_t instructions,total_us;
} FMPerfCaptureHot;
#define FM_CAPTURE_HOT_SLOTS 128u
typedef struct {
 uint64_t start_ms;
 unsigned armed,active,count,dropped,hot_dropped,elapsed_ms;
 FMPerfCaptureHot hot[FM_CAPTURE_HOT_SLOTS];
 FMPerfCaptureRow rows[FM_CAPTURE_ROWS];
} FMPerfCapture;
static inline void fm_capture_arm(FMPerfCapture *c) {
 c->armed=1; c->active=0; c->count=c->dropped=0;
}
static inline int fm_capture_begin(FMPerfCapture *c,uint64_t now) {
 if(!c->armed)return 0;
 c->armed=0;c->active=1;c->start_ms=now;c->count=c->dropped=0;
 c->hot_dropped=c->elapsed_ms=0;memset(c->hot,0,sizeof(c->hot));return 1;
}
static inline int fm_capture_push(FMPerfCapture *c,uint64_t now,
 const FMPerfCaptureRow *row) {
 if(!c->active)return 0;
 FMPerfCaptureRow r=*row;
 r.elapsed_ms=(uint32_t)(now>=c->start_ms?now-c->start_ms:0);
 c->elapsed_ms=r.elapsed_ms;
 if(c->count<FM_CAPTURE_ROWS)c->rows[c->count++]=r;else ++c->dropped;
 /* Complete at the first safe loop boundary at/after 10s, never mid-call. */
 return now>=c->start_ms && now-c->start_ms>=FM_CAPTURE_DURATION_MS;
}
static inline void fm_capture_hot(FMPerfCapture *c,uint32_t pc,
 uint32_t instructions,uint32_t us) {
 if(!c->active)return;
 for(unsigned i=0;i<FM_CAPTURE_HOT_SLOTS;++i) {
  FMPerfCaptureHot *h=&c->hot[i];
  if(!h->calls || h->pc==pc) {
   h->pc=pc;++h->calls;h->instructions+=instructions;h->total_us+=us;
   if(us>h->max_us)h->max_us=us;
   return;
  }
 }
 ++c->hot_dropped;
}
#endif
