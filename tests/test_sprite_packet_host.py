"""Native sprite packet versus resident MIPS, including unchanged fallback."""
from pathlib import Path
import subprocess,tempfile,unittest
ROOT=Path(__file__).resolve().parents[1]
class SpritePacketTests(unittest.TestCase):
 def test_exact_packets_and_fallbacks(self):
  with tempfile.TemporaryDirectory() as tmp:
   exe=str(Path(tmp)/'test')
   subprocess.run(['cc','-std=c11','-O2','-Wall','-Wextra','-Werror',
    '-I'+str(ROOT/'tests/host/include'),'-I'+str(ROOT/'3ds/include'),
    str(ROOT/'tests/host/test_sprite_packet.c'),str(ROOT/'3ds/source/fm_sprite_packet.c'),
    str(ROOT/'3ds/source/fm_interp.c'),'-o',exe],check=True)
   subprocess.run([exe],check=True)
