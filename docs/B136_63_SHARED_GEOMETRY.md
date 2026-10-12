# B136.63 — reuse exact shared-vertex geometry

## Baseline

Runtime and audio behavior start from B136.60 (remote commit
52b4552940c37e0b262496278aa0fc759de002b1). The user confirmed sound works
there and disappears in their B136.62 test. The root cause of that audio
regression is not established; this build does not carry B136.62's build
rewriter, scratchpad or inline COP2 changes. It also retains B136.60's
scheduler and snapshot contracts. The lower console stays blank.

The proposed model rewrite was refined after inspection: the core GTE
projection already is semantic native C. Translating it into more C would
preserve most of its work. The first architectural experiment instead
eliminates repeated projection arithmetic for shared vertices, keeping the
model callbacks, primitive ordering, packets and Unai renderer intact.

## Exact cache

A 128-slot direct-mapped, host-only cache stores the results of a single
vertex projection. A hit requires all three signed vertex components,
command sf/lm bits, whether the call writes MAC0/IR0, and an unchanged
projection context. That context comprises rotation controls 0..4,
translation 5..7, screen offsets 24..25, H 26, DQA 27 and DQB 28. Full
32-bit backing values are compared conservatively.

The miss path is the original B136.60 arithmetic. Results include MAC1..3,
IR1..3, projected depth, screen position, conditional MAC0/IR0, and the
per-vertex flags. Hits still shift the CURRENT SZ and SXY FIFOs exactly,
update SXY2/SXYP and merge flags. They do not copy a saved CPU snapshot.
RTPT still performs all three ordered projection effects; no GTE command,
polygon, IRQ, frame or instruction checkpoint is skipped.

Context changes advance a generation; wraparound clears entries. The key
has no guest RAM pointers, so a loaded state with identical inputs may
safely use a cached pure result. Host cache state is not serialized and
snapshot ABI is unchanged. `FM_GEOMETRY_CACHE=0` keeps the original path
for differential testing. PROFILE's `perf-latest.txt` includes explicitly
cumulative hit/miss/context counters; CLEAN does not write this report.

## Verification and performance limits

The production GTE section is compiled twice for host tests: cache enabled
and disabled. Tests compare the entire CPUState after every command across
shared meshes, randomized FIFOs/backing state, all control register
changes, sf/lm combinations, overflow/saturation cases and generation
wrap. Non-projection commands are interleaved to verify interactions.
A representative shared-mesh sequence obtained 24,169 hits and 2,499
misses. A repeated-mesh host microbenchmark ran approximately twice as
fast; neither is an Azahar FPS prediction. Mostly unique vertices or
frequent matrix changes can yield little gain and add cache overhead.

The unavailable private generated ROM core and Azahar playback cannot be
linked or exercised locally. Host correctness and ARM C compilation are
required; playback should check the same map route, duel entry, dialogue,
card geometry and sound. There is no promise of 30 FPS or a completed
replacement of the whole model renderer in this build.
