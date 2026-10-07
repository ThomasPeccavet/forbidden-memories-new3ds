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
