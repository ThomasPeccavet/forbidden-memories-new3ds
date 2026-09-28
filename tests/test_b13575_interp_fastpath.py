from pathlib import Path
import re
import unittest


ROOT = Path(__file__).resolve().parents[1]
INTERP = (ROOT / "3ds/source/fm_interp.c").read_text(encoding="utf-8")
MAIN = (ROOT / "3ds/source/main.c").read_text(encoding="utf-8")
SHIM = (ROOT / "3ds/source/fm_runtime_shim.c").read_text(encoding="utf-8")


class B13575InterpFastpathTests(unittest.TestCase):
    def test_region_chunk_ceiling_is_preserved(self) -> None:
        self.assertIn("b13519_chunks < 32u", MAIN)
        self.assertRegex(
            MAIN,
            r"fm_interp_run_region\s*\(\s*cpu,\s*2048u,",
        )
        self.assertEqual(32 * 2048, 65536)

    def test_ram_half_and_word_paths_use_fixed_size_copy(self) -> None:
        self.assertIn(
            "memcpy(&value, g_interp_ram + o, sizeof(value));",
            INTERP,
        )
        self.assertIn(
            "memcpy(g_interp_ram + o, &value, sizeof(value));",
            INTERP,
        )

    def test_set_reg_no_longer_duplicates_zero_write(self) -> None:
        m = re.search(
            r"static inline void set_reg\s*\([^)]*\)\s*\{(.*?)\n\}",
            INTERP,
            re.S,
        )
        self.assertIsNotNone(m)
        self.assertNotIn("cpu->gpr[0]", m.group(1))

    def test_main_loop_still_restores_zero_register(self) -> None:
        self.assertIn(
            "cpu->gpr[0] =\n            0;",
            INTERP,
        )

    def test_b13571_gate_safety_net_is_still_present(self) -> None:
        self.assertIn("g_b13571_forced", SHIM)
        self.assertIn("0x8009C4B8u", SHIM)
        self.assertIn("cpu->write_byte(", SHIM)


if __name__ == "__main__":
    unittest.main()
