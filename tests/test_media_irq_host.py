"""Execute the production DMA1 guest callback bridge, independently of CD IRQs."""
from pathlib import Path
import os
import shlex
import shutil
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]


class MediaIrqHostTests(unittest.TestCase):
    def test_preserves_interrupted_context_and_defers_nested_callbacks(self):
        cc = shlex.split(os.environ.get("CC", "cc"))
        if not cc or not shutil.which(cc[0]):
            self.skipTest("Host C compiler required")
        source = (ROOT / "3ds/source/main.c").read_text()
        start = source.index("static int g_media_irq_active;")
        end = source.index("static int fm_execute_guest_vblank_callback(", start)
        code = r'''
#include <assert.h>
#include <stdint.h>
#include <string.h>
typedef struct { uint32_t gpr[32], pc, hi, lo; } CPUState;
static int g_b33_cb_active, g_cd_tick_active, g_b34_ready_active, g_b35_finalizer_active;
static unsigned pending, taken;
static int fm_memory_mdec_take_callback(uint32_t *callback, uint32_t *gp) {
    if (!pending) return 0;
    --pending; ++taken; *callback = 0x8006A704; *gp = 0x8009C298; return 1;
}
'''
        code += source[start:end]
        code += r'''
int main(void) {
    CPUState cpu = {0};
    for (unsigned i = 0; i < 32; ++i) cpu.gpr[i] = i * 123;
    cpu.pc = 0x8006A560; cpu.hi = 0x12345678; cpu.lo = 0x9ABCDEF0;
    CPUState saved = cpu; pending = 2;
    g_b33_cb_active = 1; assert(!fm_media_irq_dispatch(&cpu) && pending == 2);
    g_b33_cb_active = 0; g_b34_ready_active = 1;
    assert(!fm_media_irq_dispatch(&cpu) && pending == 2);
    g_b34_ready_active = 0;
    assert(fm_media_irq_dispatch(&cpu) && pending == 1 && taken == 1);
    assert(cpu.pc == 0x8006A704 && cpu.gpr[28] == 0x8009C298);
    assert(cpu.gpr[31] == g_media_irq_sentinel && g_media_irq_active);
    assert(!fm_media_irq_dispatch(&cpu) && pending == 1); /* No recursive delivery. */
    memset(cpu.gpr, 0xAA, sizeof(cpu.gpr)); cpu.hi = cpu.lo = 0;
    cpu.pc = g_media_irq_sentinel;
    assert(fm_media_irq_dispatch(&cpu) && !g_media_irq_active);
    saved.gpr[0] = 0; assert(!memcmp(&cpu, &saved, sizeof(cpu)));
    assert(fm_media_irq_dispatch(&cpu) && pending == 0 && taken == 2);
    cpu.pc = g_media_irq_sentinel; assert(fm_media_irq_dispatch(&cpu));
    assert(!memcmp(&cpu, &saved, sizeof(cpu)));
    assert(!fm_media_irq_dispatch(&cpu));
    return 0;
}
'''
        with tempfile.TemporaryDirectory() as temp:
            path = Path(temp) / "media-irq.c"
            binary = Path(temp) / "media-irq"
            path.write_text(code)
            result = subprocess.run(cc + ["-std=c11", "-Wall", "-Werror", str(path), "-o", str(binary)],
                                    capture_output=True, text=True)
            self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
            result = subprocess.run([str(binary)], capture_output=True, text=True)
            self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
