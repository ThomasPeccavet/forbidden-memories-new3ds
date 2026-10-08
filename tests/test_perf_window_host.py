"""Check real-window FPS deltas and nested timing in the production reporter."""
from pathlib import Path
import subprocess
import tempfile
import unittest
ROOT = Path(__file__).resolve().parents[1]
class PerfWindowTests(unittest.TestCase):
    def test_window_rates_and_nested_time(self):
        source = (ROOT / "3ds/source/main.c").read_text()
        begin = source.index("static void fm_perf_window(")
        end = source.index("\n#endif", begin)
        code = r'''#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
typedef struct { uint32_t pc; } CPUState;
typedef struct { uint32_t start_pc,end_pc,hits,max_us; uint64_t total_us; } B110ProbeStat;
typedef struct { uint8_t opcode; uint32_t calls; uint64_t total_us; uint32_t max_us; } FMGpuOpcodePerf;
static void fm_gpu_perf_texture_window(uint64_t *n, uint64_t *f, uint32_t *nt, uint32_t *ft) {
    *n=1000; *f=2000; *nt=10; *ft=20;
}
static unsigned gpu_resets;
static void fm_gpu_perf_window_reset(void) { ++gpu_resets; }
static void fm_gpu_perf_window_rank(unsigned rank, FMGpuOpcodePerf *out) {
    if (!rank) { out->opcode=0x30; out->calls=10; out->total_us=1234; out->max_us=500; }
}
#define B110_PROF_SLOTS 12
#define FM_OT_DIAGNOSTICS 0
#define FM_LEGACY_FILE_DIAGNOSTICS 0
typedef struct { uint64_t dma2_linked_total_ms; uint32_t dma2_linked_transfer_count,
    dma2_linked_last_ms, dma2_linked_max_ms; } FMDmaDebugStats;
static FMDmaDebugStats dma;
static void fm_memory_dma_debug(FMDmaDebugStats *out) { *out=dma; }
static B110ProbeStat g_b110_prof[12];
static uint32_t g_b84_latch_count, g_seq_irq_done, g_seq_irq_max_ms;
static uint64_t g_seq_irq_total_ms;
static uint32_t g_b105_render_ms=1, g_b105_vblank_ms=2, g_b106_gfx_ms;
static uint32_t g_b106_wait_ms, g_b105_loop_ms=15;
static uint64_t g_b115_last_repair_ms, g_b115_last_submit_ms, g_b115_last_merge_ms;
static uint32_t g_b115_last_calls;
static uint32_t g_b91_fast_entries, g_b91_fast_blocks;
static uint64_t g_b91_fast_instructions;
static uint32_t g_b91_slow_handoff_pc, g_b91_slow_handoff_ms;
static FILE *report;
static uint64_t osGetTime(void) { return 123; }
static uint16_t fm_memory_read_half(uint32_t a) { (void)a; return 0x8002; }
static void b110_get_rank(unsigned i, B110ProbeStat *out) { *out=g_b110_prof[i]; }
static FILE *report_open(const char *path, const char *mode) {
    assert(strstr(path,"perf-latest.txt") && !strcmp(mode,"wb")); return report;
}
#define fopen report_open
static int report_close(FILE *fp) {
    int result=fflush(fp);
    /* Production closes the file; the harness keeps it for assertions.
     * Detach the reporter's stack buffer before that stack frame ends. */
    setvbuf(fp, NULL, _IONBF, 0);
    return result;
}
#define fclose report_close
''' + source[begin:end] + r'''int main(void) {
    report = tmpfile(); assert(report);
    CPUState cpu={0x80041EE8};
    fm_perf_window(1000,100,12,&cpu);
    for(unsigned i=1;i<=100;++i) {
        g_b84_latch_count=i/5;
        g_seq_irq_done=i; g_seq_irq_total_ms=i*3;
        dma.dma2_linked_total_ms=i*4; dma.dma2_linked_transfer_count=i;
        fm_perf_window(1000+i*20,100+i,12,&cpu);
    }
    rewind(report); char text[4096]={0}; fread(text,1,sizeof(text)-1,report);
    assert(strstr(text,"window_ms=2000"));
    assert(strstr(text,"host_fps_x100=5000 new_images_fps_x100=1000 samples=100"));
    assert(strstr(text,"pre_guest_input=1200 presentation=100 vblank=200"));
    assert(strstr(text,"loop=1500 max_loop=15"));
    assert(strstr(text,"seq_nested_ms=300 irq_done=100"));
    assert(strstr(text,"unclassified_ms=0"));
    assert(strstr(text,"dma2_nested_ms=400 transfers=100"));
    assert(strstr(text,"legacy_file_dumps=0"));
    assert(strstr(text,"native_sampling=random_1/64"));
    assert(strstr(text,"gpu0 opcode=30 samples=10 us=1234 max_us=500"));
    assert(gpu_resets==2);
    assert(strstr(text,"texture_fast format_specialization=1 color_lookup=1 neutral_triangles=10 fast_triangles=20 neutral_pixels=1000 fast_pixels=2000"));
    return 0;
}
'''
        with tempfile.TemporaryDirectory() as temp:
            path=Path(temp)/"perf.c"; binary=Path(temp)/"perf"
            path.write_text(code)
            subprocess.run(["cc","-std=c11","-Wall","-Werror",str(path),"-o",str(binary)],check=True)
            subprocess.run([str(binary)],check=True)
