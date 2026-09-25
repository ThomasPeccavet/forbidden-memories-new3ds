#!/usr/bin/env python3
"""Fast static sanity checks for the New3DS bring-up main.c.

The checker is intentionally conservative and dependency-free. It catches the
class of mistakes that repeatedly cost manual Azahar iterations: duplicate
trace case values, duplicate static function definitions, missing build label,
and malformed/duplicated Bxx build markers.

Usage:
  python tools/validate_main_c.py 3ds/source/main.c
"""
from __future__ import annotations

import argparse
from collections import Counter
from pathlib import Path
import re
import sys


def extract_function(text: str, name: str) -> str:
    m = re.search(rf"\b{name}\s*\([^;]*?\)\s*\{{", text, re.S)
    if not m:
        raise ValueError(f"function not found: {name}")
    start = m.start()
    brace = text.find("{", m.start())
    depth = 0
    for i in range(brace, len(text)):
        c = text[i]
        if c == "{":
            depth += 1
        elif c == "}":
            depth -= 1
            if depth == 0:
                return text[start:i + 1]
    raise ValueError(f"unterminated function: {name}")


def duplicate_case_values(function_text: str) -> dict[str, int]:
    cases = re.findall(r"\bcase\s+(0x[0-9A-Fa-f]+u?)\s*:", function_text)
    counts = Counter(x.lower().rstrip("u") for x in cases)
    return {k: v for k, v in counts.items() if v > 1}


def duplicate_static_functions(text: str) -> dict[str, int]:
    names = re.findall(
        r"(?m)^static\s+(?:inline\s+)?[A-Za-z_][\w\s\*]*?\s+([A-Za-z_]\w*)\s*\(",
        text,
    )
    counts = Counter(names)
    return {k: v for k, v in counts.items() if v > 1}


def run_checks(path: Path) -> list[str]:
    text = path.read_text(encoding="utf-8")
    errors: list[str] = []

    try:
        trace = extract_function(text, "fm_trace_dispatch")
        duplicates = duplicate_case_values(trace)
        if duplicates:
            errors.append(f"duplicate case labels in fm_trace_dispatch: {duplicates}")
    except ValueError as exc:
        errors.append(str(exc))

    duplicate_funcs = duplicate_static_functions(text)
    if duplicate_funcs:
        errors.append(f"duplicate static function definitions: {duplicate_funcs}")

    build_markers = re.findall(r'printf\("BUILD\s+([^\\n"]+)', text)
    if not build_markers:
        errors.append("no visible BUILD marker found")
    elif len(set(build_markers)) != len(build_markers):
        errors.append("duplicate BUILD marker strings found")

    # The currently active build label should be a Bxx-family label.
    if build_markers and not any(re.match(r"B\d+", x) for x in build_markers):
        errors.append("no Bxx build marker found")

    # Catch actual Git conflict markers, not decorative comment rulers
    # such as " * ========" used throughout the bring-up source.
    conflict = re.search(
        r"(?m)^[ \\t]*(<<<<<<<|=======|>>>>>>>)",
        text,
    )
    if conflict:
        errors.append(
            f"merge-conflict marker present: {conflict.group(1)}"
        )

    return errors


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("main_c", type=Path, nargs="?", default=Path("3ds/source/main.c"))
    args = parser.parse_args()

    errors = run_checks(args.main_c)
    if errors:
        print(f"FAIL {args.main_c}")
        for err in errors:
            print(f"  - {err}")
        return 1

    print(f"PASS {args.main_c}")
    print("  fm_trace_dispatch duplicate cases: none")
    print("  duplicate static functions: none")
    print("  merge markers: none")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
