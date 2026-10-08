# B136.37 — exact modulation lookup for variable-color textures

The B136.36 duel window reports 16.50 image latches/s versus 16.45 in
B136.35. Neutral coverage is zero; the neutral specialization offers no
benefit in this window. DMA2 costs 602 ms within 1156 ms pre-guest time
on a 2000 ms window (nested, not additive). The 4488 fast triangles and
1200507 covered pixels are the relevant varying-color workload.

## Implementation

The opaque, no-mask, no-texture-window textured Gouraud path uses constant
texture-depth call sites and a 1024-byte table for each RGB555 component:
`min(31, (texel_component * clamped_shade) >> 4)`. The table is exact for
all 32 by 32 inputs. Color and UV interpolation, clipping, per-triangle
palette snapshots, ordering, zero transparency and opaque 8000h black are
preserved. Raw, semi-transparent, masked and texture-window paths retain
the generic implementation. Neutral specialization remains available.
The report identifies `format_specialization=1 color_lookup=1`.

No changes to timers, SEQ delivery, VSync, input or guest execution budget.

## Validation

The differential host test compares complete VRAM and pixel counters with
frozen B136.35 production rendering: 640 cases in each of normal/PROFILE
modes, predominantly varying colors, all texture depths, transparency,
clipping, palettes and fallback guards. All 1024 lookup entries are checked.

Optional local x86 benchmark, varying-color triangles:

| Case | Depth | Before ms | After ms | Throughput ratio |
|---|---:|---:|---:|---:|
| Large | 4-bit | 89.00 | 76.69 | 1.16x |
| Large | 8-bit | 102.18 | 84.02 | 1.22x |
| Large | Direct | 92.61 | 73.83 | 1.25x |
| Small | 4-bit | 90.52 | 79.22 | 1.14x |
| Small | 8-bit | 109.05 | 93.36 | 1.17x |
| Small | Direct | 79.60 | 70.85 | 1.12x |

These are local renderer microbenchmarks, not ARM11 or Azahar FPS results.
Whole-game benefit depends on ARM cache/instruction costs and the fraction
of time spent in this path. No FPS promise or CI performance threshold.
Reload the same duel state, play 20 seconds, and compare multiple report
windows plus visual correctness. Opcode 64h sprites remain another target.
