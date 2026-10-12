# B136.40 — attribute host waits without changing clocks

B136.39 cut average idle sprite cost from 172 to 85 us, but latches only
increased from 13.47 to 13.95/s. Host waiting increased from 281 to 491 ms.
The port slices guest work at 12 ms, advances synthetic PS1 VBlank once
per host iteration and waits for host VBlank if work took less than 16 ms.
Removing that wait alone could accelerate PS1/SEQ clocks.

This diagnostic keeps the existing schedule unchanged and reports:

- `wait_reasons budget_ms/budget_loops`: a host wait in a loop that
  incremented the budget-yield counter. This takes attribution priority.
- `vsync_ms/vsync_loops`: remaining host waits with a guest VSync active
  at the end-of-loop wait decision.
- `other_ms/other_loops`: remaining host waits.
- `late_skips`: loops skipping the host wait because work took >=16 ms.
- `scheduler`: current slice budget and per-window budget yields, VSync
  mode0/modeN/immediate calls and VSync completions.

These are observations at the wait decision, not proof of causal waste.
A budget yield can coincide with a VSync flag, and VSync completion can
happen earlier in the same loop. Wait milliseconds sum to existing wait
milliseconds; loop categories sum to window samples. Millisecond rounding
remains. DMA submissions are not assumed to be complete game frames.

The reporter host test exercises all four categories and exact counter
window deltas. Existing rendering/SEQ tests remain unchanged. No new
per-pixel timing or SD dumps; compact report remains every two seconds.

Reload the same duel state, wait idle for 20 seconds, then send the report.
If budget-attributed waiting dominates, design a decoupled clock before
attempting immediate continuation. If VSync dominates, inspect caller
modes and guest frame boundaries first. No FPS claim for this build.
