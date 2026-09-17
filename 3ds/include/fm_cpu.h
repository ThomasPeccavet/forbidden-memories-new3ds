#pragma once

#include <stdint.h>
#include "cpu_state.h"

void fm_cpu_init(uint32_t entry_pc);
CPUState *fm_cpu_get(void);