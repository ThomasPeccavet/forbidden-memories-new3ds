"""Execute the real memory module on the host, without ROM/devkitPro/Azahar."""
import os
from pathlib import Path
import shlex
import shutil
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]
from tools.inline_native_memory import transform


class SpuDma4HostTests(unittest.TestCase):
    def test_memory_mmio(self):
        cc = shlex.split(os.environ.get("CC", "cc"))
        if not cc or not shutil.which(cc[0]):
            self.skipTest("Host C compiler required (set CC); Ubuntu CI provides cc")
        with tempfile.TemporaryDirectory() as temp:
            fixture = (ROOT / "tests/host/native_memory_generated.c").read_text()
            native, count = transform(fixture)
            self.assertEqual(count, 6)
            generated = Path(temp) / "native-memory.c"
            generated.write_text(fixture.replace("native_fixture(", "native_fixture_reference(") + "\n" + native)
            for profile, cycles in ((0,0), (1,0), (0,1), (1,1)):
                binary = Path(temp) / f"spu-dma4-{profile}-{cycles}"
                cmd = cc + [
                    "-std=gnu11", "-O2", "-Werror=implicit-function-declaration",
                    f"-DFM_PERF_PROFILE={profile}", "-DPSX_NO_DEBUG_TOOLS",
                    "-I", str(ROOT / "tests/host/include"),
                    "-I", str(ROOT / "3ds/include"),
                    str(ROOT / "3ds/source/fm_memory.c"),
                    str(ROOT / "3ds/source/fm_spu.c"),
                    str(ROOT / "3ds/source/fm_sort_swap.c"),
                    str(ROOT / "3ds/source/fm_mdec.c"),
                    str(ROOT / "3ds/source/fm_interp.c"),
                    str(ROOT / "tests/host/test_spu_dma4.c"),
                    str(generated),
                    "-o", str(binary),
                ]
                if cycles:
                    cmd.insert(1,"-DPSX_ENABLE_BLOCK_CYCLES")
                result = subprocess.run(cmd, capture_output=True, text=True)
                self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
                for case in ("sort_swap", "native_ram_fast", "scratch_fast", "interp_ram_fast", "ram_fast", "spu_half", "spu_word", "reverb_mask", "native_reverb_poll",
                             "timer2_clock", "dma_partial", "dma_completion", "dma_payload", "reset"):
                    with self.subTest(profile=profile, cycles=cycles, case=case):
                        result = subprocess.run([str(binary), case], capture_output=True, text=True, cwd=temp)
                        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
                        if case == "native_ram_fast" and profile:
                            watch = (Path(temp) / "fm-native-watch.txt").read_text()
                            self.assertIn("addr=8009C4B8", watch)
                            self.assertIn("addr=800EB248", watch)
