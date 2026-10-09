"""Execute the real memory module on the host, without ROM/devkitPro/Azahar."""
import os
from pathlib import Path
import shlex
import shutil
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]


class SpuDma4HostTests(unittest.TestCase):
    def test_memory_mmio(self):
        cc = shlex.split(os.environ.get("CC", "cc"))
        if not cc or not shutil.which(cc[0]):
            self.skipTest("Host C compiler required (set CC); Ubuntu CI provides cc")
        with tempfile.TemporaryDirectory() as temp:
            for profile in (0, 1):
                binary = Path(temp) / f"spu-dma4-{profile}"
                cmd = cc + [
                    "-std=gnu11", "-O2", "-Werror=implicit-function-declaration",
                    f"-DFM_PERF_PROFILE={profile}", "-DPSX_NO_DEBUG_TOOLS",
                    "-I", str(ROOT / "tests/host/include"),
                    "-I", str(ROOT / "3ds/include"),
                    str(ROOT / "3ds/source/fm_memory.c"),
                    str(ROOT / "3ds/source/fm_mdec.c"),
                    str(ROOT / "3ds/source/fm_interp.c"),
                    str(ROOT / "tests/host/test_spu_dma4.c"),
                    "-o", str(binary),
                ]
                result = subprocess.run(cmd, capture_output=True, text=True)
                self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
                for case in ("scratch_fast", "interp_ram_fast", "ram_fast", "spu_half", "spu_word", "reverb_mask", "native_reverb_poll",
                             "timer2_clock", "dma_partial", "dma_completion", "reset"):
                    with self.subTest(profile=profile, case=case):
                        result = subprocess.run([str(binary), case], capture_output=True, text=True)
                        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
