#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define FM_PERF_PROFILE 0
enum { FM_GPU_IDLE, FM_GPU_VRAM_WRITE, FM_GPU_POLYLINE_MONO_SKIP,
       FM_GPU_POLYLINE_SHADED_SKIP };
static uint16_t vram[1024 * 512], reference[1024 * 512];
static uint16_t *g_vram = vram;
static unsigned g_state, g_cmd_have, g_cmd_need, g_cmd[16];
static unsigned g_upload_x, g_upload_y, g_upload_w, g_upload_h;
static unsigned g_upload_pixels, g_upload_index, g_has_frame;
static uint64_t g_gp0_count, g_upload_data_words;
static uint8_t dirty[512], reference_dirty[512];
static uint32_t last_command;
static void sw_vram_write(int x, int y, uint16_t p)
{ vram[(y & 511) * 1024 + (x & 1023)] = p; dirty[y & 511] = 1; }
static void sw_vram_transfer_in(int x, int y, int w, int h, const uint16_t *p)
{
    assert(h == 1);
    while (w) {
        int n = 1024 - x; if (n > w) n = w;
        memcpy(vram + (y & 511) * 1024 + x, p, n * 2u);
        p += n; w -= n; x = 0;
    }
    dirty[y & 511] = 1;
}
static unsigned command_words(uint8_t opcode) { return opcode == 0xA0 ? 3 : 1; }
static void execute_command(void)
{
    if (g_cmd[0] >> 24 == 0xA0) {
        /* A0_DISPATCH */
    } else last_command = g_cmd[0];
}
void fm_gpu_gp0_write(uint32_t value);
/* GP0_ENTRY_POINTS */
static void reset(void)
{
    memset(vram, 0x5A, sizeof(vram)); memset(dirty, 0, sizeof(dirty));
    g_state = g_cmd_have = g_cmd_need = g_gp0_count = g_upload_data_words = 0;
    g_has_frame = last_command = 0;
}
static uint32_t random_word(void)
{ static uint32_t s = 712; s = s * 1664525u + 1013904223u; return s; }
static void compare(unsigned x, unsigned y, unsigned w, unsigned h)
{
    unsigned count = 3 + (w * h + 1) / 2 + 1;
    uint32_t *stream = malloc(count * 4u); assert(stream);
    stream[0] = 0xA0000000; stream[1] = y << 16 | x; stream[2] = h << 16 | w;
    for (unsigned i = 3; i < count - 1; ++i) stream[i] = random_word();
    stream[count - 1] = 0xE1001234;
    reset();
    for (unsigned i = 0; i < count; ++i) fm_gpu_gp0_write(stream[i]);
    memcpy(reference, vram, sizeof(vram)); memcpy(reference_dirty, dirty, sizeof(dirty));
    uint64_t words = g_upload_data_words;
    reset();
    for (unsigned i = 0; i < count;) {
        unsigned n = 1 + random_word() % 137; if (n > count - i) n = count - i;
        fm_gpu_gp0_words(stream + i, n); i += n;
    }
    assert(!memcmp(reference, vram, sizeof(vram)));
    assert(!memcmp(reference_dirty, dirty, sizeof(dirty)));
    assert(g_gp0_count == count && g_upload_data_words == words && g_has_frame);
    assert(g_state == FM_GPU_IDLE && g_cmd_have == 0 && last_command == 0xE1001234);
    free(stream);
}
int main(void)
{
    compare(0, 0, 480, 256); /* 320x256 RGB24 encoded in 16-bit VRAM words. */
    compare(320, 0, 24, 256); /* Native movie stripe. */
    compare(1021, 510, 17, 5); /* Odd pixel count and both VRAM boundaries. */
    compare(0, 0, 1, 1); compare(1023, 511, 1, 1);
    for (unsigned i = 0; i < 80; ++i)
        compare(random_word() & 1023, random_word() & 511,
                1 + random_word() % 1024, 1 + random_word() % 80);
    /* A 0x10000 x 0x10000 malformed upload overflows like the word path. */
    uint32_t bad[] = {0xA0000000, 0, 0, 0x12345678, 0xE1001234};
    reset(); fm_gpu_gp0_words(bad, 5);
    assert(g_state == FM_GPU_IDLE && g_gp0_count == 5 && last_command == 0xE1001234);
    /* Reproducible throughput comparison; no timing assertion on shared CI. */
    static uint32_t stripe[3072];
    for (unsigned i = 0; i < 3072; ++i) stripe[i] = random_word();
    clock_t times[2];
    for (unsigned bulk = 0; bulk < 2; ++bulk) {
        clock_t start = clock(); reset();
        for (unsigned frame = 0; frame < 100; ++frame) for (unsigned col = 0; col < 20; ++col) {
            fm_gpu_gp0_write(0xA0000000); fm_gpu_gp0_write(col * 24);
            fm_gpu_gp0_write(256u << 16 | 24u);
            if (bulk) fm_gpu_gp0_words(stripe, 3072);
            else for (unsigned i = 0; i < 3072; ++i) fm_gpu_gp0_write(stripe[i]);
        }
        times[bulk] = clock() - start;
    }
    printf("GPU upload host benchmark: word=%.2fms burst=%.2fms\n",
        times[0] * 1000.0 / CLOCKS_PER_SEC, times[1] * 1000.0 / CLOCKS_PER_SEC);
    return 0;
}
