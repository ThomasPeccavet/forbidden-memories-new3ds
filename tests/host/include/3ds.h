#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
/* The memory module only uses the platform clock for profiling. */
static inline uint64_t osGetTime(void) { return 0; }
typedef struct { void *data_vaddr; uint32_t nsamples; volatile unsigned status; } ndspWaveBuf;
#define NDSP_WBUF_FREE 0u
#define NDSP_WBUF_QUEUED 1u
#define NDSP_WBUF_PLAYING 2u
#define NDSP_WBUF_DONE 3u
#define NDSP_OUTPUT_STEREO 1
#define NDSP_FORMAT_STEREO_PCM16 6
#define NDSP_INTERP_POLYPHASE 0
#define R_FAILED(r) ((r) < 0)
int32_t ndspInit(void);
void ndspExit(void);
void *linearAlloc(size_t);
void linearFree(void *);
void ndspSetOutputMode(int);
void ndspChnReset(int);
void ndspChnSetFormat(int, unsigned);
void ndspChnSetInterp(int, int);
void ndspChnSetMix(int, float[12]);
void ndspChnSetRate(int, float);
void ndspChnWaveBufClear(int);
void ndspChnWaveBufAdd(int, ndspWaveBuf *);
void ndspChnSetPaused(int, bool);
void DSP_FlushDataCache(void *, uint32_t);

static inline uint64_t svcGetSystemTick(void) { return 0; }
