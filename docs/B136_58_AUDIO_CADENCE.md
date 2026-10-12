# B136.58 — audio cadence and short-effect preservation

B136.57 generated SPU output only at display VBlank boundaries, in 16.7ms chunks, and started the DSP immediately with one chunk. Four buffers provided at most 67ms of storage, without any initial reserve. Slow guest execution or file/report operations could starve the DSP. A brief voice could also receive KEY ON and KEY OFF between mixer calls without producing its attack samples.

This build replaces that VBlank-only producer with a 44.1kHz wall-clock accumulator. It renders elapsed samples at each host pass and before SPU register changes or DMA4 sample uploads. A short effect's elapsed waveform is therefore flushed before its key-off/volume/sample data changes. The same main thread owns the synth; no concurrent RAM access, extra guest execution or IRQ delivery is introduced.

The SPU queue now has twelve 16.7ms buffers. Playback starts after six buffers (100ms), leaving a reserve for short host stalls; queue capacity is 200ms. After a complete underrun, playback pauses and rebuilds that reserve. Explicit game pause clears clock debt; debugger/suspend gaps are bounded to 200ms of synthesis. The XA stream remains separate. A single mixer clock prevents duplicate synthesis from simultaneous VBlank/host producers.

## Validation

Host tests cover the six-buffer startup threshold, capacity/backpressure, underrun reprime, unchanged XA queue/rate, exact 100ms sample production without any VBlank, pause/restart without long catch-up, and waveform production before a brief voice is keyed off. Existing snapshot, DMA, BIOS/IRQ and raster tests also pass. SPU snapshot layout is unchanged from B136.57. Pending partial PCM and the host DSP queue are discarded on restore, followed by the new 100ms preroll.

No listening test can be performed here. The starvation path and missed short-voice interval are verified in tests; this does not prove that all game effects use that path. Test normal boot, menu movement and selection, then a duel/card placement. If sound effects remain missing or the music still breaks, `audio-status.txt` now reports DSP status, active voice envelopes, KEY ON/OFF activity, SPU queue submissions, full-queue drops and detected underruns every two seconds. The bottom screen stays blank. There is no FPS gain claim, and the SPU fidelity limits documented for B136.57 remain.
