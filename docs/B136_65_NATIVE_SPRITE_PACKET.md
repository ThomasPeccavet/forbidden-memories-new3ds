# B136.65 — native sprite packet preparation

The uploaded B136.64 ARM ELF confirms that resident 80084978 expands to
3,900 bytes, with repeated RAM-span/callback guards, CPUState traffic and five
static interrupt-check call sites. This is static evidence, not a measured
runtime share or a promised frame-rate increase.

This experiment replaces the complete 95-instruction leaf 80084978..80084AF0
when entered at its beginning. It creates the six-word GPU sprite/environment
packet and inserts it into the ordering table. This is packet preparation,
not rasterization or the complete geometry pipeline.

The native routine checks the full resident instruction sequence, standard
memory callbacks, RAM spans and aliases before writing anything. Arithmetic
uses local values; all guest registers modified by the original routine,
including caller-saved registers and early-return delay-slot effects, are
restored at exit. No persistent host continuation/cache exists. Interior
resumptions, modified code, MMIO/scratchpad, overlapping buffers, watched
writes and detailed-cycle builds keep the original implementation.

There is no inner loop or guest call: successful execution covers at most
95 guest instructions before returning to the existing scheduler. No global
IRQ, VSync, sound or save-state policy is changed. Both dispatcher and direct
generated-call interception paths use the same hook.

Validation: `python -m unittest discover -s tests -p test_sprite_packet_host.py`
compares whole CPU state and 2 MB RAM against the independent MIPS interpreter,
using the exact resident instructions from the supplied snapshot. Randomized
normal/early-return cases and unchanged fallbacks cover RAM mirrors, aliases,
watched addresses, range crossing and modified code. The existing model-walker
regression test remains relevant because both hooks share dispatch integration.

User check: build PROFILE=0 UNAI=1, load the same quick-state, inspect card
art/names, menus and dialogue; then compare movement/duel responsiveness with
B136.64. Check sound and quick-load remain functional. No 30 FPS claim: this
only helps scenes spending appreciable time preparing these sprite packets.
