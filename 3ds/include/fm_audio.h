#pragma once
#include <stdint.h>
int fm_audio_init(void);
void fm_audio_exit(void);
void fm_audio_reset(void);
void fm_audio_pause(int paused);
int fm_audio_ready(void);
int fm_audio_push(const int16_t *pcm, unsigned frames, unsigned rate);
int32_t fm_audio_status(void);
uint32_t fm_audio_queued(void);

#define FM_AUDIO_SNAPSHOT_BUFFERS 16u
#define FM_AUDIO_SNAPSHOT_FRAMES 4032u
typedef struct FMAudioSnapshot {
    uint32_t count, rate, frames[FM_AUDIO_SNAPSHOT_BUFFERS];
    int16_t pcm[FM_AUDIO_SNAPSHOT_BUFFERS][FM_AUDIO_SNAPSHOT_FRAMES * 2u];
} FMAudioSnapshot;
/* Pause the DSP before capture. The playing buffer resumes from its start. */
void fm_audio_snapshot_save(FMAudioSnapshot *out);
int fm_audio_snapshot_valid(const FMAudioSnapshot *in);
void fm_audio_snapshot_load(const FMAudioSnapshot *in);

/* Independent SPU PCM stream; never changes the XA channel's sample rate. */
int fm_audio_spu_push(const int16_t *pcm, unsigned frames);
void fm_audio_spu_reset(void);

/* Advance at 44.1kHz wall time independently of display VBlanks. */
void fm_audio_spu_clock(uint64_t now_ms, int running);
void fm_audio_spu_dump(const char *path);
