#include <3ds.h>
#include <string.h>
#include "fm_audio.h"
#include "fm_xa.h"
#define AUDIO_BUFFERS 16u
static ndspWaveBuf waves[AUDIO_BUFFERS];
static int16_t *samples;
static unsigned next_slot, current_rate;
static int32_t init_result = -1;
static uint32_t queued;
static void fm_audio_spu_exit(void);
static void fm_audio_spu_pause(int paused);
int32_t fm_audio_status(void) { return init_result; }
uint32_t fm_audio_queued(void) { return queued; }
int fm_audio_init(void)
{
    if (samples) return 0;
    init_result = ndspInit();
    if (R_FAILED(init_result)) return -1;
    samples = linearAlloc(AUDIO_BUFFERS * FM_XA_MAX_FRAMES * 4u);
    if (!samples) { ndspExit(); init_result = -2; return -1; }
    ndspSetOutputMode(NDSP_OUTPUT_STEREO);
    ndspChnReset(0); ndspChnSetFormat(0, NDSP_FORMAT_STEREO_PCM16);
    ndspChnSetInterp(0, NDSP_INTERP_POLYPHASE);
    float mix[12] = {1.0f, 1.0f}; ndspChnSetMix(0, mix);
    fm_audio_reset(); return 0;
}
void fm_audio_reset(void)
{
    if (samples) ndspChnWaveBufClear(0);
    memset(waves, 0, sizeof(waves)); next_slot = current_rate = queued = 0u;
}
void fm_audio_exit(void)
{
    if (!samples) return;
    fm_audio_spu_exit(); ndspChnWaveBufClear(0); ndspExit(); linearFree(samples); samples = NULL;
}
void fm_audio_pause(int paused) { if (samples) ndspChnSetPaused(0, paused != 0); fm_audio_spu_pause(paused); }
int fm_audio_ready(void)
{
    if (!samples) return 1; /* Decode/video still progress if DSP is unavailable. */
    return waves[next_slot].status == NDSP_WBUF_FREE || waves[next_slot].status == NDSP_WBUF_DONE;
}
int fm_audio_push(const int16_t *pcm, unsigned frames, unsigned rate)
{
    if (!samples) return 1;
    if (!pcm || frames > FM_XA_MAX_FRAMES || !frames || !fm_audio_ready()) return 0;
    if (current_rate != rate) { ndspChnWaveBufClear(0); memset(waves, 0, sizeof(waves));
        next_slot = 0; current_rate = rate; ndspChnSetRate(0, (float)rate); }
    ndspWaveBuf *w = &waves[next_slot]; memset(w, 0, sizeof(*w));
    int16_t *dst = samples + next_slot * FM_XA_MAX_FRAMES * 2u;
    memcpy(dst, pcm, frames * 4u); DSP_FlushDataCache(dst, frames * 4u);
    w->data_vaddr = dst; w->nsamples = frames; ndspChnWaveBufAdd(0, w);
    next_slot = (next_slot + 1u) % AUDIO_BUFFERS; ++queued; return 1;
}

void fm_audio_snapshot_save(FMAudioSnapshot *out)
{
    memset(out,0,sizeof(*out));
    if (!samples) return;
    out->rate=current_rate;
    for (unsigned i=0;i<AUDIO_BUFFERS;++i) {
        unsigned slot=(next_slot+i)%AUDIO_BUFFERS;
        if (waves[slot].status == NDSP_WBUF_QUEUED || waves[slot].status == NDSP_WBUF_PLAYING) {
            unsigned n=out->count++;
            out->frames[n]=waves[slot].nsamples;
            memcpy(out->pcm[n],samples+slot*FM_XA_MAX_FRAMES*2u,out->frames[n]*4u);
        }
    }
}
int fm_audio_snapshot_valid(const FMAudioSnapshot *in)
{
    if (!in || in->count > AUDIO_BUFFERS || (in->count && in->rate != 18900u && in->rate != 37800u)) return 0;
    for (unsigned i=0;i<in->count;++i)
        if (!in->frames[i] || in->frames[i] > FM_XA_MAX_FRAMES) return 0;
    return 1;
}
void fm_audio_snapshot_load(const FMAudioSnapshot *in)
{
    fm_audio_reset();
    for (unsigned i=0;i<in->count;++i) fm_audio_push(in->pcm[i],in->frames[i],in->rate);
}

#define SPU_BUFFERS 4u
#define SPU_SAMPLES 735u
static ndspWaveBuf spu_waves[SPU_BUFFERS];
static int16_t *spu_samples;
static unsigned spu_slot;
void fm_audio_spu_reset(void)
{
    if(spu_samples) ndspChnWaveBufClear(1);
    memset(spu_waves,0,sizeof(spu_waves));spu_slot=0;
}
int fm_audio_spu_push(const int16_t *pcm,unsigned frames)
{
    if(!samples) return 1;
    if(!pcm || !frames || frames>SPU_SAMPLES) return 0;
    if(!spu_samples) {
        spu_samples=linearAlloc(SPU_BUFFERS*SPU_SAMPLES*4u);
        if(!spu_samples) return 0;
        ndspChnReset(1);ndspChnSetFormat(1,NDSP_FORMAT_STEREO_PCM16);
        ndspChnSetInterp(1,NDSP_INTERP_POLYPHASE);ndspChnSetRate(1,44100.0f);
        float mix[12]={1.0f,1.0f};ndspChnSetMix(1,mix);fm_audio_spu_reset();
    }
    ndspWaveBuf *w=&spu_waves[spu_slot];
    if(w->status!=NDSP_WBUF_FREE && w->status!=NDSP_WBUF_DONE) return 0;
    int16_t *dst=spu_samples+spu_slot*SPU_SAMPLES*2u;
    memcpy(dst,pcm,frames*4u);DSP_FlushDataCache(dst,frames*4u);
    memset(w,0,sizeof(*w));w->data_vaddr=dst;w->nsamples=frames;
    ndspChnWaveBufAdd(1,w);spu_slot=(spu_slot+1u)%SPU_BUFFERS;return 1;
}
static void fm_audio_spu_exit(void)
{
    if(!spu_samples) return;
    ndspChnWaveBufClear(1);linearFree(spu_samples);spu_samples=NULL;spu_slot=0;
}
static void fm_audio_spu_pause(int paused)
{
    if(spu_samples) ndspChnSetPaused(1,paused!=0);
}
