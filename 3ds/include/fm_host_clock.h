#ifndef FM_HOST_CLOCK_H
#define FM_HOST_CLOCK_H
#include <stdint.h>
/* B136.54: retain every elapsed tick during gameplay. Bound delivery to
 * eight callbacks per host pass; excess ticks remain queued for later passes.
 * Only explicit pause, suspend, quick-load or time reversal drops the debt. */
#define FM_HOST_CLOCK_BATCH 8u
typedef struct {
    uint64_t last_ms, pending;
    uint32_t fraction;
    unsigned valid;
} FMHostClock;
static inline void fm_host_clock_reset(FMHostClock *clock) {
    clock->valid=0; clock->fraction=0; clock->pending=0;
}
static inline unsigned fm_host_clock_due(FMHostClock *clock, uint64_t now) {
    if (!clock->valid || now < clock->last_ms) {
        clock->last_ms=now; clock->fraction=0; clock->pending=0;
        clock->valid=1; return 0;
    }
    uint64_t elapsed=now-clock->last_ms; clock->last_ms=now;
    /* Split milliseconds to avoid the old 32-bit elapsed truncation. */
    uint32_t phase=clock->fraction+(uint32_t)(elapsed%1000u)*60u;
    clock->pending+=(elapsed/1000u)*60u+phase/1000u;
    clock->fraction=phase%1000u;
    unsigned due=clock->pending>FM_HOST_CLOCK_BATCH
        ? FM_HOST_CLOCK_BATCH : (unsigned)clock->pending;
    clock->pending-=due;
    return due;
}
static inline unsigned fm_host_clock_update(FMHostClock *clock, uint64_t now,
    int running) {
    if (!running) { fm_host_clock_reset(clock); return 0; }
    return fm_host_clock_due(clock,now);
}
static inline int fm_host_clock_pending(const FMHostClock *clock) {
    return clock->pending!=0;
}
/* Read-only deadline: execution and presentation may have consumed a tick
 * since the last clock update. Never advance/drop ticks from this query. */
static inline uint64_t fm_host_clock_wait_ns(const FMHostClock *clock,
    uint64_t now) {
    if (!clock->valid || now < clock->last_ms) return 16666667u;
    if (clock->pending) return 0u;
    uint64_t elapsed=now-clock->last_ms;
    if (elapsed >= 17u) return 0u;
    uint32_t phase=clock->fraction+(uint32_t)elapsed*60u;
    if (phase >= 1000u) return 0u;
    return ((uint64_t)(1000u-phase)*1000000u+59u)/60u;
}
#endif
