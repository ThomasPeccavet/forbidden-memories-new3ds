"""Wall-clock tick conservation, bounded catch-up and explicit pause reset."""
from pathlib import Path
import subprocess,tempfile,unittest
from test_gpu_perf_window_host import function
ROOT=Path(__file__).resolve().parents[1]
class HostClockTests(unittest.TestCase):
 def compile_run(self,code):
  with tempfile.TemporaryDirectory() as tmp:
   p=Path(tmp)/'clock.c';p.write_text(code);exe=Path(tmp)/'clock'
   subprocess.run(['cc','-std=c11','-Wall','-Werror','-I',str(ROOT/'3ds/include'),str(p),'-o',str(exe)],check=True)
   subprocess.run([str(exe)],check=True)
 def test_cadence_pause_and_reset(self):
  self.compile_run('''#include <assert.h>
#include "fm_host_clock.h"
int main(void){
 const unsigned steps[]={1,7,12,17,23,33,50,75,90,100,150,250,251,500};
 for(unsigned i=0;i<sizeof(steps)/sizeof(steps[0]);++i){
  FMHostClock c={0}; unsigned ticks=0;uint64_t now=1000;
  assert(fm_host_clock_due(&c,now)==0);
  while(now<11000){unsigned delta=steps[i];if(now+delta>11000)delta=11000-now;
   now+=delta;unsigned n;
   do {n=fm_host_clock_due(&c,now);assert(n<=FM_HOST_CLOCK_BATCH);ticks+=n;}
   while(fm_host_clock_pending(&c));
  }
  assert(ticks==600);
 }
 FMHostClock c={0};assert(!fm_host_clock_due(&c,0));
 assert(fm_host_clock_due(&c,16)==0);assert(fm_host_clock_due(&c,17)==1);
 assert(fm_host_clock_due(&c,217)==8);assert(c.pending==4);
 assert(fm_host_clock_due(&c,217)==4);assert(!c.pending);
 assert(fm_host_clock_due(&c,217)==0);
 assert(fm_host_clock_due(&c,1000)==8);assert(c.pending==39);
 fm_host_clock_reset(&c);assert(!c.pending && !c.fraction);
 assert(!fm_host_clock_update(&c,5000,0));assert(!c.valid);
 assert(!fm_host_clock_update(&c,90000,1)); // resume baseline, no paused time
 assert(fm_host_clock_update(&c,90017,1)==1);
 assert(!fm_host_clock_update(&c,90100,0)); // paused debt discarded explicitly
 assert(!fm_host_clock_update(&c,120000,1));
 assert(fm_host_clock_update(&c,120017,1)==1);
 assert(!fm_host_clock_due(&c,100)); // time reversal
 assert(!c.pending && !c.fraction);
 return 0;
}''')
 def test_repeated_stalls_conserve_time_and_skip_debt_wait(self):
  self.compile_run('''#include <assert.h>
#include "fm_host_clock.h"
int main(void){
 FMHostClock c={0};fm_host_clock_due(&c,0);unsigned ticks=0;
 // Regular 90ms slices formerly advanced only 44.4Hz. No flush is needed.
 for(unsigned i=1;i<=1000;++i)ticks+=fm_host_clock_due(&c,i*90u);
 assert(ticks==5400 && !c.pending);
 // A 400ms nonpreemptible guest block creates 24 ticks. Delivery stays bounded.
 unsigned n=fm_host_clock_due(&c,90400);assert(n==8 && c.pending==16);
 int guest_vsync_wait=1, guest_budget=0, running=1;
 int continue_budget=(guest_budget && !guest_vsync_wait)
  || (running && fm_host_clock_pending(&c));
 assert(continue_budget); // main scheduler must not call gspWaitForVBlank
 n=fm_host_clock_due(&c,90400);assert(n==8 && c.pending==8);
 n=fm_host_clock_due(&c,90400);assert(n==8 && !c.pending);
 // Timer callback CPU cost is also elapsed time, not silently discarded.
 n=fm_host_clock_due(&c,90450);assert(n==3);
 // Millisecond values beyond 32-bit must not truncate.
 FMHostClock large={0};fm_host_clock_due(&large,0);
 fm_host_clock_due(&large,4294967296ull);
 assert(large.pending+8==257698037ull);
 assert(large.fraction==760);
 return 0;
}''')
 def test_deadline_after_guest_work_is_read_only(self):
  self.compile_run('''#include <assert.h>
#include "fm_host_clock.h"
int main(void){
 FMHostClock c={0};fm_host_clock_due(&c,1000);
 assert(fm_host_clock_wait_ns(&c,1000)==16666667u);
 assert(fm_host_clock_wait_ns(&c,1016)==666667u);
 assert(!fm_host_clock_wait_ns(&c,1017));
 // Deadline inspection must not consume the IRQ owed by guest CPU work.
 assert(c.last_ms==1000 && c.fraction==0 && c.pending==0);
 assert(fm_host_clock_due(&c,1021)==1 && c.fraction==260);
 assert(fm_host_clock_wait_ns(&c,1021)==12333334u);
 assert(!fm_host_clock_wait_ns(&c,1034));
 assert(fm_host_clock_due(&c,1034)==1);
 // Long raster block: all debt is still delivered, without a host sleep.
 assert(fm_host_clock_due(&c,1434)==8 && c.pending==16);
 assert(!fm_host_clock_wait_ns(&c,1434));
 assert(fm_host_clock_due(&c,1434)==8);
 assert(fm_host_clock_due(&c,1434)==8);
 assert(fm_host_clock_wait_ns(&c,1434)>0);
 fm_host_clock_reset(&c);assert(fm_host_clock_wait_ns(&c,1434)>0);
 return 0;
}''')
 def test_apt_hook_marks_explicit_resume(self):
  s=(ROOT/'3ds/source/main.c').read_text()
  hook=function(s,'fm_clock_apt_hook')
  self.compile_run('''#include <assert.h>
typedef enum {APTHOOK_ONSUSPEND,APTHOOK_ONRESTORE,APTHOOK_ONSLEEP,
 APTHOOK_ONWAKEUP,APTHOOK_ONEXIT} APT_HookType;
static volatile unsigned g_clock_resume_reset;
'''+hook+'''
int main(void){
 for(unsigned i=0;i<4;++i){g_clock_resume_reset=0;
 fm_clock_apt_hook((APT_HookType)i,0);assert(g_clock_resume_reset==1);}
 g_clock_resume_reset=0;fm_clock_apt_hook(APTHOOK_ONEXIT,0);
 assert(!g_clock_resume_reset);return 0;
}''')
  self.assertIn('aptHook(&g_clock_apt_hook,fm_clock_apt_hook,NULL);',s)
  self.assertIn('aptUnhook(&g_clock_apt_hook);',s)
  register=s.index('aptHook(&g_clock_apt_hook,fm_clock_apt_hook,NULL);')
  main_loop=s.index('    while (aptMainLoop())\n    {\n        uint64_t b105_loop_start_ms')
  self.assertLess(register,main_loop)
  self.assertGreater(register,s.index('fm_cd_hle_reset();',s.index('int main(void)')))
  self.assertEqual(s.count('aptHook(&g_clock_apt_hook,fm_clock_apt_hook,NULL);'),1)
 def test_scheduler_gates_and_quickload_reset(self):
  s=(ROOT/'3ds/source/main.c').read_text()
  self.assertIn('&& !g_vsync_wait_active && !g_frame_wait_active;',s)
  self.assertIn('continue_budget |= game_running && fm_host_clock_pending(&g_ps1_host_clock);',s)
  self.assertIn('g_b105_work_ms < 16u && !continue_budget',s)
  load=s[s.index('static int fm_b135_quick_load('):s.index('static int fm_b135_quick_load(')+12000]
  self.assertIn('fm_host_clock_reset(&g_ps1_host_clock);',load)
  self.assertIn('for (unsigned clock_tick=0; clock_tick<clock_due; ++clock_tick)',s)
 def test_clock_precedes_guest_dispatch_after_input(self):
  s=(ROOT/'3ds/source/main.c').read_text()
  loop=s.index('while (aptMainLoop())')
  clock=s.index('unsigned clock_due=fm_host_clock_update(',loop)
  execution=s.index('* EXECUTION',loop)
  dispatch=s.index('uint64_t b16_slice_start_ms',loop)
  wait=s.index('gspWaitForVBlank();',dispatch)
  self.assertLess(clock,execution)
  self.assertLess(execution,dispatch)
  self.assertLess(dispatch,wait)
  self.assertEqual(s.count('unsigned clock_due=fm_host_clock_update('),1)
  self.assertIn('fm_mdec_host_frame = frame;',s[clock:execution])
  self.assertLess(s.index('fm_b135_quick_load(',loop),clock)
  self.assertIn('if (g_clock_resume_reset)',s[loop:clock])
