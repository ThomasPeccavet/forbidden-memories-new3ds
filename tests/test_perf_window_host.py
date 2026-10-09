"""Check real-window FPS deltas and nested timing in the production reporter."""
from pathlib import Path
import subprocess
import tempfile
import unittest
from test_gpu_perf_window_host import function
ROOT = Path(__file__).resolve().parents[1]
class PerfWindowTests(unittest.TestCase):
    def test_window_rates_and_nested_time(self):
        source = (ROOT / "3ds/source/main.c").read_text()
        begin = source.index("static void fm_perf_window(")
        body = function(source,"fm_perf_window")
        code = r'''#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "fm_host_clock.h"
static FMHostClock g_ps1_host_clock;
typedef struct { uint32_t pc; } CPUState;
typedef struct { uint32_t start_pc,end_pc,hits,max_us; uint64_t total_us; } B110ProbeStat;
typedef struct { uint8_t opcode; uint32_t calls; uint64_t total_us; uint32_t max_us; } FMGpuOpcodePerf;
static void fm_gpu_perf_texture_window(uint64_t *n, uint64_t *f, uint32_t *nt, uint32_t *ft) {
    *n=1000; *f=2000; *nt=10; *ft=20;
}
static unsigned gpu_resets;
static __attribute__((unused)) void fm_unai_counts(uint32_t *s,uint32_t *p,uint32_t *f) {
    static unsigned n; ++n; *s=n*3; *p=n*4; *f=n*5;
}
static unsigned g_perf_wait_reason;
static int g_frame_wait_active;
static uint32_t g_frame_wait_stops,g_frame_wait_resumes,g_frame_wait_probe_calls;
static uint64_t g_frame_wait_probe_us;
static uint32_t g_clock_ticks,g_budget_wait_skips,g_native_probe_calls,g_b13514_chain_entries;
static uint64_t g_b13514_chain_dispatches;
static uint32_t g_b105_slice_budget_ms=12, g_b84_budget_yields;
static uint32_t g_b108_vsync_mode0,g_b108_vsync_modeN,g_b108_vsync_immediate,g_b1358_vsync_completions;
static void fm_gpu_perf_window_reset(void) { ++gpu_resets; }
static void fm_gpu_perf_window_rank(unsigned rank, FMGpuOpcodePerf *out) {
    if (!rank) { out->opcode=0x30; out->calls=10; out->total_us=1234; out->max_us=500; }
}
#define B110_PROF_SLOTS 12
#define FM_OT_DIAGNOSTICS 0
#define FM_LEGACY_FILE_DIAGNOSTICS 0
typedef struct { uint64_t dma2_linked_total_ms, dma2_payload_us; uint32_t dma2_linked_transfer_count,
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
''' + body + r'''int main(void) {
    report = tmpfile(); assert(report);
    CPUState cpu={0x80041EE8};
    g_ps1_host_clock.pending=13;
    fm_perf_window(1000,100,12,&cpu);
    for(unsigned i=1;i<=100;++i) {
        g_b84_latch_count=i/5; g_clock_ticks=i*6/5; g_budget_wait_skips=i/4;
        g_frame_wait_stops=i; g_frame_wait_resumes=i/2; g_frame_wait_probe_calls=i*2; g_frame_wait_probe_us=i*7; g_frame_wait_active=1;
        g_perf_wait_reason=i%4; g_b106_wait_ms= g_perf_wait_reason==3 ? 0 : 2;
        g_b84_budget_yields=i; g_b108_vsync_mode0=i/5; g_b1358_vsync_completions=i/5;
        g_seq_irq_done=i; g_seq_irq_total_ms=i*3;
        dma.dma2_payload_us=i*3000; dma.dma2_linked_total_ms=i*4; dma.dma2_linked_transfer_count=i;
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
    assert(strstr(text,"dma2_split payload_parser_raster_us=300000 traversal_other_us=100000 coarse_total_us=400000"));
    assert(strstr(text,"gpu_timing=all_completed_commands"));
#if FM_GPU_UNAI
    assert(strstr(text,"renderer=unai-experiment sprites=3 polygons=4 fallback=5"));
#else
    assert(strstr(text,"renderer=native-reference"));
#endif
    assert(strstr(text,"native_sampling=random_1/64"));
    assert(strstr(text,"gpu0 opcode=30 calls=10 us=1234 max_us=500"));
    assert(gpu_resets==2);
    assert(strstr(text,"frame_wait stops=100 resumes=50 active=1 target_probes=200 target_probe_us=700"));
    assert(strstr(text,"ps1_clock=wall_60hz ticks=120 budget_wait_skips=25"));
    assert(strstr(text,"clock_debt pending=13 batch_limit=8"));
    assert(strstr(text,"wait_reasons budget_ms=50 budget_loops=25 vsync_ms=50 vsync_loops=25 other_ms=50 other_loops=25 no_wait_loops=25"));
    assert(strstr(text,"scheduler budget_ms=12 budget_yields=100 vsync_mode0=20 vsync_modeN=0 vsync_immediate=0 vsync_completed=20"));
    assert(strstr(text,"texture_fast format_specialization=1 color_lookup=1 neutral_triangles=10 fast_triangles=20 neutral_pixels=1000 fast_pixels=2000"));
    return 0;
}
'''
        with tempfile.TemporaryDirectory() as temp:
            path=Path(temp)/"perf.c"; binary=Path(temp)/"perf"
            path.write_text(code)
            for unai in (0,1):
                subprocess.run(["cc","-std=c11","-Wall","-Werror",f"-DFM_GPU_UNAI={unai}","-I"+str(ROOT/"3ds/include"),str(path),"-o",str(binary)],check=True)
                subprocess.run([str(binary)],check=True)
