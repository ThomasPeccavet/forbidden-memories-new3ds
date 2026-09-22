#include "fm_runtime_shim.h"
#include "fm_memory.h"
#include "fm_gpu.h"

#include <setjmp.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>


extern int psx_dispatch_game_compiled(
    CPUState *cpu,
    uint32_t addr
);


/*
 * ============================================================
 * Globals PSXRecomp
 * ============================================================
 */

uint32_t g_debug_last_store_pc = 0;

int g_psx_cps_mode = 0;

volatile uint32_t g_psx_last_fn_entry = 0;


/*
 * ============================================================
 * BIOS state
 * ============================================================
 */

static uint32_t g_bios_entry_hook_addr = 0;

static uint32_t g_bios_clear_pad = 0;

static uint32_t g_bios_memory_megabytes = 2;

static uint32_t g_bios_tty_bytes = 0;

static uint32_t g_bios_pad_buf1 = 0;
static uint32_t g_bios_pad_buf2 = 0;

static uint32_t g_bios_pad_size1 = 0;
static uint32_t g_bios_pad_size2 = 0;

static int g_bios_pad_started = 0;


/*
 * ============================================================
 * BIOS event system
 * ============================================================
 *
 * Handles are exposed as:
 *
 *   F1000000 | index
 *
 * This is sufficient for the Psy-Q event API used by the game
 * during bring-up.
 */

#define FM_BIOS_EVENT_COUNT 32u
#define FM_BIOS_EVENT_HANDLE_BASE 0xF1000000u

typedef struct FM_BiosEvent
{
    uint32_t used;
    uint32_t enabled;
    uint32_t ready;

    uint32_t class_id;
    uint32_t spec;
    uint32_t mode;
    uint32_t func;
} FM_BiosEvent;


static FM_BiosEvent g_bios_events[
    FM_BIOS_EVENT_COUNT
];


static int fm_bios_event_index(
    uint32_t handle
)
{
    if (
        (
            handle
            &
            0xFFFFFF00u
        )
        !=
        FM_BIOS_EVENT_HANDLE_BASE
    )
    {
        return -1;
    }


    uint32_t index =
        handle
        &
        0xFFu;


    if (index >= FM_BIOS_EVENT_COUNT)
    {
        return -1;
    }


    return
        (int)index;
}


/*
 * ============================================================
 * BIOS jump tables
 * ============================================================
 */

#define FM_BIOS_C0_TABLE_ADDR           0x00000674u
#define FM_BIOS_B0_TABLE_ADDR           0x00000874u
#define FM_BIOS_C0_EXCEPTION_HANDLER    0x00000C80u


#define FM_BIOS_IRQ_CHAINS 8u

static uint32_t g_bios_irq_chain_heads[
    FM_BIOS_IRQ_CHAINS
] = { 0 };


#define FM_BIOS_RCNT_COUNT 4u

static uint32_t g_bios_change_clear_rcnt[
    FM_BIOS_RCNT_COUNT
] = { 0, 0, 0, 0 };


/*
 * ============================================================
 * Probe
 * ============================================================
 */

static jmp_buf g_probe_jmp;

static int g_probe_armed = 0;

static uint32_t g_probe_budget = 0;

static uint32_t g_probe_checks = 0;

static FMRuntimeStopReason g_probe_reason =
    FM_STOP_NONE;

static uint32_t g_probe_detail = 0;

static CPUState *g_probe_cpu = NULL;


/*
 * ============================================================
 * BIOS jump tables helper
 * ============================================================
 */

static void fm_bios_prepare_jump_tables(
    CPUState *cpu
)
{
    if (
        !cpu
        ||
        !cpu->read_word
        ||
        !cpu->write_word
    )
    {
        return;
    }


    /*
     * La RAM basse n'est pas initialisée par un vrai BIOS dans
     * notre bring-up.
     *
     * C0[06] = ExceptionHandler = 0x00000C80.
     */
    uint32_t c0_exception_entry =
        FM_BIOS_C0_TABLE_ADDR
        +
        (6u * 4u);


    if (
        cpu->read_word(
            c0_exception_entry
        )
        ==
        0
    )
    {
        cpu->write_word(
            c0_exception_entry,
            FM_BIOS_C0_EXCEPTION_HANDLER
        );
    }
}


/*
 * ============================================================
 * Controlled stop
 * ============================================================
 */

static void fm_probe_stop(
    FMRuntimeStopReason reason,
    uint32_t detail
)
{
    if (!g_probe_armed)
    {
        return;
    }


    g_probe_reason =
        reason;


    g_probe_detail =
        detail;


    longjmp(
        g_probe_jmp,
        1
    );
}


/*
 * ============================================================
 * Runtime probe
 * ============================================================
 */

FMRuntimeProbeResult fm_runtime_probe(
    CPUState *cpu,
    uint32_t addr,
    uint32_t check_budget
)
{
    FMRuntimeProbeResult result;


    result.reason =
        FM_STOP_NONE;


    result.dispatch_result =
        -1;


    result.pc =
        cpu
            ? cpu->pc
            : 0;


    result.detail =
        0;


    result.checks =
        0;


    if (!cpu)
    {
        return result;
    }


    g_probe_cpu =
        cpu;


    g_probe_budget =
        check_budget;


    g_probe_checks =
        0;


    g_probe_reason =
        FM_STOP_NONE;


    g_probe_detail =
        0;


    g_probe_armed =
        1;


    int jumped =
        setjmp(
            g_probe_jmp
        );


    if (jumped == 0)
    {
        int dispatched =
            psx_dispatch_game_compiled(
                cpu,
                addr
            );


        g_probe_armed =
            0;


        result.reason =
            FM_STOP_RETURNED;


        result.dispatch_result =
            dispatched;
    }
    else
    {
        g_probe_armed =
            0;


        result.reason =
            g_probe_reason;


        result.dispatch_result =
            -1;
    }


    result.pc =
        cpu->pc;


    result.detail =
        g_probe_detail;


    result.checks =
        g_probe_checks;


    g_probe_cpu =
        NULL;


    return result;
}


/*
 * ============================================================
 * Stop reason
 * ============================================================
 */

const char *fm_runtime_stop_name(
    FMRuntimeStopReason reason
)
{
    switch (reason)
    {
        case FM_STOP_RETURNED:
            return "RETURN";

        case FM_STOP_BUDGET:
            return "WATCHDOG";

        case FM_STOP_SYSCALL:
            return "SYSCALL";

        case FM_STOP_GTE:
            return "GTE";

        case FM_STOP_GTE_STORE:
            return "GTE STORE";

        case FM_STOP_RESTORE:
            return "RESTORE";

        default:
            return "NONE";
    }
}


/*
 * ============================================================
 * B135 - quick-state BIOS/HLE
 * ============================================================
 */
void fm_runtime_quick_save(
    FMRuntimeQuickState *out
)
{
    if (!out)
    {
        return;
    }

    memset(out, 0, sizeof(*out));

    out->bios_entry_hook_addr = g_bios_entry_hook_addr;
    out->bios_clear_pad = g_bios_clear_pad;
    out->bios_memory_megabytes = g_bios_memory_megabytes;
    out->bios_tty_bytes = g_bios_tty_bytes;

    out->bios_pad_buf1 = g_bios_pad_buf1;
    out->bios_pad_buf2 = g_bios_pad_buf2;
    out->bios_pad_size1 = g_bios_pad_size1;
    out->bios_pad_size2 = g_bios_pad_size2;
    out->bios_pad_started = g_bios_pad_started;

    for (unsigned i = 0u; i < FM_BIOS_EVENT_COUNT; ++i)
    {
        out->events[i].used = g_bios_events[i].used;
        out->events[i].enabled = g_bios_events[i].enabled;
        out->events[i].ready = g_bios_events[i].ready;
        out->events[i].class_id = g_bios_events[i].class_id;
        out->events[i].spec = g_bios_events[i].spec;
        out->events[i].mode = g_bios_events[i].mode;
        out->events[i].func = g_bios_events[i].func;
    }

    memcpy(
        out->irq_chain_heads,
        g_bios_irq_chain_heads,
        sizeof(g_bios_irq_chain_heads)
    );

    memcpy(
        out->change_clear_rcnt,
        g_bios_change_clear_rcnt,
        sizeof(g_bios_change_clear_rcnt)
    );
}


void fm_runtime_quick_load(
    const FMRuntimeQuickState *in
)
{
    if (!in)
    {
        return;
    }

    g_bios_entry_hook_addr = in->bios_entry_hook_addr;
    g_bios_clear_pad = in->bios_clear_pad;
    g_bios_memory_megabytes = in->bios_memory_megabytes;
    g_bios_tty_bytes = in->bios_tty_bytes;

    g_bios_pad_buf1 = in->bios_pad_buf1;
    g_bios_pad_buf2 = in->bios_pad_buf2;
    g_bios_pad_size1 = in->bios_pad_size1;
    g_bios_pad_size2 = in->bios_pad_size2;
    g_bios_pad_started = in->bios_pad_started;

    for (unsigned i = 0u; i < FM_BIOS_EVENT_COUNT; ++i)
    {
        g_bios_events[i].used = in->events[i].used;
        g_bios_events[i].enabled = in->events[i].enabled;
        g_bios_events[i].ready = in->events[i].ready;
        g_bios_events[i].class_id = in->events[i].class_id;
        g_bios_events[i].spec = in->events[i].spec;
        g_bios_events[i].mode = in->events[i].mode;
        g_bios_events[i].func = in->events[i].func;
    }

    memcpy(
        g_bios_irq_chain_heads,
        in->irq_chain_heads,
        sizeof(g_bios_irq_chain_heads)
    );

    memcpy(
        g_bios_change_clear_rcnt,
        in->change_clear_rcnt,
        sizeof(g_bios_change_clear_rcnt)
    );

    g_probe_armed = 0;
    g_probe_budget = 0u;
    g_probe_checks = 0u;
    g_probe_reason = FM_STOP_NONE;
    g_probe_detail = 0u;
    g_probe_cpu = NULL;
}


/*
 * ============================================================
 * Static-code dirty checks
 * ============================================================
 */

int dirty_ram_text_native_ok_ranges_from(
    const uint32_t *lo_len_pairs,
    uint32_t count,
    uint32_t exec_pc
)
{
    (void)lo_len_pairs;
    (void)count;
    (void)exec_pc;


    return 1;
}


int dirty_ram_text_native_ok_ranges(
    const uint32_t *lo_len_pairs,
    uint32_t count
)
{
    (void)lo_len_pairs;
    (void)count;


    return 1;
}


/*
 * ============================================================
 * Memory helpers expected by generated code
 * ============================================================
 */

uint32_t psx_read_word(
    uint32_t addr
)
{
    return
        fm_memory_read_word(
            addr
        );
}


uint16_t psx_read_half(
    uint32_t addr
)
{
    return
        fm_memory_read_half(
            addr
        );
}


uint8_t psx_cyc_load_byte(
    CPUState *cpu,
    uint32_t addr,
    uint32_t rt,
    uint32_t reg_mask
)
{
    (void)cpu;
    (void)rt;
    (void)reg_mask;


    return
        fm_memory_read_byte(
            addr
        );
}


uint32_t psx_cyc_lwc2_read(
    CPUState *cpu,
    uint32_t addr
)
{
    (void)cpu;


    return
        fm_memory_read_word(
            addr
        );
}


/*
 * ============================================================
 * Forbidden Memories VBlank bridge
 * ============================================================
 *
 * Le runtime 3DS n'exécute pas encore toute la chaîne d'exception
 * R3000A/BIOS. Le jeu attend pourtant qu'un callback VBlank mette
 * à jour ses compteurs logiciels.
 *
 * Tant que l'IRQ VBlank est pendante ET masquée active, reproduire
 * uniquement les deux effets observés nécessaires au bring-up:
 *
 *   80093EE8 : compteur VSync global
 *   8009C428 : compteur/sémaphore de frame attendu par 80012CB8
 *
 * Puis acquitter uniquement VBlank dans I_STAT.
 *
 * Cette passerelle est volontairement ciblée; elle pourra être
 * retirée lorsque la livraison IRQ R3000A complète sera portée.
 */

static void fm_runtime_service_vblank_hle(
    CPUState *cpu
)
{
    if (!cpu)
    {
        return;
    }


    uint16_t pending =
        fm_memory_i_stat()
        &
        fm_memory_i_mask();


    if (
        (
            pending
            &
            0x0001u
        )
        ==
        0
    )
    {
        return;
    }


    /*
     * VSync software counter.
     */
    uint32_t vsync_count =
        cpu->read_word(
            0x80093EE8u
        );


    cpu->write_word(
        0x80093EE8u,
        vsync_count + 1u
    );


    /*
     * FUN_80012CB8 attend:
     *
     *   DAT_8009C428 >= DAT_8009C424
     *
     * DAT_8009C424 est un petit compteur/objectif de frame.
     * Sur hardware réel il est satisfait par la chaîne VBlank.
     */
    uint32_t frame_target =
        cpu->read_byte(
            0x8009C424u
        );


    int32_t frame_done =
        (int32_t)
            cpu->read_word(
                0x8009C428u
            );


    if (
        frame_done
        <
        (int32_t)frame_target
    )
    {
        cpu->write_word(
            0x8009C428u,
            frame_target
        );
    }


    /*
     * I_STAT est "write 0 to clear / write 1 to keep".
     * 0x07FE efface seulement VBlank (bit0).
     */
    fm_memory_write_word(
        0x1F801070u,
        0x000007FEu
    );
}


/*
 * ============================================================
 * Interrupt checkpoints
 * ============================================================
 */

void psx_check_interrupts_at(
    CPUState *cpu,
    uint32_t resume_pc
)
{
    /*
     * Service VBlank avant le watchdog. Cela permet aux boucles
     * guest de synchronisation image de voir progresser leurs
     * compteurs logiciels au prochain checkpoint généré.
     */
    fm_runtime_service_vblank_hle(
        cpu
    );


    if (!g_probe_armed)
    {
        return;
    }


    ++g_probe_checks;


    if (cpu)
    {
        cpu->pc =
            resume_pc;
    }


    if (
        g_probe_budget != 0
        &&
        g_probe_checks >= g_probe_budget
    )
    {
        fm_probe_stop(
            FM_STOP_BUDGET,
            resume_pc
        );
    }
}


void psx_check_interrupts_dispatch_entry(
    CPUState *cpu,
    uint32_t resume_pc
)
{
    psx_check_interrupts_at(
        cpu,
        resume_pc
    );
}


/*
 * ============================================================
 * Restore
 * ============================================================
 */

void psx_restore_state_escape(void)
{
    fm_probe_stop(
        FM_STOP_RESTORE,
        g_probe_cpu
            ? g_probe_cpu->pc
            : 0
    );
}


/*
 * ============================================================
 * SYSCALL
 * ============================================================
 */

int psx_syscall(
    CPUState *cpu,
    uint32_t code
)
{
    (void)code;


    if (!cpu)
    {
        return 1;
    }


    uint32_t func =
        cpu->gpr[4];


    uint32_t sr =
        cpu->cop0[12];


    switch (func)
    {
        /*
         * EnterCriticalSection
         */
        case 1:
        {
            cpu->gpr[2] =
                sr & 1u;


            cpu->cop0[12] =
                sr & ~1u;


            cpu->pc =
                0;


            cpu->gpr[0] =
                0;


            return 0;
        }


        /*
         * ExitCriticalSection
         */
        case 2:
        {
            cpu->cop0[12] =
                sr | 0x0401u;


            cpu->pc =
                0;


            cpu->gpr[0] =
                0;


            return 0;
        }


        case 3:
        {
            if (g_probe_armed)
            {
                fm_probe_stop(
                    FM_STOP_SYSCALL,
                    func
                );
            }


            return 1;
        }


        default:
        {
            if (g_probe_armed)
            {
                fm_probe_stop(
                    FM_STOP_SYSCALL,
                    func
                );
            }


            return 1;
        }
    }
}


/*
 * ============================================================
 * BIOS HLE
 * ============================================================
 */

int fm_bios_try_hle(
    CPUState *cpu,
    uint32_t addr
)
{
    if (!cpu)
    {
        return 0;
    }


    uint32_t phys =
        addr
        &
        0x1FFFFFFFu;


    uint32_t fn =
        cpu->gpr[9]
        &
        0xFFu;


    /*
     * ========================================================
     * Psy-Q internal PAD patch helpers
     *
     * Observed addresses:
     *
     *   0x884 -> SetPadEnableFlag
     *   0x894 -> ClearPadEnableFlag
     * ========================================================
     */

    if (
        phys == 0x00000884u
        ||
        phys == 0x00000894u
    )
    {
        cpu->pc =
            cpu->gpr[31];


        cpu->gpr[0] =
            0;


        return 1;
    }


    /*
     * ========================================================
     * A0 BIOS
     * ========================================================
     */

    if (phys == 0x000000A0u)
    {
        /*
         * GPU BIOS family A0:46..A0:4E.
         */
        if (
            fn >= 0x46u
            &&
            fn <= 0x4Eu
        )
        {
            if (
                fm_gpu_bios_call(
                    cpu,
                    fn
                )
            )
            {
                return 1;
            }
        }


        switch (fn)
        {
            /*
             * A0:44 FlushCache
             */
            case 0x44:
            {
                cpu->pc =
                    cpu->gpr[31];


                cpu->gpr[0] =
                    0;


                return 1;
            }


            /*
             * A0:54 / A0:71 _96_init()
             */
            case 0x54:
            case 0x71:
            {
                cpu->pc =
                    cpu->gpr[31];


                cpu->gpr[0] =
                    0;


                return 1;
            }


            /*
             * A0:55 / A0:70 _bu_init()
             */
            case 0x55:
            case 0x70:
            {
                cpu->pc =
                    cpu->gpr[31];


                cpu->gpr[0] =
                    0;


                return 1;
            }


            /*
             * A0:72 _96_remove
             */
            case 0x72:
            {
                cpu->gpr[2] =
                    0;


                cpu->pc =
                    cpu->gpr[31];


                cpu->gpr[0] =
                    0;


                return 1;
            }


            /*
             * A0:9F SetMem
             */
            case 0x9F:
            {
                uint32_t requested =
                    cpu->gpr[4];


                if (
                    requested == 2u
                    ||
                    requested == 8u
                )
                {
                    g_bios_memory_megabytes =
                        requested;
                }


                cpu->pc =
                    cpu->gpr[31];


                cpu->gpr[0] =
                    0;


                return 1;
            }


            default:
            {
                return 0;
            }
        }
    }


    /*
     * ========================================================
     * B0 BIOS
     * ========================================================
     */

    if (phys == 0x000000B0u)
    {
        switch (fn)
        {
            /*
             * ------------------------------------------------
             * B0:07 DeliverEvent(class, spec)
             * ------------------------------------------------
             */
            case 0x07:
            {
                uint32_t class_id =
                    cpu->gpr[4];


                uint32_t spec =
                    cpu->gpr[5];


                for (
                    unsigned i = 0;
                    i < FM_BIOS_EVENT_COUNT;
                    ++i
                )
                {
                    FM_BiosEvent *ev =
                        &g_bios_events[i];


                    if (
                        !ev->used
                        ||
                        !ev->enabled
                        ||
                        ev->class_id != class_id
                        ||
                        ev->spec != spec
                    )
                    {
                        continue;
                    }


                    /*
                     * Mode 0x2000 = no callback.
                     *
                     * Le prochain TestEvent/WaitEvent verra
                     * l'événement READY.
                     */
                    if (ev->mode == 0x2000u)
                    {
                        ev->ready =
                            1;
                    }


                    /*
                     * Mode 0x1000 utilise normalement un callback.
                     *
                     * Pour ce bring-up on ne lance pas encore
                     * de callback guest imbriqué depuis le BIOS HLE.
                     * On marque quand même l'événement READY afin
                     * d'éviter de bloquer les chemins qui le testent.
                     */
                    if (ev->mode == 0x1000u)
                    {
                        ev->ready =
                            1;
                    }
                }


                cpu->gpr[2] =
                    1;


                cpu->pc =
                    cpu->gpr[31];


                cpu->gpr[0] =
                    0;


                return 1;
            }


            /*
             * ------------------------------------------------
             * B0:08 OpenEvent(class, spec, mode, func)
             * ------------------------------------------------
             */
            case 0x08:
            {
                int slot =
                    -1;


                for (
                    unsigned i = 0;
                    i < FM_BIOS_EVENT_COUNT;
                    ++i
                )
                {
                    if (!g_bios_events[i].used)
                    {
                        slot =
                            (int)i;

                        break;
                    }
                }


                if (slot < 0)
                {
                    cpu->gpr[2] =
                        0xFFFFFFFFu;
                }
                else
                {
                    FM_BiosEvent *ev =
                        &g_bios_events[slot];


                    ev->used =
                        1;


                    ev->enabled =
                        0;


                    ev->ready =
                        0;


                    ev->class_id =
                        cpu->gpr[4];


                    ev->spec =
                        cpu->gpr[5];


                    ev->mode =
                        cpu->gpr[6];


                    ev->func =
                        cpu->gpr[7];


                    cpu->gpr[2] =
                        FM_BIOS_EVENT_HANDLE_BASE
                        |
                        (uint32_t)slot;
                }


                cpu->pc =
                    cpu->gpr[31];


                cpu->gpr[0] =
                    0;


                return 1;
            }


            /*
             * ------------------------------------------------
             * B0:09 CloseEvent(event)
             * ------------------------------------------------
             */
            case 0x09:
            {
                int index =
                    fm_bios_event_index(
                        cpu->gpr[4]
                    );


                if (index >= 0)
                {
                    g_bios_events[index].used =
                        0;


                    g_bios_events[index].enabled =
                        0;


                    g_bios_events[index].ready =
                        0;


                    g_bios_events[index].class_id =
                        0;


                    g_bios_events[index].spec =
                        0;


                    g_bios_events[index].mode =
                        0;


                    g_bios_events[index].func =
                        0;
                }


                cpu->gpr[2] =
                    1;


                cpu->pc =
                    cpu->gpr[31];


                cpu->gpr[0] =
                    0;


                return 1;
            }


            /*
             * ------------------------------------------------
             * B0:0A WaitEvent(event)
             * ------------------------------------------------
             */
            case 0x0A:
            {
                int index =
                    fm_bios_event_index(
                        cpu->gpr[4]
                    );


                if (
                    index < 0
                    ||
                    !g_bios_events[index].used
                    ||
                    !g_bios_events[index].enabled
                )
                {
                    cpu->gpr[2] =
                        0;
                }
                else if (g_bios_events[index].ready)
                {
                    g_bios_events[index].ready =
                        0;


                    cpu->gpr[2] =
                        1;
                }
                else
                {
                    /*
                     * Bring-up non bloquant.
                     *
                     * Le guest peut rappeler WaitEvent.
                     */
                    cpu->gpr[2] =
                        0;
                }


                cpu->pc =
                    cpu->gpr[31];


                cpu->gpr[0] =
                    0;


                return 1;
            }


            /*
             * ------------------------------------------------
             * B0:0B TestEvent(event)
             * ------------------------------------------------
             */
            case 0x0B:
            {
                int index =
                    fm_bios_event_index(
                        cpu->gpr[4]
                    );


                if (
                    index >= 0
                    &&
                    g_bios_events[index].used
                    &&
                    g_bios_events[index].enabled
                    &&
                    g_bios_events[index].ready
                )
                {
                    g_bios_events[index].ready =
                        0;


                    cpu->gpr[2] =
                        1;
                }
                else
                {
                    cpu->gpr[2] =
                        0;
                }


                cpu->pc =
                    cpu->gpr[31];


                cpu->gpr[0] =
                    0;


                return 1;
            }


            /*
             * ------------------------------------------------
             * B0:0C EnableEvent(event)
             * ------------------------------------------------
             */
            case 0x0C:
            {
                int index =
                    fm_bios_event_index(
                        cpu->gpr[4]
                    );


                if (
                    index >= 0
                    &&
                    g_bios_events[index].used
                )
                {
                    g_bios_events[index].enabled =
                        1;


                    g_bios_events[index].ready =
                        0;


                    cpu->gpr[2] =
                        1;
                }
                else
                {
                    cpu->gpr[2] =
                        0;
                }


                cpu->pc =
                    cpu->gpr[31];


                cpu->gpr[0] =
                    0;


                return 1;
            }


            /*
             * ------------------------------------------------
             * B0:0D DisableEvent(event)
             * ------------------------------------------------
             */
            case 0x0D:
            {
                int index =
                    fm_bios_event_index(
                        cpu->gpr[4]
                    );


                if (
                    index >= 0
                    &&
                    g_bios_events[index].used
                )
                {
                    g_bios_events[index].enabled =
                        0;


                    g_bios_events[index].ready =
                        0;


                    cpu->gpr[2] =
                        1;
                }
                else
                {
                    cpu->gpr[2] =
                        0;
                }


                cpu->pc =
                    cpu->gpr[31];


                cpu->gpr[0] =
                    0;


                return 1;
            }


            /*
             * B0:12 InitPAD2(buf1, siz1, buf2, siz2)
             */
            case 0x12:
            {
                uint32_t buf1 =
                    cpu->gpr[4];


                uint32_t size1 =
                    cpu->gpr[5];


                uint32_t buf2 =
                    cpu->gpr[6];


                uint32_t size2 =
                    cpu->gpr[7];


                g_bios_pad_buf1 =
                    buf1;


                g_bios_pad_buf2 =
                    buf2;


                g_bios_pad_size1 =
                    size1;


                g_bios_pad_size2 =
                    size2;


                if (size1 > 0x100u)
                {
                    size1 =
                        0x100u;
                }


                if (size2 > 0x100u)
                {
                    size2 =
                        0x100u;
                }


                if (buf1 != 0)
                {
                    for (
                        uint32_t i = 0;
                        i < size1;
                        ++i
                    )
                    {
                        cpu->write_byte(
                            buf1 + i,
                            0
                        );
                    }


                    if (size1 != 0)
                    {
                        cpu->write_byte(
                            buf1,
                            0xFF
                        );
                    }
                }


                if (buf2 != 0)
                {
                    for (
                        uint32_t i = 0;
                        i < size2;
                        ++i
                    )
                    {
                        cpu->write_byte(
                            buf2 + i,
                            0
                        );
                    }


                    if (size2 != 0)
                    {
                        cpu->write_byte(
                            buf2,
                            0xFF
                        );
                    }
                }


                g_bios_pad_started =
                    0;


                cpu->pc =
                    cpu->gpr[31];


                cpu->gpr[0] =
                    0;


                return 1;
            }


            /*
             * B0:13 StartPAD2()
             */
            case 0x13:
            {
                g_bios_pad_started =
                    1;


                cpu->pc =
                    cpu->gpr[31];


                cpu->gpr[0] =
                    0;


                return 1;
            }


            /*
             * B0:14 StopPAD2()
             */
            case 0x14:
            {
                g_bios_pad_started =
                    0;


                cpu->pc =
                    cpu->gpr[31];


                cpu->gpr[0] =
                    0;


                return 1;
            }


            /*
             * B0:18 ResetEntryInt
             */
            case 0x18:
            {
                uint32_t old_hook =
                    g_bios_entry_hook_addr;


                g_bios_entry_hook_addr =
                    0;


                cpu->gpr[2] =
                    old_hook;


                cpu->pc =
                    cpu->gpr[31];


                cpu->gpr[0] =
                    0;


                return 1;
            }


            /*
             * B0:19 HookEntryInt
             */
            case 0x19:
            {
                uint32_t old_hook =
                    g_bios_entry_hook_addr;


                g_bios_entry_hook_addr =
                    cpu->gpr[4];


                cpu->gpr[2] =
                    old_hook;


                cpu->pc =
                    cpu->gpr[31];


                cpu->gpr[0] =
                    0;


                return 1;
            }


            /*
             * B0:35 write()
             */
            case 0x35:
            {
                uint32_t fd =
                    cpu->gpr[4];


                uint32_t buffer =
                    cpu->gpr[5];


                uint32_t length =
                    cpu->gpr[6];


                if (
                    fd == 1u
                    ||
                    fd == 2u
                )
                {
                    for (
                        uint32_t i = 0;
                        i < length;
                        ++i
                    )
                    {
                        (void)
                            cpu->read_byte(
                                buffer + i
                            );
                    }


                    g_bios_tty_bytes +=
                        length;


                    cpu->gpr[2] =
                        length;
                }
                else
                {
                    cpu->gpr[2] =
                        0xFFFFFFFFu;
                }


                cpu->pc =
                    cpu->gpr[31];


                cpu->gpr[0] =
                    0;


                return 1;
            }


            /*
             * B0:4A InitCARD2(pad_enable)
             */
            case 0x4A:
            {
                cpu->pc =
                    cpu->gpr[31];


                cpu->gpr[0] =
                    0;


                return 1;
            }


            /*
             * B0:4B StartCARD2()
             */
            case 0x4B:
            {
                cpu->pc =
                    cpu->gpr[31];


                cpu->gpr[0] =
                    0;


                return 1;
            }


            /*
             * B0:4C StopCARD2()
             */
            case 0x4C:
            {
                cpu->pc =
                    cpu->gpr[31];


                cpu->gpr[0] =
                    0;


                return 1;
            }


            /*
             * B0:56 GetC0Table()
             */
            case 0x56:
            {
                fm_bios_prepare_jump_tables(
                    cpu
                );


                cpu->gpr[2] =
                    FM_BIOS_C0_TABLE_ADDR;


                cpu->pc =
                    cpu->gpr[31];


                cpu->gpr[0] =
                    0;


                return 1;
            }


            /*
             * B0:57 GetB0Table()
             */
            case 0x57:
            {
                fm_bios_prepare_jump_tables(
                    cpu
                );


                cpu->gpr[2] =
                    FM_BIOS_B0_TABLE_ADDR;


                cpu->pc =
                    cpu->gpr[31];


                cpu->gpr[0] =
                    0;


                return 1;
            }


            /*
             * B0:5B ChangeClearPAD
             */
            case 0x5B:
            {
                g_bios_clear_pad =
                    cpu->gpr[4];


                cpu->pc =
                    cpu->gpr[31];


                cpu->gpr[0] =
                    0;


                return 1;
            }


            default:
            {
                return 0;
            }
        }
    }


    /*
     * ========================================================
     * C0 BIOS
     * ========================================================
     */

    if (phys == 0x000000C0u)
    {
        uint32_t a0 =
            cpu->gpr[4];


        uint32_t a1 =
            cpu->gpr[5];


        switch (fn)
        {
            /*
             * C0:02 SysEnqIntRP
             */
            case 0x02:
            {
                if (
                    a0 < FM_BIOS_IRQ_CHAINS
                    &&
                    a1 != 0
                )
                {
                    uint32_t previous_head =
                        g_bios_irq_chain_heads[
                            a0
                        ];


                    cpu->write_word(
                        a1,
                        previous_head
                    );


                    g_bios_irq_chain_heads[
                        a0
                    ] =
                        a1;


                    cpu->gpr[2] =
                        1;
                }
                else
                {
                    cpu->gpr[2] =
                        0;
                }


                cpu->pc =
                    cpu->gpr[31];


                cpu->gpr[0] =
                    0;


                return 1;
            }


            /*
             * C0:03 SysDeqIntRP
             */
            case 0x03:
            {
                if (
                    a0 >= FM_BIOS_IRQ_CHAINS
                    ||
                    a1 == 0
                )
                {
                    cpu->gpr[2] =
                        0;


                    cpu->pc =
                        cpu->gpr[31];


                    cpu->gpr[0] =
                        0;


                    return 1;
                }


                uint32_t node =
                    g_bios_irq_chain_heads[
                        a0
                    ];


                uint32_t previous =
                    0;


                for (
                    unsigned safety = 0;
                    node != 0
                    &&
                    safety < 64u;
                    ++safety
                )
                {
                    if (node == a1)
                    {
                        uint32_t next =
                            cpu->read_word(
                                node
                            );


                        if (previous == 0)
                        {
                            g_bios_irq_chain_heads[
                                a0
                            ] =
                                next;
                        }
                        else
                        {
                            cpu->write_word(
                                previous,
                                next
                            );
                        }


                        cpu->gpr[2] =
                            a1;


                        cpu->pc =
                            cpu->gpr[31];


                        cpu->gpr[0] =
                            0;


                        return 1;
                    }


                    previous =
                        node;


                    node =
                        cpu->read_word(
                            node
                        );
                }


                cpu->gpr[2] =
                    0;


                cpu->pc =
                    cpu->gpr[31];


                cpu->gpr[0] =
                    0;


                return 1;
            }


            /*
             * C0:0A ChangeClearRCnt
             */
            case 0x0A:
            {
                if (a0 < FM_BIOS_RCNT_COUNT)
                {
                    uint32_t old_flag =
                        g_bios_change_clear_rcnt[
                            a0
                        ];


                    g_bios_change_clear_rcnt[
                        a0
                    ] =
                        a1 != 0
                            ? 1u
                            : 0u;


                    cpu->gpr[2] =
                        old_flag;
                }
                else
                {
                    cpu->gpr[2] =
                        0;
                }


                cpu->pc =
                    cpu->gpr[31];


                cpu->gpr[0] =
                    0;


                return 1;
            }


            default:
            {
                return 0;
            }
        }
    }


    return 0;
}


/*
 * ============================================================
 * BIOS diagnostics
 * ============================================================
 */

uint32_t fm_bios_hook_addr(void)
{
    return
        g_bios_entry_hook_addr;
}


/*
 * ============================================================
 * VSync
 * ============================================================
 */

int psx_vsync_query_hle_try(
    CPUState *cpu,
    uint32_t dispatch_addr
)
{
    (void)cpu;
    (void)dispatch_addr;


    return 0;
}


/*
 * ============================================================
 * GTE
 * ============================================================
 */

/*
 * B135.6 - semantique architecturale des registres GTE.
 *
 * Le shim utilisait jusque-la de simples lectures/ecritures du tableau
 * CPUState. Ce n'est pas equivalent au COP2 PS1 : plusieurs registres sont
 * 16 bits, SXYP est un alias FIFO, IRGB est derive de IR1..3 et LZCR est
 * derive de LZCS. Le renderer de carte passe massivement par ces transferts.
 *
 * Cette logique reprend la semantique O(1) du PSXRecomp epingle par le projet,
 * sans les caches PGXP qui ne sont pas utilises sur 3DS.
 */
static uint32_t fm_b136_gte_sign_extend_16(uint32_t value)
{
    return (uint32_t)(int32_t)(int16_t)(value & 0xFFFFu);
}


static uint32_t fm_b136_gte_lzcr(uint32_t value)
{
    uint32_t bits =
        (value & 0x80000000u)
            ? ~value
            : value;

    if (bits == 0u)
    {
        return 32u;
    }

    uint32_t count = 0u;

    while ((bits & 0x80000000u) == 0u)
    {
        bits <<= 1;
        ++count;
    }

    return count;
}


static uint32_t fm_b136_gte_irgb_component(uint32_t value)
{
    int32_t ir =
        (int32_t)(int16_t)(value & 0xFFFFu);

    if (ir <= 0)
    {
        return 0u;
    }

    uint32_t scaled =
        (uint32_t)ir >> 7;

    return
        scaled > 0x1Fu
            ? 0x1Fu
            : scaled;
}


static uint32_t fm_b136_gte_pack_irgb(const CPUState *cpu)
{
    uint32_t r =
        fm_b136_gte_irgb_component(cpu->gte_data[9]);

    uint32_t g =
        fm_b136_gte_irgb_component(cpu->gte_data[10]);

    uint32_t b =
        fm_b136_gte_irgb_component(cpu->gte_data[11]);

    return
        (b << 10)
        |
        (g << 5)
        |
        r;
}


static void fm_b136_gte_canonicalize_backing(CPUState *cpu)
{
    static const uint8_t data_u16[] =
    {
        1u, 3u, 5u, 7u, 16u, 17u, 18u, 19u
    };

    static const uint8_t data_s16[] =
    {
        8u, 9u, 10u, 11u
    };

    static const uint8_t ctrl_u16[] =
    {
        4u, 12u, 20u, 26u
    };

    static const uint8_t ctrl_s16[] =
    {
        27u, 29u, 30u
    };

    for (
        unsigned i = 0u;
        i < sizeof(data_u16) / sizeof(data_u16[0]);
        ++i
    )
    {
        uint8_t r = data_u16[i];
        cpu->gte_data[r] &= 0xFFFFu;
    }

    for (
        unsigned i = 0u;
        i < sizeof(data_s16) / sizeof(data_s16[0]);
        ++i
    )
    {
        uint8_t r = data_s16[i];
        cpu->gte_data[r] =
            fm_b136_gte_sign_extend_16(
                cpu->gte_data[r]
            );
    }

    cpu->gte_data[15] =
        cpu->gte_data[14];

    cpu->gte_data[23] =
        0u;

    cpu->gte_data[28] =
        fm_b136_gte_pack_irgb(cpu);

    cpu->gte_data[29] =
        cpu->gte_data[28];

    cpu->gte_data[31] =
        fm_b136_gte_lzcr(
            cpu->gte_data[30]
        );

    for (
        unsigned i = 0u;
        i < sizeof(ctrl_u16) / sizeof(ctrl_u16[0]);
        ++i
    )
    {
        uint8_t r = ctrl_u16[i];
        cpu->gte_ctrl[r] &= 0xFFFFu;
    }

    for (
        unsigned i = 0u;
        i < sizeof(ctrl_s16) / sizeof(ctrl_s16[0]);
        ++i
    )
    {
        uint8_t r = ctrl_s16[i];
        cpu->gte_ctrl[r] =
            fm_b136_gte_sign_extend_16(
                cpu->gte_ctrl[r]
            );
    }
}


uint32_t gte_read_data(
    CPUState *cpu,
    uint8_t reg
)
{
    reg &= 31u;

    switch (reg)
    {
        case 1u:
        case 3u:
        case 5u:
        case 7u:
        case 16u:
        case 17u:
        case 18u:
        case 19u:
            return cpu->gte_data[reg] & 0xFFFFu;

        case 8u:
        case 9u:
        case 10u:
        case 11u:
            return
                fm_b136_gte_sign_extend_16(
                    cpu->gte_data[reg]
                );

        case 15u:
            return cpu->gte_data[14];

        case 23u:
            return 0u;

        case 28u:
        case 29u:
            return fm_b136_gte_pack_irgb(cpu);

        case 31u:
            return fm_b136_gte_lzcr(cpu->gte_data[30]);

        default:
            return cpu->gte_data[reg];
    }
}


uint32_t gte_read_ctrl(
    CPUState *cpu,
    uint8_t reg
)
{
    reg &= 31u;

    switch (reg)
    {
        case 4u:
        case 12u:
        case 20u:
        case 26u:
            return cpu->gte_ctrl[reg] & 0xFFFFu;

        case 27u:
        case 29u:
        case 30u:
            return
                fm_b136_gte_sign_extend_16(
                    cpu->gte_ctrl[reg]
                );

        default:
            return cpu->gte_ctrl[reg];
    }
}


void gte_write_data(
    CPUState *cpu,
    uint8_t reg,
    uint32_t value
)
{
    reg &= 31u;

    switch (reg)
    {
        case 1u:
        case 3u:
        case 5u:
        case 7u:
        case 16u:
        case 17u:
        case 18u:
        case 19u:
            cpu->gte_data[reg] =
                value & 0xFFFFu;
            return;

        case 8u:
        case 9u:
        case 10u:
        case 11u:
            cpu->gte_data[reg] =
                fm_b136_gte_sign_extend_16(value);

            if (reg >= 9u)
            {
                uint32_t packed =
                    fm_b136_gte_pack_irgb(cpu);

                cpu->gte_data[28] = packed;
                cpu->gte_data[29] = packed;
            }
            return;

        case 12u:
        case 13u:
            cpu->gte_data[reg] = value;
            return;

        case 14u:
            cpu->gte_data[14] = value;
            cpu->gte_data[15] = value;
            return;

        case 15u:
            cpu->gte_data[12] = cpu->gte_data[13];
            cpu->gte_data[13] = cpu->gte_data[14];
            cpu->gte_data[14] = value;
            cpu->gte_data[15] = value;
            return;

        case 23u:
            cpu->gte_data[23] = 0u;
            return;

        case 28u:
        {
            cpu->gte_data[9] =
                (value & 0x1Fu) << 7;

            cpu->gte_data[10] =
                ((value >> 5) & 0x1Fu) << 7;

            cpu->gte_data[11] =
                ((value >> 10) & 0x1Fu) << 7;

            uint32_t packed =
                value & 0x7FFFu;

            cpu->gte_data[28] = packed;
            cpu->gte_data[29] = packed;
            return;
        }

        case 29u:
        {
            uint32_t packed =
                fm_b136_gte_pack_irgb(cpu);

            cpu->gte_data[28] = packed;
            cpu->gte_data[29] = packed;
            return;
        }

        case 30u:
            cpu->gte_data[30] = value;
            cpu->gte_data[31] =
                fm_b136_gte_lzcr(value);
            return;

        case 31u:
            cpu->gte_data[31] =
                fm_b136_gte_lzcr(
                    cpu->gte_data[30]
                );
            return;

        default:
            cpu->gte_data[reg] = value;
            return;
    }
}


void gte_write_ctrl(
    CPUState *cpu,
    uint8_t reg,
    uint32_t value
)
{
    reg &= 31u;

    switch (reg)
    {
        case 4u:
        case 12u:
        case 20u:
        case 26u:
            cpu->gte_ctrl[reg] =
                value & 0xFFFFu;
            return;

        case 27u:
        case 29u:
        case 30u:
            cpu->gte_ctrl[reg] =
                fm_b136_gte_sign_extend_16(value);
            return;

        case 31u:
            cpu->gte_ctrl[31] =
                value & 0x7FFFF000u;
            return;

        default:
            cpu->gte_ctrl[reg] = value;
            return;
    }
}


/*
 * ============================================================
 * B135.2 - noyau GTE necessaire a la scene Simon
 * ============================================================
 *
 * Le premier verrou etait GPF (0x3D) a 80088CD0. Apres ce correctif,
 * la scene avance puis atteint RTPT (0x30) a 80087B64.
 *
 * Le pseudo-C Ghidra des helpers 800879D8 / 80087A38 montre que ce
 * chemin enchaine directement :
 *   RTPT (0x30) -> RTPS (0x01) -> AVSZ3/AVSZ4 (0x2D/0x2E)
 *
 * On implemente donc ce petit noyau geometrique coherent, plus NCLIP
 * (0x06), plutot que de patcher une instruction par test.
 *
 * Les autres commandes GTE restent fail-stop : si un nouveau groupe
 * fonctionnel est requis, le prochain STOP restera explicite.
 */

#define FM_GTE_FLAG_MAC1_POS  (1u << 30)
#define FM_GTE_FLAG_MAC2_POS  (1u << 29)
#define FM_GTE_FLAG_MAC3_POS  (1u << 28)
#define FM_GTE_FLAG_MAC1_NEG  (1u << 27)
#define FM_GTE_FLAG_MAC2_NEG  (1u << 26)
#define FM_GTE_FLAG_MAC3_NEG  (1u << 25)
#define FM_GTE_FLAG_IR1_SAT   (1u << 24)
#define FM_GTE_FLAG_IR2_SAT   (1u << 23)
#define FM_GTE_FLAG_IR3_SAT   (1u << 22)
#define FM_GTE_FLAG_SZ_OTZ    (1u << 18)
#define FM_GTE_FLAG_DIV_OVF   (1u << 17)
#define FM_GTE_FLAG_MAC0_POS  (1u << 16)
#define FM_GTE_FLAG_MAC0_NEG  (1u << 15)
#define FM_GTE_FLAG_SX_SAT    (1u << 14)
#define FM_GTE_FLAG_SY_SAT    (1u << 13)
#define FM_GTE_FLAG_IR0_SAT   (1u << 12)
#define FM_GTE_FLAG_ERROR_MASK 0x7F87E000u


static int32_t fm_b135_gte_s16(uint32_t value)
{
    return (int32_t)(int16_t)(value & 0xFFFFu);
}


static int32_t fm_b135_gte_hi_s16(uint32_t value)
{
    return (int32_t)(int16_t)((value >> 16) & 0xFFFFu);
}


static void fm_b135_gte_finish_flags(
    CPUState *cpu,
    uint32_t flags
)
{
    if (flags & FM_GTE_FLAG_ERROR_MASK)
    {
        flags |= 0x80000000u;
    }

    cpu->gte_ctrl[31] = flags;
}


static void fm_b135_gte_check_mac(
    int64_t value,
    unsigned index,
    uint32_t *flags
)
{
    static const uint32_t pos_bits[3] =
    {
        FM_GTE_FLAG_MAC1_POS,
        FM_GTE_FLAG_MAC2_POS,
        FM_GTE_FLAG_MAC3_POS
    };

    static const uint32_t neg_bits[3] =
    {
        FM_GTE_FLAG_MAC1_NEG,
        FM_GTE_FLAG_MAC2_NEG,
        FM_GTE_FLAG_MAC3_NEG
    };

    if (index >= 3u)
    {
        return;
    }

    if (value > 0x7FFFFFFFFLL)
    {
        *flags |= pos_bits[index];
    }

    if (value < -0x800000000LL)
    {
        *flags |= neg_bits[index];
    }
}


static void fm_b135_gte_check_mac0(
    int64_t value,
    uint32_t *flags
)
{
    if (value > 0x7FFFFFFFLL)
    {
        *flags |= FM_GTE_FLAG_MAC0_POS;
    }

    if (value < -0x80000000LL)
    {
        *flags |= FM_GTE_FLAG_MAC0_NEG;
    }
}


static int32_t fm_b135_gte_sat_ir(
    int64_t value,
    int lm,
    uint32_t flag_bit,
    uint32_t *flags
)
{
    int64_t lo = lm ? 0 : -32768;

    if (value < lo)
    {
        *flags |= flag_bit;
        return (int32_t)lo;
    }

    if (value > 32767)
    {
        *flags |= flag_bit;
        return 32767;
    }

    return (int32_t)value;
}


static uint32_t fm_b135_gte_sat_color(
    int64_t value,
    uint32_t flag_bit,
    uint32_t *flags
)
{
    if (value < 0)
    {
        *flags |= flag_bit;
        return 0u;
    }

    if (value > 255)
    {
        *flags |= flag_bit;
        return 255u;
    }

    return (uint32_t)value;
}


static uint16_t fm_b135_gte_sat_sz(
    int64_t value,
    uint32_t *flags
)
{
    if (value < 0)
    {
        *flags |= FM_GTE_FLAG_SZ_OTZ;
        return 0u;
    }

    if (value > 0xFFFF)
    {
        *flags |= FM_GTE_FLAG_SZ_OTZ;
        return 0xFFFFu;
    }

    return (uint16_t)value;
}


static int32_t fm_b135_gte_sat_ir0(
    int64_t value,
    uint32_t *flags
)
{
    if (value < 0)
    {
        *flags |= FM_GTE_FLAG_IR0_SAT;
        return 0;
    }

    if (value > 0x1000)
    {
        *flags |= FM_GTE_FLAG_IR0_SAT;
        return 0x1000;
    }

    return (int32_t)value;
}


static void fm_b135_gte_push_sz(
    CPUState *cpu,
    int64_t value,
    uint32_t *flags
)
{
    cpu->gte_data[16] = cpu->gte_data[17] & 0xFFFFu;
    cpu->gte_data[17] = cpu->gte_data[18] & 0xFFFFu;
    cpu->gte_data[18] = cpu->gte_data[19] & 0xFFFFu;
    cpu->gte_data[19] =
        (uint32_t)fm_b135_gte_sat_sz(
            value,
            flags
        );
}


static void fm_b135_gte_push_sxy(
    CPUState *cpu,
    int64_t sx,
    int64_t sy,
    uint32_t *flags
)
{
    int32_t sx_sat;
    int32_t sy_sat;

    if (sx < -0x400)
    {
        sx_sat = -0x400;
        *flags |= FM_GTE_FLAG_SX_SAT;
    }
    else if (sx > 0x3FF)
    {
        sx_sat = 0x3FF;
        *flags |= FM_GTE_FLAG_SX_SAT;
    }
    else
    {
        sx_sat = (int32_t)sx;
    }

    if (sy < -0x400)
    {
        sy_sat = -0x400;
        *flags |= FM_GTE_FLAG_SY_SAT;
    }
    else if (sy > 0x3FF)
    {
        sy_sat = 0x3FF;
        *flags |= FM_GTE_FLAG_SY_SAT;
    }
    else
    {
        sy_sat = (int32_t)sy;
    }

    cpu->gte_data[12] = cpu->gte_data[13];
    cpu->gte_data[13] = cpu->gte_data[14];
    cpu->gte_data[14] =
        ((uint32_t)(uint16_t)sy_sat << 16)
        |
        (uint32_t)(uint16_t)sx_sat;

    /* SXYP aliases SXY2 after a normal projection push. */
    cpu->gte_data[15] = cpu->gte_data[14];
}


static uint8_t g_b135_div_table[0x101];
static int g_b135_div_table_ready = 0;


static void fm_b135_gte_init_div_table(void)
{
    if (g_b135_div_table_ready)
    {
        return;
    }

    for (
        uint32_t divisor = 0x8000u;
        divisor < 0x10000u;
        divisor += 0x80u
    )
    {
        uint32_t xa = 512u;

        for (unsigned i = 1u; i < 5u; ++i)
        {
            xa =
                (
                    xa
                    *
                    (
                        1024u * 512u
                        -
                        ((divisor >> 7) * xa)
                    )
                )
                >> 18;
        }

        g_b135_div_table[(divisor >> 7) & 0xFFu] =
            (uint8_t)(
                ((xa + 1u) >> 1)
                -
                0x101u
            );
    }

    g_b135_div_table[0x100] =
        g_b135_div_table[0xFF];

    g_b135_div_table_ready = 1;
}


static unsigned fm_b135_gte_clz16(uint16_t value)
{
    unsigned n = 0u;

    for (int bit = 15; bit >= 0; --bit)
    {
        if (value & (uint16_t)(1u << bit))
        {
            break;
        }

        ++n;
    }

    return n;
}


static int32_t fm_b135_gte_calc_recip(uint16_t divisor)
{
    int32_t x =
        0x101
        +
        g_b135_div_table[
            (((divisor & 0x7FFFu) + 0x40u) >> 7)
        ];

    int32_t tmp =
        (
            ((int32_t)divisor * -x)
            +
            0x80
        )
        >> 8;

    int32_t tmp2 =
        (
            x
            *
            (131072 + tmp)
            +
            0x80
        )
        >> 8;

    return tmp2;
}


static int32_t fm_b135_gte_divide(
    uint16_t h,
    uint16_t sz3,
    uint32_t *flags
)
{
    fm_b135_gte_init_div_table();

    if ((uint32_t)sz3 * 2u <= (uint32_t)h)
    {
        *flags |= FM_GTE_FLAG_DIV_OVF;
        return 0x1FFFF;
    }

    unsigned shift =
        fm_b135_gte_clz16(
            sz3
        );

    uint32_t dividend =
        (uint32_t)h << shift;

    uint32_t divisor =
        (uint32_t)sz3 << shift;

    uint32_t result =
        (uint32_t)(
            (
                (uint64_t)dividend
                *
                (uint32_t)fm_b135_gte_calc_recip(
                    (uint16_t)(divisor | 0x8000u)
                )
                +
                32768u
            )
            >> 16
        );

    if (result > 0x1FFFFu)
    {
        result = 0x1FFFFu;
    }

    return (int32_t)result;
}


static void fm_b135_gte_unpack_rt(
    const CPUState *cpu,
    int32_t rt[3][3]
)
{
    const uint32_t *c = cpu->gte_ctrl;

    rt[0][0] = fm_b135_gte_s16(c[0]);
    rt[0][1] = fm_b135_gte_hi_s16(c[0]);
    rt[0][2] = fm_b135_gte_s16(c[1]);

    rt[1][0] = fm_b135_gte_hi_s16(c[1]);
    rt[1][1] = fm_b135_gte_s16(c[2]);
    rt[1][2] = fm_b135_gte_hi_s16(c[2]);

    rt[2][0] = fm_b135_gte_s16(c[3]);
    rt[2][1] = fm_b135_gte_hi_s16(c[3]);
    rt[2][2] = fm_b135_gte_s16(c[4]);
}


static void fm_b135_gte_unpack_vertex(
    const CPUState *cpu,
    unsigned index,
    int32_t out[3]
)
{
    unsigned base = index * 2u;

    out[0] = fm_b135_gte_s16(cpu->gte_data[base]);
    out[1] = fm_b135_gte_hi_s16(cpu->gte_data[base]);
    out[2] = fm_b135_gte_s16(cpu->gte_data[base + 1u]);
}


static void fm_b135_gte_rtps_one(
    CPUState *cpu,
    const int32_t vertex[3],
    int set_mac0,
    uint32_t cmd,
    uint32_t *flags
)
{
    int32_t rt[3][3];
    fm_b135_gte_unpack_rt(cpu, rt);

    const int shift =
        (cmd & (1u << 19))
            ? 12
            : 0;

    const int lm =
        (cmd & (1u << 10))
            ? 1
            : 0;

    int64_t mac1_raw =
        (int64_t)(int32_t)cpu->gte_ctrl[5] * 4096
        +
        (int64_t)rt[0][0] * vertex[0]
        +
        (int64_t)rt[0][1] * vertex[1]
        +
        (int64_t)rt[0][2] * vertex[2];

    int64_t mac2_raw =
        (int64_t)(int32_t)cpu->gte_ctrl[6] * 4096
        +
        (int64_t)rt[1][0] * vertex[0]
        +
        (int64_t)rt[1][1] * vertex[1]
        +
        (int64_t)rt[1][2] * vertex[2];

    int64_t mac3_raw =
        (int64_t)(int32_t)cpu->gte_ctrl[7] * 4096
        +
        (int64_t)rt[2][0] * vertex[0]
        +
        (int64_t)rt[2][1] * vertex[1]
        +
        (int64_t)rt[2][2] * vertex[2];

    fm_b135_gte_check_mac(mac1_raw >> 12, 0u, flags);
    fm_b135_gte_check_mac(mac2_raw >> 12, 1u, flags);
    fm_b135_gte_check_mac(mac3_raw >> 12, 2u, flags);

    int32_t mac1 =
        (int32_t)(mac1_raw >> shift);

    int32_t mac2 =
        (int32_t)(mac2_raw >> shift);

    int32_t mac3 =
        (int32_t)(mac3_raw >> shift);

    cpu->gte_data[25] = (uint32_t)mac1;
    cpu->gte_data[26] = (uint32_t)mac2;
    cpu->gte_data[27] = (uint32_t)mac3;

    int32_t ir1 =
        fm_b135_gte_sat_ir(
            mac1,
            lm,
            FM_GTE_FLAG_IR1_SAT,
            flags
        );

    int32_t ir2 =
        fm_b135_gte_sat_ir(
            mac2,
            lm,
            FM_GTE_FLAG_IR2_SAT,
            flags
        );

    /*
     * Hardware quirk: FLAG.IR3 is evaluated from the unshifted >>12
     * view with lm=0, while the stored IR3 uses the actual sf/lm.
     */
    (void)fm_b135_gte_sat_ir(
        mac3_raw >> 12,
        0,
        FM_GTE_FLAG_IR3_SAT,
        flags
    );

    int32_t ir3 = mac3;
    int32_t ir3_lo = lm ? 0 : -32768;

    if (ir3 < ir3_lo)
    {
        ir3 = ir3_lo;
    }

    if (ir3 > 32767)
    {
        ir3 = 32767;
    }

    cpu->gte_data[9] = (uint32_t)ir1;
    cpu->gte_data[10] = (uint32_t)ir2;
    cpu->gte_data[11] = (uint32_t)ir3;

    fm_b135_gte_push_sz(
        cpu,
        mac3_raw >> 12,
        flags
    );

    uint16_t h =
        (uint16_t)(cpu->gte_ctrl[26] & 0xFFFFu);

    uint16_t sz3 =
        (uint16_t)(cpu->gte_data[19] & 0xFFFFu);

    int32_t h_div_sz =
        fm_b135_gte_divide(
            h,
            sz3,
            flags
        );

    int64_t sx =
        (
            (int64_t)(int32_t)cpu->gte_ctrl[24]
            +
            (int64_t)ir1 * h_div_sz
        )
        >> 16;

    int64_t sy =
        (
            (int64_t)(int32_t)cpu->gte_ctrl[25]
            +
            (int64_t)ir2 * h_div_sz
        )
        >> 16;

    fm_b135_gte_push_sxy(
        cpu,
        sx,
        sy,
        flags
    );

    if (set_mac0)
    {
        int32_t dqa =
            fm_b135_gte_s16(
                cpu->gte_ctrl[27]
            );

        int32_t dqb =
            (int32_t)cpu->gte_ctrl[28];

        int64_t mac0 =
            (int64_t)dqa * h_div_sz
            +
            dqb;

        fm_b135_gte_check_mac0(
            mac0,
            flags
        );

        cpu->gte_data[24] =
            (uint32_t)(int32_t)mac0;

        cpu->gte_data[8] =
            (uint32_t)fm_b135_gte_sat_ir0(
                mac0 >> 12,
                flags
            );
    }
}


static void fm_b135_gte_rtps(
    CPUState *cpu,
    uint32_t cmd
)
{
    uint32_t flags = 0u;
    int32_t v0[3];

    fm_b135_gte_unpack_vertex(
        cpu,
        0u,
        v0
    );

    fm_b135_gte_rtps_one(
        cpu,
        v0,
        1,
        cmd,
        &flags
    );

    fm_b135_gte_finish_flags(
        cpu,
        flags
    );
}


static void fm_b135_gte_rtpt(
    CPUState *cpu,
    uint32_t cmd
)
{
    uint32_t flags = 0u;
    int32_t v[3];

    for (unsigned i = 0u; i < 3u; ++i)
    {
        fm_b135_gte_unpack_vertex(
            cpu,
            i,
            v
        );

        fm_b135_gte_rtps_one(
            cpu,
            v,
            i == 2u,
            cmd,
            &flags
        );
    }

    fm_b135_gte_finish_flags(
        cpu,
        flags
    );
}


static void fm_b135_gte_nclip(
    CPUState *cpu
)
{
    uint32_t flags = 0u;

    int32_t sx0 = fm_b135_gte_s16(cpu->gte_data[12]);
    int32_t sy0 = fm_b135_gte_hi_s16(cpu->gte_data[12]);
    int32_t sx1 = fm_b135_gte_s16(cpu->gte_data[13]);
    int32_t sy1 = fm_b135_gte_hi_s16(cpu->gte_data[13]);
    int32_t sx2 = fm_b135_gte_s16(cpu->gte_data[14]);
    int32_t sy2 = fm_b135_gte_hi_s16(cpu->gte_data[14]);

    int64_t mac0 =
        (int64_t)sx0 * (sy1 - sy2)
        +
        (int64_t)sx1 * (sy2 - sy0)
        +
        (int64_t)sx2 * (sy0 - sy1);

    fm_b135_gte_check_mac0(
        mac0,
        &flags
    );

    cpu->gte_data[24] =
        (uint32_t)(int32_t)mac0;

    fm_b135_gte_finish_flags(
        cpu,
        flags
    );
}


static void fm_b135_gte_avsz(
    CPUState *cpu,
    int four_points
)
{
    uint32_t flags = 0u;

    int64_t sum;

    int32_t zsf;

    if (four_points)
    {
        sum =
            (int64_t)(cpu->gte_data[16] & 0xFFFFu)
            +
            (int64_t)(cpu->gte_data[17] & 0xFFFFu)
            +
            (int64_t)(cpu->gte_data[18] & 0xFFFFu)
            +
            (int64_t)(cpu->gte_data[19] & 0xFFFFu);

        zsf =
            fm_b135_gte_s16(
                cpu->gte_ctrl[30]
            );
    }
    else
    {
        sum =
            (int64_t)(cpu->gte_data[17] & 0xFFFFu)
            +
            (int64_t)(cpu->gte_data[18] & 0xFFFFu)
            +
            (int64_t)(cpu->gte_data[19] & 0xFFFFu);

        zsf =
            fm_b135_gte_s16(
                cpu->gte_ctrl[29]
            );
    }

    int64_t mac0 =
        (int64_t)zsf * sum;

    fm_b135_gte_check_mac0(
        mac0,
        &flags
    );

    cpu->gte_data[24] =
        (uint32_t)(int32_t)mac0;

    cpu->gte_data[7] =
        (uint32_t)fm_b135_gte_sat_sz(
            mac0 >> 12,
            &flags
        );

    fm_b135_gte_finish_flags(
        cpu,
        flags
    );
}


static void fm_b135_gte_unpack_matrix(
    const CPUState *cpu,
    unsigned base,
    int32_t out[3][3]
)
{
    const uint32_t *c = cpu->gte_ctrl;

    out[0][0] = fm_b135_gte_s16(c[base + 0u]);
    out[0][1] = fm_b135_gte_hi_s16(c[base + 0u]);
    out[0][2] = fm_b135_gte_s16(c[base + 1u]);

    out[1][0] = fm_b135_gte_hi_s16(c[base + 1u]);
    out[1][1] = fm_b135_gte_s16(c[base + 2u]);
    out[1][2] = fm_b135_gte_hi_s16(c[base + 2u]);

    out[2][0] = fm_b135_gte_s16(c[base + 3u]);
    out[2][1] = fm_b135_gte_hi_s16(c[base + 3u]);
    out[2][2] = fm_b135_gte_s16(c[base + 4u]);
}


static void fm_b135_gte_mvmva(
    CPUState *cpu,
    uint32_t cmd
)
{
    uint32_t flags = 0u;

    unsigned mx = (cmd >> 17) & 3u;
    unsigned vv = (cmd >> 15) & 3u;
    unsigned tv = (cmd >> 13) & 3u;

    int sf = (int)((cmd >> 19) & 1u);
    int lm = (int)((cmd >> 10) & 1u);

    int32_t m[3][3] = {{0}};
    int32_t v[3] = {0, 0, 0};
    int64_t t[3] = {0, 0, 0};

    switch (mx)
    {
        case 0u:
            fm_b135_gte_unpack_matrix(cpu, 0u, m);
            break;

        case 1u:
            fm_b135_gte_unpack_matrix(cpu, 8u, m);
            break;

        case 2u:
            fm_b135_gte_unpack_matrix(cpu, 16u, m);
            break;

        default:
            /*
             * Matrix 3 is reserved/garbage on hardware. The current
             * Forbidden Memories path does not use it; keep a deterministic
             * zero matrix rather than inventing host-dependent garbage.
             */
            break;
    }

    switch (vv)
    {
        case 0u:
        case 1u:
        case 2u:
            fm_b135_gte_unpack_vertex(cpu, vv, v);
            break;

        default:
            v[0] = fm_b135_gte_s16(cpu->gte_data[9]);
            v[1] = fm_b135_gte_s16(cpu->gte_data[10]);
            v[2] = fm_b135_gte_s16(cpu->gte_data[11]);
            break;
    }

    switch (tv)
    {
        case 0u:
            t[0] = (int64_t)(int32_t)cpu->gte_ctrl[5] * 4096;
            t[1] = (int64_t)(int32_t)cpu->gte_ctrl[6] * 4096;
            t[2] = (int64_t)(int32_t)cpu->gte_ctrl[7] * 4096;
            break;

        case 1u:
            t[0] = (int64_t)(int32_t)cpu->gte_ctrl[13] * 4096;
            t[1] = (int64_t)(int32_t)cpu->gte_ctrl[14] * 4096;
            t[2] = (int64_t)(int32_t)cpu->gte_ctrl[15] * 4096;
            break;

        case 2u:
            t[0] = (int64_t)(int32_t)cpu->gte_ctrl[21] * 4096;
            t[1] = (int64_t)(int32_t)cpu->gte_ctrl[22] * 4096;
            t[2] = (int64_t)(int32_t)cpu->gte_ctrl[23] * 4096;
            break;

        default:
            break;
    }

    int64_t mac1 =
        t[0]
        + (int64_t)m[0][0] * v[0]
        + (int64_t)m[0][1] * v[1]
        + (int64_t)m[0][2] * v[2];

    int64_t mac2 =
        t[1]
        + (int64_t)m[1][0] * v[0]
        + (int64_t)m[1][1] * v[1]
        + (int64_t)m[1][2] * v[2];

    int64_t mac3 =
        t[2]
        + (int64_t)m[2][0] * v[0]
        + (int64_t)m[2][1] * v[1]
        + (int64_t)m[2][2] * v[2];

    if (sf)
    {
        mac1 >>= 12;
        mac2 >>= 12;
        mac3 >>= 12;
    }

    fm_b135_gte_check_mac(mac1, 0u, &flags);
    fm_b135_gte_check_mac(mac2, 1u, &flags);
    fm_b135_gte_check_mac(mac3, 2u, &flags);

    cpu->gte_data[25] = (uint32_t)(int32_t)mac1;
    cpu->gte_data[26] = (uint32_t)(int32_t)mac2;
    cpu->gte_data[27] = (uint32_t)(int32_t)mac3;

    cpu->gte_data[9] =
        (uint32_t)fm_b135_gte_sat_ir(
            mac1,
            lm,
            FM_GTE_FLAG_IR1_SAT,
            &flags
        );

    cpu->gte_data[10] =
        (uint32_t)fm_b135_gte_sat_ir(
            mac2,
            lm,
            FM_GTE_FLAG_IR2_SAT,
            &flags
        );

    cpu->gte_data[11] =
        (uint32_t)fm_b135_gte_sat_ir(
            mac3,
            lm,
            FM_GTE_FLAG_IR3_SAT,
            &flags
        );

    fm_b135_gte_finish_flags(
        cpu,
        flags
    );
}


static void fm_b135_gte_light_transform(
    CPUState *cpu,
    const int32_t vertex[3],
    uint32_t cmd,
    uint32_t *flags
)
{
    int32_t m[3][3];
    fm_b135_gte_unpack_matrix(cpu, 8u, m);

    int lm = (cmd & (1u << 10)) ? 1 : 0;

    int64_t mac1 =
        (
            (int64_t)m[0][0] * vertex[0]
            +
            (int64_t)m[0][1] * vertex[1]
            +
            (int64_t)m[0][2] * vertex[2]
        )
        >> 12;

    int64_t mac2 =
        (
            (int64_t)m[1][0] * vertex[0]
            +
            (int64_t)m[1][1] * vertex[1]
            +
            (int64_t)m[1][2] * vertex[2]
        )
        >> 12;

    int64_t mac3 =
        (
            (int64_t)m[2][0] * vertex[0]
            +
            (int64_t)m[2][1] * vertex[1]
            +
            (int64_t)m[2][2] * vertex[2]
        )
        >> 12;

    cpu->gte_data[25] = (uint32_t)(int32_t)mac1;
    cpu->gte_data[26] = (uint32_t)(int32_t)mac2;
    cpu->gte_data[27] = (uint32_t)(int32_t)mac3;

    cpu->gte_data[9] =
        (uint32_t)fm_b135_gte_sat_ir(
            mac1,
            lm,
            FM_GTE_FLAG_IR1_SAT,
            flags
        );

    cpu->gte_data[10] =
        (uint32_t)fm_b135_gte_sat_ir(
            mac2,
            lm,
            FM_GTE_FLAG_IR2_SAT,
            flags
        );

    cpu->gte_data[11] =
        (uint32_t)fm_b135_gte_sat_ir(
            mac3,
            lm,
            FM_GTE_FLAG_IR3_SAT,
            flags
        );
}


static void fm_b135_gte_light_color(
    CPUState *cpu,
    uint32_t cmd,
    uint32_t *flags
)
{
    int32_t m[3][3];
    fm_b135_gte_unpack_matrix(cpu, 16u, m);

    int lm = (cmd & (1u << 10)) ? 1 : 0;

    int64_t ir1 = fm_b135_gte_s16(cpu->gte_data[9]);
    int64_t ir2 = fm_b135_gte_s16(cpu->gte_data[10]);
    int64_t ir3 = fm_b135_gte_s16(cpu->gte_data[11]);

    int64_t mac1 =
        (
            (int64_t)(int32_t)cpu->gte_ctrl[13] * 4096
            +
            (int64_t)m[0][0] * ir1
            +
            (int64_t)m[0][1] * ir2
            +
            (int64_t)m[0][2] * ir3
        )
        >> 12;

    int64_t mac2 =
        (
            (int64_t)(int32_t)cpu->gte_ctrl[14] * 4096
            +
            (int64_t)m[1][0] * ir1
            +
            (int64_t)m[1][1] * ir2
            +
            (int64_t)m[1][2] * ir3
        )
        >> 12;

    int64_t mac3 =
        (
            (int64_t)(int32_t)cpu->gte_ctrl[15] * 4096
            +
            (int64_t)m[2][0] * ir1
            +
            (int64_t)m[2][1] * ir2
            +
            (int64_t)m[2][2] * ir3
        )
        >> 12;

    cpu->gte_data[25] = (uint32_t)(int32_t)mac1;
    cpu->gte_data[26] = (uint32_t)(int32_t)mac2;
    cpu->gte_data[27] = (uint32_t)(int32_t)mac3;

    cpu->gte_data[9] =
        (uint32_t)fm_b135_gte_sat_ir(
            mac1,
            lm,
            FM_GTE_FLAG_IR1_SAT,
            flags
        );

    cpu->gte_data[10] =
        (uint32_t)fm_b135_gte_sat_ir(
            mac2,
            lm,
            FM_GTE_FLAG_IR2_SAT,
            flags
        );

    cpu->gte_data[11] =
        (uint32_t)fm_b135_gte_sat_ir(
            mac3,
            lm,
            FM_GTE_FLAG_IR3_SAT,
            flags
        );
}


static void fm_b135_gte_depth_cue_from_ir(
    CPUState *cpu,
    uint32_t cmd,
    uint32_t *flags
)
{
    int shift = (cmd & (1u << 19)) ? 12 : 0;
    int lm = (cmd & (1u << 10)) ? 1 : 0;

    int64_t ir1 = fm_b135_gte_s16(cpu->gte_data[9]);
    int64_t ir2 = fm_b135_gte_s16(cpu->gte_data[10]);
    int64_t ir3 = fm_b135_gte_s16(cpu->gte_data[11]);
    int64_t ir0 = fm_b135_gte_s16(cpu->gte_data[8]);

    int64_t base1 = ir1 * 4096;
    int64_t base2 = ir2 * 4096;
    int64_t base3 = ir3 * 4096;

    int32_t step1 =
        fm_b135_gte_sat_ir(
            (
                (
                    (int64_t)(int32_t)cpu->gte_ctrl[21] * 4096
                    -
                    base1
                )
                >> shift
            ),
            0,
            FM_GTE_FLAG_IR1_SAT,
            flags
        );

    int32_t step2 =
        fm_b135_gte_sat_ir(
            (
                (
                    (int64_t)(int32_t)cpu->gte_ctrl[22] * 4096
                    -
                    base2
                )
                >> shift
            ),
            0,
            FM_GTE_FLAG_IR2_SAT,
            flags
        );

    int32_t step3 =
        fm_b135_gte_sat_ir(
            (
                (
                    (int64_t)(int32_t)cpu->gte_ctrl[23] * 4096
                    -
                    base3
                )
                >> shift
            ),
            0,
            FM_GTE_FLAG_IR3_SAT,
            flags
        );

    int64_t mac1 =
        (
            base1
            +
            ir0 * step1
        )
        >> shift;

    int64_t mac2 =
        (
            base2
            +
            ir0 * step2
        )
        >> shift;

    int64_t mac3 =
        (
            base3
            +
            ir0 * step3
        )
        >> shift;

    fm_b135_gte_check_mac(mac1, 0u, flags);
    fm_b135_gte_check_mac(mac2, 1u, flags);
    fm_b135_gte_check_mac(mac3, 2u, flags);

    cpu->gte_data[25] = (uint32_t)(int32_t)mac1;
    cpu->gte_data[26] = (uint32_t)(int32_t)mac2;
    cpu->gte_data[27] = (uint32_t)(int32_t)mac3;

    cpu->gte_data[9] =
        (uint32_t)fm_b135_gte_sat_ir(
            mac1,
            lm,
            FM_GTE_FLAG_IR1_SAT,
            flags
        );

    cpu->gte_data[10] =
        (uint32_t)fm_b135_gte_sat_ir(
            mac2,
            lm,
            FM_GTE_FLAG_IR2_SAT,
            flags
        );

    cpu->gte_data[11] =
        (uint32_t)fm_b135_gte_sat_ir(
            mac3,
            lm,
            FM_GTE_FLAG_IR3_SAT,
            flags
        );
}


static void fm_b135_gte_color_output(
    CPUState *cpu,
    uint32_t cmd,
    uint32_t *flags
)
{
    int lm = (cmd & (1u << 10)) ? 1 : 0;

    uint32_t rgbc = cpu->gte_data[6];

    int64_t ir1 = fm_b135_gte_s16(cpu->gte_data[9]);
    int64_t ir2 = fm_b135_gte_s16(cpu->gte_data[10]);
    int64_t ir3 = fm_b135_gte_s16(cpu->gte_data[11]);

    int64_t mac1 =
        (
            (int64_t)(rgbc & 0xFFu)
            *
            ir1
            *
            16
        )
        >> 12;

    int64_t mac2 =
        (
            (int64_t)((rgbc >> 8) & 0xFFu)
            *
            ir2
            *
            16
        )
        >> 12;

    int64_t mac3 =
        (
            (int64_t)((rgbc >> 16) & 0xFFu)
            *
            ir3
            *
            16
        )
        >> 12;

    cpu->gte_data[25] = (uint32_t)(int32_t)mac1;
    cpu->gte_data[26] = (uint32_t)(int32_t)mac2;
    cpu->gte_data[27] = (uint32_t)(int32_t)mac3;

    cpu->gte_data[9] =
        (uint32_t)fm_b135_gte_sat_ir(
            mac1,
            lm,
            FM_GTE_FLAG_IR1_SAT,
            flags
        );

    cpu->gte_data[10] =
        (uint32_t)fm_b135_gte_sat_ir(
            mac2,
            lm,
            FM_GTE_FLAG_IR2_SAT,
            flags
        );

    cpu->gte_data[11] =
        (uint32_t)fm_b135_gte_sat_ir(
            mac3,
            lm,
            FM_GTE_FLAG_IR3_SAT,
            flags
        );

    uint32_t r =
        fm_b135_gte_sat_color(
            mac1 >> 4,
            1u << 21,
            flags
        );

    uint32_t g =
        fm_b135_gte_sat_color(
            mac2 >> 4,
            1u << 20,
            flags
        );

    uint32_t b =
        fm_b135_gte_sat_color(
            mac3 >> 4,
            1u << 19,
            flags
        );

    uint32_t code =
        rgbc & 0xFF000000u;

    cpu->gte_data[20] = cpu->gte_data[21];
    cpu->gte_data[21] = cpu->gte_data[22];
    cpu->gte_data[22] =
        code
        |
        (b << 16)
        |
        (g << 8)
        |
        r;
}


static void fm_b135_gte_ncds(
    CPUState *cpu,
    uint32_t cmd
)
{
    uint32_t flags = 0u;
    int32_t v0[3];

    fm_b135_gte_unpack_vertex(
        cpu,
        0u,
        v0
    );

    fm_b135_gte_light_transform(
        cpu,
        v0,
        cmd,
        &flags
    );

    fm_b135_gte_light_color(
        cpu,
        cmd,
        &flags
    );

    fm_b135_gte_depth_cue_from_ir(
        cpu,
        cmd,
        &flags
    );

    fm_b135_gte_color_output(
        cpu,
        cmd,
        &flags
    );

    fm_b135_gte_finish_flags(
        cpu,
        flags
    );
}


static void fm_b135_gte_gpf(
    CPUState *cpu,
    uint32_t cmd
)
{
    int sf = (int)((cmd >> 19) & 1u);
    int lm = (int)((cmd >> 10) & 1u);

    int64_t ir0 = fm_b135_gte_s16(cpu->gte_data[8]);
    int64_t ir1 = fm_b135_gte_s16(cpu->gte_data[9]);
    int64_t ir2 = fm_b135_gte_s16(cpu->gte_data[10]);
    int64_t ir3 = fm_b135_gte_s16(cpu->gte_data[11]);

    int64_t mac1 = ir0 * ir1;
    int64_t mac2 = ir0 * ir2;
    int64_t mac3 = ir0 * ir3;

    if (sf)
    {
        mac1 >>= 12;
        mac2 >>= 12;
        mac3 >>= 12;
    }

    cpu->gte_data[25] = (uint32_t)(int32_t)mac1;
    cpu->gte_data[26] = (uint32_t)(int32_t)mac2;
    cpu->gte_data[27] = (uint32_t)(int32_t)mac3;

    uint32_t flags = 0u;

    fm_b135_gte_check_mac(mac1, 0u, &flags);
    fm_b135_gte_check_mac(mac2, 1u, &flags);
    fm_b135_gte_check_mac(mac3, 2u, &flags);

    int32_t out1 = fm_b135_gte_sat_ir(mac1, lm, FM_GTE_FLAG_IR1_SAT, &flags);
    int32_t out2 = fm_b135_gte_sat_ir(mac2, lm, FM_GTE_FLAG_IR2_SAT, &flags);
    int32_t out3 = fm_b135_gte_sat_ir(mac3, lm, FM_GTE_FLAG_IR3_SAT, &flags);

    cpu->gte_data[9]  = (uint32_t)out1;
    cpu->gte_data[10] = (uint32_t)out2;
    cpu->gte_data[11] = (uint32_t)out3;

    uint32_t r = fm_b135_gte_sat_color(mac1 >> 4, 1u << 21, &flags);
    uint32_t g = fm_b135_gte_sat_color(mac2 >> 4, 1u << 20, &flags);
    uint32_t b = fm_b135_gte_sat_color(mac3 >> 4, 1u << 19, &flags);
    uint32_t code = cpu->gte_data[6] & 0xFF000000u;

    cpu->gte_data[20] = cpu->gte_data[21];
    cpu->gte_data[21] = cpu->gte_data[22];
    cpu->gte_data[22] = code | (b << 16) | (g << 8) | r;

    fm_b135_gte_finish_flags(
        cpu,
        flags
    );
}


void gte_execute(
    CPUState *cpu,
    uint32_t cmd
)
{
    if (!cpu)
    {
        fm_probe_stop(
            FM_STOP_GTE,
            cmd
        );

        return;
    }

    switch (cmd & 0x3Fu)
    {
        case 0x01u:
            fm_b135_gte_rtps(cpu, cmd);
            return;

        case 0x06u:
            fm_b135_gte_nclip(cpu);
            return;

        case 0x12u:
            fm_b135_gte_mvmva(cpu, cmd);
            return;

        case 0x13u:
            fm_b135_gte_ncds(cpu, cmd);
            return;

        case 0x2Du:
            fm_b135_gte_avsz(cpu, 0);
            return;

        case 0x2Eu:
            fm_b135_gte_avsz(cpu, 1);
            return;

        case 0x30u:
            fm_b135_gte_rtpt(cpu, cmd);
            return;

        case 0x3Du:
            fm_b135_gte_gpf(cpu, cmd);
            return;

        default:
            fm_probe_stop(
                FM_STOP_GTE,
                cmd
            );
            return;
    }
}


/*
 * B135.4 - hook de precision GTE.
 *
 * Dans PSXRecomp amont ce hook est uniquement une aide PGXP/precision :
 * il ne fait PAS partie de la semantique SWC2 et ne doit jamais arreter
 * l'execution. Le vrai store guest a deja lieu dans le code genere.
 *
 * Le runtime 3DS n'embarque pas le moteur PGXP, donc le comportement
 * correct ici est un no-op. C'est particulierement important pour les
 * registres hors SXY (ex. reg 11 / IR3) : l'amont les ignore egalement.
 */
void gte_precision_store_word(
    uint32_t addr,
    uint8_t reg
)
{
    (void)addr;
    (void)reg;
}
