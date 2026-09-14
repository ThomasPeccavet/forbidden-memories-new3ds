#!/usr/bin/env python3
"""Run a new, isolated Ghidra analysis of the verified French PS1 payload."""
import argparse
import datetime
import hashlib
import json
import os
from pathlib import Path
import subprocess
import sys
import uuid

ROOT = Path(__file__).resolve().parents[1]

def main():
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument('--ghidra', type=Path, required=True, help='Extracted Ghidra installation directory')
    p.add_argument('--payload', type=Path, required=True)
    p.add_argument('--out', type=Path, default=ROOT / 'work' / 'ghidra')
    a = p.parse_args()
    profile = json.loads((ROOT / 'profiles' / 'SLES-03948.json').read_text())
    payload = a.payload.resolve()
    if not payload.is_file(): p.error('Payload absent. Run inspect_disc.py first.')
    with payload.open('rb') as f:
        digest = hashlib.file_digest(f, 'sha256').hexdigest()
    if digest != profile['payload_sha256']:
        p.error('Payload does not match the analysed French release. No analysis started.')
    launcher = a.ghidra.resolve() / 'support' / ('analyzeHeadless.bat' if os.name == 'nt' else 'analyzeHeadless')
    if not launcher.is_file(): p.error('Ghidra analyzeHeadless launcher not found at ' + str(launcher))
    run = a.out.resolve() / (datetime.datetime.now(datetime.timezone.utc).strftime('%Y%m%dT%H%M%SZ') + '-' + uuid.uuid4().hex[:8])
    project = run / 'project'; export = run / 'export'
    project.mkdir(parents=True); export.mkdir()
    args = [str(launcher), str(project), 'FM_FR', '-import', str(payload),
            '-loader', 'BinaryLoader', '-processor', 'MIPS:LE:32:default',
            '-loader-baseAddr', '0x80010000',
            '-scriptPath', str(ROOT / 'tools' / 'ghidra'),
            '-preScript', 'PrepareFrench.java',
            '-postScript', 'ExportAnalysis.java', str(export),
            '-log', str(run / 'ghidra.log'), '-scriptlog', str(run / 'scripts.log')]
    (run / 'invocation.json').write_text(json.dumps({'argv':args,'payload_sha256':digest}, indent=2))
    print('Analysis directory:', run, flush=True)
    result = subprocess.run(args, check=False)
    if result.returncode:
        print('Ghidra failed; inspect logs in', run, file=sys.stderr)
        return result.returncode
    if not (export / 'COMPLETE.txt').is_file():
        print('Export did not finish; inspect Ghidra logs.', file=sys.stderr)
        return 1
    print('Export complete:', export)
    print('Check functions.tsv for individual decompilation failures. Output is analysis pseudo-C.')
    return 0

if __name__ == '__main__':
    raise SystemExit(main())
