#pragma once
#include "cpu_state.h"
/* Native resident model-group walker. Returns 0 without changing state when
 * the entry is unsupported; returns 1 with a normal guest continuation. */
int fm_model_walk_try(CPUState *cpu, uint32_t address);
