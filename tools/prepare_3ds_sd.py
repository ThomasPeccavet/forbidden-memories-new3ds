#!/usr/bin/env python3
"""Stage the native platform prototype. The PS1 game is not yet executed."""
import argparse
import hashlib
import json
from pathlib import Path
import shutil
import struct

DISC_SIZE = 548427600
DISC_SHA = '9ef0d0ba5e42b838bd8312ecfe4071b09c44bc08ee896f6b76f913a41fe4b835'

def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--app', type=Path, required=True, help='Compiled fm-new3ds.3dsx')
    ap.add_argument('--output', type=Path, required=True, help='New staging directory (not the SD root)')
    ap.add_argument('--preview', type=Path, help='Optional 320x256 PC screenshot, requires Pillow')
    ap.add_argument('--disc', type=Path, help='Optional verified French raw BIN; copied, never embedded')
    args = ap.parse_args()
    if args.output.exists():
        ap.error('Output must be a new staging directory; copy its contents to SD afterwards')
    if args.app.read_bytes()[:4] != b'3DSX':
        ap.error('Not a 3DSX executable')
    preview = None
    if args.preview:
        from PIL import Image
        with Image.open(args.preview) as im:
            if im.size != (320, 256):
                ap.error('Preview must be exactly 320x256; no implicit cropping')
            preview = b''.join(struct.pack('<H', (r >> 3) | ((g >> 3) << 5) | ((b >> 3) << 10))
                               for r, g, b in im.convert('RGB').getdata())
    if args.disc:
        if args.disc.stat().st_size != DISC_SIZE:
            ap.error('Wrong disc size: expected 548427600 bytes')
        with args.disc.open('rb') as f:
            if hashlib.file_digest(f, 'sha256').hexdigest() != DISC_SHA:
                ap.error('Wrong disc SHA-256: expected the verified French image')
    target = args.output / '3ds' / 'fm-new3ds'
    target.mkdir(parents=True)
    shutil.copyfile(args.app, target / 'fm-new3ds.3dsx')
    if preview is not None:
        (target / 'preview.rgb555').write_bytes(preview)
    if args.disc:
        shutil.copyfile(args.disc, target / 'disc.bin')
    files = {}
    for p in target.iterdir():
        with p.open('rb') as f:
            files[p.name] = {'bytes': p.stat().st_size, 'sha256': hashlib.file_digest(f, 'sha256').hexdigest()}
    (args.output / 'manifest.json').write_text(json.dumps({
        'stage': 'native-platform-bring-up-not-playable', 'files': files,
        'console_execution_verified': False, 'preview_is_static_pc_capture': preview is not None
    }, indent=2) + '\n', encoding='utf-8')
    print('Ready:', args.output)
    print('Copy 3ds/ to the SD root. START+SELECT exits. This is not a playable game.')

if __name__ == '__main__':
    main()
