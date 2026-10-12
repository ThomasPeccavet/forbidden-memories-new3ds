"""Cached versus original GTE: compare all CPU fields after every command."""
from pathlib import Path
import subprocess,tempfile,unittest
ROOT=Path(__file__).resolve().parents[1]
class GeometryCacheTests(unittest.TestCase):
 def test_exact_projection_flags_and_fifo_with_reuse(self):
  s=(ROOT/'3ds/source/fm_runtime_shim.c').read_text()
  a=s.index('static uint32_t fm_b136_gte_sign_extend_16(')
  b=s.index('/*\n * B135.4 -',a)
  source='''#include "fm_geometry_cache.h"
#include <stdlib.h>
#define FM_STOP_GTE 1
static void fm_probe_stop(int reason,uint32_t detail) {(void)reason;(void)detail;abort();}
'''+s[a:b]+'''\nvoid test_force_wrap(void) {g_geometry_cache.generation=0xffffffffu;g_geometry_cache.controls[0]^=1;}
'''
  with tempfile.TemporaryDirectory() as tmp:
   t=Path(tmp);c=t/'gte.c';c.write_text(source)
   base=['cc','-std=c11','-O3','-Wall','-Wextra','-Wno-unused-function',
    '-I'+str(ROOT/'tests/host/include'),'-I'+str(ROOT/'3ds/include')]
   subprocess.run(base+['-c',str(c),'-o',str(t/'cache.o')],check=True)
   names=['gte_execute','gte_read_data','gte_read_ctrl','gte_write_data','gte_write_ctrl',
    'fm_runtime_geometry_cache_stats','test_force_wrap']
   subprocess.run(base+['-DFM_GEOMETRY_CACHE=0']+['-D'+n+'=ref_'+n for n in names]+
    ['-c',str(c),'-o',str(t/'ref.o')],check=True)
   exe=t/'test'
   subprocess.run(base+[str(ROOT/'tests/host/test_geometry_cache.c'),str(t/'cache.o'),str(t/'ref.o'),'-o',str(exe)],check=True)
   result=subprocess.run([str(exe)],capture_output=True,text=True)
   self.assertEqual(result.returncode,0,result.stdout+result.stderr)
   print(result.stdout)
