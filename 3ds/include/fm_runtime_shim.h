#pragma once

#include <stdint.h>

#include "cpu_state.h"


/*
 * ============================================================
 * Motifs d'arrêt de la sonde runtime
 * ============================================================
 */

typedef enum FMRuntimeStopReason
{
    FM_STOP_NONE = 0,

    /*
     * Le dispatcher PSXRecomp a rendu la main.
     */
    FM_STOP_RETURNED,

    /*
     * La tranche d'exécution a atteint sa limite.
     */
    FM_STOP_BUDGET,

    /*
     * Syscall PS1 non encore géré complètement.
     */
    FM_STOP_SYSCALL,

    /*
     * Commande GTE non encore implémentée.
     */
    FM_STOP_GTE,

    /*
     * Écriture liée au suivi de précision GTE.
     */
    FM_STOP_GTE_STORE,

    /*
     * Restore / exception demandant un retour contrôlé.
     */
    FM_STOP_RESTORE

} FMRuntimeStopReason;


/*
 * ============================================================
 * Résultat d'une tranche d'exécution
 * ============================================================
 */

typedef struct FMRuntimeProbeResult
{
    /*
     * Pourquoi l'exécution s'est arrêtée.
     */
    FMRuntimeStopReason reason;


    /*
     * Résultat de psx_dispatch_game_compiled()
     *
     *  1 = adresse reconnue et exécutée
     *  0 = adresse inconnue du dispatcher statique
     * -1 = arrêt volontaire de notre sonde
     */
    int dispatch_result;


    /*
     * PC guest après l'exécution.
     */
    uint32_t pc;


    /*
     * Information complémentaire.
     *
     * WATCHDOG :
     *   PC de reprise
     *
     * SYSCALL :
     *   numéro de syscall / fonction
     *
     * GTE :
     *   commande GTE
     *
     * GTE STORE :
     *   informations adresse / registre
     */
    uint32_t detail;


    /*
     * Nombre de checkpoints runtime atteints
     * pendant cette tranche.
     */
    uint32_t checks;

} FMRuntimeProbeResult;


/*
 * ============================================================
 * Exécution du code recompilé
 * ============================================================
 */

FMRuntimeProbeResult fm_runtime_probe(
    CPUState *cpu,
    uint32_t addr,
    uint32_t check_budget
);

/*
 * B135.14 - execute plusieurs dispatchs recompiles consecutifs sous le
 * meme setjmp tant que le PC reste dans une plage resident donnee.
 */
FMRuntimeProbeResult fm_runtime_probe_chain(
    CPUState *cpu,
    uint32_t addr,
    uint32_t check_budget,
    uint32_t phys_begin,
    uint32_t phys_end,
    uint32_t phys2_begin,
    uint32_t phys2_end,
    uint32_t max_dispatches,
    uint32_t *out_dispatches
);


/*
 * Nom lisible du motif d'arrêt.
 */
const char *fm_runtime_stop_name(
    FMRuntimeStopReason reason
);


/*
 * B135 - etat BIOS/HLE persistant necessaire au quick-state.
 * Le contexte de probe/setjmp n'est volontairement jamais serialise.
 */
typedef struct FMRuntimeQuickState
{
    uint32_t bios_entry_hook_addr;
    uint32_t bios_clear_pad;
    uint32_t bios_memory_megabytes;
    uint32_t bios_tty_bytes;

    uint32_t bios_pad_buf1;
    uint32_t bios_pad_buf2;
    uint32_t bios_pad_size1;
    uint32_t bios_pad_size2;
    int32_t bios_pad_started;

    struct
    {
        uint32_t used;
        uint32_t enabled;
        uint32_t ready;
        uint32_t class_id;
        uint32_t spec;
        uint32_t mode;
        uint32_t func;
    } events[32];

    uint32_t irq_chain_heads[8];
    uint32_t change_clear_rcnt[4];
} FMRuntimeQuickState;

void fm_runtime_quick_save(FMRuntimeQuickState *out);
void fm_runtime_quick_load(const FMRuntimeQuickState *in);


/*
 * ============================================================
 * BIOS HLE minimal
 * ============================================================
 */

/*
 * Essaie de traiter une adresse BIOS PS1.
 *
 * addr peut être :
 *
 *   0x000000A0
 *   0x000000B0
 *   0x000000C0
 *
 * ou un alias KSEG0/KSEG1.
 *
 * Retour :
 *
 *   1 = appel BIOS traité
 *   0 = appel inconnu / non encore implémenté
 */
int fm_bios_try_hle(
    CPUState *cpu,
    uint32_t addr
);


/*
 * Renvoie l'adresse du contexte enregistrée par :
 *
 *   B0:19 HookEntryInt(addr)
 *
 * 0 si aucun hook n'a encore été installé.
 */
uint32_t fm_bios_hook_addr(void);