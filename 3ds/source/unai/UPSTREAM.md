# Unai renderer provenance

Source: https://github.com/libretro/pcsx_rearmed

Pinned commit: `c8816799b50388e61cfe237fe2cdbb7d8175f20a`

The headers and `gpu_arm.S` are imported from `plugins/gpu_unai/`.
`arm_features.h` and `compiler_features.h` come from upstream `include/`.
Original copyright and GPL-2.0-or-later notices are retained. The license
text is included as `COPYING`. No upstream algorithms have been modified.

The project-specific adapter is `../fm_unai.cpp`; it calls the rasterizers
directly, not PCSX's CD, CPU, scheduler or GPU command-list frontend.
Only 34h–37h, 3Ch–3Fh and 64h–67h are routed through this experiment.
It uses the float/reciprocal polygon options selected by upstream's CTR
build, and the ARMv6 assembly selected by `arm_features.h`.

Pixel skipping, line skipping, frame skipping, fast lighting and dithering
are disabled. Texture windows, masks, source/destination aliasing, wrapping
texture/CLUT addresses, invalid sizes and coordinate overflow fall back.
