# B136.44 — opt-in Unai rendering experiment

## Problem and scope

B136.43 produces 30 presented images over 2006 ms (14.95/s) in the reported
idle duel. DMA2 occupies 641 ms, primarily GP0 parsing/rasterization. This
experiment replaces the hot textured sprites (64h family) and Gouraud
textured triangles/quads (34h/3Ch families) with PCSX ReARMed's Unai renderer,
including its ARMv6 assembly. It is not a replacement PS1 emulator.

Unai is pinned to `c8816799b50388e61cfe237fe2cdbb7d8175f20a`. Source,
copyright and GPL-2.0-or-later notices are under `3ds/source/unai/`.
Its float/reciprocal polygon settings match upstream's New3DS CTR build.

## Integration

`UNAI=0` remains the default reference. `UNAI=1` selects a separate build
directory and executable; switching cannot reuse objects from the other
backend. Both identify themselves as B136.44. The compact report identifies
`renderer=native-reference` or `renderer=unai-experiment` and includes
sprite/polygon/fallback deltas for each reporting window.

The adapter draws into the existing VRAM. Every call supplies drawing area,
offset and page, so quick-load does not depend on cached frontend state.
The native parser still owns packet lengths, page updates, frame visibility
and dirty notifications. All other GP0 commands use the existing renderer.

Fallbacks are decided before writes: texture windows, mask checks/sets,
source/CLUT overlap with the drawing area, wrapping texture/CLUT addresses,
reserved texture depth, invalid dimensions and coordinate overflow. The
experimental backend does not skip pixels, scanlines or frames.

No scheduler, VSync, CD, SEQ, input or bottom-screen behavior is changed.

## Validation and limits

- Host test compares 240 clipped/raw/neutral/modulated sprite cases over all
  three texture depths against the current production native renderer.
  RGB555 agrees exactly; Unai preserves source bit15 where the native opaque
  renderer clears it. This semantic difference is explicit, not hidden by
  a claim of byte-identical VRAM.
- The test checks fallback atomicity, pointer/environment rebinding,
  textured quad coverage and execution of Gouraud/transparency paths.
- ARM compilation checks the assembly structure offsets. CI also partially
  links the C++ and assembly objects and rejects missing rasterizer symbols.
- Existing host component checks continue to run for the native backend.
- Local x86 C++ benchmark (no ARM assembly): three textured quad cases were
  about 1.09–1.51x faster; sprites ranged from 0.79–1.23x. These are isolated
  workloads, not New3DS or Azahar FPS. The experiment can regress.
- Triangle edge/UV/color interpolation differs from the existing renderer;
  pixel-perfect polygon equivalence is not claimed. Inspect cards, text,
  blending, menu and scene backgrounds in the actual game.
- No local ROM/devkitPro/Azahar is available for full-game validation.

## Windows test

Close Azahar first. Pull the active branch, then build the experimental
profile executable:

```powershell
Set-Location "C:\Users\MAO\Documents\forbidden-memories-new3ds"
git pull --ff-only origin fix/b136-spu-dma4-mmio-audit
if ($LASTEXITCODE -ne 0) { throw "Pull échoué." }
& "C:\devkitPro\msys2\usr\bin\bash.exe" -lc 'cd /c/Users/MAO/Documents/forbidden-memories-new3ds && export DEVKITPRO=/opt/devkitpro && export DEVKITARM=/opt/devkitpro/devkitARM && export PATH=/opt/devkitpro/devkitARM/bin:/opt/devkitpro/tools/bin:$PATH && make -C 3ds PROFILE=1 UNAI=1 -j2'
if ($LASTEXITCODE -ne 0) { throw "Compilation échouée." }
$testApp = (Resolve-Path ".\3ds\fm-new3ds-profile-unai.3dsx").Path
$testAzahar = Join-Path $env:LOCALAPPDATA "Programs\Azahar\azahar.exe"
Start-Process -FilePath $testAzahar -ArgumentList "`"$testApp`""
```

Load the same duel quick-state (SELECT+Y). Stay on the idle board for 20
seconds and read the report; then animate a card and read a second report:

```powershell
$testSd = Join-Path $env:APPDATA "Azahar\sdmc\3ds\fm-new3ds"
Get-Content "$testSd\perf-latest.txt"
```

For a reference comparison, close Azahar, repeat the build with `UNAI=0`
and launch `fm-new3ds-profile.3dsx`. Load exactly the same quick-state and
repeat the same idle interval/action. Compare presented-image rate, DMA2
time, opcode cost per call and visible artifacts. The `host_fps_x100` label
still represents the logical PS1 clock rate, not new rendered frames.

Success requires a measurable improvement and acceptable graphics. Neither
30 FPS nor a gain from this backend is guaranteed before this test.
