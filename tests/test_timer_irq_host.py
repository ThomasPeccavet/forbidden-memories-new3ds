"""Root-counter BIOS delivery: masks, event modes, and IRQ acknowledgement."""
from pathlib import Path
import subprocess
import tempfile
import unittest
ROOT = Path(__file__).resolve().parents[1]
class TimerIrqTests(unittest.TestCase):
    def test_enabled_timer_event_only_and_preserves_other_irqs(self):
        source = (ROOT / "3ds/source/fm_runtime_shim.c").read_text()
        start = source.index("int fm_runtime_take_timer_callback(")
        end = source.index("/* B136.5 -", start)
        code = r"""
#include <assert.h>
#include <stdint.h>
#define FM_BIOS_EVENT_COUNT 4
typedef struct { uint32_t used,enabled,ready,class_id,spec,mode,func; } FM_BiosEvent;
static FM_BiosEvent g_bios_events[4];
static uint16_t stat, mask;
static uint16_t fm_memory_i_stat(void) { return stat; }
static uint16_t fm_memory_i_mask(void) { return mask; }
static void fm_memory_write_half(uint32_t address, uint16_t value) {
    assert(address == 0x1F801070u); stat &= value;
}
""" + source[start:end] + r"""
int main(void) {
    uint32_t cb = 0;
    g_bios_events[0] = (FM_BiosEvent){1,1,0,0xF2000002,2,0x1000,0x8004BBC4};
    stat = 0x49; mask = 0x09;
    assert(!fm_runtime_take_timer_callback(&cb) && stat == 0x49);
    mask = 0x49; g_bios_events[0].enabled = 0;
    assert(!fm_runtime_take_timer_callback(&cb) && stat == 0x49);
    g_bios_events[0].enabled = 1; g_bios_events[0].mode = 0x2000;
    assert(!fm_runtime_take_timer_callback(&cb) && stat == 0x49);
    g_bios_events[0].mode = 0x1000;
    assert(fm_runtime_take_timer_callback(&cb) && cb == 0x8004BBC4 && stat == 9);
    assert(!fm_runtime_take_timer_callback(&cb));
    return 0;
}
"""
        with tempfile.TemporaryDirectory() as tmp:
            c = Path(tmp)/"timer.c"; exe = Path(tmp)/"timer"; c.write_text(code)
            result = subprocess.run(["cc","-std=c11","-Wall","-Werror",str(c),"-o",str(exe)],capture_output=True,text=True)
            self.assertEqual(result.returncode,0,result.stderr)
            self.assertEqual(subprocess.run([str(exe)]).returncode,0)
