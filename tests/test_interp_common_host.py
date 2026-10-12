"""Differential production/reference interpreter, RAM/MMIO and overlay exits."""
from pathlib import Path
import subprocess,tempfile,unittest
ROOT=Path(__file__).resolve().parents[1]
class InterpCommonTests(unittest.TestCase):
 def test_common_operations_and_overlay_chain(self):
  with tempfile.TemporaryDirectory() as tmp:
   tmp=Path(tmp)
   base=['cc','-std=c11','-O2','-Wall','-Wextra','-Werror',
     '-I'+str(ROOT/'tests/host/include'),'-I'+str(ROOT/'3ds/include')]
   source=str(ROOT/'3ds/source/fm_interp.c')
   subprocess.run(base+['-c',source,'-o',str(tmp/'fast.o')],check=True)
   subprocess.run(base+['-DFM_INTERP_FAST_COMMON=0',
     '-Dfm_interp_bind_ram=ref_bind','-Dfm_interp_run_block=ref_block',
     '-Dfm_interp_run_region=ref_region','-Dfm_interp_stop_name=ref_stop',
     '-c',source,'-o',str(tmp/'ref.o')],check=True)
   exe=tmp/'test'
   subprocess.run(base+[str(ROOT/'tests/host/test_interp_common.c'),
     str(tmp/'fast.o'),str(tmp/'ref.o'),'-o',str(exe)],check=True)
   subprocess.run([str(exe)],check=True)
