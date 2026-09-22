# B132 — native menu display capture

Base: B131 (`46ea564`). The user considers performance acceptable and now wants
readable main-menu choices. The supplied B131 screenshot shows displaced,
repeated labels; the PC reference is `research/first-menu/menu.png`.

## Change

Remove the B103 presentation heuristic that combines non-black pixels from two
PS1 framebuffers, and the density-based substitution of a different page.
Capture the selected 320x256 page when GP1(05) executes, before subsequent guest
work can overwrite it. Even repeated selections of the same coordinates advance
the capture serial. Black pixels remain opaque. Packed RGB24 decoding is retained;
same-page video updates and the existing direct-render completion path can request
an explicit capture. B131 dirty-only presentation and GPU fast paths remain.

This fixes an identified presentation defect; it does not establish that all menu
corruption originates there. A game capture is still needed. If repeated labels
remain, they are already in the selected VRAM page and the next investigation must
follow primitive positions, texture sources, ordering and clears. Do not add
replacement text or restore page blending to conceal that evidence.

## Validation

`python tests/test_gpu_display_capture.py /path/to/pinned/psxrecomp` compiles the
real GPU bridge and upstream renderer on the host with AddressSanitizer and
UndefinedBehaviorSanitizer. It checks capture isolation, opaque black pages,
multiple/same-coordinate flips, X/Y wrapping, RGB24 and reset/rebind behavior.
In ptrace-based containers use `ASAN_OPTIONS=detect_leaks=0` (LeakSanitizer cannot
run under ptrace; address and undefined-behavior checks remain enabled).

`git diff --check` passes. The existing main.c static checker reports the same
pre-existing false positive as B131: decorative `=======` comment separators.
No new checker findings. Full devkitARM linking and in-game validation were not
available in the editing environment.

## User check

Build marker: `BUILD B132-NATIVE-MENU-FRAME`.
Diagnostic: `PAGE native:... xy:.../... merge:OFF`.
Start from a fresh launch, open the main menu, allow its entrance animation to
finish, then capture the menu and diagnostics. Compare centered choices and
background with the PC reference; also check navigation/highlight behavior.
