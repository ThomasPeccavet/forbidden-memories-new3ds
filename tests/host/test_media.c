#include <3ds.h>
#include "fm_media.h"
#include "fm_audio.h"
#include "fm_memory.h"
#include "fm_platform.h"
#include "fm_xa.h"
#include "mdec.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>
uint32_t g_debug_last_store_pc;
void fm_gpu_gp0_write(uint32_t v) { (void)v; assert(0); }
void fm_gpu_gp0_words(const uint32_t *v, uint32_t n) { (void)v; (void)n; assert(0); }
void fm_gpu_gp1_write(uint32_t v) { (void)v; assert(0); }
uint32_t fm_gpu_status(void) { assert(0); return 0; }
void fm_gpu_b13532_profile_reset(void) { assert(0); }
static int dsp_fail, paused;
static unsigned queued, clears, flush_bytes;
static float audio_rate;
static ndspWaveBuf *audio_queue[256];
int32_t ndspInit(void) { return dsp_fail ? -123 : 0; }
void ndspExit(void) {}
void *linearAlloc(size_t n) { return malloc(n); }
void linearFree(void *p) { free(p); }
void ndspSetOutputMode(int mode) { assert(mode == NDSP_OUTPUT_STEREO); }
void ndspChnReset(int ch) { assert(ch == 0); }
void ndspChnSetFormat(int ch, unsigned format) { assert(ch == 0 && format == NDSP_FORMAT_STEREO_PCM16); }
void ndspChnSetInterp(int ch, int interp) { assert(ch == 0 && interp == NDSP_INTERP_POLYPHASE); }
void ndspChnSetMix(int ch, float mix[12]) { assert(ch == 0 && mix[0] == 1 && mix[1] == 1); }
void ndspChnSetRate(int ch, float rate) { assert(ch == 0); audio_rate = rate; }
void ndspChnWaveBufClear(int ch) { assert(ch == 0); ++clears;
    for (unsigned i = 0; i < queued; ++i) audio_queue[i]->status = NDSP_WBUF_FREE;
    queued = 0; }
void ndspChnWaveBufAdd(int ch, ndspWaveBuf *w) { assert(ch == 0 && queued < 256);
    w->status = NDSP_WBUF_QUEUED; audio_queue[queued++] = w; }
void ndspChnSetPaused(int ch, bool p) { assert(ch == 0); paused = p; }
void DSP_FlushDataCache(void *p, uint32_t size) { assert(p); flush_bytes = size; }
static uint8_t ram[2 * 1024 * 1024];
static uint8_t raw[2352];
static int16_t pcm[FM_XA_MAX_FRAMES * 2];
static void put16(uint8_t *p, unsigned v) { p[0] = v; p[1] = v >> 8; }
static void put32(uint8_t *p, uint32_t v) { put16(p, v); put16(p + 2, v >> 16); }
static void raw_sector(unsigned coding)
{
    memset(raw, 0, sizeof(raw)); raw[0] = raw[11] = 0;
    memset(raw + 1, 255, 10); raw[12] = 0; raw[13] = 2; raw[14] = 0; raw[15] = 2;
    raw[16] = raw[20] = 1; raw[17] = raw[21] = 2;
    raw[18] = raw[22] = 0x64; raw[19] = raw[23] = coding;
    for (unsigned g = 0; g < 18; ++g) {
        memset(raw + 24 + g * 128, 12, 16);
        memset(raw + 24 + g * 128 + 16, 0xF1, 112);
    }
}
static void xa_test(void)
{
    FMXaDecoder d; fm_xa_reset(&d); unsigned rate;
    raw_sector(1);
    assert(fm_xa_decode(&d, raw, pcm, FM_XA_MAX_FRAMES, &rate) == 2016 && rate == 37800);
    for (unsigned i = 0; i < 2016; ++i) assert(pcm[i * 2] == 1 && pcm[i * 2 + 1] == -1);
    raw_sector(4); fm_xa_reset(&d);
    assert(fm_xa_decode(&d, raw, pcm, FM_XA_MAX_FRAMES, &rate) == 4032 && rate == 18900);
    for (unsigned u = 0; u < 144; ++u) for (unsigned i = 0; i < 28; ++i) {
        int expected = (u & 1) ? -1 : 1;
        assert(pcm[(u * 28 + i) * 2] == expected && pcm[(u * 28 + i) * 2 + 1] == expected);
    }
    raw_sector(0x11); fm_xa_reset(&d);
    for (unsigned g = 0; g < 18; ++g) memset(raw + 24 + g * 128, 8, 16);
    assert(fm_xa_decode(&d, raw, pcm, FM_XA_MAX_FRAMES, &rate) == 1008);
    for (unsigned i = 0; i < 1008; ++i) assert(pcm[i * 2] == -15 && pcm[i * 2 + 1] == -15);
    /* Reserved shifts map to 9, without undefined signed shifts. */
    raw_sector(1); fm_xa_reset(&d);
    for (unsigned g = 0; g < 18; ++g) memset(raw + 24 + g * 128, 15, 16);
    assert(fm_xa_decode(&d, raw, pcm, FM_XA_MAX_FRAMES, &rate) == 2016);
    assert(pcm[0] == 8 && pcm[1] == -8);
    FMXaDecoder before = d;
    assert(fm_xa_decode(&d, raw, pcm, 1, &rate) == -1 && !memcmp(&before, &d, sizeof(d)));
    raw[19] = raw[23] = 2;
    assert(fm_xa_decode(&d, raw, pcm, FM_XA_MAX_FRAMES, &rate) == -1);
    /* Predictors carry across units/sectors but reset on a channel change. */
    raw_sector(1); fm_xa_reset(&d);
    for (unsigned g = 0; g < 18; ++g) memset(raw + 24 + g * 128, 0x1C, 16);
    assert(fm_xa_decode(&d, raw, pcm, FM_XA_MAX_FRAMES, &rate) == 2016);
    assert(pcm[0] == 1 && pcm[2] == 2 && pcm[4] == 3 && pcm[0] != pcm[2015 * 2]);
    assert(fm_xa_decode(&d, raw, pcm, FM_XA_MAX_FRAMES, &rate) == 2016 && pcm[0] > 1);
    raw[17] = raw[21] = 3;
    assert(fm_xa_decode(&d, raw, pcm, FM_XA_MAX_FRAMES, &rate) == 2016 && pcm[0] == 1);
}
static void audio_test(void)
{
    assert(fm_audio_init() == 0); memset(pcm, 0x12, sizeof(pcm));
    for (unsigned i = 0; i < 16; ++i) assert(fm_audio_push(pcm, 2016, 37800));
    assert(audio_rate == 37800 && flush_bytes == 8064 && queued == 16);
    assert(!fm_audio_ready() && !fm_audio_push(pcm, 2016, 37800));
    int16_t saved = ((int16_t *)audio_queue[0]->data_vaddr)[0];
    assert(saved == 0x1212);
    audio_queue[0]->status = NDSP_WBUF_DONE;
    assert(fm_audio_ready() && fm_audio_push(pcm, 2016, 37800));
    fm_audio_pause(1); assert(paused); fm_audio_pause(0); assert(!paused);
    unsigned old_clears = clears; fm_audio_reset(); assert(clears > old_clears);
    assert(fm_audio_push(pcm, 4032, 18900) && audio_rate == 18900);
    fm_audio_exit(); dsp_fail = 1;
    assert(fm_audio_init() == -1 && fm_audio_status() == -123);
    assert(fm_audio_ready() && fm_audio_push(pcm, 2016, 37800));
}
static void make_video(unsigned frame, unsigned chunk, unsigned count)
{
    raw_sector(0); raw[18] = raw[22] = 0x48; memset(raw + 24, 0, 32);
    uint8_t *p = raw + 24; put16(p, 0x160); put16(p + 2, 0x8001);
    put16(p + 4, chunk); put16(p + 6, count); put32(p + 8, frame);
    put32(p + 12, count * 2016); put16(p + 16, 320); put16(p + 18, 240);
    memset(p + 32, (int)(frame + chunk), 2016);
}
static void video_test(void)
{
    fm_memory_init(ram, sizeof(ram)); fm_media_reset();
    fm_memory_write_word(0x800F70E4, 0x80111000); fm_memory_write_word(0x800F70F0, 5);
    make_video(1, 0, 2); assert(fm_media_str_sector(raw) == 1);
    assert(fm_memory_read_half(0x80111000) == 0); /* No partial frame visible. */
    make_video(1, 1, 2); assert(fm_media_str_sector(raw) == 1);
    assert(fm_memory_read_half(0x80111000) == 2 && fm_memory_read_half(0x80111020) == 3);
    assert(fm_memory_read_word(0x800F70D4) == 2);
    assert(fm_memory_read_byte(0x80111000 + 5 * 32) == 1);
    assert(fm_memory_read_byte(0x80111000 + 5 * 32 + 2016) == 2);
    make_video(2, 0, 2); assert(fm_media_str_sector(raw) == 1);
    make_video(2, 1, 2); assert(fm_media_str_sector(raw) == 1);
    assert(fm_memory_read_word(0x800F70D4) == 4);
    make_video(3, 0, 2); assert(fm_media_str_sector(raw) == 1);
    make_video(3, 1, 2); assert(fm_media_str_sector(raw) == 1);
    assert(fm_memory_read_word(0x800F70D4) == 4); /* Unread frame cannot be overwritten. */
    make_video(4, 0, 2); assert(fm_media_str_sector(raw) == 0);
    fm_memory_write_half(0x80111000, 0); fm_memory_write_half(0x80111020, 0);
    assert(fm_media_str_sector(raw) == 1);
    assert(fm_memory_read_half(0x80111080) == 1); /* Native wrap marker. */
    assert(fm_memory_read_half(0x80111000) == 2 && fm_memory_read_word(0x800F710C) == 3);
    make_video(5, 0, 21); assert(fm_media_str_sector(raw) == -1);
}
static void mdec_test(void)
{
    fm_memory_init(ram, sizeof(ram));
    fm_memory_write_word(0x1F801824, 0x60000000);
    for (unsigned i = 0; i < 6; ++i) fm_memory_write_word(0x80001000 + i * 4, 0xFE000000);
    fm_memory_mdec_set_callback(0x8006A704, 0x8009C298);
    /* Arm the output before input arrives: it must wait, never produce zeros. */
    fm_memory_write_word(0x1F801090, 0x2000);
    fm_memory_write_word(0x1F801094, 0x00040020);
    fm_memory_write_word(0x1F801098, 0x01000200);
    assert(fm_memory_read_word(0x1F801098) & 0x01000000);
    fm_memory_write_word(0x1F801820, 0x38000006);
    fm_memory_write_word(0x1F801080, 0x1000);
    fm_memory_write_word(0x1F801084, 6);
    fm_memory_write_word(0x1F801088, 0x11000001);
    assert(!(fm_memory_read_word(0x1F801088) & 0x01000000));
    assert(!(fm_memory_read_word(0x1F801098) & 0x01000000));
    for (unsigned i = 0; i < 128; ++i) assert(fm_memory_read_word(0x80002000 + i * 4) == 0x42104210);
    assert((fm_memory_read_word(0x1F8010F4) & 0x03000000) == 0x03000000);
    uint32_t cb, gp; assert(fm_memory_mdec_take_callback(&cb, &gp));
    assert(cb == 0x8006A704 && gp == 0x8009C298 && !fm_memory_mdec_take_callback(&cb, &gp));
    /* The SDK also requests 24-bit output. */
    fm_memory_write_word(0x1F801820, 0x30000006);
    for (unsigned i = 0; i < 6; ++i) fm_memory_write_word(0x1F801820, 0xFE000000);
    for (unsigned i = 0; i < 192; ++i) assert(fm_memory_read_word(0x1F801820) == 0x80808080);
    MDECDebugState m; mdec_debug_get_state(&m); assert(m.decode_macroblocks == 1 && m.decode_blocks == 6);
    assert(!m.dma_read_underflows);
    /* Forward bursts split at the RAM mirror boundary; backward DMA retains
     * the word path and decrements MADR. Both must deliver the same RGB bytes. */
    for (unsigned backwards = 0; backwards < 2; ++backwards) {
        fm_memory_write_word(0x1F801820, 0x30000006);
        for (unsigned i = 0; i < 6; ++i) fm_memory_write_word(0x1F801820, 0xFE000000);
        fm_memory_write_word(0x1F801090, backwards ? 4 : 0x1FFFFC);
        fm_memory_write_word(0x1F801094, 192);
        fm_memory_write_word(0x1F801098, 0x11000000 | (backwards ? 2 : 0));
        for (unsigned i = 0; i < 192; ++i) {
            unsigned addr = ((backwards ? 4 : 0x1FFFFC) + (backwards ? -4u * i : 4u * i)) & 0x1FFFFC;
            assert(fm_memory_read_word(0x80000000 | addr) == 0x80808080);
        }
        assert(!(fm_memory_read_word(0x1F801098) & 0x01000000));
        unsigned end = ((backwards ? 4 : 0x1FFFFC) + (backwards ? -4u * 192 : 4u * 192)) & 0x1FFFFC;
        assert(fm_memory_read_word(0x1F801090) == end);
    }
    /* Bursts cannot read past the FIFO and match single-word reads at every
     * supported output depth, including a final short burst. */
    for (unsigned depth = 0; depth < 4; ++depth) {
        uint32_t ref[192], burst[192]; unsigned words = depth < 2 ? 96 : (depth == 2 ? 192 : 128);
        for (unsigned pass = 0; pass < 2; ++pass) {
            mdec_write(0x1F801820, 0x20000006 | depth << 27);
            for (unsigned i = 0; i < 6; ++i) mdec_write(0x1F801820, 0xFE000000);
            /* Mono depth decodes six independent luma blocks. */
            if (!pass) for (unsigned i = 0; i < words; ++i) ref[i] = mdec_dma_read_word();
            else {
                unsigned offset = 0;
                while (offset < words) {
                    unsigned n = mdec_dma_read_words(burst + offset, 7);
                    assert(n && n <= 7); offset += n;
                }
                assert(offset == words && !memcmp(ref, burst, words * 4u));
                assert(mdec_dma_read_words(burst, 1) == 0);
            }
        }
    }
    const uint8_t bytes[] = {1, 2, 3, 4};
    assert(fm_memory_copy_to_ram(0xA0001000, bytes, 4));
    assert(fm_memory_read_word(0x80001000) == 0x04030201);
    assert(!fm_memory_copy_to_ram(0x801FFFFF, bytes, 4));
    assert(!fm_memory_copy_to_ram(0x1F801820, bytes, 4));
    assert(!fm_memory_gpu_send_words(0x801FFFFC, 2));
    assert(!fm_memory_gpu_send_words(0x80001001, 1));
    fm_memory_init(ram, sizeof(ram)); assert(!fm_memory_mdec_take_callback(&cb, &gp));
    assert(fm_memory_read_word(0x1F801088) == 0 && fm_memory_read_word(0x1F801098) == 0);
}

static void snapshot_test(void)
{
    fm_memory_init(ram,sizeof(ram)); fm_media_reset();
    /* Partial MDEC input is replayable; malformed reads preserve the live FIFO. */
    mdec_write(0x1F801820,0x28000006);
    for (unsigned i=0;i<3;++i) mdec_write(0x1F801820,0xFE000000);
    unsigned n=mdec_snapshot_bytes(); uint8_t *snap=malloc(n),*before=malloc(n);
    assert(snap && before); mdec_snapshot_write(snap);
    assert(!mdec_snapshot_read(snap,n-1)); mdec_snapshot_write(before);
    assert(!memcmp(snap,before,n));
    /* Semantic corruption with valid size cannot partially change quantizers. */
    uint8_t saved=snap[62]; snap[62]=255; assert(!mdec_snapshot_read(snap,n)); snap[62]=saved;
    mdec_snapshot_write(before); assert(!memcmp(snap,before,n));
    for (unsigned i=0;i<3;++i) mdec_write(0x1F801820,0xFE000000);
    assert(mdec_dma_read_ready()); uint32_t reference=mdec_dma_read_word();
    assert(mdec_snapshot_read(snap,n));
    for (unsigned i=0;i<3;++i) mdec_write(0x1F801820,0xFE000000);
    assert(mdec_dma_read_word()==reference); free(snap); free(before);
    n=mdec_snapshot_bytes(); snap=malloc(n); assert(snap); mdec_snapshot_write(snap);
    uint32_t words[31],replayed[31];
    assert(mdec_dma_read_words(words,31)==31); assert(mdec_snapshot_read(snap,n));
    assert(mdec_dma_read_words(replayed,31)==31 && !memcmp(words,replayed,sizeof(words))); free(snap);
    /* Pending DMA callbacks survive MMIO reset and are delivered once. */
    fm_memory_mdec_set_callback(0x8006A704,0x8009C298);
    fm_memory_write_word(0x1F801090,0x1000);
    fm_memory_write_word(0x1F801094,1);
    fm_memory_write_word(0x1F801098,0x11000000);
    FMMemoryQuickState mmio; FMMemoryAsyncState dma;
    fm_memory_quick_save(&mmio); fm_memory_async_save(&dma); assert(fm_memory_async_valid(&dma));
    uint32_t cb,gp; assert(fm_memory_mdec_take_callback(&cb,&gp));
    fm_memory_init(ram,sizeof(ram)); fm_memory_quick_load(&mmio); fm_memory_async_load(&dma);
    assert(fm_memory_mdec_take_callback(&cb,&gp) && cb==0x8006A704 && gp==0x8009C298);
    assert(!fm_memory_mdec_take_callback(&cb,&gp));
    /* Host audio buffers are rebuilt in queued order, including the playing buffer. */
    assert(!fm_audio_init()); fm_audio_reset();
    for (unsigned i=0;i<3;++i) { memset(pcm,i+1,sizeof(pcm)); assert(fm_audio_push(pcm,2016,37800)); }
    audio_queue[0]->status=NDSP_WBUF_PLAYING;
    FMAudioSnapshot *audio=malloc(sizeof(*audio)); assert(audio);
    fm_audio_pause(1); fm_audio_snapshot_save(audio); assert(audio->count==3 && fm_audio_snapshot_valid(audio));
    fm_audio_reset(); fm_audio_snapshot_load(audio); assert(queued==3);
    for (unsigned i=0;i<3;++i) assert(!memcmp(audio->pcm[i],audio_queue[i]->data_vaddr,2016*4));
    audio->frames[0]=4033; assert(!fm_audio_snapshot_valid(audio)); free(audio); fm_audio_exit();
    /* A half-assembled STR frame survives a media reset, with XA predictor state. */
    fm_memory_write_word(0x800F70E4,0x80100000); fm_memory_write_word(0x800F70F0,4);
    fm_memory_write_word(0x800F70D4,0); fm_memory_write_word(0x800F70D8,0);
    memset(raw,0,sizeof(raw)); put16(raw+24,0x160); put16(raw+26,0x8000);
    put16(raw+30,2); put32(raw+32,123); put32(raw+36,3000);
    put16(raw+40,320); put16(raw+42,256);
    assert(fm_media_str_sector(raw)==1);
    FMMediaSnapshot media,copy; fm_media_snapshot_save(&media); assert(media.str.seen==1);
    media.xa.history[0][0]=1234; assert(fm_media_snapshot_valid(&media));
    fm_media_reset(); fm_media_snapshot_load(&media); fm_media_snapshot_save(&copy);
    assert(!memcmp(&copy,&media,sizeof(copy)));
    put16(raw+28,1); assert(fm_media_str_sector(raw)==1);
    assert(fm_memory_read_half(0x80100000)==2 && fm_memory_read_half(0x80100020)==3);
    media.str.seen=8; assert(!fm_media_snapshot_valid(&media));
}
static void disc_test(const char *path)
{
    assert(fm_disc_open(path) == 0); assert(fm_disc_read_raw_sector(100, raw) == 0);
    assert(raw[2323] == 0xA5 && raw[2351] == 0x7E); /* Full Form2 tail preserved. */
    uint8_t data[2048]; assert(fm_disc_read_sector(100, data) == 0);
    assert(!memcmp(data, raw + 24, 2048));
    assert(fm_disc_read_raw_sector(233175, raw) != 0);
    fm_disc_close(); assert(fm_disc_read_raw_sector(100, raw) != 0);
}
static void pipeline_test(const char *path)
{
    fm_memory_init(ram, sizeof(ram)); fm_media_reset(); assert(fm_audio_init() == 0);
    assert(fm_disc_open(path) == 0);
    fm_memory_write_byte(0x80001000, 1); fm_memory_write_byte(0x80001001, 2);
    fm_media_command(0x0D, 0x80001000, -1, 100);
    /* The game's CdlMix writes a 2x2 CD volume matrix. Swap channels. */
    fm_memory_write_byte(0x1F801800, 2); fm_memory_write_byte(0x1F801802, 0);
    fm_memory_write_byte(0x1F801803, 128); fm_memory_write_byte(0x1F801800, 3);
    fm_memory_write_byte(0x1F801801, 0); fm_memory_write_byte(0x1F801802, 128);
    fm_memory_write_byte(0x1F801803, 0x20);
    fm_media_command(0x1B, 0, 0x4A, 100);
    fm_media_poll(101, 1); assert(queued == 1); /* Other XA channel filtered. */
    const int16_t *p = audio_queue[0]->data_vaddr;
    assert(p[0] == -1 && p[1] == 1 && audio_queue[0]->nsamples == 2016);
    fm_media_poll(101, 0); assert(paused);
    fm_media_command(9, 0, -1, 101); assert(queued == 0);
    fm_media_poll(102, 1); assert(queued == 0);
    fm_disc_close(); fm_audio_exit();
}
static void xa_dump(const char *src, const char *dst)
{
    FILE *in = fopen(src, "rb"), *out = fopen(dst, "wb"); assert(in && out);
    FMXaDecoder d; fm_xa_reset(&d); unsigned rate;
    for (unsigned sector = 0; sector < 16; ++sector) {
        assert(fread(raw, 1, sizeof(raw), in) == sizeof(raw));
        int frames = fm_xa_decode(&d, raw, pcm, FM_XA_MAX_FRAMES, &rate);
        assert(frames > 0 && rate == 37800);
        assert(fwrite(pcm, 4, (size_t)frames, out) == (size_t)frames);
    }
    fclose(in); fclose(out);
}
int main(int argc, char **argv)
{
    assert(argc >= 2);
    if (!strcmp(argv[1], "xa")) xa_test();
    else if (!strcmp(argv[1], "audio")) audio_test();
    else if (!strcmp(argv[1], "video")) video_test();
    else if (!strcmp(argv[1], "mdec")) mdec_test();
    else if (!strcmp(argv[1], "snapshot")) snapshot_test();
    else if (!strcmp(argv[1], "disc")) { assert(argc == 3); disc_test(argv[2]); }
    else if (!strcmp(argv[1], "pipeline")) { assert(argc == 3); pipeline_test(argv[2]); }
    else if (!strcmp(argv[1], "xa_dump")) { assert(argc == 4); xa_dump(argv[2], argv[3]); }
    else assert(0);
    return 0;
}
