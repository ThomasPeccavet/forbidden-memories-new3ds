"""Production BIOS branches and IRQ gate; masked pending bits never vanish."""
from pathlib import Path
import subprocess
import tempfile
import unittest
ROOT=Path(__file__).resolve().parents[1]
def body(text, start):
    a=text.index('{',start); depth=1; b=a+1
    while depth:
        depth+=(text[b]=='{')-(text[b]=='}'); b+=1
    return text[a:b]
class BiosIRQTests(unittest.TestCase):
    def test_hook_reset_and_critical_section_contracts(self):
        src=(ROOT/'3ds/source/fm_runtime_shim.c').read_text()
        cases=[]
        for label,case in [('B0:18 ResetEntryInt','0x18'),('B0:19 HookEntryInt','0x19')]:
            a=src.index('case '+case+':',src.index(label)); cases.append('case '+case+':'+body(src,a))
        a=src.index('int psx_syscall(')
        critical=[f'case {i}:'+body(src,src.index(f'case {i}:',a)) for i in [1,2]]
        a=src.index('static void fm_runtime_service_vblank_hle(')
        vblank='static void service(CPUState *cpu)'+body(src,a)
        code=r'''
#include "fm_irq.h"
#include <assert.h>
static uint32_t g_bios_entry_hook_addr;
static uint16_t stat,mask;
static uint32_t counter,done; static uint8_t target;
static uint16_t fm_memory_i_stat(void) { return stat; }
static uint16_t fm_memory_i_mask(void) { return mask; }
static void fm_memory_write_word(uint32_t a,uint32_t v) { assert(a==0x1F801070); stat&=v; }
static uint32_t readw(uint32_t a) { return a==0x80093EE8 ? counter : done; }
static uint8_t readb(uint32_t a) { assert(a==0x8009C424); return target; }
static void writew(uint32_t a,uint32_t v) { if(a==0x80093EE8) counter=v; else done=v; }
static int bios(CPUState *cpu,unsigned fn) { switch(fn) {
'''+'\n'.join(cases)+r''' } return 0; }
static int critical(CPUState *cpu) { uint32_t sr=cpu->cop0[12]; switch(cpu->gpr[4]) {
'''+'\n'.join(critical)+r''' } return 1; }
'''+vblank+r'''
int main(void) {
    CPUState c={0}; c.gpr[31]=0x80012340; c.read_word=readw;c.read_byte=readb;c.write_word=writew;
    c.gpr[4]=0x800ABCDE; assert(bios(&c,0x19) && c.gpr[2]==0);
    assert(bios(&c,0x18) && c.gpr[2]==0x800ABCDE && !g_bios_entry_hook_addr);
    assert(bios(&c,0x18) && c.gpr[2]==0 && c.pc==c.gpr[31]);
    c.cop0[12]=0x40000401; c.gpr[4]=1; assert(!critical(&c) && c.gpr[2]==1);
    assert(!fm_irq_cpu_enabled(&c));
    assert(!critical(&c) && c.gpr[2]==0); /* nested enter reports previous IEC */
    mask=0x49;stat=0x41;target=3; service(&c); assert(stat==0x41 && !counter);
    c.gpr[4]=2; assert(!critical(&c) && c.cop0[12]==0x40000401 && fm_irq_cpu_enabled(&c));
    c.cop0[12]=1; service(&c); assert(stat==0x41 && !counter); /* IM2 disabled */
    c.cop0[12]=0x401;mask=0x40;service(&c); assert(stat==0x41 && !counter);
    mask=0x49;service(&c);assert(counter==1 && stat==0x40 && done>=target);
    service(&c);assert(counter==1 && stat==0x40);
    return 0;
}
'''
        with tempfile.TemporaryDirectory() as tmp:
            c=Path(tmp)/'test.c';c.write_text(code);exe=Path(tmp)/'test'
            result=subprocess.run(['cc','-std=c11','-Wall','-Werror','-I',str(ROOT/'tests/host/include'),
                '-I',str(ROOT/'3ds/include'),str(c),'-o',str(exe)],capture_output=True,text=True)
            self.assertEqual(result.returncode,0,result.stderr)
            result=subprocess.run([str(exe)],capture_output=True,text=True)
            self.assertEqual(result.returncode,0,result.stderr)
