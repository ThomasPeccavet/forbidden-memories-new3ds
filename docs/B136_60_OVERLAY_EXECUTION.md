# B136.60 — continuous overlay execution and common ARM paths

Inspection found two concrete costs in the B91 dynamic overlay path: returning
from fm_interp_run_block after every MIPS branch, and decoding ordinary
instructions again in the large exec_normal helper after the hot loop had
already decoded their operands.

Overlays now use fm_interp_run_region with 2048-instruction chunks, returning
before execution leaves physical RAM 0x100000..0x1fffff. Thus calls to resident
ARM routines, BIOS and HLE still pass through main.c. Both release and diagnostic
builds check the CPU slice/PS1 deadline between chunks. Up to 32 chunks are
allowed per dispatch visit; the time limit remains authoritative.

The hot loop handles common shifts, integer arithmetic/comparisons, logical
operations, aligned loads and stores in short inline C paths compiled to ARM.
Branch delay slots, control flow, GTE, COP0, multiply/divide and unaligned merges
retain the original helper. RAM access and MMIO callbacks use the same functions;
PROFILE store-PC attribution and watches remain active. This is an interpreter
optimization, not native recompilation of every overlay or a new CPU model.

Differential validation executes 16000 randomized instruction cases against the
production interpreter compiled with FM_INTERP_FAST_COMMON=0. It compares full
CPU state, RAM, stop result and callback stores, including register zero,
signed offsets, aliases and MMIO fallback. A bounded loop with a branch delay
slot and resident return compares continuous vs old block execution exactly:
5001 dispatcher returns become 20. One host run took 22.33ms vs 31.69ms over
100 repeats (~1.42x for this synthetic loop). This is not a 3DS FPS prediction.
Performance remains dependent on how much time the active scene spends in
overlays; resident execution, rasterization and SPU mixing costs remain.

Validation: full host/static suite and ARM C object workflow. Gameplay still
requires the full assets/Azahar on Windows. Test the same duel and deck/chest
menu, card art/stats, AI actions, Start/new game and save/load. Snapshot format
is unchanged from B136.59. No new profiling session is required to try this.
