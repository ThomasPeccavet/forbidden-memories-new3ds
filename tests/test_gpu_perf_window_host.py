"""GPU opcode windows must aggregate multiple DMA lists without stale ranks."""
from pathlib import Path
import re
import subprocess
import tempfile
import unittest
ROOT=Path(__file__).resolve().parents[1]

def function(s,name):
    match=re.search(r'^(?:static[^\n]*|void)\s+'+name+r'\(',s,re.M)
    assert match,name
    a=match.start(); b=s.index('{',a); end=b+1; depth=1
    while depth:
        depth+=(s[end]=='{')-(s[end]=='}');end+=1
    return s[a:end]

class GpuPerfWindowTests(unittest.TestCase):
    def test_across_dma_resets_and_window_reset(self):
        s=(ROOT/'3ds/source/fm_gpu.c').read_text()
        funcs='\n'.join(function(s,n) for n in ('b122_record_opcode',
            'fm_gpu_perf_window_reset','fm_gpu_perf_window_rank',
            'fm_gpu_b13532_profile_reset'))
        declarations=[]
        for name in sorted(set(re.findall(r'\bg_[a-zA-Z0-9_]+',funcs))):
            match=re.search(r'static\s+(\w+)\s+(?:[^;\n]*,\s*)?'+name+r'(\[[^\]]+\])?',s)
            assert match,name
            declarations.append('static '+match[1]+' '+name+(match[2] or '')+';')
        code='''#include <stdint.h>
#include <string.h>
#include <assert.h>
typedef struct { uint8_t opcode; uint32_t calls; uint64_t total_us; uint32_t max_us; } FMGpuOpcodePerf;
static uint64_t b122_ticks_to_us(uint64_t t) { return t; }
'''+ '\n'.join(declarations)+'\n'+funcs+'''
int main(void) {
    FMGpuOpcodePerf hot;
    b122_record_opcode(0x30,400);
    fm_gpu_b13532_profile_reset();
    b122_record_opcode(0x30,200);
    b122_record_opcode(0x34,500);
    fm_gpu_perf_window_rank(0,&hot);
    assert(hot.opcode==0x30 && hot.calls==2 && hot.total_us==600 && hot.max_us==400);
    fm_gpu_perf_window_rank(1,&hot);
    assert(hot.opcode==0x34 && hot.calls==1 && hot.total_us==500);
    fm_gpu_perf_window_reset(); fm_gpu_perf_window_rank(0,&hot);
    assert(hot.calls==0);
    return 0;
}
'''
        with tempfile.TemporaryDirectory() as tmp:
            p=Path(tmp)/'gpu.c';p.write_text(code);exe=Path(tmp)/'gpu'
            subprocess.run(['cc','-std=c11','-O2','-Wall','-Werror',str(p),'-o',str(exe)],check=True)
            subprocess.run([str(exe)],check=True)
