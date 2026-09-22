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

uint32_t gte_read_data(
    CPUState *cpu,
    uint8_t reg
)
{
    return
        cpu->gte_data[
            reg & 31u
        ];
}


uint32_t gte_read_ctrl(
    CPUState *cpu,
    uint8_t reg
)
{
    return
        cpu->gte_ctrl[
            reg & 31u
        ];
}


void gte_write_data(
    CPUState *cpu,
    uint8_t reg,
    uint32_t value
)
{
    cpu->gte_data[
        reg & 31u
    ] =
        value;
}


void gte_write_ctrl(
    CPUState *cpu,
    uint8_t reg,
    uint32_t value
)
{
    cpu->gte_ctrl[
        reg & 31u
    ] =
        value;
}


/*
 * ============================================================
 * B135 - premier opcode GTE natif : GPF (0x3D)
 * ============================================================
 *
 * B131 s'arrete volontairement dans gte_execute() pour toute commande
 * COP2 non couverte par les HLE B62. La scene de Simon Muran atteint
 * FUN_80088BD8 (PC observe 80088CD0), qui emet 0x0198003D : GPF.
 *
 * On implemente uniquement GPF ici. Les autres commandes conservent le
 * fail-stop historique afin de ne pas masquer le prochain verrou.
 */
static int32_t fm_b135_gte_s16(uint32_t value)
{
    return (int32_t)(int16_t)(value & 0xFFFFu);
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

    int32_t out1 = fm_b135_gte_sat_ir(mac1, lm, 1u << 24, &flags);
    int32_t out2 = fm_b135_gte_sat_ir(mac2, lm, 1u << 23, &flags);
    int32_t out3 = fm_b135_gte_sat_ir(mac3, lm, 1u << 22, &flags);

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

    if (flags != 0u)
    {
        flags |= 0x80000000u;
    }

    cpu->gte_ctrl[31] = flags;
}


void gte_execute(
    CPUState *cpu,
    uint32_t cmd
)
{
    if (
        cpu != NULL
        &&
        (cmd & 0x3Fu) == 0x3Du
    )
    {
        fm_b135_gte_gpf(
            cpu,
            cmd
        );

        return;
    }


    fm_probe_stop(
        FM_STOP_GTE,
        cmd
    );
}


void gte_precision_store_word(
    uint32_t addr,
    uint8_t reg
)
{
    uint32_t info =
        (
            addr
            &
            0x00FFFFFFu
        )
        |
        (
            (uint32_t)reg
            <<
            24
        );


    fm_probe_stop(
        FM_STOP_GTE_STORE,
        info
    );
}
