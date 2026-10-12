# Decoder provenance

`3ds/source/fm_mdec.c`, `3ds/include/mdec.h`, `pst_wire.h` and `psx_align.h`
come from [Unchiga/psxrecomp](https://github.com/Unchiga/psxrecomp), pinned to
`1965b2df424da03483a5370340433a862f78f103`, the same revision used by the
project's generated runtime. Copyright (c) 2026 Matthew Stanley.
The upstream license is preserved in `PSXRecomp-LICENSE.txt` and applies to
these files; the port does not relicense them.

3DS changes: replace the dependency on the full PC peripheral clock with
two local telemetry counters (`fm_mdec_clock.h`), rename those counter
references, release old input/output FIFOs when soft resetting, use bounded
DMA bursts / bulk FIFO output, and expose a low-frequency decode timer.
The RLE, quantization, IDCT and RGB output algorithms are unchanged.

The separately written XA decoder follows the [XA format specification](https://psx-spx.consoledev.net/ps1/cdr/cdromformat/).
Its 4-bit stereo PCM is checked against an independent FFmpeg decoder using
synthetic nonzero sectors, without distributing game audio/video or a ROM.
