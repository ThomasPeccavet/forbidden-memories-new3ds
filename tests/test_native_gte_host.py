"""Compare every COP2 transfer with the pre-specialization implementation."""
from pathlib import Path
import subprocess
import tempfile
import unittest
ROOT=Path(__file__).resolve().parents[1]
class NativeGteTests(unittest.TestCase):
    def test_all_registers_aliases_and_state_effects(self):
        code=r'''
#include "fm_native_gte.h"
#include <assert.h>
#include <string.h>
uint32_t ref_gte_read_data(CPUState *,uint8_t);
uint32_t ref_gte_read_ctrl(CPUState *,uint8_t);
void ref_gte_write_data(CPUState *,uint8_t,uint32_t);
void ref_gte_write_ctrl(CPUState *,uint8_t,uint32_t);
static uint32_t seed=13662;
static uint32_t rnd(void) {seed=seed*1664525u+1013904223u;return seed;}
int main(void) {
 const uint32_t edge[]={0,1,0x7fff,0x8000,0xffff,0x80000000,0xffffffff,0x7fffffff};
 for(unsigned k=0;k<512;++k) for(unsigned r=0;r<256;++r) {
  CPUState a={0},b;
  for(unsigned i=0;i<32;++i){a.gte_data[i]=rnd();a.gte_ctrl[i]=rnd();}
  b=a;uint32_t v=k<8?edge[k]:rnd();
  assert(fm_native_gte_read_data(&a,r)==ref_gte_read_data(&b,r));
  assert(fm_native_gte_read_ctrl(&a,r)==ref_gte_read_ctrl(&b,r));
  assert(!memcmp(&a,&b,sizeof a));
  fm_native_gte_write_data(&a,r,v);ref_gte_write_data(&b,r,v);
  assert(!memcmp(&a,&b,sizeof a));
  fm_native_gte_write_ctrl(&a,r,v);ref_gte_write_ctrl(&b,r,v);
  assert(!memcmp(&a,&b,sizeof a));
 }
 return 0;
}
'''
        with tempfile.TemporaryDirectory() as tmp:
            c=Path(tmp)/'test.c';c.write_text(code);exe=Path(tmp)/'test'
            result=subprocess.run(['cc','-std=c11','-O2','-Wall','-Werror','-I',str(ROOT/'tests/host/include'),
                '-I',str(ROOT/'3ds/include'),str(c),str(ROOT/'tests/host/gte_transfer_reference.c'),'-o',str(exe)],capture_output=True,text=True)
            self.assertEqual(result.returncode,0,result.stderr)
            result=subprocess.run([str(exe)],capture_output=True,text=True)
            self.assertEqual(result.returncode,0,result.stderr)
