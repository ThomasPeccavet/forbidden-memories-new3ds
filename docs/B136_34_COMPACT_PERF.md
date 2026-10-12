# B136.34 — remove legacy report workload and expose DMA cost

The B136.33 duel window reports 12.45 image latches/s, 37.86 host loops/s,
1285 ms pre-presentation, 103 ms presentation, 240 ms wait and 318 ms
residual time in 2007 ms. The compact report itself took 59 ms in the
previous window; maximum loop time was 259 ms. This does not identify the
cause of every hitch, or establish a causal slowdown from B136.32.

The large periodic console/file diagnostic block still executed every
120 host iterations despite console printf being compiled away. B136.34
skips that read-only block by default (`FM_LEGACY_FILE_DIAGNOSTICS=0`),
including debug-latest, intro-diag, video-watch, memory-watch, c4b8 and q20
periodic dumps. Old files may remain on SD and are stale. Explicit compiler
`-DFM_LEGACY_FILE_DIAGNOSTICS=1` restores the old block. One-shot startup
traces and quickstate read/write remain available. Bottom screen stays blank.

The PROFILE compact report stays on a two-second wall-clock cadence.
An explicit 8 KiB stdio buffer batches formatted output until close.
`dma2_nested_ms` is a delta of existing cumulative linked-list timings:
OT traversal, GP0 parsing and software rasterization together. Its value
is nested inside existing phases and must not be added to their totals.
`max_ms` is the maximum since reset, not a per-window maximum.
The report's own duration is still printed as previous_report_ms.

Native dispatch sampling now selects upper bits of a deterministic PRNG
(approximately 1/64), instead of always taking every 64th dispatch. This
reduces phase-lock bias on periodic game call patterns. Sampled totals
remain unscaled and do not establish total CPU cost.

Host tests exercise the actual report with 400 ms cumulative DMA delta
and 100 transfers, alongside existing phase/rate and nested-time checks.
Static checks and 54 host tests pass. No full 3DS/Azahar duel measurement
is available locally; FPS improvement is not claimed. Timers, VSync wait,
OT repairs, rasterization and input semantics are unchanged.

For comparison load the same duel quickstate, play for 20 seconds, then
read perf-latest.txt. Check B136.34 and legacy_file_dumps=0. Two or three
windows give more confidence than a single different moment in the duel.
