# B133 — restore source OT submission for menu text

Base: B132 (`fix/b132-menu-text`).

## Purpose

B117 removed the direct submission of the source ordering table before
`GsSortOt`, assuming the later destination-OT / DMA2 path would preserve every
primitive. In the following builds, the main-menu background and selected entry
still rendered, but several static menu labels disappeared.

B133 restores the pre-B117 source-OT submission as a controlled diagnostic:

```c
if (g_hle_85d98_src_tag != 0u)
{
    fm_submit_ot_safe(cpu, g_hle_85d98_src_tag);
}
```

The existing C `GsSortOt`, DMA2 path, B124/B125/B129 GPU fast paths, B131
dirty-frame pacing, and B132 native display capture remain unchanged.

## Expected result

Build marker:

`BUILD B133-RESTORE-SOURCE-OT`

Start from a fresh launch and wait for the main-menu entrance animation to
finish. If the missing static labels return, the regression is tied to the B117
OT submission-path change rather than B132 framebuffer capture.

This diagnostic can render some primitives twice and may cost performance. If it
restores the text, the next step is to fix the OT splice / draw path so the
direct duplicate submission can be removed again without losing primitives.
