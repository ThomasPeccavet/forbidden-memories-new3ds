from pathlib import Path
import subprocess
import tempfile
import unittest
ROOT=Path(__file__).resolve().parents[1]
class SPUCoreTests(unittest.TestCase):
    def test_voice_mixer_and_snapshot(self):
        with tempfile.TemporaryDirectory() as directory:
            exe=Path(directory)/"spu"
            subprocess.run(["cc","-std=c11","-O2","-Wall","-Wextra","-Werror","-I",str(ROOT/"3ds/include"),str(ROOT/"3ds/source/fm_spu.c"),str(ROOT/"tests/host/test_spu_core.c"),"-o",str(exe)],check=True,capture_output=True)
            subprocess.run([str(exe)],check=True,capture_output=True)
