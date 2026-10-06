#pragma once
#include <stdint.h>
/* The memory module only uses the platform clock for profiling. */
static inline uint64_t osGetTime(void) { return 0; }
