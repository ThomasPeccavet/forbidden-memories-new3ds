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
    ndspChnWaveBufClear(0); ndspExit(); linearFree(samples); samples = NULL;
}
void fm_audio_pause(int paused) { if (samples) ndspChnSetPaused(0, paused != 0); }
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
