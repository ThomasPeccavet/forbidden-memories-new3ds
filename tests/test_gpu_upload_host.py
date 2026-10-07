"""Compare production GP0 word and burst paths, including partial/wrapped uploads."""
import os
from pathlib import Path
import shlex
import shutil
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]


class GpuUploadHostTests(unittest.TestCase):
    def test_word_and_burst_equivalence(self):
        cc = shlex.split(os.environ.get("CC", "cc"))
        if not cc or not shutil.which(cc[0]):
            self.skipTest("Host C compiler required")
        source = (ROOT / "3ds/source/fm_gpu.c").read_text()
        start = source.index("void fm_gpu_gp0_words(")
        end = source.index("\nvoid fm_gpu_gp1_write(", start)
        # Use both actual production entry points. Only the renderer API and
        # command dispatcher are isolated; the A0 state transition is copied
        # from the production dispatcher, not reimplemented in the test.
        a0 = source[source.index("        g_upload_x =", source.index("CPU -> VRAM\n")):
                    source.index("        return;", source.index("        g_upload_x =", source.index("CPU -> VRAM\n")))]
        harness = (ROOT / "tests/host/test_gpu_upload.c").read_text()
        harness = harness.replace("/* A0_DISPATCH */", a0)
        harness = harness.replace("/* GP0_ENTRY_POINTS */", source[start:end])
        with tempfile.TemporaryDirectory() as temp:
            c = Path(temp) / "gpu.c"
            binary = Path(temp) / "gpu"
            c.write_text(harness)
            result = subprocess.run(cc + ["-std=gnu11", "-O3", "-Wall", "-Wextra",
                                        str(c), "-o", str(binary)], capture_output=True, text=True)
            self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
            result = subprocess.run([str(binary)], capture_output=True, text=True)
            self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
