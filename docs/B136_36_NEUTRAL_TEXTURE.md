# B136.36 — neutral modulation in the measured textured hotspot

The B136.35 user window reports 16.45 image latches/s, 629 ms DMA2 cost,
99 transfers and a 31 ms maximum host loop in 2006 ms. This is a different
workload/window than B136.34 (30 transfers), so the FPS change cannot be
fully attributed to the Gouraud setup patch. The measured opcode leaders
are 3Ch, 34h and 64h. This patch targets the common 3Ch/34h triangle path.

## Exact specialization

When all vertex RGB555 components are 16 (RGB888 components 128..135),
the existing per-pixel modulation is identity: (channel * 16) >> 4 equals
the original channel. Under the existing opaque/no-mask/no-texture-window
fast-path guards, the new span loop removes color interpolation, clamps,
channel multiplications and repacking. Constant depth call sites separate
4-bit, 8-bit and direct texture lookup. UV interpolation, the packed-word
cache, per-triangle palette snapshot, clipping and draw ordering remain
unchanged. No cross-command palette cache is introduced.

A zero source texel remains transparent. 8000h remains opaque black:
transparency is tested before masking the high bit. Raw, semi-transparent,
masked, texture-window and non-neutral cases retain the existing raster
path. RGB gradients are zero for neutral vertices regardless of flags,
matching the original arithmetic exactly.

The PROFILE report adds `texture_fast`: neutral/fast triangle counts and
neutral/fast covered pixel counts, per window. Covered pixels include
transparent texels; these are not counts of actual VRAM writes or timings.
Their ratio measures specialization coverage, not predicted FPS gain.
Timers, VSync, input and overlays are unchanged.

## Validation and measured limits

57 host tests pass. The new differential test compares all VRAM pixels
and pixel counters against frozen production B136.35 for 640 cases, in
both normal and PROFILE builds. Cases exercise all texture depths,
neutral/variable colors, lower RGB bits, clipping, degenerate triangles,
wrapped palettes, palette/destination overlap, raw/semi/mask/window guards,
and opaque-black output. Existing Gouraud and timer tests still pass.

A local x86 host benchmark of 700 large neutral triangles gives:

| Texture | B136.35 ms | B136.36 ms | Local speed ratio |
|---|---:|---:|---:|
| 4-bit | 96.03 | 35.70 | 2.69x |
| 8-bit | 107.41 | 39.73 | 2.70x |
| Direct | 95.68 | 31.13 | 3.07x |

This is a particular renderer workload on the local host, not an ARM11
measurement or a whole-game FPS improvement. The eligible fraction of the
user's duel is unknown until the new counters are read. Optional host
benchmark: set `FM_GPU_HOST_BENCHMARK=1` and run the textured-neutral test.
No performance threshold is asserted in CI.

Reload the same duel quickstate and compare multiple perf-latest windows
and visible rendering. If neutral coverage is low, the next target is
non-neutral 34h/3Ch rendering rather than further tuning this special case.
