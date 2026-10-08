"""Differential VLC tests against the original FR Ghidra routine."""
import os
from pathlib import Path
import re
import shlex
import shutil
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]


class VlcHostTests(unittest.TestCase):
    def test_generated_entry_escape_and_native_fallback(self):
        cc = shlex.split(os.environ.get("CC", "cc"))
        if not cc or not shutil.which(cc[0]):
            self.skipTest("Host C compiler required")
        source = (ROOT / "3ds/source/fm_runtime_shim.c").read_text()
        start = source.index("void psx_check_interrupts_dispatch_entry(")
        end = source.index("#if FM_PERF_PROFILE", start)
        c_source = r'''
#include "cpu_state.h"
#include <assert.h>
static int g_probe_armed, enabled, tries, stops, observed;
enum { FM_STOP_BUDGET = 2 };
static int fm_vlc_try(CPUState *cpu) {
    ++tries; if (!enabled) return 0;
    cpu->gpr[2] = 7; cpu->pc = cpu->gpr[31]; return 1;
}
static void fm_probe_stop(int reason, unsigned pc) {
    assert(reason == FM_STOP_BUDGET && (pc == 0x8006A670 || pc == 0x80076DB8)); ++stops;
}
static void fm_media_guest_entry(CPUState *cpu, unsigned phys) { (void)cpu; (void)phys; ++observed; }
/* ENTRY */
int main(void) {
    CPUState cpu = {0}; cpu.gpr[31] = 0x8006A670;
    g_probe_armed = enabled = 1;
    psx_check_interrupts_dispatch_entry(&cpu, 0x800914A8);
    assert(tries == 1 && stops == 1 && !observed && cpu.pc == cpu.gpr[31] && cpu.gpr[2] == 7);
    enabled = 0;
    psx_check_interrupts_dispatch_entry(&cpu, 0x800914A8);
    assert(tries == 2 && stops == 1 && observed == 1);
    g_probe_armed = 0; enabled = 1;
    psx_check_interrupts_dispatch_entry(&cpu, 0x800914A8);
    assert(tries == 2 && stops == 1 && observed == 2);
    g_probe_armed = 1;
    psx_check_interrupts_dispatch_entry(&cpu, 0x8006A354);
    assert(tries == 2 && stops == 1 && observed == 3);
    psx_check_interrupts_dispatch_entry(&cpu, 0x80076DB8);
    assert(stops == 2 && tries == 2 && observed == 3);
    return 0;
}
'''.replace("/* ENTRY */", source[start:end] + "}\n")
        with tempfile.TemporaryDirectory() as temp:
            c = Path(temp) / "entry.c"
            binary = Path(temp) / "entry"
            c.write_text(c_source)
            result = subprocess.run(cc + ["-std=gnu11", "-O2", "-I", str(ROOT / "tests/host/include"),
                                         str(c), "-o", str(binary)], capture_output=True, text=True)
            self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
            result = subprocess.run([str(binary)], capture_output=True, text=True)
            self.assertEqual(result.returncode, 0, result.stdout + result.stderr)

    def test_native_tables_output_and_continuations(self):
        cc = shlex.split(os.environ.get("CC", "cc"))
        if not cc or not shutil.which(cc[0]):
            self.skipTest("Host C compiler required")
        native = (ROOT / "research/ghidra-fr/export/pseudo-c/800914a8.c").read_text()
        # Guest arithmetic stays uint32. Widen only pointer-bearing signed ints
        # so the original pseudo-C can run on a 64-bit host without truncation.
        native = native.replace("int param_3", "intptr_t param_3").replace("int iVar3;", "intptr_t iVar3;")
        native = native.replace("(int)", "(int32_t)")
        native = re.sub(r"\(int32_t\)(param_[12]|puVar\d+)", r"(intptr_t)\1", native)
        native = native.replace("FUN_800914a8", "native_vlc")
        # The PsyQ whole-frame boundary is outside the output array. Native
        # MIPS computes an integer address; do so on the host as well.
        native = native.replace("puVar17 = DAT_8009b460 + DAT_8009b458;",
                                "puVar17 = (undefined2 *)((uintptr_t)DAT_8009b460 + (uintptr_t)DAT_8009b458 * 2);")
        harness = (ROOT / "tests/host/test_vlc.c").read_text().replace("/* NATIVE_REFERENCE */", native)
        with tempfile.TemporaryDirectory() as temp:
            c = Path(temp) / "vlc.c"
            binary = Path(temp) / "vlc"
            c.write_text(harness)
            cmd = cc + ["-std=gnu11", "-O2", "-Wall", "-Wextra",
                        "-I", str(ROOT / "tests/host/include"), "-I", str(ROOT / "3ds/include"),
                        str(ROOT / "3ds/source/fm_vlc.c"), str(c), "-o", str(binary)]
            result = subprocess.run(cmd, capture_output=True, text=True)
            self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
            result = subprocess.run([str(binary)], capture_output=True, text=True, timeout=15)
            self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
