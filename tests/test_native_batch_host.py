"""Native batching preserves HLE boundaries, misses, watchdogs and time yields."""
from pathlib import Path
import subprocess,tempfile,unittest
ROOT=Path(__file__).resolve().parents[1]
class NativeBatchTests(unittest.TestCase):
 def test_production_chain(self):
  s=(ROOT/'3ds/source/fm_runtime_shim.c').read_text();a=s.index('FMRuntimeProbeResult fm_runtime_probe_chain(');b=s.index('\n\n/*',a)
  code='''#include <stdint.h>
#include <stddef.h>
#include <setjmp.h>
#include <assert.h>
#include "fm_native_batch.h"
typedef struct {uint32_t pc;} CPUState;
typedef struct {int reason,dispatch_result;uint32_t pc,detail,checks;} FMRuntimeProbeResult;
#define FM_STOP_NONE 0
#define FM_STOP_RETURNED 1
static CPUState *g_probe_cpu;
static uint32_t g_probe_budget,g_probe_checks,g_probe_detail;
static int g_probe_reason,g_probe_armed;
static jmp_buf g_probe_jmp;
static uint64_t now;
static unsigned calls,scenario;
static uint64_t osGetTime(void){return now;}
static int psx_dispatch_game_compiled(CPUState *cpu,uint32_t current){
 ++calls;++g_probe_checks;
 if(scenario==1){cpu->pc=current+4;return 1;}
 if(scenario==2){now+=1;cpu->pc=current+4;return 1;}
 if(scenario==3)return 0;
 if(scenario==4){g_probe_reason=7;g_probe_detail=123;longjmp(g_probe_jmp,1);}
 if(scenario==5){
  if(current==0x800408BCu)cpu->pc=0x800418C0u;
  else if(current==0x800418C0u)cpu->pc=0x80084978u;
  else if(current==0x80084978u)cpu->pc=0x80042538u;
  else assert(0);
  return 1;
 }
 cpu->pc=current==0x80084018u?0x80084978u:0x80085D98u;
 return 1;
}
'''+s[a:b]+'''
static FMRuntimeProbeResult run(CPUState *cpu,unsigned limit,unsigned *count){
 calls=0;now=0;
 return fm_runtime_probe_chain(cpu,cpu->pc,100,0x342B0,0x35AC8,0x4D260,0x4D5B8,
  0x89D60,0x8A204,0x5721C,0x58860,limit,count);
}
int main(void){
 assert(fm_native_object_batch(0x80084978));
 assert(!fm_native_object_batch(0x80085D98));
 assert(!fm_native_object_batch(0x80081AEC));
 assert(!fm_native_object_batch(0x800746B8));
 assert(!fm_native_object_batch(0x80153070));
 assert(fm_native_render_batch(0x80040350));
 assert(fm_native_render_batch(0x800418C0));
 assert(fm_native_render_batch(0x80042508));
 assert(fm_native_render_batch(0x80042ADC));
 assert(fm_native_render_batch(0x80042BDC));
 assert(!fm_native_render_batch(0x8004034C));
 assert(!fm_native_render_batch(0x80042BE0));
 assert(!fm_native_batchable(0x80042538));
 assert(!fm_native_batchable(0x80043CD4));
 assert(!fm_native_batchable(0x80012CD4));
 assert(!fm_native_batchable(0x800914A8));
 assert(!fm_native_batchable(0x80180CF4));
 CPUState cpu={0x80084018};unsigned count;
 scenario=0;FMRuntimeProbeResult r=run(&cpu,64,&count);
 assert(count==2 && calls==2 && cpu.pc==0x80085D98 && r.dispatch_result==1);
 assert(!g_probe_armed && !g_probe_cpu);
 scenario=1;cpu.pc=0x80084018;r=run(&cpu,3,&count);assert(count==3 && calls==3);
 scenario=2;cpu.pc=0x80084018;r=run(&cpu,64,&count);assert(count==4 && calls==4);
 scenario=3;cpu.pc=0x80084018;r=run(&cpu,64,&count);assert(count==1 && r.dispatch_result==0);
 scenario=4;cpu.pc=0x80084018;r=run(&cpu,64,&count);assert(r.reason==7 && r.detail==123 && !g_probe_armed);
 scenario=0;cpu.pc=0x80085D98;r=run(&cpu,64,&count);assert(count==0 && calls==0);
 scenario=5;cpu.pc=0x800408BC;r=run(&cpu,64,&count);
 assert(count==3 && calls==3 && r.reason==FM_STOP_RETURNED && r.pc==0x80042538);
 /* Re-entering the diagnostic/safety boundary must never execute it. */
 r=run(&cpu,64,&count);assert(count==0 && calls==0 && r.pc==0x80042538);
 return 0;
}'''
  with tempfile.TemporaryDirectory() as tmp:
   p=Path(tmp)/'batch.c';p.write_text(code);exe=Path(tmp)/'batch'
   subprocess.run(['cc','-std=c11','-O2','-Wall','-Werror','-I',str(ROOT/'3ds/include'),str(p),'-o',str(exe)],check=True)
   subprocess.run([str(exe)],check=True)
