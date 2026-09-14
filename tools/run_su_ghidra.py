#!/usr/bin/env python3
"""Analyse both SU candidates with resident French code; Python 3.11+."""
import argparse
import datetime
import hashlib
import json
import os
from pathlib import Path
import subprocess
import uuid

ROOT = Path(__file__).resolve().parents[1]
EXPECTED = {
    0: "50cb0bc724960a22d586fc38fc6d49cfcf4884a341cff463edbb9850bada5a40",
    1: "afc3703f8a57196d54b6a15bd4a96679aef83ad7382c892d94fac11e809410f0",
}

def digest(path):
    with path.open("rb") as f:
        return hashlib.file_digest(f, "sha256").hexdigest()

def main():
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument("--ghidra", required=True, type=Path)
    p.add_argument("--probe-dir", required=True, type=Path)
    p.add_argument("--payload", type=Path, default=ROOT / "work/extracted/payload.bin")
    a = p.parse_args()
    payload = a.payload.resolve()
    profile = json.loads((ROOT / "profiles/SLES-03948.json").read_text())
    if not payload.is_file() or digest(payload) != profile["payload_sha256"]:
        p.error("French payload missing or different; use --payload with its full path")
    launcher = a.ghidra.resolve() / "support" / ("analyzeHeadless.bat" if os.name == "nt" else "analyzeHeadless")
    if not launcher.is_file():
        p.error("Ghidra launcher not found")
    blobs = {}
    for variant, expected in EXPECTED.items():
        path = a.probe_dir.resolve() / ("su_variant_%d_candidate.bin" % variant)
        if not path.is_file() or digest(path) != expected:
            p.error("Missing or different candidate: " + str(path))
        blobs[variant] = path
    stamp = datetime.datetime.now(datetime.timezone.utc).strftime("%Y%m%dT%H%M%SZ") + "-" + uuid.uuid4().hex[:8]
    run = ROOT / "work/su-ghidra" / stamp
    published = ROOT / "research/su-ghidra" / stamp
    summary = {"payload_sha256": profile["payload_sha256"], "runs": [],
               "warning": "Synthetic static snapshots, not captured runtime RAM. Other overlays absent."}
    for variant, blob in blobs.items():
        name = "variant_%d" % variant
        project = run / name
        export = published / name
        project.mkdir(parents=True)
        export.mkdir(parents=True)
        args = [str(launcher), str(project), "FM_SU", "-import", str(payload),
                "-loader", "BinaryLoader", "-processor", "MIPS:LE:32:default",
                "-loader-baseAddr", "0x80010000",
                "-scriptPath", str(ROOT / "tools/ghidra"),
                "-preScript", "PrepareSU.java", str(blob),
                "-postScript", "ExportAnalysis.java", str(export),
                "-log", str(export / "ghidra.log"),
                "-scriptlog", str(export / "scripts.log")]
        print("Analysing", name, flush=True)
        result = subprocess.run(args, check=False)
        complete = export / "COMPLETE.txt"
        ok = result.returncode == 0 and complete.is_file()
        summary["runs"].append({"variant": variant, "candidate_sha256": EXPECTED[variant],
                                "exit_code": result.returncode, "export_completed": ok,
                                "summary": complete.read_text() if complete.is_file() else None})
        (published / "run-summary.json").write_text(json.dumps(summary, indent=2) + "\n")
        if not ok:
            print("Analysis failed; logs:", export)
            return 1
    print("Both exports completed:", published)
    print("Review/commit research/su-ghidra in GitHub Desktop. No BIN or Ghidra project is included there.")
    print("Completion does not guarantee that all exported functions are valid.")
    return 0

if __name__ == "__main__":
    raise SystemExit(main())
