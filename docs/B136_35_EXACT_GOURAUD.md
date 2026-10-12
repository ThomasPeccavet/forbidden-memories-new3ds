# B136.35 — exact Gouraud setup and GPU window ranking

The B136.34 duel measurement has 920 ms of DMA2 linked-list cost per
2064 ms window (45%), with 30 transfers and a 107 ms maximum. Linked-list
cost includes traversal, GP0 dispatch and software rasterization together;
no per-opcode attribution was available in the compact report.

## First bounded implementation

Untextured Gouraud triangles (native 30h/38h families) still performed six
RGB gradient divisions and three edge divisions with 64-bit integer
arithmetic. B136.35 replaces the normal setup with a floating estimate,
then integer multiplication/residual checks that prove the exact quotient.
The old integer division remains a fallback for large slopes, divisors,
or an estimate needing more than one correction. Pixel interpolation,
coverage, mask and blending rules are preserved. Pixel diagnostic counts
are accumulated locally and published once per triangle.

`FM_GPU_EXACT_GRADIENTS=0` selects exact integer quotient calculation in
the new helper for comparison; default is 1. This is not an approximate
floating-point rasterizer. No timer, waiting, input or interpreter changes.

GPU profiling now accumulates sampled opcode costs across a complete
two-second window, independent of old per-DMA resets. Random selection
averages 1/16 completed commands, avoiding deterministic phase locking.
`gpu0`...`gpu5` report opcode, number of samples, total sampled microseconds
and maximum sampled command time. Totals are unscaled sampled times, not
full GPU costs. DMA2 remains the authoritative full linked-list measure.

## Validation and limits

56 host tests pass. New tests compare 250000 gradient quotients with
signed integer division (including exceptional estimates), and 600 raster
cases pixel-for-pixel against a frozen copy of production B136.34.
They cover clipping, degenerate/flat triangles, positive/negative gradients,
all blending modes and mask settings; pixel counters also agree.
The profiler test checks accumulation across real per-DMA resets and
clearing at window boundaries. Report tests include opcode formatting.

There is no local ARM11 execution benchmark or uploaded duel quickstate.
No global FPS gain is claimed: if 30h/38h are uncommon, this change may have
little impact. Its ARM cost must be checked in the user's duel. Existing
textured 34h/3Ch paths already use VFP setup and are untouched here.

If the entire 45% DMA2 cost were halved, the fixed-work model predicts
about +29% global throughput, not a doubling. This patch targets only one
part of that cost. The opcode ranking selects the next optimization;
palette caching is deferred until its cost and invalidation needs are known.
