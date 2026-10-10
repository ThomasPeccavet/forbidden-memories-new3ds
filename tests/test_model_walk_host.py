"""Native model traversal versus the resident MIPS reference at every handoff."""
from pathlib import Path
import subprocess,tempfile,unittest
ROOT=Path(__file__).resolve().parents[1]
class ModelWalkTests(unittest.TestCase):
 def test_complete_traversal_and_resumable_callbacks(self):
  with tempfile.TemporaryDirectory() as tmp:
   exe=str(Path(tmp)/'test')
   subprocess.run(['cc','-std=c11','-O2','-Wall','-Wextra','-Werror',
    '-I'+str(ROOT/'tests/host/include'),'-I'+str(ROOT/'3ds/include'),
    str(ROOT/'tests/host/test_model_walk.c'),str(ROOT/'3ds/source/fm_model_walk.c'),
    str(ROOT/'3ds/source/fm_interp.c'),'-o',exe],check=True)
   subprocess.run([exe],check=True)
