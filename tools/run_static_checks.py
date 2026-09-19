#!/usr/bin/env python3
"""Run the lightweight CI checks locally with one command."""
from __future__ import annotations

from pathlib import Path
import compileall
import subprocess
import sys


ROOT = Path(__file__).resolve().parents[1]


def run(cmd: list[str]) -> None:
    print("+", " ".join(cmd))
    subprocess.run(cmd, cwd=ROOT, check=True)


def main() -> int:
    ok = compileall.compile_dir(ROOT / "tools", quiet=1)
    ok = compileall.compile_dir(ROOT / "tests", quiet=1) and ok
    if not ok:
        return 1

    run([sys.executable, "tools/validate_main_c.py", "3ds/source/main.c"])
    run([sys.executable, "-m", "unittest", "discover", "-s", "tests", "-v"])
    print("All static checks passed.")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
