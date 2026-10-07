#pragma once
#include <stddef.h>
#include <stdint.h>
#define FM_XA_MAX_FRAMES 4032u
typedef struct FMXaDecoder {
    int32_t history[2][2];
    uint8_t file, channel, coding, valid;
} FMXaDecoder;
void fm_xa_reset(FMXaDecoder *decoder);
/* Returns stereo PCM frames, zero for non-audio, -1 for invalid/capacity.
 * Output is native 37800/18900 Hz; the host DSP performs rate conversion. */
int fm_xa_decode(FMXaDecoder *decoder, const uint8_t raw[2352],
                 int16_t *stereo, size_t capacity_frames, unsigned *rate);
