#!/usr/bin/env python3
"""Build deterministic reverse-engineering indexes from committed Ghidra exports.

The output deliberately separates direct Ghidra edges, unresolved call sites,
and inferred callback/table edges.  It never presents an inferred edge as a
direct call.
"""

from __future__ import annotations

import csv
import json
import re
from collections import defaultdict
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
RESIDENT = ROOT / "research/ghidra-fr/export"
SU = ROOT / "research/su-ghidra/20260914T192136Z-c0a29453/variant_0"
OUT = ROOT / "research/reverse-map"

STATE_TARGETS = [
    "8002cfdc", "8002d354", "8002d038", "8002d0bc", "8002d2b4",
    "8002d4ac", "8002d5cc", "8002d544", "8002d75c", "8002d800",
    "8002d858", "8002d89c", "8002d8f4", "8002d988", "8002d990",
    "8002dbe0", "8002de14",
]

GLOBAL_RE = re.compile(r"(?<![A-Za-z0-9])_?(?:PTR_)?DAT_[0-9A-Fa-f]{8}(?![A-Za-z0-9])")
CALLBACK_RE = re.compile(r"=\s*&?(?:FUN|seed|LAB)_([0-9A-Fa-f]{8})\s*;")
INDIRECT_RE = re.compile(r"\(\*\(code \*\)|\(\*DAT_|\(\*\*\(code \*\*\)|\(\*pcVar")


def read_tsv(path: Path) -> list[dict[str, str]]:
    with path.open(newline="", encoding="utf-8") as handle:
        return list(csv.DictReader(handle, delimiter="\t"))


def write_tsv(path: Path, fieldnames: list[str], rows: list[dict[str, object]]) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    with path.open("w", newline="", encoding="utf-8") as handle:
        writer = csv.DictWriter(handle, fieldnames=fieldnames, delimiter="\t", lineterminator="\n")
        writer.writeheader()
        writer.writerows(rows)


def normalize_global(token: str) -> str:
    return token.lstrip("_").upper()


def function_origin(address: str, resident_addresses: set[str]) -> str:
    value = int(address, 16)
    if address in resident_addresses:
        return "resident_export"
    if value >= 0x80100000:
        return "dynamic_or_overlay_seed"
    return "resident_seed_from_su_pass"


def access_for_line(line: str, token: str) -> str:
    escaped = re.escape(token)
    direct_write = re.search(rf"(?<![A-Za-z0-9]){escaped}\s*(?:\[[^]]+\])?\s*=", line)
    increment = re.search(rf"(?:\+\+|--){escaped}|{escaped}(?:\+\+|--)", line)
    compound = re.search(rf"{escaped}\s*(?:\+=|-=|\|=|&=|\^=)", line)
    count = len(re.findall(escaped, line))
    if increment or compound:
        return "read_write"
    if direct_write:
        return "read_write" if count > 1 else "write"
    return "read"


def main() -> None:
    OUT.mkdir(parents=True, exist_ok=True)

    resident_functions = read_tsv(RESIDENT / "functions.tsv")
    su_functions = read_tsv(SU / "functions.tsv")
    resident_addresses = {row["address"].lower() for row in resident_functions}

    functions_by_address: dict[str, dict[str, str]] = {}
    for row in resident_functions + su_functions:
        address = row["address"].lower()
        functions_by_address[address] = row

    function_rows: list[dict[str, object]] = []
    for address in sorted(functions_by_address, key=lambda value: int(value, 16)):
        row = functions_by_address[address]
        function_rows.append({
            "address": address,
            "name": row["name"],
            "body_bytes": row["body_bytes"],
            "status": row["status"],
            "origin": function_origin(address, resident_addresses),
            "region": "overlay_window" if int(address, 16) >= 0x80100000 else "resident",
        })
    write_tsv(
        OUT / "functions_enriched.tsv",
        ["address", "name", "body_bytes", "status", "origin", "region"],
        function_rows,
    )

    direct_edges: set[tuple[str, str, str]] = set()
    unresolved_rows: list[dict[str, object]] = []
    calls_by_source: dict[str, list[dict[str, str]]] = defaultdict(list)
    for export_name, export_dir in (("resident", RESIDENT), ("su_variant_0", SU)):
        for row in read_tsv(export_dir / "calls.tsv"):
            caller = row["caller"].lower()
            site = row["site"].lower()
            target = row["target"].lower()
            calls_by_source[caller].append(row)
            if target == "unresolved":
                unresolved_rows.append({
                    "caller": caller,
                    "site": site,
                    "kind": "ghidra_unresolved",
                    "expression": "",
                    "source_export": export_name,
                })
            else:
                direct_edges.add((caller, site, target))

    callback_edges: set[tuple[str, str]] = set()
    indirect_expressions: dict[str, set[str]] = defaultdict(set)
    global_access: dict[tuple[str, str], set[str]] = defaultdict(set)

    # The SU pass is a strict superset for the relevant seeded state/overlay
    # functions, while the resident export remains the origin authority.
    for path in sorted((SU / "pseudo-c").glob("*.c")):
        function = path.stem.lower()
        text = path.read_text(encoding="utf-8", errors="replace")
        for line_number, line in enumerate(text.splitlines(), 1):
            callback = CALLBACK_RE.search(line)
            if callback:
                callback_edges.add((function, callback.group(1).lower()))
            if INDIRECT_RE.search(line):
                indirect_expressions[function].add(f"L{line_number}: {line.strip()}")
            for raw_global in GLOBAL_RE.findall(line):
                normalized = normalize_global(raw_global)
                global_access[(function, normalized)].add(access_for_line(line, raw_global))

    enriched_rows: list[dict[str, object]] = []
    for caller, site, target in sorted(direct_edges, key=lambda item: tuple(int(v, 16) for v in item)):
        enriched_rows.append({
            "caller": caller,
            "site": site,
            "target": target,
            "edge_kind": "direct_ghidra",
            "confidence": "confirmed_static",
            "evidence": "calls.tsv",
        })
    for index, target in enumerate(STATE_TARGETS):
        enriched_rows.append({
            "caller": "8002df60",
            "site": "8002dfbc",
            "target": target,
            "edge_kind": "indexed_table",
            "confidence": "confirmed_table_dump",
            "evidence": f"PTR_80091f7c[{index}]",
        })
    for caller, target in sorted(callback_edges, key=lambda item: tuple(int(v, 16) for v in item)):
        enriched_rows.append({
            "caller": caller,
            "site": "assignment",
            "target": target,
            "edge_kind": "callback_assignment",
            "confidence": "confirmed_static_assignment",
            "evidence": "pseudo-C assignment",
        })
    write_tsv(
        OUT / "call_graph_enriched.tsv",
        ["caller", "site", "target", "edge_kind", "confidence", "evidence"],
        enriched_rows,
    )

    # Attach the decompiler expression(s) to unresolved rows by caller.  A
    # site-to-expression one-to-one mapping requires instruction listings and
    # is intentionally not guessed here.
    dedup_unresolved: dict[tuple[str, str], dict[str, object]] = {}
    for row in unresolved_rows:
        key = (str(row["caller"]), str(row["site"]))
        expressions = sorted(indirect_expressions.get(key[0], set()))
        row["expression"] = " | ".join(expressions)
        previous = dedup_unresolved.get(key)
        if previous:
            previous["source_export"] = "resident+su_variant_0"
        else:
            dedup_unresolved[key] = row
    write_tsv(
        OUT / "indirect_calls.tsv",
        ["caller", "site", "kind", "expression", "source_export"],
        sorted(dedup_unresolved.values(), key=lambda row: (int(str(row["caller"]), 16), int(str(row["site"]), 16))),
    )

    global_rows: list[dict[str, object]] = []
    for (function, global_name), accesses in sorted(
        global_access.items(), key=lambda item: (item[0][1], int(item[0][0], 16))
    ):
        if "read_write" in accesses or {"read", "write"}.issubset(accesses):
            access = "read_write"
        elif "write" in accesses:
            access = "write"
        else:
            access = "read"
        global_rows.append({"global": global_name, "function": function, "access": access})
    write_tsv(OUT / "global_usage.tsv", ["global", "function", "access"], global_rows)

    state_machines = {
        "main_dispatch": {
            "dispatcher": "8002df60",
            "state_global": "DAT_8009C60A",
            "index_expression": "state & 0x1f",
            "flags": {"0x80": "per-state pre-service latch", "0x40": "state initialized/active", "0x20": "handler-specific alternate path"},
            "table": "80091f7c",
            "targets": [{"index": index, "target": target} for index, target in enumerate(STATE_TARGETS)],
        },
        "duel_entry": {
            "main_state": 3,
            "handler": "8002d0bc",
            "substate_global": "DAT_8009C60B",
            "substates": [0, 1, 2],
            "constructor": "80032824",
            "frame_callback": "80031b58",
        },
        "script_vm": {
            "dispatcher": "8002fca4",
            "opcode_state": "DAT_8009C610",
            "script_id_flags": "DAT_8009C628",
            "script_pc": "DAT_8009C624",
            "override_opcode": "DAT_8009C622",
            "table": "80092068",
            "mask": "0x1f",
        },
        "dialogue_vm": {
            "dispatcher": "800393b8",
            "current_opcode": "DAT_8009C6DA",
            "handler_result": "DAT_8009C6CC",
            "nested_script_active": "DAT_8009C6D2",
            "control_table": "80091f6c",
            "render_state_table": "80092270",
        },
        "render_pipeline": {
            "frame_driver": "80012c50",
            "render_callbacks": "80012f70",
            "wait": "80012cb8",
            "finalizer": "80012d60",
            "submit_gate": "DAT_8009C4B8",
            "gate_setter": "80015c18",
            "gate_controller": "8001522c",
            "sort": "80085d98",
            "draw": "80085d08",
        },
    }
    (OUT / "state_machines.json").write_text(
        json.dumps(state_machines, indent=2, sort_keys=True) + "\n", encoding="utf-8"
    )

    summary = {
        "functions": len(function_rows),
        "direct_edges": len(direct_edges),
        "indexed_table_edges": len(STATE_TARGETS),
        "callback_assignment_edges": len(callback_edges),
        "unresolved_call_sites": len(dedup_unresolved),
        "global_usage_rows": len(global_rows),
        "note": "Indirect targets not proven by committed table bytes/runtime traces remain unresolved.",
    }
    (OUT / "SUMMARY.json").write_text(json.dumps(summary, indent=2) + "\n", encoding="utf-8")


if __name__ == "__main__":
    main()
