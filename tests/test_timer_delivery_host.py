"""Timer delivery does not wait for a rendered update or modify its CPU."""
from pathlib import Path
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]


class TimerDeliveryTests(unittest.TestCase):
    def test_delivery_observes_unmasking_between_host_boundaries(self):
        source = (ROOT / "3ds/source/main.c").read_text()
        main = source[source.index("int main(void)"):]
        # A capture can be inside DrawSync with I_MASK=0. Delivery must also
        # see the guest re-enable IRQs before returning to the host loop.
        self.assertEqual(main.count("fm_execute_guest_timer_callback(cpu)"), 2)
        dispatch = main.index("fm_media_guest_entry(cpu, phys)")
        call = main.rfind("fm_execute_guest_timer_callback(cpu)", 0, dispatch)
        self.assertLess(call, dispatch)
        self.assertNotIn("continue;", main[call:dispatch])

    def test_complete_isolated_isr_masking_and_bounded_failure(self):
        source = (ROOT / "3ds/source/main.c").read_text()
        start = source.index("static uint32_t g_seq_irq_calls")
        end = source.index("static int fm_execute_guest_vblank_callback(", start)
        code = r'''
#include <assert.h>
#include <stdint.h>
#include <string.h>
typedef struct { uint32_t gpr[32], pc, hi, lo, cop0[32]; } CPUState;
static int fm_irq_cpu_enabled(const CPUState *c) { return c && (c->cop0[12] & 0x401u)==0x401u; }
typedef struct { unsigned reason; } FMInterpResult;
#define FM_INTERP_BLOCK_DONE 1
#define FM_INTERP_BUDGET 2
static int g_media_irq_active, g_b33_cb_active, g_cd_tick_active;
static int g_b34_ready_active, g_b35_finalizer_active;
static const uint32_t g_media_irq_sentinel = 0x8000FFD0u;
static unsigned pending, enabled, fail, spin, calls;
static uint64_t now;
static uint64_t osGetTime(void) { return now++; }
static int fm_runtime_take_timer_callback(uint32_t *callback) {
    if (!pending || !enabled) return 0;
    --pending; *callback = 0x8004BBC4u; return 1;
}
static int fm_bios_try_hle(CPUState *cpu, uint32_t pc) {
    (void)cpu; (void)pc; assert(0); return 0;
}
static FMInterpResult fm_interp_run_block(CPUState *cpu, unsigned budget) {
    assert(budget == 512);
    assert(cpu->gpr[29] == 0x801FF800u);
    assert(cpu->gpr[31] == g_media_irq_sentinel);
    ++calls;
    cpu->hi = cpu->lo = cpu->cop0[12] = 0xBAD;
    cpu->gpr[4] = 0xBAD; cpu->gpr[2] = 0;
    if (!spin) cpu->pc = g_media_irq_sentinel;
    return (FMInterpResult){ fail ? 99u : FM_INTERP_BLOCK_DONE };
}
''' + source[start:end] + r'''
int main(void) {
    CPUState cpu = {0};
    for (unsigned i = 0; i < 32; ++i) cpu.gpr[i] = i * 123;
    cpu.pc = 0x80081AEC; cpu.hi = 12; cpu.lo = 34; cpu.cop0[12] = 0x401;
    CPUState saved = cpu;
    pending = 1;
    assert(!fm_execute_guest_timer_callback(&cpu) && pending == 1);
    enabled = 1;
    cpu.cop0[12]=0x400; assert(!fm_execute_guest_timer_callback(&cpu) && pending==1);
    cpu.cop0[12]=1; assert(!fm_execute_guest_timer_callback(&cpu) && pending==1); cpu=saved;
    assert(!fm_execute_guest_timer_callback(0) && pending == 1);
    g_cd_tick_active = 1;
    assert(!fm_execute_guest_timer_callback(&cpu) && pending == 1);
    g_cd_tick_active = 0; g_media_irq_active = 1;
    assert(!fm_execute_guest_timer_callback(&cpu) && pending == 1);
    g_media_irq_active = 0;
    /* The main PC can stay in the same draw/wait loop across host ticks.
     * It must no longer suppress all timer IRQs until it reaches 12C50. */
    for (unsigned frame = 0; frame < 100; ++frame) {
        pending = 1;
        assert(fm_execute_guest_timer_callback(&cpu) == 1 && pending == 0);
        assert(!memcmp(&cpu, &saved, sizeof(cpu)));
    }
    assert(g_seq_irq_calls == 100 && g_seq_irq_done == 100);
    assert(g_seq_irq_serviced == 100 && !g_seq_irq_skipped);
    pending = 1; fail = 1;
    assert(fm_execute_guest_timer_callback(&cpu) == -1);
    assert(!memcmp(&cpu, &saved, sizeof(cpu)));
    fail = 0; spin = 1; pending = 1;
    unsigned before = calls;
    assert(fm_execute_guest_timer_callback(&cpu) == -1);
    assert(calls - before == 100000);
    assert(!memcmp(&cpu, &saved, sizeof(cpu)));
    return 0;
}
'''
        with tempfile.TemporaryDirectory() as temp:
            path = Path(temp) / "timer-delivery.c"
            binary = Path(temp) / "timer-delivery"
            path.write_text(code)
            result = subprocess.run(["cc", "-std=c11", "-Wall", "-Werror",
                                     str(path), "-o", str(binary)],
                                    capture_output=True, text=True)
            self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
            result = subprocess.run([str(binary)], capture_output=True, text=True)
            self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
