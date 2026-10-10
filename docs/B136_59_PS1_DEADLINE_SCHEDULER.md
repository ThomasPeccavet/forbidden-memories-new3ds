# B136.59 — PS1 deadline scheduler

The main loop previously updated the PS1 clock before guest execution, then
used the old pending-debt flag when deciding whether to wait for a GSP VBlank.
A tick elapsed during CPU execution/rasterization was invisible to that check.
GSP and the wall-clock PS1 accumulator can have different phases.

The scheduler now queries a read-only deadline, yields at a dispatch boundary
when a PS1 tick is due (even before the first dispatch), and skips sleeping when
execution/presentation has crossed that deadline. While running, an idle wait
uses svcSleepThread until the PS1 deadline rather than a GSP event. Paused
operation still waits for GSP. The existing 12ms work ceiling is retained.

This preserves all clock debt, IRQ eligibility, snapshot layout, and the 60Hz
PS1 rate. CPU blocks and raster commands remain nonpreemptible; this change
cannot guarantee 30 game frames/s or remove their computation cost. Sleep can
overshoot on the host; debt is preserved and recovered on the next pass.

Validation: host deadline tests cover submillisecond remainder, elapsed guest
work, long raster stalls, debt conservation, pause reset and read-only queries.
Full static/host suite and ARM C object workflow run for this build. Full ROM
link and Azahar gameplay are performed on the user's Windows environment.

Gameplay check: use the same combat save, compare menu response, card animation,
AI turns and music; also test Start, new-game intro, save/load and pause/resume.
No additional profiling run is required for the first comparison.
