# B136.38 — complete GPU timing and DMA payload split

The B136.37 user window measures 982 ms DMA2 in 2049 ms, with a single
sampled 2Ah command costing 30876 us. A random 1/16 sample cannot establish
the cumulative cost of rare expensive operations. This measurement build
times every completed GP0 command and ranks actual measured totals. The
report now labels opcode counts as calls, not samples. This includes
command execution, not upload payload handling after an upload header.

DMA linked lists separately accumulate system ticks around each nonempty
node's payload loop: RAM word reads, GP0 parsing and synchronous rendering.
`payload_parser_raster_us` is that interval; `traversal_other_us` is the
nonnegative remainder against the existing millisecond DMA total. The
remainder includes traversal, other list bookkeeping and measurement cost,
and has millisecond rounding error per transfer. It is not a pure raster
versus traversal split: the payload bucket also includes parsing/RAM reads.

All GPU timings include clock overhead; this build is for identifying the
next hotspot, not claiming an FPS improvement. CLEAN has no new clock calls.
Native sampling stays random 1/64. Guest/render semantics, timers, input,
SEQ delivery and blank bottom screen are preserved.

Host checks verify ranking survives per-DMA resets and window reset, and
validate payload delta/report formatting. Memory tests compile PROFILE and
CLEAN with the host clock stub. ARM compilation is checked by CI.

Reload the same duel state and provide three perf-latest reports separated
by a few seconds, noting whether a card animation is active or the board
is idle. This separates intermittent effects from sustained rendering.
