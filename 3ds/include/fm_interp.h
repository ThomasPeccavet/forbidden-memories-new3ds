#pragma once

#include <stddef.h>
#include <stdint.h>

#include "cpu_state.h"


typedef enum FMInterpStopReason
{
    FM_INTERP_NONE = 0,

    /*
     * Un basic block MIPS complet a été exécuté.
     *
     * cpu->pc contient la prochaine adresse.
     */
    FM_INTERP_BLOCK_DONE,

    /*
     * Trop d'instructions en ligne droite.
     */
    FM_INTERP_BUDGET,

    /*
     * SYSCALL non supporté.
     */
    FM_INTERP_SYSCALL,

    /*
     * Commande GTE rencontrée.
     */
    FM_INTERP_GTE,

    /*
     * Opcode MIPS que notre fallback ne connaît pas encore.
     */
    FM_INTERP_UNSUPPORTED

} FMInterpStopReason;


typedef struct FMInterpResult
{
    FMInterpStopReason reason;

    /*
     * Dernier PC interprété.
     */
    uint32_t pc;

    /*
     * Instruction correspondante.
     */
    uint32_t instruction;

    /*
     * Nombre d'instructions exécutées.
     */
    uint32_t instructions;

} FMInterpResult;


/*
 * Exécute un basic block R3000A.
 *
 * L'interpréteur rend la main après un :
 *
 *   J
 *   JAL
 *   JR
 *   JALR
 *   BEQ/BNE/...
 *
 * delay slot inclus.
 */
/*
 * B135.18 - bind the PS1 RAM backing so the hot fallback interpreter can
 * fetch resident code and ordinary RAM data without a function-pointer
 * round trip through the full MMIO decoder on every MIPS instruction.
 */
void fm_interp_bind_ram(
    uint8_t *ram,
    size_t ram_size
);


FMInterpResult fm_interp_run_block(
    CPUState *cpu,
    uint32_t max_instructions
);


/*
 * B135.19 - execute continuously across branch/basic-block boundaries while
 * the next PC remains inside one hot resident region. This avoids returning
 * to main.c after every tiny MIPS basic block.
 *
 * stop_phys is handed back to the native dispatcher even when it lies in
 * the region (used for the real compiled function entry 0x00034D30).
 */
FMInterpResult fm_interp_run_region(
    CPUState *cpu,
    uint32_t max_instructions,
    uint32_t phys_begin,
    uint32_t phys_end,
    uint32_t stop_phys
);


const char *fm_interp_stop_name(
    FMInterpStopReason reason
);