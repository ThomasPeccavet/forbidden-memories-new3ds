#!/usr/bin/env python3
"""Validate the SLES-03948 SU.MRG layout directly from a raw MODE2/2352 BIN.

This tool is intentionally dependency-free. It validates the exact SU layout
used by the New3DS bring-up and prints enough data to confirm/refute hypotheses
such as the B76 0x801AF800 resource-tail mapping.

Usage:
  python tools/validate_su_layout.py disc.bin
  python tools/validate_su_layout.py disc.bin --json
  python tools/validate_su_layout.py disc.bin --skip-disc-hash
"""
from __future__ import annotations

import argparse
import hashlib
import json
from pathlib import Path
import struct
import sys

SECTOR_RAW = 2352
SECTOR_USER = 2048
SYNC = b"\x00" + b"\xff" * 10 + b"\x00"

SU_LAYOUT = [
    {"name": "buffer_0", "offset": 0x00000, "size": 0x20000, "destination": "scratch/buffer"},
    {"name": "buffer_1", "offset": 0x20000, "size": 0x10000, "destination": "scratch/buffer"},
    {"name": "small_block", "offset": 0x30000, "size": 0x01000, "destination": "0x801DD000"},
    {"name": "overlay_code", "offset": 0x31000, "size": 0x08000, "destination": "0x80180000"},
    {"name": "resource_tail", "offset": 0x39000, "size": 0x00800, "destination": "0x801AF800"},
]

EXPECTED_OVERLAY_WORDS = [0x00000033, 0x80184398, 0x80183740, 0x80183920]


def _read_profile(path: Path) -> dict:
    return json.loads(path.read_text(encoding="utf-8"))


def _su_entry(profile: dict) -> dict:
    for item in profile.get("files", []):
        if item.get("path", "").upper() == "DATA/SU.MRG;1":
            return item
    raise ValueError("DATA/SU.MRG;1 not present in profile")


def read_mode2_form1_sector(f, lba: int) -> bytes:
    f.seek(lba * SECTOR_RAW)
    raw = f.read(SECTOR_RAW)
    if len(raw) != SECTOR_RAW:
        raise ValueError(f"short raw sector at LBA {lba}")
    if raw[:12] != SYNC:
        raise ValueError(f"invalid sync pattern at LBA {lba}")
    if raw[15] != 2:
        raise ValueError(f"sector {lba} is not MODE2")
    # XA subheader duplicated at 16..19 and 20..23.
    if raw[16:20] != raw[20:24]:
        raise ValueError(f"XA subheader mismatch at LBA {lba}")
    # Submode bit 0x20 = Form 2. We need Form 1 for SU.MRG.
    if raw[18] & 0x20:
        raise ValueError(f"sector {lba} is XA Form 2; expected Form 1")
    return raw[24:2072]


def read_user_bytes(f, lba: int, offset: int, size: int) -> bytes:
    if offset < 0 or size < 0:
        raise ValueError("negative offset/size")
    first_sector = offset // SECTOR_USER
    in_sector = offset % SECTOR_USER
    out = bytearray()
    cur = lba + first_sector
    need = in_sector + size
    while len(out) < need:
        out.extend(read_mode2_form1_sector(f, cur))
        cur += 1
    return bytes(out[in_sector:in_sector + size])


def count_nonzero(data: bytes) -> int:
    return sum(1 for b in data if b)


def u32_words(data: bytes, count: int = 4) -> list[int]:
    result = []
    for i in range(count):
        off = i * 4
        if off + 4 > len(data):
            break
        result.append(struct.unpack_from("<I", data, off)[0])
    return result


def build_report(disc: Path, profile_path: Path, skip_disc_hash: bool = False) -> dict:
    profile = _read_profile(profile_path)
    su = _su_entry(profile)

    size = disc.stat().st_size
    if size % SECTOR_RAW:
        raise ValueError("disc size is not a multiple of 2352 bytes")

    report = {
        "disc": str(disc),
        "disc_bytes": size,
        "disc_sectors": size // SECTOR_RAW,
        "profile": str(profile_path),
        "profile_disc_bytes_match": size == profile.get("disc_bytes"),
        "profile_disc_sectors_match": size // SECTOR_RAW == profile.get("disc_sectors"),
        "su": {
            "path": su["path"],
            "lba": su["lba"],
            "iso_size": su["iso_size"],
            "layout_total": sum(x["size"] for x in SU_LAYOUT),
            "layout": [],
        },
    }

    if not skip_disc_hash:
        h = hashlib.sha256()
        with disc.open("rb") as f:
            while True:
                chunk = f.read(4 * 1024 * 1024)
                if not chunk:
                    break
                h.update(chunk)
        disc_hash = h.hexdigest()
        report["disc_sha256"] = disc_hash
        report["profile_disc_sha256_match"] = disc_hash == profile.get("disc_sha256")

    with disc.open("rb") as f:
        for part in SU_LAYOUT:
            data = read_user_bytes(f, su["lba"], part["offset"], part["size"])
            row = dict(part)
            row.update({
                "relative_sector": part["offset"] // SECTOR_USER,
                "absolute_lba": su["lba"] + part["offset"] // SECTOR_USER,
                "sha256": hashlib.sha256(data).hexdigest(),
                "nonzero": count_nonzero(data),
                "first16": data[:16].hex(),
                "first_words": [f"0x{x:08X}" for x in u32_words(data)],
            })
            report["su"]["layout"].append(row)

    overlay = next(x for x in report["su"]["layout"] if x["name"] == "overlay_code")
    resource = next(x for x in report["su"]["layout"] if x["name"] == "resource_tail")
    overlay_words = [int(x, 16) for x in overlay["first_words"]]

    report["checks"] = {
        "layout_total_is_0x39800": report["su"]["layout_total"] == 0x39800,
        "layout_fits_su_file": report["su"]["layout_total"] <= su["iso_size"],
        "resource_tail_offset_is_0x39000": resource["offset"] == 0x39000,
        "resource_tail_relative_sector_is_0x72": resource["relative_sector"] == 0x72,
        "resource_tail_absolute_lba": resource["absolute_lba"],
        "resource_tail_nonzero": resource["nonzero"] > 0,
        "overlay_signature_matches_runtime": overlay_words[:4] == EXPECTED_OVERLAY_WORDS,
    }

    report["checks"]["all_required"] = all(
        report["checks"][key]
        for key in (
            "layout_total_is_0x39800",
            "layout_fits_su_file",
            "resource_tail_offset_is_0x39000",
            "resource_tail_relative_sector_is_0x72",
            "resource_tail_nonzero",
        )
    )
    return report


def print_human(report: dict) -> None:
    su = report["su"]
    print("SU.MRG validation")
    print("=================")
    print(f"disc: {report['disc']}")
    print(f"SU.MRG: LBA {su['lba']}  size {su['iso_size']} bytes")
    print()
    for part in su["layout"]:
        print(
            f"{part['name']:14s} off=0x{part['offset']:05X} "
            f"size=0x{part['size']:05X} rel=0x{part['relative_sector']:02X} "
            f"LBA={part['absolute_lba']} dst={part['destination']} "
            f"nz={part['nonzero']}/{part['size']}"
        )
        print(f"  first16={part['first16']}")
        print(f"  words={' '.join(part['first_words'])}")
    print()
    print("checks")
    for key, value in report["checks"].items():
        if key == "resource_tail_absolute_lba":
            print(f"  {key}: {value}")
        else:
            print(f"  {key}: {'PASS' if value else 'FAIL'}")


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("disc", type=Path)
    parser.add_argument(
        "--profile",
        type=Path,
        default=Path(__file__).resolve().parents[1] / "profiles" / "SLES-03948.json",
    )
    parser.add_argument("--json", action="store_true")
    parser.add_argument("--skip-disc-hash", action="store_true")
    args = parser.parse_args()

    try:
        report = build_report(args.disc, args.profile, args.skip_disc_hash)
    except Exception as exc:
        print(f"ERROR: {exc}", file=sys.stderr)
        return 2

    if args.json:
        print(json.dumps(report, indent=2))
    else:
        print_human(report)

    return 0 if report["checks"]["all_required"] else 1


if __name__ == "__main__":
    raise SystemExit(main())
