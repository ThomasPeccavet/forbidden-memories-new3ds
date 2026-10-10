"""Inline generated CPU RAM callbacks in build copies, leaving originals intact."""
from pathlib import Path
import argparse
import re

# Mask comments/literals without moving offsets. Never rewrite text in them.
NON_CODE = re.compile(r'//(?:\\\r?\n|[^\n])*|/\*[\s\S]*?\*/|"(?:\\[\s\S]|[^"\\])*"|\'(?:\\[\s\S]|[^\'\\])*\'')
CYCLE_CALL = re.compile(r"\bpsx_cyc_load_(word|half|byte)(?=\s*\(\s*cpu\s*,)")
GTE_CALL = re.compile(r"\b(gte_(?:read|write)_(?:data|ctrl))(?=\s*\(\s*cpu\s*,)")
CALL = re.compile(r'\bcpu\s*->\s*((?:read|write)_(?:word|half|byte))\s*\(')


def transform(source: str) -> tuple[str, int]:
    masked = NON_CODE.sub(lambda m: ''.join('\n' if c == '\n' else ' ' for c in m[0]), source)
    replacements = [(m.start(), m.end(), f'fm_native_{m[1]}(cpu, ') for m in CALL.finditer(masked)]
    replacements += [(m.start(), m.end(), f'fm_native_cyc_load_{m[1]}') for m in CYCLE_CALL.finditer(masked)]
    replacements += [(m.start(), m.end(), f'fm_native_{m[1]}') for m in GTE_CALL.finditer(masked)]
    parts, cursor = [], 0
    for start, end, replacement in sorted(replacements):
        parts.extend((source[cursor:start], replacement))
        cursor = end
    parts.append(source[cursor:])
    source = ''.join(parts)
    if replacements:
        # Resolve CPUState through the same runtime include path as the build.
        source = '#include "psx_runtime.h"\n#include "fm_native_memory.h"\n#include "fm_native_gte.h"\n' + source
    return source, len(replacements)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('source', type=Path)
    parser.add_argument('output', type=Path)
    args = parser.parse_args()
    if args.source.resolve() == args.output.resolve():
        parser.error('output must differ from original generated sources')
    args.output.mkdir(parents=True, exist_ok=True)
    count = 0
    files = sorted(args.source.glob('SLES_039.48_*.c'))
    for path in files:
        source, changed = transform(path.read_text(encoding='utf-8-sig'))
        (args.output / path.name).write_text(source, encoding='utf-8')
        count += changed
    if not files or not count:
        raise SystemExit('ERROR: no generated CPU memory calls transformed; refusing silent no-op')
    print(f'B136.62: {count} native memory/GTE call sites specialized in {len(files)} build copies')


if __name__ == '__main__':
    main()
