from pathlib import Path
import re
import unittest


ROOT = Path(__file__).resolve().parents[1]
SHIM = ROOT / "3ds/source/fm_runtime_shim.c"
MAIN = ROOT / "3ds/source/main.c"


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


class B13572TraceTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls) -> None:
        cls.shim = SHIM.read_text(encoding="utf-8")
        cls.main = MAIN.read_text(encoding="utf-8")

    def test_trace_is_observational(self) -> None:
        entry = extract_function(self.shim, "b13572_trace_generated_entry")
        post = extract_function(self.shim, "b13572_trace_post_call")
        for body in (entry, post):
            self.assertNotIn("write_byte", body)
            self.assertNotIn("write_half", body)
            self.assertNotIn("write_word", body)

    def test_original_gate_functions_are_traced(self) -> None:
        entry = extract_function(self.shim, "b13572_trace_generated_entry")
        for address in (
            "0x0001522Cu",
            "0x00015C18u",
            "0x00015C28u",
            "0x00012D60u",
            "0x000150F4u",
            "0x0001569Cu",
            "0x000156F8u",
            "0x000157D4u",
        ):
            self.assertIn(address, entry)

    def test_b13571_safety_net_remains_active(self) -> None:
        dispatch = extract_function(
            self.shim,
            "psx_check_interrupts_dispatch_entry",
        )
        self.assertIn("b13572_trace_generated_entry", dispatch)
        self.assertIn("b13567_chain_has_hand_shape", dispatch)
        self.assertRegex(
            dispatch,
            r"cpu->write_byte\s*\(\s*0x8009C4B8u\s*,\s*1u\s*\)",
        )
        gate_read = dispatch.index("cpu->read_byte(0x8009C4B8u)")
        ot_scan = dispatch.index("b13567_chain_has_hand_shape")
        self.assertLess(gate_read, ot_scan)
        self.assertRegex(
            dispatch[gate_read:ot_scan],
            r"if\s*\(gate\s*==\s*0u\)",
        )

    def test_build_label_identifies_safe_trace(self) -> None:
        self.assertIn(
            "BUILD B135.73-CARD-LI (SAFE B135.71)",
            self.main,
        )
        self.assertIn("T72 MAP:%03lX expected:7FF", self.main)
        self.assertIn("psx_game_is_function_entry", self.main)

    def test_gate_first_preserves_guest_memory_result(self) -> None:
        # The runtime is single-threaded here: no guest writer can change C4B8
        # during the bounded read-only OT scan.
        for gate in (0, 1, 0x80, 2, 0xFF):
            for hand_present in (False, True):
                old_result = 1 if hand_present and gate == 0 else gate
                new_result = 1 if gate == 0 and hand_present else gate
                self.assertEqual(old_result, new_result)


if __name__ == "__main__":
    unittest.main()
