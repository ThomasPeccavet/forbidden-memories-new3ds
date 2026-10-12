"""CPU-side contract of the experimental hardware renderer; no GPU timing claim."""
from pathlib import Path
import subprocess,tempfile,unittest
ROOT=Path(__file__).resolve().parents[1]
class PicaTests(unittest.TestCase):
 def test_packets_pixels_and_textures(self):
  with tempfile.TemporaryDirectory() as tmp:
   exe=str(Path(tmp)/'pica')
   subprocess.run(['cc','-std=c11','-O2','-Wall','-Wextra','-Werror',
    '-fsanitize=undefined','-fno-sanitize-recover=all','-I'+str(ROOT/'3ds/include'),
    str(ROOT/'tests/host/test_pica_plan.c'),str(ROOT/'3ds/source/fm_pica_plan.c'),'-o',exe],check=True)
   subprocess.run([exe],check=True)
