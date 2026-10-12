#include "fm_xa.h"
#include <string.h>

void fm_xa_reset(FMXaDecoder *d) { if (d) memset(d, 0, sizeof(*d)); }
static int clip16(int v) { return v < -32768 ? -32768 : v > 32767 ? 32767 : v; }
static int decode_sample(FMXaDecoder *d, unsigned ch, int value, unsigned bits,
                         uint8_t header)
{
    static const int positive[4] = {0, 60, 115, 98};
    static const int negative[4] = {0, 0, -52, -55};
    unsigned shift = header & 15u, filter = (header >> 4) & 3u;
    if (shift > 12u) shift = 9u;
    /* Multiplication avoids undefined signed left shifts on negative samples. */
    int sample = (value * (bits == 4u ? 4096 : 256)) >> shift;
    sample += (d->history[ch][0] * positive[filter]
            + d->history[ch][1] * negative[filter] + 32) >> 6;
    sample = clip16(sample);
    d->history[ch][1] = d->history[ch][0]; d->history[ch][0] = sample;
    return sample;
}
int fm_xa_decode(FMXaDecoder *d, const uint8_t raw[2352], int16_t *out,
                 size_t cap, unsigned *rate)
{
    if (!d || !raw || !out || !rate) return -1;
    if (raw[15] != 2u || memcmp(raw + 16, raw + 20, 4)) return -1;
    if ((raw[18] & 0x44u) != 0x44u) return 0;
    uint8_t coding = raw[19];
    /* Reserved channel/rate/word-size fields and emphasis are unsupported. */
    if (coding & 0xEAu) return -1;
    unsigned stereo = coding & 1u, bits = (coding & 16u) ? 8u : 4u;
    unsigned units = bits == 4u ? 8u : 4u;
    unsigned frames = 18u * 28u * units / (stereo ? 2u : 1u);
    if (cap < frames) return -1;
    if (!d->valid || d->file != raw[16] || d->channel != raw[17] || d->coding != coding) {
        fm_xa_reset(d); d->valid = 1; d->file = raw[16];
        d->channel = raw[17]; d->coding = coding;
    }
    *rate = (coding & 4u) ? 18900u : 37800u;
    unsigned frame = 0;
    for (unsigned g = 0; g < 18u; ++g) {
        const uint8_t *group = raw + 24u + g * 128u;
        for (unsigned u = 0; u < units; ++u) {
            unsigned channel = stereo ? u & 1u : 0u;
            for (unsigned i = 0; i < 28u; ++i) {
                uint8_t data = group[16u + i * 4u + (bits == 4u ? u / 2u : u)];
                int v;
                if (bits == 4u) { v = (data >> ((u & 1u) * 4u)) & 15u; if (v >= 8) v -= 16; }
                else { v = data; if (v >= 128) v -= 256; }
                int sample = decode_sample(d, channel, v, bits, group[4u + u]);
                unsigned pos = frame + i;
                out[pos * 2u + channel] = (int16_t)sample;
                if (!stereo) out[pos * 2u + 1u] = (int16_t)sample;
            }
            if (!stereo || channel == 1u) frame += 28u;
        }
    }
    return (int)frames;
}
