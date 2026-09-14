#!/usr/bin/env python3
"""Probe the known French BIN without modifying it. Python 3.11+.
Usage: py -3 tools/probe_su_overlay.py "disc/game.bin"
Candidate overlays are hypotheses, not confirmed executable modules.
"""
import argparse
import datetime
import hashlib
import json
from pathlib import Path
import struct
import uuid

ROOT = Path(__file__).resolve().parents[1]

def main():
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument("disc", type=Path)
    p.add_argument("--out", type=Path, default=ROOT / "research" / "su-probe")
    a = p.parse_args()
    profile = json.loads((ROOT / "profiles" / "SLES-03948.json").read_text())
    if a.disc.stat().st_size != profile["disc_bytes"]:
        p.error("Unexpected disc size")
    with a.disc.open("rb") as disc:
        if hashlib.file_digest(disc, "sha256").hexdigest() != profile["disc_sha256"]:
            p.error("Disc hash does not match the analysed French release")
        def read_bytes(file_lba, offset, size):
            result = bytearray()
            while len(result) < size:
                sector, inside = divmod(offset, 2048)
                disc.seek((file_lba + sector) * 2352)
                raw = disc.read(2352)
                if len(raw) != 2352 or raw[:12] != b"\0" + b"\xff" * 10 + b"\0" or raw[15] != 2:
                    raise ValueError("Invalid Mode 2 sector")
                if raw[16:20] != raw[20:24] or raw[18] & 0x20:
                    raise ValueError("Expected Form 1 sector")
                count = min(2048 - inside, size - len(result))
                result.extend(raw[24 + inside:24 + inside + count])
                offset += count
            return bytes(result)
        exe = next(f for f in profile["files"] if f["path"] == profile["boot"])
        su = next(f for f in profile["files"] if f["path"] == "DATA/SU.MRG;1")
        def memory(address, count):
            offset = address - profile["header"]["load_address"]
            if offset < 0 or offset + count > profile["header"]["payload_size"]:
                raise ValueError("Requested address outside EXE payload")
            return read_bytes(exe["lba"], 2048 + offset, count)
        pointers = {}
        for addr in list(range(0x80010000, 0x80010034, 4)) + list(range(0x800101d8, 0x800101ec, 4)):
            pointers[f"{addr:08x}"] = f"{struct.unpack("<I", memory(addr, 4))[0]:08x}"
        # Read 32 raw words, NOT an assertion of 32 valid state handlers.
        state_words = [f"{v:08x}" for v in struct.unpack("<32I", memory(0x80091f7c, 128))]
        source_bases = [f"{v:08x}" for v in struct.unpack("<4I", memory(0x800eb198, 16))]
        stamp = datetime.datetime.now(datetime.timezone.utc).strftime("%Y%m%dT%H%M%SZ") + "-" + uuid.uuid4().hex[:8]
        out = a.out / stamp
        out.mkdir(parents=True, exist_ok=False)
        report = {
            "disc_sha256": profile["disc_sha256"],
            "pointer_words": pointers,
            "state_table_address": "80091f7c",
            "state_table_raw_words": state_words,
            "source_base_words_at_800eb198": source_bases,
            "warning": "Static initial bytes only. Chunk layout assumes sequential callback consumption; runtime confirmation required.",
            "candidates": [],
        }
        # FUN_8006b560: stride 0x88 sectors, request 0x73 sectors.
        # FUN_8006b350 stages: 0x20000, 0x10000, 0x1000, 0x8000, 0x800.
        # Extract only variants 0 and 1 as probes, not an exhaustive variant list.
        for variant in (0, 1):
            offset = variant * 0x88 * 2048 + 0x31000
            size = 0x8000
            if offset + size > su["iso_size"]:
                raise ValueError("Candidate exceeds SU.MRG bounds")
            blob = read_bytes(su["lba"], offset, size)
            name = f"su_variant_{variant}_candidate.bin"
            (out / name).write_bytes(blob)
            report["candidates"].append({
                "variant": variant, "su_offset": hex(offset), "size": size,
                "file": name, "sha256": hashlib.sha256(blob).hexdigest(),
                "first_256_bytes_hex": blob[:256].hex(),
                "word_at_plus_1c": hex(struct.unpack_from("<I", blob, 0x1c)[0]),
                "bytes_at_plus_390": blob[0x390:0x3d0].hex(),
                "nonzero_bytes": sum(b != 0 for b in blob),
            })
        (out / "report.json").write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
        print("Probe complete:", out)
        print("Commit only report.json; candidate BIN files remain local and ignored.")
        print("This does not prove an overlay or produce a playable port.")

if __name__ == "__main__":
    main()
