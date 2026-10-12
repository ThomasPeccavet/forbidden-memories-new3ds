# B136.42 — service elapsed VBlanks before guest execution

B136.41 user window: 121 clock ticks / 2023 ms, 31 budget wait skips,
but 53 VSync wait loops / 24 VSync completions and 11.86 image latches/s.
The independent clock works, yet waits move to VSync (704 ms). This does
not demonstrate that all those waits are redundant, but exposes an ordering
problem: elapsed time from the host wait was serviced only after the next
guest slice had already retested VSync with an old frame counter.

Move the existing bounded clock/callback block before guest execution and
after input and quick-load handling. Guest VSync now sees clock ticks that
elapsed during the previous host wait. Refresh the MDEC host frame/cycle
view after those ticks. No changes to clock frequency, pause/catch-up limits,
IRQ isolation, timer deltas, budget, host wait policy or presentation gates.
The moved block retains startup bookkeeping and callback order internally.

Host tests verify there is exactly one clock service block, before dispatch
and after quick-load handling, and that the MDEC view is refreshed. Clock
cadence and existing component tests remain in the suite. No Azahar FPS
improvement is claimed before a same-state measurement. Input, boot and
animation cadence should also be checked because callback ordering changes.

Compare vsync_loops, vsync_completed, clock ticks and new_images_fps_x100.
Clock ticks should stay near 120 per two-second window. A lower ratio of
wait loops to completions would support the ordering hypothesis.
