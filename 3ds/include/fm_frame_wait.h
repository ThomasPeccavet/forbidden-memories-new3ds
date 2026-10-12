#pragma once
#include "cpu_state.h"

/* B136.45: recognize only the verified FR resident frame-counter loop.
 * Read-only: the normal checkpoint's VBlank service remains responsible for
 * making the counter ready. Never synthesize a completion or skip the loop. */
static inline int fm_frame_wait_pending(const CPUState *cpu, uint32_t pc)
{
    static const uint32_t words[6] = {
        0x9383018Cu, 0x8F820190u, 0u, 0x0043102Au, 0x1440FFFBu, 0u
    };
    if (!cpu || !cpu->read_word || !cpu->read_byte
        || (pc & 0x1FFFFFFFu) != 0x00012CD4u
        || ((cpu->gpr[28] + 0x18Cu) & 0x1FFFFFFFu) != 0x0009C424u
        || ((cpu->gpr[28] + 0x190u) & 0x1FFFFFFFu) != 0x0009C428u)
        return 0;
    for (unsigned i = 0; i < 6; ++i)
        if (cpu->read_word(0x80012CD4u + i * 4u) != words[i]) return 0;
    return (int32_t)cpu->read_word(cpu->gpr[28] + 0x190u)
        < (int32_t)cpu->read_byte(cpu->gpr[28] + 0x18Cu);
}
