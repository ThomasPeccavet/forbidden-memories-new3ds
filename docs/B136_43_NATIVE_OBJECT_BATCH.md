# B136.43 — batch resident object/packet native execution

B136.42 idle duel spends 1457 ms before presentation, including 618 ms
DMA2 and 181 ms SEQ, leaving roughly 658 ms of other work per 2006 ms.
This remainder does not establish dispatcher cost. Native samples repeatedly
show resident object helpers 84978, 84018, 85824 and related routines.

## Change

Extend the existing single-setjmp native chain to resident object/packet
helpers in [84018,85D98) and [85D9C,89D60). Share the predicate between main
and runtime. The main.c HLE at 85D98 remains excluded; 81Axx wait loops,
VSync, CD entry points and overlay addresses remain outside these new ranges.
Existing four regions stay supported. All blocks still execute their actual
compiled code; unknown compiled entries and runtime stops return to main.

Object entries permit up to 64 native dispatches in one probe. Existing
region entries keep their limit of 16. Every fourth dispatch checks elapsed
host time and returns at >=2 ms; a single compiled function is indivisible,
so this is a soft latency bound, not a guaranteed two-millisecond maximum.
The cumulative instruction watchdog and longjmp stop handling remain intact.
Main regains control to service eligible IRQs and other special handlers.

This batches native execution, not frames or DMA lists. Rendering, draw
ordering, clock frequency, input and synchronization are unchanged.

`native_batch` reports window deltas: main-loop probe calls, chain entries,
and dispatches completed within chains. It excludes probes in isolated IRQ
callbacks. More blocks per chain indicate that batching is being used,
not proof of a given FPS gain. Existing native timing samples may represent
several blocks after this change and should not be compared as single calls.

## Validation and expected test

The host test executes the production chain with a mock compiled dispatcher:
85D98 boundary preserved, block limit, elapsed-time limit, unknown result,
watchdog longjmp and cleanup are checked. The predicate rejects CD/VSync,
81Axx waits and overlays. Existing component tests remain in the suite.
This cannot validate a complete duel without its runtime/ROM/Azahar.

Reload the same idle duel for 20 seconds and send the report. Compare
new_images_fps_x100, pre_guest_input, wait categories and native_batch.
Then play a card to check controls and rendering. No 30 FPS guarantee: the
actual removable dispatcher fraction is still unmeasured.
