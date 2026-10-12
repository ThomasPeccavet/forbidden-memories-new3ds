# B136.68 — remove the duplicate vertical flip

Runtime B136.67 evidence: center=00000080, mirror=FF000080,
red_pixels=64. The GPU drew the expected 8x8 opaque red rectangle, but the
CPU readback looked at the vertically mirrored rows. Alpha/coverage were not
the remaining startup failure; PICA stayed disabled as designed.

Change GX display-transfer flip from 1 to 0 and seed framebuffer tiles in
CPU top-down order. Keep shader clip mapping and sampled-texture orientation
unchanged: texture sampling has a separate contract.

Extend startup with two asymmetric framebuffer-seed markers, including bit15.
Their GPU readback must roundtrip independently of the drawn rectangle. Restore
the 64 drawn CPU pixels and both marker words on success or failure. The test
still fails closed and never activates an unchecked backend.

Expected startup: initialized=1 selftest=1 seed_ok=1. Center RGB is red;
its mirrored counterpart is no longer the diagnostic rectangle. This is a
correctness fix supported by runtime pixels, not a measured speed gain.
