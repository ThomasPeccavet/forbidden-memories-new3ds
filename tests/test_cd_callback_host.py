"""Execute production CD scheduling against guest caller/IRQ ordering."""
import os
from pathlib import Path
import re
import shlex
import shutil
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]


class CdCallbackHostTests(unittest.TestCase):
    def test_deferred_delivery_and_nested_command(self):
        cc = shlex.split(os.environ.get("CC", "cc"))
        if not cc or not shutil.which(cc[0]):
            self.skipTest("Host C compiler required")
        source = (ROOT / "3ds/source/main.c").read_text()
        start = source.index("static uint32_t fm_bcd_to_u32(")
        end = source.index("static int g_media_irq_active;", start)
        code = source[start:end]
        declarations = []
        for name in sorted(set(re.findall(r"\bg_[a-zA-Z0-9_]+\b", code))):
            declaration = re.search(r"^static [^;\n]*\b" + name + r"\b[^;]*;", source, re.M).group()
            if declaration not in declarations:
                declarations.append(declaration)
        harness = r'''
#include <assert.h>
#include <stdint.h>
#include <string.h>
typedef struct {
    uint32_t gpr[32], pc, hi, lo, cop0[32];
    void (*write_byte)(uint32_t, uint8_t);
    uint8_t (*read_byte)(uint32_t);
} CPUState;
static int fm_irq_cpu_enabled(const CPUState *c) { return c && (c->cop0[12]&0x401u)==0x401u; }
static uint64_t test_now;
static uint64_t osGetTime(void) { return test_now; }
static void fm_media_command(uint32_t cmd, uint32_t params, int mode, uint32_t lba) {
    (void)cmd; (void)params; (void)mode; (void)lba;
}
static uint8_t ram[0x200000];
static void store(uint32_t a, uint8_t v) { ram[a & 0x1fffff] = v; }
static uint8_t load(uint32_t a) { return ram[a & 0x1fffff]; }
'''
        harness += "\n".join(declarations) + "\n" + code
        harness += r'''
int main(void) {
    CPUState cpu = {0}; cpu.cop0[12]=0x401; cpu.write_byte = store; cpu.read_byte = load;
    cpu.pc = 0x8007a1d4; cpu.gpr[31] = 0x8007c6d8;
    cpu.gpr[28] = 0x8009c298;
    assert(fm_b33_schedule_cd_callback(&cpu, 9, 0x8007ca78,
        cpu.gpr[31], 0, 0, 0, 10, -1));
    assert(cpu.pc == 0x8007c6d8 && cpu.gpr[2] == 0);
    assert(!g_b33_cb_active && g_b33_pending && load(0x80094bec) == 0);
    assert(!fm_b33_deliver_cd_callback(&cpu, 10));
    /* The guest caller sets busy AFTER enqueue returns. */
    uint32_t busy = 0x400;
    cpu.pc = 0x800746b8; cpu.gpr[31] = 0x80012d48;
    cpu.gpr[2] = 0x1234; cpu.hi = 0x5678; cpu.lo = 0x9abc;
    cpu.gpr[28] = 0x80123400; /* Different delivery context. */
    cpu.cop0[12]=0x400; assert(!fm_b33_deliver_cd_callback(&cpu,11) && g_b33_pending);
    cpu.cop0[12]=0x401;
    assert(fm_b33_deliver_cd_callback(&cpu, 11));
    assert(cpu.pc == 0x8007ca78 && cpu.gpr[4] == 2);
    assert(load(0x80094bec) == 2);
    assert(g_b33_cb_resume == 0x800746b8);
    assert(g_b33_saved_gpr[31] == 0x80012d48);
    assert(g_b33_saved_gpr[28] == 0x80123400);
    assert(cpu.gpr[28] == 0x8009c298);
    assert(g_b33_cb_return_value == 0x1234);
    assert(g_b33_saved_hi == 0x5678 && g_b33_saved_lo == 0x9abc);
    busy &= ~0x400u; /* Native completion clears busy after the caller set it. */
    assert(busy == 0);
    /* Queue progression may issue the next command inside this callback. */
    assert(fm_b33_schedule_cd_callback(&cpu, 0x0d, 0x8007ca78,
        0x8007c6d8, 0, 0, 0, 11, -1));
    assert(g_b33_cb_cmd == 9 && g_b33_cb_resume == 0x800746b8);
    assert(g_b33_pending_cmd == 0x0d);
    assert(!fm_b33_deliver_cd_callback(&cpu, 12));
    /* Refuse overflow; retain the first pending command and active context. */
    assert(fm_b33_schedule_cd_callback(&cpu, 6, 0x80013fbc,
        0x80014930, 0, 0, 1, 11, 0x4a));
    assert(cpu.gpr[2] == 0 && g_b33_pending_cmd == 0x0d);
    assert(!g_cd_reading && !g_cd_streaming && g_cd_mode == 0);
    assert(g_b33_cb_cmd == 9 && g_b33_cb_resume == 0x800746b8);
    g_b33_cb_active = 0; /* Completed IRQ, restored interrupted caller. */
    cpu.pc = 0x800746b8;
    assert(fm_b33_deliver_cd_callback(&cpu, 12));
    assert(g_b33_cb_cmd == 0x0d);
    /* Wrapper ReadS applies both mode and seek, unlike bare ReadS. */
    store(0x80001000, 0x45); store(0x80001001, 0x03); store(0x80001002, 0x45);
    fm_cd_apply_command(&cpu, 0x1b, 0x80001000, 0x4a, 1000);
    uint32_t start = (45 * 60 + 3) * 75 + 45 - 150;
    assert(g_cd_streaming && !g_cd_reading && g_cd_lba == start);
    fm_cd_stream_tick(1010, 1); assert(g_cd_lba == start);
    fm_cd_stream_tick(1020, 1); assert(g_cd_lba == start + 1);
    fm_cd_stream_tick(2000, 1); assert(g_cd_lba == start + 75);
    /* Repeated location queries do not accelerate the transport. */
    for (unsigned i = 0; i < 10; ++i) {
        fm_cd_apply_command(&cpu, 0x10, 0, -1, 2000);
        fm_b33_fill_cd_result(&cpu, 0x10);
    }
    assert(g_cd_lba == start + 75);
    uint32_t abs = g_cd_lba + 150;
    assert(fm_bcd_to_u32(load(g_b33_result_scratch)) == abs / 4500);
    assert(fm_bcd_to_u32(load(g_b33_result_scratch + 1)) == abs % 4500 / 75);
    assert(fm_bcd_to_u32(load(g_b33_result_scratch + 2)) == abs % 75);
    fm_cd_stream_tick(3000, 0); assert(g_cd_lba == start + 75);
    fm_cd_stream_tick(4000, 1); assert(g_cd_lba == start + 150);
    fm_cd_apply_command(&cpu, 9, 0, -1, 4000);
    fm_cd_stream_tick(5000, 1); assert(!g_cd_streaming && g_cd_lba == start + 150);
    fm_cd_apply_command(&cpu, 0x1b, 0x80001000, 0xca, 5000);
    fm_cd_stream_tick(6000, 1); assert(g_cd_lba == start + 150);
    /* Switching to ordinary ReadN restores the sector-driven path. */
    fm_cd_apply_command(&cpu, 6, 0, -1, 6000);
    fm_cd_stream_tick(7000, 1); assert(!g_cd_streaming && g_cd_reading && g_cd_lba == start + 150);
    return 0;
}
'''
        with tempfile.TemporaryDirectory() as temp:
            path = Path(temp) / "cd-callback.c"
            binary = Path(temp) / "cd-callback"
            path.write_text(harness)
            result = subprocess.run(cc + ["-std=c11", "-Wall", "-Werror", str(path), "-o", str(binary)], capture_output=True, text=True)
            self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
            result = subprocess.run([str(binary)], capture_output=True, text=True)
            self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
