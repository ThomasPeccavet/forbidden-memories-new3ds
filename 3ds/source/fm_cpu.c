#include "fm_cpu.h"
#include "fm_memory.h"

#include <string.h>

static CPUState g_cpu;


void fm_cpu_init(uint32_t entry_pc)
{
    memset(
        &g_cpu,
        0,
        sizeof(g_cpu)
    );


    /*
     * Point d'entrée Forbidden Memories FR.
     */
    g_cpu.pc =
        entry_pc;


    /*
     * Stack PS-X EXE.
     */
    g_cpu.gpr[29] =
        0x801FFFF0u;


    /*
     * $zero R3000A.
     */
    g_cpu.gpr[0] =
        0;


    /*
     * ------------------------------------------------------------
     * Raccordement CPU -> mémoire PS1
     * ------------------------------------------------------------
     */

    g_cpu.read_word =
        fm_memory_read_word;

    g_cpu.write_word =
        fm_memory_write_word;

    g_cpu.read_half =
        fm_memory_read_half;

    g_cpu.write_half =
        fm_memory_write_half;

    g_cpu.read_byte =
        fm_memory_read_byte;

    g_cpu.write_byte =
        fm_memory_write_byte;


    /*
     * Etat initial du pipeline load-delay.
     *
     * 0x20 signifie "aucun registre".
     */
    g_cpu.read_absorb_which =
        0x20;

    g_cpu.read_fudge =
        0x20;

    g_cpu.ld_which_t =
        0x20;
}


CPUState *fm_cpu_get(void)
{
    return &g_cpu;
}