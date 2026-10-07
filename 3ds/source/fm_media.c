#include "fm_media.h"
#include "fm_memory.h"
#include "fm_platform.h"
#include "fm_audio.h"
#include "fm_xa.h"
#include "mdec.h"
#include "fm_mdec_clock.h"
#include <string.h>

uint64_t fm_mdec_host_cycles, fm_mdec_host_frame;
#define STR_CHUNKS 20u
#define STR_PAYLOAD 2016u
static struct {
    uint8_t headers[STR_CHUNKS][32], data[STR_CHUNKS][STR_PAYLOAD];
    uint32_t number, count, seen, last_published;
    int complete;
} str;
static FMXaDecoder xa;
static int active;
static uint8_t mode, filter_file, filter_channel, index_reg;
static uint8_t pending_volume[4] = {128, 0, 0, 128};
static uint8_t volume[4] = {128, 0, 0, 128};
static uint32_t next_lba, raw_sectors, errors, xa_sectors, xa_frames, filtered;
static uint32_t video_sectors, video_frames, stalls, invalid_frames, last_width, last_height;
static uint32_t entry_str, entry_vlc, entry_out;
static uint16_t le16(const uint8_t *p) { return p[0] | (uint16_t)p[1] << 8; }
static uint32_t le32(const uint8_t *p) { return le16(p) | (uint32_t)le16(p + 2) << 16; }
static int clip16(int v) { return v < -32768 ? -32768 : v > 32767 ? 32767 : v; }
static int guest_span(uint32_t base, uint32_t size)
{ return base >= 0x80000000u && base <= 0x80200000u && size <= 0x80200000u - base; }

static int publish_frame(void)
{
    uint32_t base = fm_memory_read_word(0x800F70E4u);
    uint32_t slots = fm_memory_read_word(0x800F70F0u);
    uint32_t producer = fm_memory_read_word(0x800F70D4u);
    if (!slots || slots > 128u || str.count >= slots || producer >= slots
        || !guest_span(base, slots * (32u + STR_PAYLOAD))) return 0;
    uint32_t start = producer;
    /* Reserve the entire frame before writing; never overwrite an unread one. */
    if (start + str.count >= slots) start = 0;
    if (start != producer && fm_memory_read_half(base + producer * 32u)) return 0;
    for (unsigned i = 0; i < str.count; ++i)
        if (fm_memory_read_half(base + (start + i) * 32u)) return 0;
    if (start != producer) fm_memory_write_half(base + producer * 32u, 1u); /* native wrap marker */
    for (unsigned i = 0; i < str.count; ++i) {
        uint32_t header = base + (start + i) * 32u;
        uint32_t data = base + slots * 32u + (start + i) * STR_PAYLOAD;
        fm_memory_copy_to_ram(header, str.headers[i], 32u);
        fm_memory_copy_to_ram(data, str.data[i], STR_PAYLOAD);
        fm_memory_write_half(header, i == 0u ? 2u : 3u);
    }
    fm_memory_write_word(0x800F70D4u, start + str.count);
    fm_memory_write_word(0x800F70D8u, start + str.count);
    fm_memory_write_word(0x800F7108u, le32(str.headers[str.count - 1u] + 28u));
    fm_memory_write_word(0x800F710Cu, str.number);
    fm_memory_write_word(0x800F7100u, 0u);
    ++video_frames; str.last_published = str.number; str.complete = 0; str.seen = 0;
    return 1;
}

int fm_media_str_sector(const uint8_t raw[2352])
{
    if (str.complete && !publish_frame()) return 0;
    const uint8_t *p = raw + 24;
    if (le16(p) != 0x0160u || (le16(p + 2u) & 0xFC00u) != 0x8000u) return -1;
    uint32_t chunk = le16(p + 4u), count = le16(p + 6u), number = le32(p + 8u);
    uint32_t size = le32(p + 12u), w = le16(p + 16u), h = le16(p + 18u);
    if (!count || count > STR_CHUNKS || chunk >= count || !size || size > count * STR_PAYLOAD
        || !w || w > 480u || !h || h > 256u || (w & 15u) || (h & 15u)) return -1;
    if (str.last_published == number) return 1;
    if (!str.seen || str.number != number) { str.number = number; str.count = count; str.seen = 0; }
    if (str.count != count) return -1;
    if (str.seen && (le32(str.headers[0] + 12u) != size
        || le16(str.headers[0] + 16u) != w || le16(str.headers[0] + 18u) != h)) return -1;
    /* First chunk is required first; malformed/out-of-order frames are discarded. */
    if (!str.seen && chunk != 0u) return -1;
    memcpy(str.headers[chunk], p, 32u); memcpy(str.data[chunk], p + 32u, STR_PAYLOAD);
    memcpy(str.headers[chunk] + 28u, raw + 12u, 3u); str.headers[chunk][31] = 0;
    str.seen |= 1u << chunk; ++video_sectors; last_width = w; last_height = h;
    if (str.seen == (1u << count) - 1u) { str.complete = 1; publish_frame(); }
    return 1;
}

void fm_media_reset(void)
{
    fm_audio_reset(); fm_xa_reset(&xa); memset(&str, 0, sizeof(str)); str.last_published = UINT32_MAX;
    active = 0; next_lba = raw_sectors = errors = xa_sectors = xa_frames = filtered = 0;
    video_sectors = video_frames = stalls = invalid_frames = last_width = last_height = 0;
    entry_str = entry_vlc = entry_out = 0; mode = filter_file = filter_channel = index_reg = 0;
    const uint8_t defaults[4] = {128, 0, 0, 128};
    memcpy(volume, defaults, 4); memcpy(pending_volume, defaults, 4);
}
void fm_media_command(uint32_t cmd, uint32_t params, int raw_mode, uint32_t lba)
{
    if (raw_mode >= 0) mode = (uint8_t)raw_mode;
    if (cmd == 0x0Eu && params && raw_mode < 0) mode = fm_memory_read_byte(params);
    if (cmd == 0x0Du && params) { filter_file = fm_memory_read_byte(params);
        filter_channel = fm_memory_read_byte(params + 1u); fm_xa_reset(&xa); }
    if (cmd == 0x1Bu) { active = 1; next_lba = lba; fm_xa_reset(&xa);
        memset(&str, 0, sizeof(str)); str.last_published = UINT32_MAX; fm_audio_reset(); }
    else if (cmd == 0x08u || cmd == 0x09u || cmd == 0x0Au || cmd == 0x06u) {
        active = 0; fm_audio_reset(); if (cmd == 0x0Au) mode = 0; }
}
void fm_media_poll(uint32_t target, int running)
{
    fm_audio_pause(!running);
    if (!active || !running) return;
    if (str.complete && !publish_frame()) { ++stalls; return; }
    uint8_t raw[2352]; static int16_t pcm[FM_XA_MAX_FRAMES * 2u];
    for (unsigned budget = 0; budget < 32u && next_lba <= target; ++budget) {
        if (!fm_audio_ready()) { ++stalls; return; }
        if (next_lba >= 233175u || fm_disc_read_raw_sector(next_lba, raw)) {
            ++errors; active = 0; return; }
        int audio = (mode & 0x40u) && (raw[18] & 0x44u) == 0x44u;
        if (audio && (mode & 8u) && (raw[16] != filter_file || raw[17] != filter_channel)) {
            ++filtered;
        } else if (audio) {
            unsigned rate; int frames = fm_xa_decode(&xa, raw, pcm, FM_XA_MAX_FRAMES, &rate);
            if (frames < 0) ++errors;
            else if (frames) {
                for (int i = 0; i < frames; ++i) {
                    int l = pcm[i * 2], r = pcm[i * 2 + 1];
                    pcm[i * 2] = (int16_t)clip16((l * volume[0] + r * volume[2]) >> 7);
                    pcm[i * 2 + 1] = (int16_t)clip16((l * volume[1] + r * volume[3]) >> 7);
                }
                fm_audio_push(pcm, (unsigned)frames, rate); ++xa_sectors; xa_frames += (unsigned)frames;
            }
        } else if ((mode & 0x20u) && le16(raw + 24) == 0x0160u) {
            int rc = fm_media_str_sector(raw);
            if (!rc) { ++stalls; return; } if (rc < 0) ++invalid_frames;
        }
        ++next_lba; ++raw_sectors;
        if (str.complete) return;
    }
}
void fm_media_guest_entry(CPUState *cpu, uint32_t phys)
{
    if (!cpu) return;
    if (phys == 0x00091084u) fm_memory_mdec_set_callback(cpu->gpr[4], cpu->gpr[28]);
    if (phys == 0x00078B58u) ++entry_str;
    if (phys == 0x000914A8u) ++entry_vlc;
    if (phys == 0x00091228u) ++entry_out;
}
void fm_media_cd_write(uint32_t addr, uint8_t v)
{
    unsigned reg = addr & 3u;
    if (!reg) { index_reg = v & 3u; return; }
    if (index_reg == 2u && reg == 2u) pending_volume[0] = v;
    if (index_reg == 2u && reg == 3u) pending_volume[1] = v;
    if (index_reg == 3u && reg == 1u) pending_volume[3] = v;
    if (index_reg == 3u && reg == 2u) pending_volume[2] = v;
    if (index_reg == 3u && reg == 3u && (v & 0x20u)) memcpy(volume, pending_volume, 4);
}
uint8_t fm_media_cd_read(uint32_t addr)
{ return (addr & 3u) == 0u ? (uint8_t)(0x18u | index_reg) : 0u; }
void fm_media_dump(FILE *f)
{
    MDECDebugState m; mdec_debug_get_state(&m);
    MDECPerf perf; mdec_perf_get(&perf);
    uint64_t elapsed = perf.last_ms - perf.first_ms;
    fprintf(f, "movie_perf=decoded:%lu elapsed_ms:%llu decode_ms:%llu fps_x100:%llu\n",
        (unsigned long)perf.frames, (unsigned long long)elapsed,
        (unsigned long long)perf.decode_ms,
        (unsigned long long)(elapsed && perf.frames > 1u
            ? (perf.frames - 1u) * 100000ull / elapsed : 0));
    fprintf(f, "media_raw=%lu next=%08lX errors=%lu active=%d\n"
        "xa_decoded=%lu pcm_frames=%lu filtered=%lu dsp=%08lX queued=%lu\n"
        "str_sectors=%lu frames=%lu invalid=%lu stalls=%lu size=%lux%lu\n"
        "str_entries=%lu vlc_entries=%lu out_entries=%lu\n"
        "mdec_blocks=%lu macroblocks=%lu in=%lu out=%lu underflows=%lu stop=%lu\n",
        (unsigned long)raw_sectors, (unsigned long)next_lba, (unsigned long)errors, active,
        (unsigned long)xa_sectors, (unsigned long)xa_frames, (unsigned long)filtered,
        (unsigned long)(uint32_t)fm_audio_status(), (unsigned long)fm_audio_queued(),
        (unsigned long)video_sectors, (unsigned long)video_frames, (unsigned long)invalid_frames,
        (unsigned long)stalls, (unsigned long)last_width, (unsigned long)last_height,
        (unsigned long)entry_str, (unsigned long)entry_vlc, (unsigned long)entry_out,
        (unsigned long)m.decode_blocks, (unsigned long)m.decode_macroblocks,
        (unsigned long)m.dma_in_words, (unsigned long)m.dma_out_words,
        (unsigned long)m.dma_read_underflows, (unsigned long)m.decode_stop_reason);
}
