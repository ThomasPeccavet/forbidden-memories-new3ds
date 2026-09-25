from pathlib import Path
import unittest


ROOT = Path(__file__).resolve().parents[1]
MAIN = (ROOT / "3ds/source/main.c").read_text(encoding="utf-8")


class B13580C2IndirectTests(unittest.TestCase):
    def test_c2_slot_is_exact_table_index_one(self) -> None:
        self.assertIn("cpu->read_word(0x800923E0u)", MAIN)
        self.assertIn("exp:800408BC", MAIN)

    def test_c2_head_is_read_from_exact_list_head(self) -> None:
        self.assertIn("cpu->read_half(0x800F11C2u)", MAIN)

    def test_408bc_compiled_entry_status_is_reported(self) -> None:
        self.assertIn(
            "psx_game_is_function_entry(0x800408BCu)",
            MAIN,
        )

    def test_41674_render_orchestrator_is_counted(self) -> None:
        self.assertIn("case 0x00041674u:", MAIN)
        self.assertIn("++g_b13580_hit_41674;", MAIN)
        self.assertIn("r416:%lu", MAIN)

    def test_b13580_does_not_mutate_function_table(self) -> None:
        marker = "B135.80 - inspect the exact function-pointer slot"
        pos = MAIN.index(marker)
        block = MAIN[pos:pos + 2200]
        self.assertNotIn("write_word(0x800923E0", block)
        self.assertNotIn("fm_memory_write_word(0x800923E0", block)


if __name__ == "__main__":
    unittest.main()
