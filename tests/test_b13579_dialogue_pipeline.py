from pathlib import Path
import unittest


ROOT = Path(__file__).resolve().parents[1]
MAIN = (ROOT / "3ds/source/main.c").read_text(encoding="utf-8")


class B13579DialoguePipelineTests(unittest.TestCase):
    def test_missing_display_walkers_are_counted(self) -> None:
        for addr in (
            "case 0x000408BCu:",
            "case 0x00040F2Cu:",
            "case 0x0004110Cu:",
            "case 0x0004139Cu:",
        ):
            self.assertIn(addr, MAIN)

    def test_object_probe_runs_only_in_compact_debug_block(self) -> None:
        marker = "B135.79 - dialogue pipeline."
        pos = MAIN.index(marker)
        block = MAIN[pos:pos + 6500]
        self.assertIn("b13549_obj_list_probe(", block)
        self.assertIn("OBJ79 n:", block)

    def test_walker_delta_line_is_visible(self) -> None:
        self.assertIn(
            "WALK79 b48/8bc/f2c/10c/39c/048:",
            MAIN,
        )

    def test_gpu_2d_delta_line_is_visible(self) -> None:
        self.assertIn(
            "GP2D79 rect/q/2c/3a:",
            MAIN,
        )

    def test_presenter_logic_is_not_rewritten_by_b13579(self) -> None:
        self.assertIn(
            "A real GP1(05) display change is authoritative",
            MAIN,
        )
        self.assertIn(
            "The draw page is a candidate backbuffer",
            MAIN,
        )


if __name__ == "__main__":
    unittest.main()
