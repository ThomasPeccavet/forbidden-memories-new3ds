from pathlib import Path
import unittest


ROOT = Path(__file__).resolve().parents[1]
MAIN = (ROOT / "3ds/source/main.c").read_text(encoding="utf-8")


class B13577DrawPagePriorityTests(unittest.TestCase):
    def test_draw_environment_is_resolved_before_presenter_branches(self) -> None:
        env = MAIN.index("int b13577_draw_x1 = 0;")
        b104 = MAIN.index("B104 : GP1(08)", env)
        self.assertLess(env, b104)
        self.assertIn("fm_gpu_b100_env_get(", MAIN[env:b104])

    def test_canonical_draw_page_has_priority_over_display_changed(self) -> None:
        priority = MAIN.index("b13577_draw_page_valid")
        display_heuristic = MAIN.index("else if (display_changed)", priority)
        block = MAIN[priority:display_heuristic]
        self.assertIn("latch_x = b13577_draw_page_x;", block)
        self.assertIn("latch_y = b13577_draw_page_y;", block)
        self.assertIn("++g_b13577_drawpage_priority;", block)

    def test_priority_handles_gp1_change_and_vsync_refresh(self) -> None:
        marker = "B135.77: the guest's draw environment is a stronger signal"
        pos = MAIN.index(marker)
        pre = MAIN[pos - 900:pos]
        self.assertIn("display_changed", pre)
        self.assertIn("g_b1358_vsync_completed", pre)
        self.assertIn("b104_gp0 != g_b1357_last_latched_gp0", pre)

    def test_density_heuristic_is_fallback_only(self) -> None:
        priority = MAIN.index("++g_b13577_drawpage_priority;")
        heuristic = MAIN.index("B103 :", priority)
        self.assertGreater(heuristic, priority)

    def test_compact_presenter_line_exposes_priority_counter(self) -> None:
        self.assertIn(
            "PRES gp1:%u,%u latch:%u,%u draw:%lu,%lu pri:%lu",
            MAIN,
        )


if __name__ == "__main__":
    unittest.main()
