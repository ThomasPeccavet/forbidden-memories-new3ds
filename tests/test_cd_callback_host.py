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
        start = source.index("static void fm_b33_fill_cd_result(")
        end = source.index("static int fm_execute_guest_vblank_callback(", start)
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
    uint32_t gpr[32], pc, hi, lo;
    void (*write_byte)(uint32_t, uint8_t);
    uint8_t (*read_byte)(uint32_t);
} CPUState;
static uint8_t ram[0x200000];
static void store(uint32_t a, uint8_t v) { ram[a & 0x1fffff] = v; }
static uint8_t load(uint32_t a) { return ram[a & 0x1fffff]; }
'''
        harness += "\n".join(declarations) + "\n" + code
        harness += r'''
int main(void) {
    CPUState cpu = {0}; cpu.write_byte = store; cpu.read_byte = load;
    cpu.pc = 0x8007a1d4; cpu.gpr[31] = 0x8007c6d8;
    cpu.gpr[28] = 0x8009c298;
    assert(fm_b33_schedule_cd_callback(&cpu, 9, 0x8007ca78,
        cpu.gpr[31], 0, 0, 0, 10));
    assert(cpu.pc == 0x8007c6d8 && cpu.gpr[2] == 0);
    assert(!g_b33_cb_active && g_b33_pending && load(0x80094bec) == 0);
    assert(!fm_b33_deliver_cd_callback(&cpu, 10));
    /* The guest caller sets busy AFTER enqueue returns. */
    uint32_t busy = 0x400;
    cpu.pc = 0x800746b8; cpu.gpr[31] = 0x80012d48;
    cpu.gpr[2] = 0x1234; cpu.hi = 0x5678; cpu.lo = 0x9abc;
    cpu.gpr[28] = 0x80123400; /* Different delivery context. */
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
        0x8007c6d8, 0, 0, 0, 11));
    assert(g_b33_cb_cmd == 9 && g_b33_cb_resume == 0x800746b8);
    assert(g_b33_pending_cmd == 0x0d);
    assert(!fm_b33_deliver_cd_callback(&cpu, 12));
    /* Refuse overflow; retain the first pending command and active context. */
    assert(fm_b33_schedule_cd_callback(&cpu, 6, 0x80013fbc,
        0x80014930, 0, 0, 1, 11));
    assert(cpu.gpr[2] == 0 && g_b33_pending_cmd == 0x0d);
    assert(g_b33_cb_cmd == 9 && g_b33_cb_resume == 0x800746b8);
    g_b33_cb_active = 0; /* Completed IRQ, restored interrupted caller. */
    cpu.pc = 0x800746b8;
    assert(fm_b33_deliver_cd_callback(&cpu, 12));
    assert(g_b33_cb_cmd == 0x0d);
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
