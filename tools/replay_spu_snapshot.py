#!/usr/bin/env python3
"""Replay native sound paths with production MIPS/MMIO and a private quickstate."""
from pathlib import Path
import argparse
import os
import shlex
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parents[1]


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("snapshot", type=Path)
    parser.add_argument("mode", choices=("menu", "sequence", "timed-sequence"))
    args = parser.parse_args()
    with tempfile.TemporaryDirectory() as temp:
        binary = Path(temp) / "replay-spu"
        subprocess.run(shlex.split(os.environ.get("CC", "cc")) + [
            "-std=gnu11", "-O2", "-DFM_PERF_PROFILE=0", "-DPSX_NO_DEBUG_TOOLS",
            "-I", str(ROOT / "tests/host/include"), "-I", str(ROOT / "3ds/include"),
            str(ROOT / "3ds/source/fm_memory.c"), str(ROOT / "3ds/source/fm_mdec.c"),
            str(ROOT / "3ds/source/fm_interp.c"),
            str(ROOT / "tests/host/replay_spu_snapshot.c"), "-o", str(binary),
        ], check=True)
        return subprocess.run([str(binary), str(args.snapshot.resolve()), args.mode],
                              timeout=30).returncode


if __name__ == "__main__":
    raise SystemExit(main())
