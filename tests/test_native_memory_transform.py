"""Build-copy rewriting must not change non-code or callback assignments."""
import tempfile
import subprocess
import sys
from pathlib import Path
import unittest
from tools.inline_native_memory import transform

ROOT = Path(__file__).resolve().parents[1]


class NativeMemoryTransformTests(unittest.TestCase):
    def test_code_only_and_all_widths(self):
        untouched = '''// cpu->read_word(0)
/* cpu->write_byte(0, 1) */
const char *s = "cpu->read_half(0)";
cpu->read_word = custom;
void *p = cpu->write_word;
'''
        source = untouched + '''cpu -> read_word (f(g(1)));
cpu->write_word(a, cpu->read_half(b));
cpu->write_half(a, 3); cpu->read_byte(a); cpu->write_byte(a, 4);
'''
        result, count = transform(source)
        self.assertEqual(count, 6)
        self.assertIn(untouched, result)
        self.assertIn('fm_native_read_word(cpu, f(g(1)))', result)
        self.assertIn('fm_native_write_word(cpu, a, fm_native_read_half(cpu, b))', result)
        self.assertEqual(transform(result)[1], 0)

    def test_cycle_helpers_keep_arguments(self):
        source = 'psx_cyc_load_word(cpu,f(a),31,0x20); psx_cyc_load_half(cpu,a,2,3); psx_cyc_load_byte(cpu,a,2,3);'
        result, count = transform(source)
        self.assertEqual(count,3)
        self.assertIn('fm_native_cyc_load_word(cpu,f(a),31,0x20)', result)
        self.assertEqual(transform(result)[1],0)

    def test_gte_calls_only_not_declarations_or_text(self):
        source = '// gte_read_data(cpu, 1)\nuint32_t gte_read_data(CPUState *, uint8_t);\n'
        source += 'gte_read_data(cpu, 15); gte_read_ctrl(cpu, 26); gte_write_data(cpu, 30, f()); gte_write_ctrl(cpu, 31, 1);'
        result, count = transform(source)
        self.assertEqual(count, 4)
        self.assertIn('uint32_t gte_read_data(CPUState *, uint8_t);', result)
        self.assertIn('fm_native_gte_write_data(cpu, 30, f())', result)
        self.assertEqual(transform(result)[1], 0)

    def test_build_copies_originals_unchanged(self):
        with tempfile.TemporaryDirectory() as temp:
            source, out = Path(temp)/'original', Path(temp)/'copies'
            source.mkdir()
            text = 'void f(CPUState *cpu) { cpu->write_word(1,2); }'
            original = source/'SLES_039.48_full_00.c'
            original.write_text(text)
            subprocess.run([sys.executable, str(ROOT/'tools/inline_native_memory.py'), str(source), str(out)], check=True, capture_output=True)
            self.assertEqual(original.read_text(), text)
            self.assertIn('fm_native_write_word(cpu, 1,2)', (out/original.name).read_text())

    def test_no_matching_calls_fails_explicitly(self):
        with tempfile.TemporaryDirectory() as temp:
            source=Path(temp)/'original'; source.mkdir()
            (source/'SLES_039.48_full_00.c').write_text('// cpu->read_word(0)')
            result=subprocess.run([sys.executable, str(ROOT/'tools/inline_native_memory.py'), str(source), str(Path(temp)/'copies')], capture_output=True, text=True)
            self.assertNotEqual(result.returncode, 0)
            self.assertIn('refusing silent no-op', result.stderr)
