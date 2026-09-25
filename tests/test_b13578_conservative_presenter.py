from pathlib import Path
import unittest


ROOT = Path(__file__).resolve().parents[1]
MAIN = (ROOT / "3ds/source/main.c").read_text(encoding="utf-8")


class B13578ConservativePresenterTests(unittest.TestCase):
    def test_real_gp1_change_is_authoritative(self) -> None:
        marker = "A real GP1(05) display change is authoritative"
        pos = MAIN.index(marker)
        block = MAIN[pos:pos + 1800]
        self.assertIn("latch_x = current_x;", block)
        self.assertIn("latch_y = current_y;", block)
        self.assertIn("b103_merge = 0;", block)
        self.assertNotIn("latch_x = b103_base_x;", block)

    def test_stale_vsync_uses_hash_change_arbitration(self) -> None:
        marker = "The draw page is a candidate backbuffer"
        pos = MAIN.index(marker)
        block = MAIN[pos:pos + 4200]
        self.assertIn("int current_changed =", block)
        self.assertIn("int draw_changed =", block)
        self.assertIn("!current_changed", block)
        self.assertIn("draw_changed", block)
        self.assertIn("draw_nz >= 32u", block)

    def test_black_or_static_draw_page_does_not_win_automatically(self) -> None:
        marker = "int follow_draw ="
        pos = MAIN.index(marker)
        block = MAIN[pos:pos + 1400]
        self.assertIn("if (follow_draw)", block)
        self.assertIn("else", block)
        self.assertIn("latch_x = current_x;", block)
        self.assertIn("latch_y = current_y;", block)

    def test_sampling_is_lightweight(self) -> None:
        marker = "static void b13578_sample_page"
        pos = MAIN.index(marker)
        block = MAIN[pos:pos + 1800]
        self.assertIn("py += 8u", block)
        self.assertIn("px += 8u", block)

    def test_debug_line_exposes_pick_and_occupancy(self) -> None:
        self.assertIn(
            "PRES g:%u,%u l:%u,%u d:%lu,%lu p:%lu nz:%lu/%lu",
            MAIN,
        )


if __name__ == "__main__":
    unittest.main()
