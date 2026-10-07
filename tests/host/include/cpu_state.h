#pragma once
#include <stdint.h>
/* fm_gpu.h only needs the pointer type in this memory-only host test. */
typedef struct CPUState { uint32_t gpr[32], pc; } CPUState;
