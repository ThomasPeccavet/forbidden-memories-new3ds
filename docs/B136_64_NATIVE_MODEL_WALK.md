# B136.64 — native model-group traversal

The resident `8008A0D8` traversal now runs as a bounded native C routine:
model-group list walking, parameter-table copying, primitive callback setup,
callback-return handling, packet-pointer refresh, and caller restoration.
Both main dispatcher probes and direct generated function entries use it.

This replaces the complete walker, **not the complete model renderer**.
Primitive-specific transformation, subdivision, shading and packet generation
remain in the original callbacks. Unai and the sound implementation are unchanged.
No game FPS improvement is claimed from host tests.

## Contracts

- Guest stack and s0..s4 retain all continuation state; no hidden host coroutine.
- Exact callback address, a0, ra, scratch cursor and global packet pointer.
- Ordinary RAM fast accesses retain watched writes and callback fallback.
- Copy loops re-read lengths after each store, preserving overlapping memory.
- At most 128 copy iterations before a resumable original-loop handoff; at most
  eight empty groups before a resumable native-loop handoff.
- Entry ABI signatures are rechecked after every restore; unsupported entries
  and changed signatures use the original path.
- Detailed block-cycle builds keep the original path.
- Direct generated calls unwind through the existing probe boundary, so a
  primitive callback can suspend, resume, or load a snapshot as before.

## Validation

`python -m unittest tests.test_model_walk_host -v` runs the original resident
MIPS routine in the production interpreter and compares every CPU field, all
RAM and scratchpad at native handoffs. Cases cover random parameters, empty
and multiple groups, several primitive callbacks per group, caller-saved
register changes, packet-pointer updates, cyclic lists, copy-budget fallback,
and code-signature rejection. Each continuation is replayed with no hidden
native state. The test uses only this small traversal reference, not game assets.

The ARM object CI also compiles `fm_model_walk.c` with the pinned PSXRecomp ABI.
A complete linked game and Azahar execution require the user's generated core.

## User check

Load the same in-game quickstate with SELECT+Y. Compare map movement, the
pre-duel deck/chest menu, and a duel/card animation with B136.63. Check that
card art, geometry, text and sound remain correct. No manual profiling capture
is required. If fluidity is unchanged, this walker was not the dominant cost;
that does not demonstrate a gain in the still-original primitive callbacks.
