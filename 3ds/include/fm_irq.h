#pragma once
#include "cpu_state.h"
/* HLE external interrupt input IP2: both IEC and IM2 must be enabled.
 * Pending peripheral bits are left latched when this gate is closed. */
static inline int fm_irq_cpu_enabled(const CPUState *cpu)
{ return cpu && (cpu->cop0[12] & 0x401u) == 0x401u; }
