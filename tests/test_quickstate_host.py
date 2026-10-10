"""Execute production quick-save/load with real memory/media/MDEC backends."""
from pathlib import Path
import re
import subprocess
import tempfile
import unittest
ROOT = Path(__file__).resolve().parents[1]
class QuickStateTests(unittest.TestCase):
    def test_transactional_load_streaming_and_legacy_import(self):
        source=(ROOT/"3ds/source/main.c").read_text()
        start=source.index("#define FM_B135_QS_MAGIC")
        end=source.index("/*\n * ============================================================\n * B135.49",start)
        code=source[start:end]
        defined=set(re.findall(r"^static [^;\n]*\b(g_\w+)[^;]*;",code,re.M))
        declarations=[]
        for name in sorted(set(re.findall(r"\bg_\w+\b",code))-defined):
            match=re.search(r"^static [^;\n]*\b"+name+r"\b[^;]*;",source,re.M)
            self.assertIsNotNone(match,name)
            if match.group() not in declarations: declarations.append(match.group())
        fixture=str(ROOT/"tests/host/test_media.c")
        harness=r'''
#include "fm_snapshot.h"
#include "fm_spu.h"
#include "fm_gpu.h"
#include "fm_runtime_shim.h"
#include "fm_host_clock.h"
#include "fm_mdec_clock.h"
#define main media_fixture_main
#include "FIXTURE"
#undef main
static FMGpuQuickState gpu_state;
static FMRuntimeQuickState runtime_state;
void fm_runtime_frame_wait_scope(CPUState *cpu) { (void)cpu; }
void fm_gpu_quick_save(FMGpuQuickState *out) { *out=gpu_state; }
void fm_gpu_quick_load(const FMGpuQuickState *in) { gpu_state=*in; }
void fm_runtime_quick_save(FMRuntimeQuickState *out) { *out=runtime_state; }
void fm_runtime_quick_load(const FMRuntimeQuickState *in) { runtime_state=*in; }
static unsigned reset_calls;
static void fm_cd_hle_reset(void);
''' .replace('FIXTURE',fixture)
        harness+='\n'.join(declarations)+'\n'+code+r'''
static void fm_cd_hle_reset(void) {
    ++reset_calls; fm_media_reset(); g_cd_lba=0; g_b33_pending=0; g_b34_ready_pending=0;
    g_media_irq_active=g_b33_cb_active=g_b34_ready_active=g_b35_finalizer_active=g_cd_tick_active=0;
}
int main(void) {
    assert(!system("mkdir -p sdmc:/3ds/fm-new3ds"));
    fm_memory_init(ram,sizeof(ram)); mdec_init(); fm_media_reset();
    CPUState cpu={0}; cpu.pc=0x80081AEC; cpu.cop0[12]=0x401;
    cpu.gpr[28]=0x8009C298; cpu.gte_data[5]=234; cpu.read_absorb_which=cpu.ld_which_t=32;
    static uint16_t vram[1024*512]; vram[123]=0x4567; ram[456]=0xAB;
    g_snapshot_disc=123; g_cd_lba=9876; g_cd_streaming=1;
    g_b33_pending=1; g_b33_pending_callback=0x8007CA78; g_b33_pending_frame=44;
    g_vblank_registered_cb=0x80012BD8; g_vblank_registered_gp=0x8009C298;
    g_fast401_forced=g_fast43e_forced=1;
    g_vsync_wait_active=1; g_vsync_wait_until_frame=44;
    g_media_irq_active=1; assert(fm_b135_quick_save(&cpu,ram,vram,43,123)==1);
    g_media_irq_active=0; assert(!fm_b135_quick_save(&cpu,ram,vram,43,123));
    CPUState saved=cpu;
    cpu.pc=0x80010000; cpu.gte_data[5]=0; ram[456]=0; vram[123]=0;
    g_cd_lba=11; g_cd_streaming=0; g_b33_pending=0;
    unsigned frame=0; uint32_t dispatch=0;
    assert(!fm_b135_quick_load(&cpu,ram,vram,&frame,&dispatch));
    assert(!memcmp(&cpu,&saved,sizeof(cpu)) && ram[456]==0xAB && vram[123]==0x4567);
    assert(frame==43 && dispatch==123 && g_cd_lba==9876 && g_cd_streaming && g_b33_pending);
    assert(g_vsync_wait_active && g_vsync_wait_until_frame==44);
    /* Corruption whose outer CRC is valid still must not mutate any subsystem. */
    void *blob; uint32_t bytes; int legacy;
    assert(!fm_snapshot_read(FM_B135_QS_PATH,&blob,&bytes,fm_snapshot_schema(),123,&legacy));
    unsigned fixed=sizeof(FMB135QuickStateHeader)+sizeof(ram)+sizeof(vram);
    FMQuickExtension *ext=(FMQuickExtension *)((uint8_t *)blob+fixed);
    /* B136.56 v4 files have no SPU tail; preserve their import path. */
    unsigned old_bytes=bytes-fm_spu_snapshot_bytes();
    assert(!fm_snapshot_write(FM_B135_QS_PATH,blob,old_bytes,fm_snapshot_schema(),123,13656));
    assert(!fm_b135_quick_load(&cpu,ram,vram,&frame,&dispatch));
    /* A malformed SPU tail is rejected before CD/CPU/RAM are committed. */
    uint8_t *spu=(uint8_t *)blob+old_bytes;spu[0]^=1;
    assert(!fm_snapshot_write(FM_B135_QS_PATH,blob,bytes,fm_snapshot_schema(),123,13657));
    unsigned before=reset_calls;
    assert(fm_b135_quick_load(&cpu,ram,vram,&frame,&dispatch)==-8 && reset_calls==before);
    spu[0]^=1;
    uint8_t *decoder=(uint8_t *)blob+fixed+sizeof(*ext); decoder[62]=255;
    assert(!fm_snapshot_write(FM_B135_QS_PATH,blob,bytes,fm_snapshot_schema(),123,13656));
    unsigned previous=reset_calls; g_cd_lba=222;
    assert(fm_b135_quick_load(&cpu,ram,vram,&frame,&dispatch)==-8);
    assert(reset_calls==previous && g_cd_lba==222 && ram[456]==0xAB);
    assert(!memcmp(&cpu,&saved,sizeof(cpu)));
    /* A legacy idle-duel state remains importable; a loading v3 is rejected. */
    FMB135QuickStateHeader *h=blob; h->version=3;
    uint8_t *saved_ram=(uint8_t *)blob+sizeof(*h); saved_ram[0x9C3EB]=1;
    memset(saved_ram+0xEB1C8,0,4);
    FILE *f=fopen(FM_B135_QS_PATH,"wb"); assert(f); assert(fwrite(blob,fixed,1,f)==1); fclose(f);
    assert(!fm_b135_quick_load(&cpu,ram,vram,&frame,&dispatch));
    assert(g_fast401_forced && g_fast43e_forced && g_vblank_registered_cb==0x80012BD8);
    saved_ram[0xEB1C8]=1;
    f=fopen(FM_B135_QS_PATH,"wb"); assert(f); assert(fwrite(blob,fixed,1,f)==1); fclose(f);
    previous=reset_calls;
    assert(fm_b135_quick_load(&cpu,ram,vram,&frame,&dispatch)==-7 && reset_calls==previous);
    free(blob); return 0;
}
'''
        with tempfile.TemporaryDirectory() as temp:
            c=Path(temp)/"test.c"; c.write_text(harness); exe=Path(temp)/"test"
            sources=["fm_memory","fm_spu","fm_mdec","fm_media","fm_vlc","fm_xa","fm_audio","disc","fm_snapshot"]
            cmd=["cc","-std=gnu11","-O2","-Wall","-Werror=implicit-function-declaration","-DPSX_NO_DEBUG_TOOLS",
                "-I",str(ROOT/"tests/host/include"),"-I",str(ROOT/"3ds/include"),str(c)]
            cmd+=[str(ROOT/f"3ds/source/{s}.c") for s in sources]+["-o",str(exe)]
            result=subprocess.run(cmd,capture_output=True,text=True)
            self.assertEqual(result.returncode,0,result.stderr)
            result=subprocess.run([str(exe)],cwd=temp,capture_output=True,text=True)
            self.assertEqual(result.returncode,0,result.stderr)
