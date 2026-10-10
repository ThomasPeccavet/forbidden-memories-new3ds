"""10-second recorder: load-trigger, exact safe duration, overflow, rearm."""
from pathlib import Path
import subprocess,tempfile,unittest
from test_gpu_perf_window_host import function
ROOT=Path(__file__).resolve().parents[1]
class PerfCaptureTests(unittest.TestCase):
 def test_record_duration_and_overflow(self):
  code=r'''#include <assert.h>
#include "fm_perf_capture.h"
static FMPerfCapture c;
int main(void){FMPerfCaptureRow r={0};r.start_pc=0x80123456;r.pre_ms=9;
 assert(!fm_capture_begin(&c,100));assert(!fm_capture_push(&c,101,&r));
 fm_capture_arm(&c);assert(c.armed&&!c.active);
 assert(fm_capture_begin(&c,1000));assert(!fm_capture_begin(&c,1001));
 for(unsigned i=1;i<=9999;++i){assert(!fm_capture_push(&c,1000+i,&r));}
 assert(c.count==FM_CAPTURE_ROWS&&c.dropped==9999-FM_CAPTURE_ROWS);
 assert(c.rows[0].elapsed_ms==1&&c.rows[0].start_pc==r.start_pc);
 assert(c.rows[0].pre_ms==9);
 assert(fm_capture_push(&c,11000,&r));assert(c.elapsed_ms==10000);
 fm_capture_hot(&c,0x80100000,20,7);fm_capture_hot(&c,0x80100000,30,9);
 assert(c.hot[0].calls==2&&c.hot[0].instructions==50&&c.hot[0].total_us==16&&c.hot[0].max_us==9);
 for(unsigned i=1;i<FM_CAPTURE_HOT_SLOTS;++i)fm_capture_hot(&c,0x80100000+i*4,1,1);
 fm_capture_hot(&c,0x80200000,1,1);assert(c.hot_dropped==1);
 c.active=0;assert(!fm_capture_push(&c,11001,&r));
 fm_capture_arm(&c);assert(c.count==0&&c.dropped==0&&!c.active);
 assert(fm_capture_begin(&c,20000));assert(!fm_capture_push(&c,29999,&r));
 assert(fm_capture_push(&c,30037,&r)); // no interruption of a long guest call
 assert(c.count==2&&c.rows[1].elapsed_ms==10037);
 fm_capture_arm(&c);assert(!c.count&&!c.active&&c.armed);
 return 0;}'''
  with tempfile.TemporaryDirectory() as tmp:
   p=Path(tmp)/'test.c';p.write_text(code);exe=Path(tmp)/'test'
   subprocess.run(['cc','-std=c11','-Wall','-Wextra','-Werror','-I'+str(ROOT/'3ds/include'),str(p),'-o',str(exe)],check=True)
   subprocess.run([str(exe)],check=True)
 def test_csv_and_hotspots_are_written_only_at_completion(self):
  body=function((ROOT/'3ds/source/main.c').read_text(),'fm_perf_capture_finish')
  code=r'''#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "fm_perf_capture.h"
static FMPerfCapture g_perf_capture;
'''+body+r'''
int main(void){
 assert(!system("mkdir -p sdmc:/3ds/fm-new3ds"));
 fm_capture_arm(&g_perf_capture);fm_capture_begin(&g_perf_capture,1000);
 FMPerfCaptureRow r={0};r.start_pc=0x80123456;r.end_pc=0x800746B8;r.pre_ms=9;
 assert(!fm_capture_push(&g_perf_capture,1010,&r));
 assert(!fopen("sdmc:/3ds/fm-new3ds/perf-capture.csv","rb"));
 fm_capture_hot(&g_perf_capture,r.start_pc,2048,37);
 assert(fm_capture_push(&g_perf_capture,11020,&r));
 fm_perf_capture_finish();assert(!g_perf_capture.active);
 FILE*f=fopen("sdmc:/3ds/fm-new3ds/perf-capture.csv","rb");assert(f);
 char text[4096]={0};fread(text,1,sizeof(text)-1,f);fclose(f);
 assert(strstr(text,"duration_ms=10020 rows=2 dropped=0 completed=1"));
 assert(strstr(text,"10,80123456,800746B8"));assert(strstr(text,"10020,80123456,800746B8"));
 f=fopen("sdmc:/3ds/fm-new3ds/perf-capture-summary.txt","rb");assert(f);
 memset(text,0,sizeof(text));fread(text,1,sizeof(text)-1,f);fclose(f);
 assert(strstr(text,"interp pc=80123456 calls=1 instructions=2048 us=37 max_us=37"));
 return 0;}
'''
  with tempfile.TemporaryDirectory() as tmp:
   p=Path(tmp)/'test.c';p.write_text(code);exe=Path(tmp)/'test'
   subprocess.run(['cc','-std=c11','-Wall','-Wextra','-Werror','-I'+str(ROOT/'3ds/include'),str(p),'-o',str(exe)],check=True)
   subprocess.run([str(exe)],cwd=tmp,check=True)
 def test_only_successful_load_arms_and_no_audio_io_in_capture(self):
  s=(ROOT/'3ds/source/main.c').read_text()
  a=s.index('static int fm_b135_quick_load(');b=s.index('invalid:',a)
  self.assertIn('fm_capture_arm(&g_perf_capture);',s[a:b])
  self.assertNotIn('fm_capture_arm',s[b:s.index('/*',b)])
  self.assertIn('&& !g_perf_capture.active && !g_perf_capture.armed',s)
  self.assertIn('perf-capture-summary.txt',s)
  self.assertIn('perf-capture.csv',s)
