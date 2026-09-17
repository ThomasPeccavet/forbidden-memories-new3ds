#pragma once

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
FMInterpResult fm_interp_run_block(
    CPUState *cpu,
    uint32_t max_instructions
);


const char *fm_interp_stop_name(
    FMInterpStopReason reason
);