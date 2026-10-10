"""Production file writer: integrity, identity, failure and FAT recovery."""
from pathlib import Path
import subprocess
import tempfile
import unittest
ROOT = Path(__file__).resolve().parents[1]
class SnapshotIOTests(unittest.TestCase):
    def test_validation_rotation_and_failed_write_preserve_previous_save(self):
        code = r'''
#include "fm_snapshot.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
static void expect(const char *p, const char *s) {
    void *out=0; uint32_t n=0; int old=0;
    assert(fm_snapshot_read(p,&out,&n,7,123,&old)==0 && !old);
    assert(n==strlen(s)+1 && !strcmp(out,s)); free(out);
}
int main(void) {
    const char *p="state.bin";
    assert(fm_snapshot_crc("123456789",9)==0xCBF43926u);
    assert(!fm_snapshot_write(p,"first",6,7,123,13656)); expect(p,"first");
    assert(!fm_snapshot_write(p,"second",7,7,123,13656)); expect(p,"second");
    expect("state.bin.bak","first");
    void *out=0; uint32_t n=0; int old=0;
    assert(fm_snapshot_read(p,&out,&n,8,123,&old)==-4 && !out);
    assert(fm_snapshot_read(p,&out,&n,7,124,&old)==-4 && !out);
    assert(!mkdir("state.bin.tmp",0700));
    assert(fm_snapshot_write(p,"bad",4,7,123,13656)==-2); expect(p,"second");
    assert(!remove("state.bin.tmp"));
    FILE *f=fopen(p,"r+b"); assert(f); assert(!fseek(f,-1,SEEK_END));
    fputc(1,f); fclose(f);
    assert(fm_snapshot_read(p,&out,&n,7,123,&old)==-5 && !out);
    /* An absent primary after interrupted rotation recovers the old file. */
    assert(!remove(p)); expect(p,"first");
    f=fopen(p,"wb"); assert(f); fputs("short",f); fclose(f);
    assert(fm_snapshot_read(p,&out,&n,7,123,&old)==-3 && !out);
    return 0;
}
'''
        with tempfile.TemporaryDirectory() as temp:
            c=Path(temp)/"test.c"; c.write_text(code); exe=Path(temp)/"test"
            subprocess.run(["cc","-std=c11","-Wall","-Wextra","-Werror",
                "-I",str(ROOT/"3ds/include"),str(c),str(ROOT/"3ds/source/fm_snapshot.c"),"-o",str(exe)],check=True,capture_output=True)
            result=subprocess.run([str(exe)],cwd=temp,capture_output=True,text=True)
            self.assertEqual(result.returncode,0,result.stderr)
