#pragma once
#include "cpu_state.h"
/* Exact RAM-only completion of the resident byte-exchange helper.
 * Supports its entry and loop checkpoint; zero means unchanged fallback. */
int fm_sort_swap_try(CPUState *cpu, uint32_t phys);
