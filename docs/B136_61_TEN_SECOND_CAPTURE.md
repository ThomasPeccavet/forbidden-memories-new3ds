# B136.61 — post-load 10-second performance capture

Build PROFILE=1 UNAI=1. A successful port quick-load (SELECT+Y) arms a
host-only recorder. The next host loop starts a fresh ten-second wall window;
file parsing and load I/O are excluded. A failed load never arms it. Loading
again cancels/restarts capture. Loading Azahar's own emulator savestate does not
invoke this hook: use the port's quickstate-b135.bin and SELECT+Y.

Outputs under sdmc:/3ds/fm-new3ds:
- perf-capture.csv: one row per completed host loop with elapsed time, start/end
  PC, PS1 ticks/image counter, running state, stage timings, waits, DMA/IRQ/VSync,
  native probe and CD-sector counts, interpreter instructions and clock debt.
- perf-capture-summary.txt: aggregate statistics over the whole capture, all
  active GPU opcode costs, sampled native hotspots, and main-thread interpreted
  chunk entry PCs/calls/instruction counts/elapsed costs (128 exact slots).

Rows are buffered in static RAM (4096 slots). No capture file or periodic audio
status is written during the window. Files are written at completion; writing
can cause a short pause after the measured window. Each output records its
capture_start_ms, actual duration, row count and overflow count. A long call may
finish after 10000ms; no call is interrupted to end recording. Row/hotspot
capacity overflow is explicitly reported. Completed files remain until the next
completed capture. Avoid suspend/pause or save I/O during the comparison.

This is performance telemetry, not a video or a full instruction/register trace.
Native routine timing keeps its random 1/64 sampling; GPU command timings and
main-thread interpreter chunk timing are exhaustive within their stated scope.
IRQ interpreter execution is included in SEQ/pre-guest time, not in the main
interpreter hotspot table. DMA and SEQ columns are nested in pre-guest time;
do not add them to it. Profiling itself has a cost. The lower screen stays blank.

Guest behavior and snapshot format are unchanged. Capture state is never loaded
from a snapshot. The clean build contains no active recording calls/storage.

Validation covers start/finish, restart, failed-load hook placement, overflow,
read-only hot data, CSV export, absence of writes before completion and a fresh
10s aggregate window including its first loop. Host/static suite and ARM object
workflows validate the implementation; full gameplay is checked on Windows.
