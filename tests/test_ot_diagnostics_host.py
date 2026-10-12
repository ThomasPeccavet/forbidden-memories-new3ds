"""Legacy inspection must not traverse guest OTs unless explicitly enabled."""
from pathlib import Path
import subprocess
import tempfile
import unittest
ROOT = Path(__file__).resolve().parents[1]


def function(source, name):
    start = source.index('static int ' + name + '(')
    brace = source.index('{', start)
    depth = 1
    end = brace + 1
    while depth:
        depth += (source[end] == '{') - (source[end] == '}')
        end += 1
    return source[start:end]


class OtDiagnosticsTests(unittest.TestCase):
    def test_opt_in_walks_and_default_zero_reads(self):
        source = (ROOT / '3ds/source/main.c').read_text()
        funcs = '\n'.join(function(source, name) for name in (
            'b13556_chain_contains_hand', 'fm_chain_has_hand_shape',
            'b13557_chain_has_hand_shape',
            'b13558_chain_reaches'))
        code = r'''#include <stdint.h>
#include <assert.h>
#include <string.h>
#define B13556_HAND_SLOTS 1
static uint32_t g_b13556_hand_packet[1];
static uint32_t ram[16384], saved[16384], reads;
typedef struct { uint32_t (*read_word)(uint32_t); } CPUState;
static uint32_t read_word(uint32_t a) {
    ++reads; return ram[(a & 0x1fffff)/4];
}
''' + funcs + r'''
int main(void) {
    for(unsigned i=0;i<4096;++i) ram[i]=4*(i+1);
    unsigned packet=4095*4;
    ram[4095]=0x05ffffff;
    ram[4096]=0xe1000000; ram[4097]=0x64000000;
    ram[4100]=0x003c0034;
    g_b13556_hand_packet[0]=packet;
    memcpy(saved,ram,sizeof(ram));
    CPUState cpu={read_word}; uint32_t steps=123,p=123,stop=123,h=123;
    int found=b13557_chain_has_hand_shape(&cpu,0x80000004,&steps,&p);
    assert(found==FM_OT_DIAGNOSTICS);
    if(FM_OT_DIAGNOSTICS) { assert(steps==4095 && p==0x80000000+packet); }
    else { assert(steps==0 && p==0 && reads==0); }
    found=b13556_chain_contains_hand(&cpu,0x80000004,&steps);
    assert(found==FM_OT_DIAGNOSTICS);
    found=b13558_chain_reaches(&cpu,0x80000004,packet,&steps,&stop,&h);
    assert(found==FM_OT_DIAGNOSTICS);
    if(FM_OT_DIAGNOSTICS) { assert(steps==4095 && reads>=12000 && h==0x05ffffff); }
    else { assert(steps==0 && stop==0 && h==0 && reads==0); }
    /* Functional bridge still finds the packet even with diagnostics off. */
    assert(fm_chain_has_hand_shape(&cpu,0x80000004,&steps,&p));
    assert(steps==4095 && p==0x80000000+packet);
    assert(!memcmp(saved,ram,sizeof(ram)));
    return 0;
}
'''
        with tempfile.TemporaryDirectory() as temp:
            path=Path(temp)/'walk.c'; path.write_text(code)
            for enabled in (0,1):
                binary=Path(temp)/f'walk{enabled}'
                subprocess.run(['cc','-std=c11','-O2','-Wall','-Werror',
                    f'-DFM_OT_DIAGNOSTICS={enabled}',str(path),'-o',str(binary)],check=True)
                subprocess.run([str(binary)],check=True)
