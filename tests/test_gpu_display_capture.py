#!/usr/bin/env python3
"""Compile the real GPU bridge on the host and test B132 display latching.
Usage: python tests/test_gpu_display_capture.py /path/to/psxrecomp
No game assets or devkitARM are required.
"""
from pathlib import Path
import subprocess
import sys
import tempfile

root = Path(__file__).resolve().parents[1]
runtime = Path(sys.argv[1]).resolve() / 'runtime'
source = r'''
#include <assert.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "fm_gpu.h"
#include "gpu_sw_renderer.h"
/* Disable PC-only widescreen support, as in native 3DS mode. */
int g_ws_bd_stretch_on = 0, g_ws_bd_stretch_pct = 0;
int psx_ws_prim_in_backdrop(void) { return 0; }
static uint16_t vram[1024*512], frame[320*256];
static void select_page(unsigned x, unsigned y) {
    fm_gpu_gp1_write(0x05000000u | x | (y << 10));
}
int main(void) {
    sw_renderer_init(vram);
    fm_gpu_init(vram);
    fm_gpu_set_display_capture(frame);
    vram[0] = 0x001f; vram[320] = 0x03e0;
    select_page(0, 0);
    uint32_t first = fm_gpu_display_capture_serial();
    assert(frame[0] == 0x001f);
    /* Rendering/clearing after a flip must not alter the captured image. */
    memset(vram, 0, 320 * sizeof(uint16_t));
    assert(frame[0] == 0x001f);
    select_page(320, 0);
    assert(frame[0] == 0x03e0);
    /* A black front page is authoritative, even when the other is dense. */
    select_page(0, 0);
    assert(frame[0] == 0);
    assert(fm_gpu_display_capture_serial() == first + 2);
    /* Same coordinates can still contain a new frame. */
    vram[0] = 0x7c00;
    select_page(0, 0);
    assert(frame[0] == 0x7c00);
    assert(fm_gpu_display_capture_serial() == first + 3);
    /* X/Y wrap stays inside VRAM. */
    vram[511*1024+1023] = 0x1234;
    vram[511*1024] = 0x2345;
    vram[1023] = 0x3456;
    select_page(1023, 511);
    assert(frame[0] == 0x1234 && frame[1] == 0x2345);
    assert(frame[320] == 0x3456);
    /* Packed RGB888 video remains supported, including row wrap. */
    uint8_t *bytes = (uint8_t *)vram;
    bytes[2046] = 248; bytes[2047] = 128; bytes[0] = 64;
    fm_gpu_gp1_write(0x08000010u);
    select_page(1023, 0);
    assert(frame[0] == (31 | (16 << 5) | (8 << 10)));
    /* Reset detaches caller memory; rebind is explicit. */
    frame[0] = 0x7777;
    fm_gpu_init(vram);
    select_page(0, 0);
    assert(frame[0] == 0x7777);
    fm_gpu_set_display_capture(frame);
    select_page(0, 0);
    assert(frame[0] == vram[0]);
    puts("PASS: flip isolation, opaque black, repeated flips, VRAM wrap, RGB24, reset");
    return 0;
}
'''
with tempfile.TemporaryDirectory() as temp:
    tmp = Path(temp)
    # The current bridge includes 3ds.h but uses no libctru symbols.
    (tmp / '3ds.h').write_text('/* Host GPU regression test: only timer conversion needs libctru. */\n#define SYSCLOCK_ARM11 268123480u\n')
    (tmp / 'test.c').write_text(source)
    command = ['cc', '-std=gnu11', '-O2', '-g', '-fsanitize=address,undefined',
               '-I' + str(tmp), '-I' + str(root / '3ds/include'),
               '-I' + str(runtime / 'include'), str(tmp / 'test.c'),
               str(root / '3ds/source/fm_gpu.c'),
               str(runtime / 'src/gpu_sw_renderer.c'),
               str(runtime / 'src/gpu_vram_dirty.c'), '-lm', '-o', str(tmp / 'test')]
    subprocess.run(command, check=True)
    subprocess.run([str(tmp / 'test')], check=True)
