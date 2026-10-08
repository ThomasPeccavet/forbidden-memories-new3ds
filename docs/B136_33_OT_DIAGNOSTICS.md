# B136.33 — optional legacy ordering-table inspection

B136.32 duel measurement: 2122 ms, 88 host iterations (41.47/s),
14.60 image latches/s. Pre-presentation work accounts for 1013 ms,
presentation 124 ms, wait 593 ms, residual 340 ms; maximum loop 276 ms.
Audio callback time (132 ms) is nested, not an additional phase.
The deterministic 1/64 native samples do not establish an ARM cost bound.

Legacy B135 hand-packet diagnostics repeatedly walk source/destination
ordering tables, with up to 8192 nodes per inspection. They execute outside
native-call sampling. B136.33 disables the three diagnostic walkers by
 default (`FM_OT_DIAGNOSTICS=0`), in both PROFILE and ordinary builds.
Their output parameters remain zero. Opt in with a compiler definition
`-DFM_OT_DIAGNOSTICS=1` for packet-lifetime investigations; old hand
reachability counters are unavailable otherwise.

The shape predicate used by the B135.64 recovery bridge remains enabled
through a separate functional helper. Sentinel repair, native/C sorting,
DMA submission, rasterization, timer cadence and input are unchanged.
`perf-latest.txt` records `diagnostic_ot_scans=0`.

Host validation compiles actual production walkers with diagnostics on/off:
a 4095-node chain requires over 12000 guest reads for the three enabled
inspections, versus zero disabled reads. Both leave guest RAM untouched;
the functional bridge predicate finds the packet in either mode.
This verifies removed diagnostic work, not a measured FPS improvement.

Reload the same duel quickstate, play about 20 seconds, compare
`perf-latest.txt`, and check that cards/UI remain visible and responsive.
No duel quickstate was provided to the local test environment.
