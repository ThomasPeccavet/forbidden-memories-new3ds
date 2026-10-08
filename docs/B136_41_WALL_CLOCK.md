# B136.41 — continue budget slices with an independent VBlank clock

B136.40 idle duel: 88 slices / 28 images, 60 budget yields, 285 ms waiting
in 30 budget-yield loops and 196 ms with guest VSync active. This supports
continuing budget slices, but deleting waits while keeping one PS1 timer
step per slice would accelerate the game clock.

## Scheduling change

The guest slice budget remains 12 ms. When a slice exhausted that budget,
no guest VSync is active and work is below 16 ms, skip the host VBlank
wait and return to guest work. Over-budget work retains the existing no
wait behavior. Active guest VSync and other short loops retain the host
wait. Presentation still uses existing stable boundaries.

PS1 VBlank, root timers (including Timer2/SEQ), and guest VBlank callbacks
now advance from a 60 Hz elapsed host-millisecond clock rather than one
step per slice. Fractional time is retained: different slice counts yield
the same number of clock ticks. This preserves the port's existing 60 Hz
basis, not a new PAL/NTSC timing implementation. Timer IRQ isolation,
registered callbacks and IRQ gates are unchanged.

Catch-up is limited to four ticks per loop; excess ticks are discarded
rather than building an unbounded ISR backlog. A pause over 250 ms or
host time reversal resets the phase. Quick-load resets the wall-clock
anchor, while retaining the restored logical frame counter. These limits
avoid replaying a long interval of stale input after a pause.

The report adds `ps1_clock=wall_60hz ticks=... budget_wait_skips=...`.
`wait_reasons` now labels the no-wait category `no_wait_loops`: it includes
both late loops and budget continuations. Categories remain observations,
not a precise causal trace. The same complete GPU timing stays enabled.

## Validation and limits

Host clock tests simulate 1/7/12/17/23/33/50 ms slices: all give exactly
600 ticks in ten seconds. Pause, bounded catch-up, reversal and quick-load
reset are checked. The reporter test verifies clock and skip deltas.
Existing rendering, CD, isolated SEQ and timer tests pass.

This changes scheduler timing and requires Azahar validation. Local tests
cannot prove visual cadence, audible music speed, input edges across all
scenes, or whole-game FPS. Reload the same duel, leave idle 20 seconds and
check clock ticks near 120 per two-second window, skip counts, image rate,
card animation pace and controls. No measured FPS improvement is claimed.
