from pathlib import Path
import re
import unittest


ROOT = Path(__file__).resolve().parents[1]
SHIM = ROOT / "3ds/source/fm_runtime_shim.c"
MAIN = ROOT / "3ds/source/main.c"
HEADER = ROOT / "3ds/include/fm_runtime_shim.h"


def extract_function(text: str, name: str) -> str:
    match = re.search(rf"\b{name}\s*\([^;]*?\)\s*\{{", text, re.S)
    if not match:
        raise AssertionError(f"function not found: {name}")

    brace = text.find("{", match.start())
    depth = 0
    for index in range(brace, len(text)):
        if text[index] == "{":
            depth += 1
        elif text[index] == "}":
            depth -= 1
            if depth == 0:
                return text[match.start():index + 1]

    raise AssertionError(f"unterminated function: {name}")


class B13573CardLoadImageTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls) -> None:
        cls.shim = SHIM.read_text(encoding="utf-8")
        cls.main = MAIN.read_text(encoding="utf-8")
        cls.header = HEADER.read_text(encoding="utf-8")

    def test_both_resident_upload_wrappers_are_trapped(self) -> None:
        entry = extract_function(
            self.shim,
            "psx_check_interrupts_dispatch_entry",
        )
        self.assertIn("0x0007FF10u", entry)
        self.assertIn("0x00082380u", entry)
        self.assertIn("FM_STOP_LOADIMAGE_HLE", entry)
        self.assertIn("FM_STOP_LOADIMAGE_HLE", self.header)

    def test_nested_upload_uses_verified_gp0_hle(self) -> None:
        self.assertRegex(
            self.main,
            r"probe\.reason\s*==\s*FM_STOP_LOADIMAGE_HLE",
        )
        self.assertIn("fm_hle_gpu_load_image(cpu)", self.main)
        upload = extract_function(self.main, "fm_hle_gpu_load_image")
        self.assertIn("fm_gpu_gp0_write(0xA0000000u)", upload)

    def test_card_lookup_trace_is_read_only(self) -> None:
        lookup = extract_function(self.shim, "b13573_trace_card_lookup")
        self.assertNotIn("write_byte", lookup)
        self.assertNotIn("write_half", lookup)
        self.assertNotIn("write_word", lookup)
        self.assertIn("0x801A7E20u", lookup)
        self.assertIn("0x8018C2D8u", lookup)
        self.assertIn("0x580u", lookup)

    def test_b13571_safety_net_is_not_removed(self) -> None:
        entry = extract_function(
            self.shim,
            "psx_check_interrupts_dispatch_entry",
        )
        self.assertRegex(
            entry,
            r"cpu->write_byte\s*\(\s*0x8009C4B8u\s*,\s*1u\s*\)",
        )
        self.assertIn("SAFE B135.71", self.main)


if __name__ == "__main__":
    unittest.main()
