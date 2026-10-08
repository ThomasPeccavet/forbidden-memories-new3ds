#ifndef FM_HOST_CLOCK_H
#define FM_HOST_CLOCK_H
#include <stdint.h>
/* 60 Hz wall clock shared by PS1 VBlank and root timers. Millisecond
 * fractions are retained. Long pauses reset instead of replaying input. */
typedef struct { uint64_t last_ms; uint32_t fraction; unsigned valid; } FMHostClock;
static inline void fm_host_clock_reset(FMHostClock *clock) {
    clock->valid=0; clock->fraction=0;
}
static inline unsigned fm_host_clock_due(FMHostClock *clock, uint64_t now) {
    if (!clock->valid || now < clock->last_ms) {
        clock->last_ms=now; clock->fraction=0; clock->valid=1; return 0;
    }
    uint64_t elapsed=now-clock->last_ms; clock->last_ms=now;
    if (elapsed>250u) { clock->fraction=0; return 0; }
    uint32_t phase=clock->fraction+(uint32_t)elapsed*60u;
    unsigned due=phase/1000u; clock->fraction=phase%1000u;
    /* At most four callbacks per slice: discard excess after a long stall. */
    return due>4u ? 4u : due;
}
#endif
