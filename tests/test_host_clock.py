"""Wall-clock cadence must be independent of scheduler slice count."""
from pathlib import Path
import subprocess,tempfile,unittest
ROOT=Path(__file__).resolve().parents[1]
class HostClockTests(unittest.TestCase):
 def test_cadence_pause_and_reset(self):
  code='''#include <assert.h>
#include "fm_host_clock.h"
int main(void){
 const unsigned steps[]={1,7,12,17,23,33,50};
 for(unsigned i=0;i<sizeof(steps)/sizeof(steps[0]);++i){
  FMHostClock c={0}; unsigned ticks=0;uint64_t now=1000;
  assert(fm_host_clock_due(&c,now)==0);
  while(now<11000){unsigned delta=steps[i];if(now+delta>11000)delta=11000-now;
   now+=delta;ticks+=fm_host_clock_due(&c,now);}
  assert(ticks==600);
 }
 FMHostClock c={0};assert(!fm_host_clock_due(&c,0));
 assert(fm_host_clock_due(&c,16)==0);assert(fm_host_clock_due(&c,17)==1);
 assert(fm_host_clock_due(&c,217)==4); /* bounded callback backlog */
 assert(fm_host_clock_due(&c,1000)==0); /* pause does not replay input */
 assert(fm_host_clock_due(&c,1017)==1);
 fm_host_clock_reset(&c);assert(fm_host_clock_due(&c,5000)==0);
 assert(fm_host_clock_due(&c,5017)==1);
 assert(fm_host_clock_due(&c,100)==0); /* host time reversal */
 return 0;
}'''
  with tempfile.TemporaryDirectory() as tmp:
   p=Path(tmp)/'clock.c';p.write_text(code);exe=Path(tmp)/'clock'
   subprocess.run(['cc','-std=c11','-Wall','-Werror','-I',str(ROOT/'3ds/include'),str(p),'-o',str(exe)],check=True)
   subprocess.run([str(exe)],check=True)
 def test_scheduler_gates_and_quickload_reset(self):
  s=(ROOT/'3ds/source/main.c').read_text()
  self.assertIn('&& !g_vsync_wait_active;',s)
  self.assertIn('g_b105_work_ms < 16u && !continue_budget',s)
  load=s[s.index('static int fm_b135_quick_load('):s.index('static int fm_b135_quick_load(')+12000]
  self.assertIn('fm_host_clock_reset(&g_ps1_host_clock);',load)
  self.assertIn('for (unsigned clock_tick=0; clock_tick<clock_due; ++clock_tick)',s)
