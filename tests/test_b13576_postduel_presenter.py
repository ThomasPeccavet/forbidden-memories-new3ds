from pathlib import Path
import re
import unittest


ROOT = Path(__file__).resolve().parents[1]
MAIN = (ROOT / "3ds/source/main.c").read_text(encoding="utf-8")


class B13576PostDuelPresenterTests(unittest.TestCase):
    def _draw_page_resolution_block(self) -> str:
        marker = "int b13577_draw_x1 = 0;"
        start = MAIN.index(marker)
        end = MAIN.index("B104 : GP1(08)", start)
        return MAIN[start:end]

    def test_stale_gp1_path_reads_real_draw_environment(self) -> None:
        block = self._draw_page_resolution_block()
        self.assertIn("fm_gpu_b100_env_get(", block)
        self.assertNotIn("fm_gpu_b127_perf_snapshot(", block)

    def test_stale_gp1_path_tracks_both_x_and_y_pages(self) -> None:
        block = self._draw_page_resolution_block()
        self.assertIn("unsigned b13577_draw_page_x = current_x;", block)
        self.assertIn("unsigned b13577_draw_page_y = current_y;", block)
        self.assertIn("b13577_draw_y1 >= 256", block)
        self.assertIn("b13577_draw_page_y = 256u;", block)
        self.assertIn("b13577_draw_page_valid_y = 1;", block)

    def test_density_sampling_uses_current_display_y(self) -> None:
        self.assertIn("unsigned sample_y = current_y;", MAIN)
        self.assertIn("unsigned sy = (sample_y + py) & 511u;", MAIN)

    def test_fallback_no_longer_forces_y_zero(self) -> None:
        marker = "B135.76: preserve the current GP1 Y page"
        pos = MAIN.index(marker)
        snippet = MAIN[pos:pos + 500]
        self.assertIn("latch_y = current_y;", snippet)
        self.assertNotIn("latch_y = 0u;", snippet)

    def test_compact_presenter_diagnostic_is_visible(self) -> None:
        self.assertIn(
            "PRES gp1:%u,%u latch:%u,%u draw:%lu,%lu",
            MAIN,
        )


if __name__ == "__main__":
    unittest.main()
