"""Sparse thumbnail selection must consume skipped physical CD sectors."""
from pathlib import Path
import re
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]

class CdSectorCursorTests(unittest.TestCase):
    def test_sparse_cards_and_request_restart(self):
        source = (ROOT / "3ds/source/main.c").read_text()
        start = source.index("static uint32_t fm_cd_begin_dataready_sector(")
        end = source.index("\n}\n", start) + 3
        production = source[start:end]
        declarations = []
        for name in sorted(set(re.findall(r"\bg_[a-zA-Z0-9_]+\b", production))):
            declarations.append(re.search(r"^static [^;\n]*\b" + name + r"\b[^;]*;", source, re.M).group())
        code = "#include <stdint.h>\n#include <assert.h>\n" + "\n".join(declarations) + production + r"""
int main(void) {
    /* Unique card IDs from the supplied duel RAM. A card occupies one
     * sector; the guest copies only selected cards into compact slots. */
    const unsigned cards[] = {9,24,56,58,105,122,123,167,179,192,197,198,
        202,214,222,227,237,242,282,289,292,298,316,335,336,338,344,387,
        393,394,395,397,398,399,402,411,436,444,451,486,492,501,504,548,
        558,570,585,589,591,606};
    unsigned selected = 0, copied[50] = {0};
    unsigned base = 1000 + cards[0] - 1;
    for (unsigned id = cards[0]; id <= cards[49]; ++id) {
        unsigned remaining = (cards[49] - id + 1) * 2048;
        unsigned lba = fm_cd_begin_dataready_sector(0x800EB1B8, base, remaining);
        assert(lba == 1000 + id - 1);
        assert(g_cd_lba == lba + 1);
        if (selected < 50 && id == cards[selected]) {
            /* CdGetSector sees this physical sector, not the count of
             * previous DMA copies. The other events do no transfer. */
            copied[selected++] = lba - 1000 + 1;
        }
    }
    assert(selected == 50 && g_b57_resets == 1);
    for (unsigned i = 0; i < 50; ++i) assert(copied[i] == cards[i]);
    assert(copied[35] == 411 && copied[18] == 282 && copied[12] == 202);
    assert(copied[24] == 336 && copied[11] == 198);
    /* Reusing the same request, even with the same base and length. */
    assert(fm_cd_begin_dataready_sector(0x800EB1B8, base, 598 * 2048) == base);
    assert(g_b57_resets == 2);
    /* Ordinary consecutive reads and final partial sector. */
    assert(fm_cd_begin_dataready_sector(0x800EB1B8, 42, 4100) == 42);
    assert(fm_cd_begin_dataready_sector(0x800EB1B8, 42, 2052) == 43);
    assert(fm_cd_begin_dataready_sector(0x800EB1B8, 42, 4) == 44);
    assert(fm_cd_begin_dataready_sector(0x800EB1B8, 42, 4) == 42);
    assert(fm_cd_begin_dataready_sector(0x80123400, 42, 2) == 42);
    return 0;
}
"""
        with tempfile.TemporaryDirectory() as tmp:
            path = Path(tmp) / "cursor.c"
            path.write_text(code)
            exe = Path(tmp) / "cursor"
            subprocess.run(["cc", "-std=c11", "-O2", "-Wall", "-Werror", str(path), "-o", str(exe)], check=True)
            subprocess.run([str(exe)], check=True)
        delivery = source[source.index("* B34 : livraison"):source.index("if (g_direct2df_active)", source.index("* B34 : livraison"))]
        self.assertIn("g_b34_ready_lba = fm_cd_begin_dataready_sector(", delivery)
        dma = source[source.index("if (phys == 0x0007E968u)"):source.index("* B25 - GPU LoadImage HLE")]
        self.assertIn("? g_b34_ready_lba : g_b57_next_lba", dma)
        self.assertRegex(dma, r"if \(!dataready_sector\)\s*\{\s*\+\+g_b57_next_lba;")
