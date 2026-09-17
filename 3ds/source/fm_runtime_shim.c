#include "fm_runtime_shim.h"
#include "fm_memory.h"
#include "fm_gpu.h"

#include <setjmp.h>
#include <stdint.h>


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


/*
 * Adresses des tables BIOS retail SCPH-1001/PSOne.
 *
 * B0:56 GetC0Table -> 0x00000674
 * B0:57 GetB0Table -> 0x00000874
 *
 * C0[6] est le handler d'exception. Les patchs libapi classiques
 * s'attendent a recuperer 0x00000C80 a cet index.
 */
#define FM_BIOS_C0_TABLE_ADDR           0x00000674u
#define FM_BIOS_B0_TABLE_ADDR           0x00000874u
#define FM_BIOS_C0_EXCEPTION_HANDLER    0x00000C80u


#define FM_BIOS_IRQ_CHAINS 8

static uint32_t g_bios_irq_chain_heads[
    FM_BIOS_IRQ_CHAINS
] = { 0 };


#define FM_BIOS_RCNT_COUNT 4

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
 * BIOS jump tables
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
     * La RAM basse n'est pas initialisee par un vrai BIOS dans
     * notre bring-up. On fournit au minimum l'entree que les
     * patchs libapi utilisent classiquement :
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
        return;


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
        return result;


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
 * Interrupt checkpoints
 * ============================================================
 */

void psx_check_interrupts_at(
    CPUState *cpu,
    uint32_t resume_pc
)
{
    if (!g_probe_armed)
        return;


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
        return 1;


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
        return 0;


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
     * A0 BIOS
     * ========================================================
     */

    if (phys == 0x000000A0u)
    {
        /*
         * ----------------------------------------------------
         * GPU BIOS family
         *
         * A0:46..A0:4E
         * ----------------------------------------------------
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
             * B0:56 GetC0Table()
             *
             * Retail SCPH-1001/PSOne:
             * C0 jump table = 0x00000674.
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
             *
             * Retail SCPH-1001/PSOne:
             * B0 jump table = 0x00000874.
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
                    safety < 64;
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
                if (
                    a0 < FM_BIOS_RCNT_COUNT
                )
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


void gte_execute(
    CPUState *cpu,
    uint32_t cmd
)
{
    (void)cpu;


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
