#pragma once
#include "cpu_state.h"
/* Only declarations needed by the generated memory fixture. The real
 * host test defines these helpers and verifies when they are called. */
uint32_t psx_cyc_load_word(CPUState *,uint32_t,uint32_t,uint32_t);
uint16_t psx_cyc_load_half(CPUState *,uint32_t,uint32_t,uint32_t);
uint8_t psx_cyc_load_byte(CPUState *,uint32_t,uint32_t,uint32_t);
