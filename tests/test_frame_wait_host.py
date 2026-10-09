"""Verified guest wait escapes only after normal VBlank service, without writes."""
from pathlib import Path
import subprocess
import tempfile
import unittest
from test_gpu_perf_window_host import function
ROOT = Path(__file__).resolve().parents[1]

class FrameWaitTests(unittest.TestCase):
    def test_checkpoint_and_read_only_guards(self):
        source = (ROOT/'3ds/source/fm_runtime_shim.c').read_text()
        checkpoint = function(source, 'psx_check_interrupts_at')
        probe = function(source.replace('FMRuntimeProbeResult fm_runtime_probe(', 'static FMRuntimeProbeResult fm_runtime_probe('), 'fm_runtime_probe').removeprefix('static ')
        code = r'''
#include <assert.h>
#include <stddef.h>
#include <string.h>
#include <setjmp.h>
#include "fm_frame_wait.h"
#include "fm_runtime_shim.h"
static const uint32_t code_words[6]={0x9383018C,0x8F820190,0,0x0043102A,0x1440FFFB,0};
static uint32_t done, target, bad_word=99;
static uint32_t read_word(uint32_t a) {
    a &= 0x1FFFFFFF;
    if(a==0x9C428) return done;
    assert(a>=0x12CD4 && a<=0x12CE8 && !(a&3));
    unsigned i=(a-0x12CD4)/4; return code_words[i]^(i==bad_word);
}
static uint8_t read_byte(uint32_t a) {assert((a&0x1FFFFFFF)==0x9C424);return target;}
static CPUState *g_probe_cpu, *g_frame_wait_cpu;
static unsigned g_probe_checks, g_probe_budget, g_probe_armed;
static unsigned services, pending_vblank;
static FMRuntimeStopReason stopped;
static uint32_t stop_pc;
static jmp_buf escape, g_probe_jmp;
static FMRuntimeStopReason g_probe_reason;
static uint32_t g_probe_detail;
static int use_probe;
static void fm_probe_stop(FMRuntimeStopReason r,uint32_t pc) {
    stopped=r;stop_pc=pc;
    if(use_probe){g_probe_reason=r;g_probe_detail=pc;longjmp(g_probe_jmp,1);}
    longjmp(escape,1);
}
static void fm_runtime_service_vblank_hle(CPUState *cpu) {
    (void)cpu; ++services;
    if(pending_vblank){done=target;pending_vblank=0;}
}
static void b13570_sample_slot1(CPUState *cpu,unsigned a,unsigned b) {(void)cpu;(void)a;(void)b;}
''' + checkpoint + r'''
static int psx_dispatch_game_compiled(CPUState *cpu,uint32_t addr) {
    (void)addr;psx_check_interrupts_at(cpu,0x80012CD4);
    cpu->pc=0x80012CEC;return 1;
}
''' + probe + r'''
static void check(CPUState *cpu,uint32_t pc) {
    stopped=FM_STOP_NONE;
    if(!setjmp(escape)) psx_check_interrupts_at(cpu,pc);
}
int main(void) {
    CPUState cpu={0}, other={0};cpu.gpr[28]=0x8009C298;
    cpu.read_word=read_word;cpu.read_byte=read_byte;
    cpu.gpr[3]=123;cpu.gpr[2]=456;cpu.gpr[29]=0x801FF000;
    CPUState original=cpu;
    target=1;done=0;assert(fm_frame_wait_pending(&cpu,0x80012CD4));
    assert(!fm_frame_wait_pending(&cpu,0x80012CD8));
    assert(!fm_frame_wait_pending(NULL,0x80012CD4));
    for(unsigned i=0;i<6;++i){bad_word=i;assert(!fm_frame_wait_pending(&cpu,0x80012CD4));}
    bad_word=99;cpu.gpr[28]+=4;assert(!fm_frame_wait_pending(&cpu,0x80012CD4));cpu=original;
    done=1;assert(!fm_frame_wait_pending(&cpu,0x80012CD4));
    done=2;assert(!fm_frame_wait_pending(&cpu,0x80012CD4));
    done=0xFFFFFFFF;assert(fm_frame_wait_pending(&cpu,0x80012CD4));
    assert(!memcmp(&cpu,&original,sizeof(cpu))); /* helper is entirely read-only */
    g_probe_cpu=g_frame_wait_cpu=&cpu;g_probe_armed=1;g_probe_budget=1;
    check(&cpu,0x80012CD4);assert(stopped==FM_STOP_FRAME_WAIT && stop_pc==0x80012CD4);
    original.pc=0x80012CD4;assert(!memcmp(&cpu,&original,sizeof(cpu)));
    assert(done==0xFFFFFFFF && target==1 && services==1);
    pending_vblank=1;g_probe_checks=0;
    check(&cpu,0x80012CD4);assert(stopped==FM_STOP_BUDGET && done==1 && services==2);
    done=0;g_probe_budget=0;
    check(&cpu,0x80012CD4);assert(stopped==FM_STOP_FRAME_WAIT);
    g_frame_wait_cpu=NULL;check(&cpu,0x80012CD4);assert(stopped==FM_STOP_NONE);
    other=cpu;g_frame_wait_cpu=&other;check(&cpu,0x80012CD4);assert(stopped==FM_STOP_NONE);
    g_frame_wait_cpu=&cpu;g_probe_cpu=&other;check(&cpu,0x80012CD4);assert(stopped==FM_STOP_NONE);
    g_probe_cpu=&cpu;g_probe_armed=0;check(&cpu,0x80012CD4);assert(stopped==FM_STOP_NONE);
    g_probe_armed=1;bad_word=4;check(&cpu,0x80012CD4);assert(stopped==FM_STOP_NONE);
    bad_word=99;done=0;use_probe=1;g_frame_wait_cpu=&cpu;
    FMRuntimeProbeResult r=fm_runtime_probe(&cpu,0x80012CB8,100);
    assert(r.reason==FM_STOP_FRAME_WAIT && r.pc==0x80012CD4 && r.detail==r.pc);
    assert(r.checks==1 && !g_probe_armed && !g_probe_cpu);
    pending_vblank=1;r=fm_runtime_probe(&cpu,cpu.pc,100);
    assert(r.reason==FM_STOP_RETURNED && r.pc==0x80012CEC && done==target);
    assert(!g_probe_armed && !g_probe_cpu);
    return 0;
}
'''
        with tempfile.TemporaryDirectory() as tmp:
            p=Path(tmp)/'wait.c';p.write_text(code);exe=Path(tmp)/'wait'
            subprocess.run(['cc','-std=c11','-O2','-Wall','-Werror','-I',str(ROOT/'3ds/include'),'-I',str(ROOT/'tests/host/include'),str(p),'-o',str(exe)],check=True)
            subprocess.run([str(exe)],check=True)
