# B136.57 — first SPU audio path

The DMA4 bridge previously discarded its payload, and voice-register writes were ignored. This build adds 512KB of SPU RAM, actual DMA4/PIO transfers in both directions, and a software mixer for 24 ADPCM voices. KEY ON/OFF, pitch, loop flags/ENDX, direct/sweeping stereo volumes and ADSR are implemented. PCM runs at 44.1kHz on NDSP channel 1; XA retains channel 0 and its own sample rate/queue.

SPU state advances once per existing wall-clock PS1 VBlank (735 samples), independently of audio-queue availability. Queue pressure drops output, rather than blocking the CPU or its interrupt delivery. Four SPU buffers bound queued latency to approximately 67ms. DMA4 preserves the existing synchronous START/DICR/event completion contract and programmed MADR; transfers larger than 2MB are bounded to 2MB. No render-thread changes, new bottom-screen text or FPS improvement is claimed.

## Verification

77 host tests and static checks pass. Tests cover wrapped sample transfers and DMA4 readback; ADPCM stereo output, looping and ENDX; ADSR release and mute; bit-identical PCM after SPU save/restore; separate NDSP stream ownership/backpressure; malformed snapshots failing before live-state mutation; and importing B136.56 snapshots without an SPU tail. The ARM object workflow compiles the new module and both main frontends. A full linked ROM build and listening test require the user's assets/emulator.

## First listening test

Start normally without loading an old snapshot, allow the title/menu to appear, and navigate the choices. Check music and selection sounds, then enter a duel and compare movement/card effects. Save a new snapshot, play another few seconds and reload it; audio should resume with the scene. Pause/resume and verify both streams pause.

`sdmc:/3ds/fm-new3ds/audio-status.txt` records the DSP initialization result once at startup. `dsp=00000000` means NDSP initialized. Earlier logs showed `D880A7FA`, libctru's missing-DSP-component result. NDSP looks for `/3ds/dspfirm.cdc` or the homebrew `hb:ndsp` component. In Azahar the SD file is `%APPDATA%\Azahar\sdmc\3ds\dspfirm.cdc`. Supply a valid DSP component from your own console/environment if it is absent; this repository does not bundle one. See [libctru's loader](https://github.com/devkitPro/libctru/blob/master/libctru/source/ndsp/ndsp.c).

## Snapshots and limits

New v4 snapshots append a validated SPU state after the existing MDEC section: sample RAM, registers, ADPCM histories, voice positions, envelope/sweep counters and noise state. Existing B136.56 v4 files and eligible v3 files still import, but contain no sample RAM/voices: they remain partial audio imports until the game reloads its sound assets. Old builds reject the new extended payload safely. The SPU NDSP queue is cleared on restore, so up to approximately 67ms of already queued audio is skipped; the synthesizer state resumes exactly.

This is a first audio implementation, not a cycle-exact SPU. It uses linear interpolation instead of the hardware Gaussian filter. Noise is approximate; reverb, capture RAM and SPU address IRQ are not yet synthesized. XA routing through SPU main/CD volumes remains separate. KEY ON is immediate rather than delayed by hardware cycles. The next step is listening validation on menu and duel scenes before adding those fidelity features.

Register, pitch, ADPCM and envelope reference: [PSX-SPX SPU](https://psx-spx.consoledev.net/soundprocessingunitspu/).
