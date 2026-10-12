"""Run the production LibCD result writer with sentinel guest RAM."""
import os
from pathlib import Path
import re
import shlex
import shutil
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]


class CdResultHostTests(unittest.TestCase):
    def test_result_does_not_corrupt_game_or_ready_buffer(self):
        cc = shlex.split(os.environ.get("CC", "cc"))
        if not cc or not shutil.which(cc[0]):
            self.skipTest("Host C compiler required")
        source = (ROOT / "3ds/source/main.c").read_text()
        constant = re.search(r"static const uint32_t g_b33_result_scratch = .*?;", source).group()
        start = source.index("static void fm_b33_fill_cd_result(")
        end = source.index("static int fm_b33_schedule_cd_callback(", start)
        writer = source[start:end]
        harness = r'''
#include <assert.h>
#include <stdint.h>
#include <string.h>
typedef struct { void (*write_byte)(uint32_t, uint8_t); } CPUState;
static uint8_t ram[0x200000];
static uint32_t g_cd_lba;
static void store(uint32_t a, uint8_t v) { ram[a & 0x1fffff] = v; }
'''
        harness += constant + "\n" + writer
        harness += r'''
int main(void) {
    CPUState cpu = {store};
    memset(ram, 0xa5, sizeof(ram));
    ram[0x9c4b8] = 1;
    uint8_t game[16], ready[8];
    memcpy(game, ram + 0x9c4b4, 16);
    memcpy(ready, ram + 0xf7138, 8);
    fm_b33_fill_cd_result(&cpu, 9);
    assert(ram[0xf7130] == 2);
    for (int i = 1; i < 8; ++i) assert(ram[0xf7130+i] == 0);
    assert(memcmp(game, ram + 0x9c4b4, 16) == 0);
    assert(memcmp(ready, ram + 0xf7138, 8) == 0);
    g_cd_lba = 4500;
    fm_b33_fill_cd_result(&cpu, 0x10);
    assert(ram[0xf7130] == 0x01 && ram[0xf7131] == 0x02);
    assert(ram[0xf7132] == 0);
    assert(memcmp(game, ram + 0x9c4b4, 16) == 0);
    assert(memcmp(ready, ram + 0xf7138, 8) == 0);
    fm_b33_fill_cd_result(0, 9);
    return 0;
}
'''
        with tempfile.TemporaryDirectory() as temp:
            path = Path(temp) / "cd-result.c"
            binary = Path(temp) / "cd-result"
            path.write_text(harness)
            result = subprocess.run(cc + ["-std=c11", "-Wall", "-Werror", str(path), "-o", str(binary)], capture_output=True, text=True)
            self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
            result = subprocess.run([str(binary)], capture_output=True, text=True)
            self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
