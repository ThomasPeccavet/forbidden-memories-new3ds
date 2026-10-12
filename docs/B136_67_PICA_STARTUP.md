# B136.67 — PICA startup and disabled-backend cost

B136.66 user evidence: initialized=0 selftest=0, one draw/batch, one 2 MiB
seed/readback. Only the startup probe ran; combat remained on Unai. This is
not a performance measurement of active hardware rendering.

Remove disabled-backend dispatch and cache-invalidation work with an inline
enabled guard. Treat untextured opaque drawing as unconditionally opaque:
alpha testing is needed only for textured zero texels. Encode unmasked alpha
as 128 (vertex 0.5 exactly) instead of 1/255, avoiding float24 quantization
near alpha-test zero. Masked alpha remains 255, decode threshold is 192.
All 65536 seed pixel values still roundtrip exactly.

This is a plausible startup fix, not proof of the observed failure's cause.
Record raw center/mirrored pixel and red pixel count if the self-test still
fails, to distinguish missing draw, orientation and alpha/color packing.
Keep fail-closed startup; do not bypass the test or claim PICA is active.
