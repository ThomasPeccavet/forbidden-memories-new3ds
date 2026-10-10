# B136.39 — specialize measured opaque sprite hotspot

B136.38 user measurements: idle 64h costs 469303 us / 2004 ms (2727 calls),
3Ch/34h 276243 us; during card animation 64h costs 104332 us, 3Ch/34h
337632 us. DMA traversal/other costs only 26–29 ms. Optimize the sustained
idle sprite load first. The B136.37 varying-color triangle path is retained.

## Exact sprite span

For opaque sprites without masks or texture windows, select the texture
depth outside the inner loop. Select three exact RGB555 modulation lookup
rows once per sprite. Raw and neutral colors take the identity path.
Zero texels stay transparent; 8000h stays opaque black. Clipping, texture
wrapping and pixel counters match the original path. Semi-transparent,
masked and texture-window sprites keep their original implementation.

Texture and CLUT reads remain live per pixel: no palette snapshot or
packed-word reuse across writes, preserving palette/texture/destination
aliasing. This avoids a cache-invalidation dependency. No game timers,
SEQ delivery, input, draw order or waits are changed. Complete B136.38
profiling is retained for comparable opcode measurements.

## Validation and local benchmark

The frozen B136.38 sprite implementation is compared against production
for 700 randomized cases in CLEAN and PROFILE modes. Full VRAM and pixel/
texel counters are identical. Cases include all texture depths, clipping,
wrapping, zero/8000h entries, neutral/variable/raw colors, masks, texture
windows, semi-transparency and overlapping texture/CLUT/destination.

Optional x86 benchmark, 500 sprites of 200 by 100 pixels:

| Depth | Modulation | Before ms | After ms | Throughput ratio |
|---|---|---:|---:|---:|
| 4-bit | Variable | 49.88 | 25.27 | 1.97x |
| 8-bit | Variable | 52.99 | 26.08 | 2.03x |
| Direct | Variable | 39.56 | 16.16 | 2.45x |
| 4-bit | Neutral | 51.46 | 15.21 | 3.38x |
| 8-bit | Neutral | 51.86 | 15.71 | 3.30x |
| Direct | Neutral | 39.29 | 8.99 | 4.37x |

These are local renderer timings, not ARM11/Azahar FPS improvements.
Reload the same duel state and compare idle and animation windows. The
remaining 3Ch/34h cost still needs further optimization if it dominates.
Run the optional benchmark with FM_GPU_HOST_BENCHMARK=1 and the sprite test.
