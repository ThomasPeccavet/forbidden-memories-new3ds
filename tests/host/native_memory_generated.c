/* Representative generated call syntax; compiled unchanged and transformed. */
#include "cpu_state.h"
uint32_t psx_cyc_load_word(CPUState *,uint32_t,uint32_t,uint32_t);
uint16_t psx_cyc_load_half(CPUState *,uint32_t,uint32_t,uint32_t);
uint8_t psx_cyc_load_byte(CPUState *,uint32_t,uint32_t,uint32_t);
uint32_t native_fixture(CPUState *cpu, uint32_t a)
{
    cpu->write_word(a, cpu->gpr[1]);
    cpu->write_half(a + 5u, (uint16_t)cpu->gpr[2]);
    cpu->write_byte(a + 9u, (uint8_t)cpu->gpr[3]);
    return psx_cyc_load_word(cpu,a,1,2) ^ psx_cyc_load_half(cpu,a + 5u,2,4)
        ^ psx_cyc_load_byte(cpu,a + 9u,3,8);
}
