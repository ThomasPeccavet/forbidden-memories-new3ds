#include <3ds.h>

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fm_platform.h"
#include "fm_cpu.h"
#include "fm_memory.h"
#include "fm_runtime_shim.h"
#include "fm_interp.h"
#include "fm_gpu.h"

#include "gpu_sw_renderer.h"


int g_ws_bd_stretch_on = 0;

int g_ws_bd_stretch_pct = 100;


int psx_ws_prim_in_backdrop(void)
{
    return 0;
}


/*
 * ============================================================
 * Preview
 * ============================================================
 */

static int load_preview(
    uint16_t *pixels
)
{
    FILE *f =
        fopen(
            "sdmc:/3ds/fm-new3ds/preview.rgb555",
            "rb"
        );


    if (!f)
    {
        return 0;
    }


    int ok =
        fread(
            pixels,
            sizeof(uint16_t),
            320 * 256,
            f
        )
        ==
        320 * 256;


    fclose(f);


    return ok;
}


/*
 * ============================================================
 * Main
 * ============================================================
 */

int main(void)
{
    gfxInitDefault();

    gfxSet3D(
        false
    );


    consoleInit(
        GFX_BOTTOM,
        NULL
    );


    bool is_new =
        false;


    APT_CheckNew3DS(
        &is_new
    );


    if (is_new)
    {
        osSetSpeedupEnable(
            true
        );
    }


    /*
     * ========================================================
     * Memory
     * ========================================================
     */

    uint16_t *vram =
        calloc(
            1024 * 512,
            sizeof(uint16_t)
        );


    uint16_t *preview =
        malloc(
            320
            *
            256
            *
            sizeof(uint16_t)
        );


    uint8_t *ram =
        malloc(
            2
            *
            1024
            *
            1024
        );


    if (
        !vram
        ||
        !preview
        ||
        !ram
    )
    {
        printf(
            "Memoire insuffisante.\n"
        );


        while (aptMainLoop())
        {
            hidScanInput();


            if (
                hidKeysDown()
                &
                KEY_START
            )
            {
                break;
            }


            gspWaitForVBlank();
        }


        free(vram);
        free(preview);
        free(ram);


        gfxExit();


        return 1;
    }


    memset(
        ram,
        0,
        2 * 1024 * 1024
    );


    /*
     * ========================================================
     * Renderer / GPU
     * ========================================================
     */

    sw_renderer_init(
        vram
    );


    sw_renderer_set_scale(
        1
    );


    fm_gpu_init(
        vram
    );


    /*
     * ========================================================
     * Preview prototype
     * ========================================================
     */

    int have_preview =
        load_preview(
            preview
        );


    int show_preview =
        have_preview;


    int crop =
        0;


    int x =
        160;


    int y =
        128;


    /*
     * ========================================================
     * Disc / EXE
     * ========================================================
     */

    uint32_t entry =
        0;


    int disc_status =
        fm_disc_open(
            "sdmc:/3ds/fm-new3ds/disc.bin"
        );


    int exe_status =
        disc_status
            ? -99
            : fm_disc_load_exe(
                ram,
                &entry
            );


    /*
     * ========================================================
     * PS1 CPU
     * ========================================================
     */

    int memory_status =
        -1;


    CPUState *cpu =
        NULL;


    uint32_t first_instruction =
        0;


    if (exe_status == 0)
    {
        fm_memory_init(
            ram,
            2 * 1024 * 1024
        );


        fm_cpu_init(
            entry
        );


        memory_status =
            fm_memory_self_test();


        cpu =
            fm_cpu_get();


        first_instruction =
            cpu->read_word(
                cpu->pc
            );
    }


    /*
     * ========================================================
     * Runtime
     * ========================================================
     */

    int probe_ran =
        0;


    int game_running =
        0;


    int static_miss =
        0;


    uint32_t last_dispatch_address =
        0;


    FMRuntimeProbeResult probe;


    memset(
        &probe,
        0,
        sizeof(probe)
    );


    int interp_ran =
        0;


    FMInterpResult interp;


    memset(
        &interp,
        0,
        sizeof(interp)
    );


    unsigned frame =
        0;


    uint16_t old_pad =
        0;


    uint64_t render_ticks =
        0;


    unsigned render_count =
        0;


    /*
     * ========================================================
     * Main loop
     * ========================================================
     */

    while (aptMainLoop())
    {
        hidScanInput();


        uint32_t held =
            hidKeysHeld();


        uint32_t down =
            hidKeysDown();


        /*
         * Exit
         */
        if (
            (
                held
                &
                (
                    KEY_START
                    |
                    KEY_SELECT
                )
            )
            ==
            (
                KEY_START
                |
                KEY_SELECT
            )
        )
        {
            break;
        }


        /*
         * ====================================================
         * RUN / PAUSE
         * ====================================================
         */

        if (
            (down & KEY_A)
            &&
            exe_status == 0
            &&
            memory_status == 0
        )
        {
            game_running =
                !game_running;


            static_miss =
                0;


            if (!probe_ran)
            {
                fm_cpu_init(
                    entry
                );


                cpu =
                    fm_cpu_get();
            }
        }


        /*
         * ====================================================
         * RESET
         * ====================================================
         */

        if (down & KEY_B)
        {
            game_running =
                0;


            static_miss =
                0;


            last_dispatch_address =
                0;


            if (exe_status == 0)
            {
                fm_cpu_init(
                    entry
                );


                cpu =
                    fm_cpu_get();
            }


            fm_gpu_init(
                vram
            );


            memset(
                &probe,
                0,
                sizeof(probe)
            );


            memset(
                &interp,
                0,
                sizeof(interp)
            );


            probe_ran =
                0;


            interp_ran =
                0;
        }


        /*
         * ====================================================
         * EXECUTION
         * ====================================================
         */

        if (
            game_running
            &&
            cpu
            &&
            exe_status == 0
            &&
            memory_status == 0
        )
        {
            /*
             * Plusieurs passages ARM / BIOS / interpréteur
             * dans la même frame.
             */
            for (
                unsigned handoff = 0;
                handoff < 128
                &&
                game_running;
                ++handoff
            )
            {
                uint32_t dispatch_address =
                    cpu->pc;


                last_dispatch_address =
                    dispatch_address;


                uint32_t phys =
                    dispatch_address
                    &
                    0x1FFFFFFFu;


                /*
                 * BIOS vectors.
                 */
                if (
                    phys == 0xA0u
                    ||
                    phys == 0xB0u
                    ||
                    phys == 0xC0u
                )
                {
                    if (
                        fm_bios_try_hle(
                            cpu,
                            dispatch_address
                        )
                    )
                    {
                        static_miss =
                            0;


                        continue;
                    }


                    static_miss =
                        1;


                    game_running =
                        0;


                    break;
                }


                /*
                 * ARM recompiled code.
                 */
                probe =
                    fm_runtime_probe(
                        cpu,
                        dispatch_address,
                        250000
                    );


                probe_ran =
                    1;


                /*
                 * Time slice.
                 */
                if (
                    probe.reason
                    ==
                    FM_STOP_BUDGET
                )
                {
                    static_miss =
                        0;


                    break;
                }


                /*
                 * Normal dispatcher return.
                 */
                if (
                    probe.reason
                    ==
                    FM_STOP_RETURNED
                )
                {
                    /*
                     * Static ARM code found.
                     */
                    if (
                        probe.dispatch_result
                        ==
                        1
                    )
                    {
                        if (
                            cpu->pc == 0
                            &&
                            cpu->gpr[31] != 0
                        )
                        {
                            cpu->pc =
                                cpu->gpr[31];
                        }


                        if (cpu->pc == 0)
                        {
                            game_running =
                                0;


                            static_miss =
                                0;


                            break;
                        }


                        static_miss =
                            0;


                        continue;
                    }


                    /*
                     * ========================================
                     * R3000A fallback
                     * ========================================
                     */

                    interp =
                        fm_interp_run_block(
                            cpu,
                            1024
                        );


                    interp_ran =
                        1;


                    if (
                        interp.reason
                        ==
                        FM_INTERP_BLOCK_DONE
                    )
                    {
                        static_miss =
                            0;


                        continue;
                    }


                    if (
                        interp.reason
                        ==
                        FM_INTERP_BUDGET
                    )
                    {
                        static_miss =
                            0;


                        break;
                    }


                    /*
                     * Instruction actuellement non supportée.
                     */
                    static_miss =
                        0;


                    game_running =
                        0;


                    break;
                }


                /*
                 * Native runtime stop.
                 */
                game_running =
                    0;


                break;
            }
        }


        /*
         * ====================================================
         * Old prototype controls
         * ====================================================
         */

        if (
            (down & KEY_X)
            &&
            have_preview
        )
        {
            show_preview =
                !show_preview;
        }


        if (down & KEY_Y)
        {
            crop =
                !crop;
        }


        x +=
            (held & KEY_DRIGHT ? 2 : 0)
            -
            (held & KEY_DLEFT ? 2 : 0);


        y +=
            (held & KEY_DDOWN ? 2 : 0)
            -
            (held & KEY_DUP ? 2 : 0);


        if (x < 32)
            x = 32;


        if (x > 288)
            x = 288;


        if (y < 32)
            y = 32;


        if (y > 224)
            y = 224;


        /*
         * ====================================================
         * TOP SCREEN
         * ====================================================
         */

        uint64_t render_start =
            svcGetSystemTick();


        /*
         * ================================================
         * GAME VRAM
         *
         * Dès qu'un vrai draw GPU a eu lieu,
         * le triangle disparaît.
         * ================================================
         */

        if (
            fm_gpu_has_frame()
        )
        {
            unsigned display_x =
                fm_gpu_display_x();


            unsigned display_y =
                fm_gpu_display_y();


            const uint16_t *game_frame =
                vram
                +
                display_y * 1024
                +
                display_x;


            fm_present_rgb555(
                game_frame,
                1024,
                crop
            );
        }

        /*
         * Ancienne preview.
         */
        else if (
            show_preview
        )
        {
            fm_present_rgb555(
                preview,
                320,
                crop
            );
        }

        /*
         * Triangle de diagnostic.
         */
        else
        {
            sw_fill_rect(
                0,
                0,
                320,
                256,
                0x1842
            );


            int pulse =
                (
                    frame
                    /
                    2
                )
                %
                32;


            sw_draw_gouraud_triangle(
                x,
                y - 30,
                31,

                x - 30,
                y + 30,
                31 << 5,

                x + 30,
                y + 30,
                (uint16_t)(
                    pulse << 10
                )
            );


            fm_present_rgb555(
                vram,
                1024,
                crop
            );
        }


        render_ticks +=
            svcGetSystemTick()
            -
            render_start;


        ++render_count;


        /*
         * ====================================================
         * Controller
         * ====================================================
         */

        uint16_t pad =
            fm_pad_bits(
                held
            );


        /*
         * ====================================================
         * Debug console
         * ====================================================
         */

        if (
            frame % 30 == 0
            ||
            pad != old_pad
            ||
            down
        )
        {
            printf(
                "\x1b[2J"
                "\x1b[H"
            );


            printf(
                "FORBIDDEN MEMORIES / NEW 3DS\n"
            );


            printf(
                "============================\n"
            );


            printf(
                "Disque     : %d\n",
                disc_status
            );


            printf(
                "EXE        : %d\n",
                exe_status
            );


            printf(
                "Entry      : %08lX\n",
                (unsigned long)
                    entry
            );


            printf(
                "Instr @PC  : %08lX\n",
                (unsigned long)
                    first_instruction
            );


            printf(
                "RAM        : %s\n",
                memory_status == 0
                    ? "OK"
                    : "ERREUR"
            );


            printf(
                "Unmapped   : %u\n",
                fm_memory_unmapped_count()
            );


            if (
                fm_memory_unmapped_count()
                !=
                0
            )
            {
                printf(
                    "Last MMIO  : %08lX\n",
                    (unsigned long)
                        fm_memory_last_unmapped()
                );
            }


            /*
             * CPU
             */
            printf(
                "\n--- CPU ---\n"
            );


            if (cpu)
            {
                printf(
                    "PC : %08lX  RA : %08lX\n",
                    (unsigned long)
                        cpu->pc,
                    (unsigned long)
                        cpu->gpr[31]
                );


                printf(
                    "A0 : %08lX  A1 : %08lX\n",
                    (unsigned long)
                        cpu->gpr[4],
                    (unsigned long)
                        cpu->gpr[5]
                );


                printf(
                    "A2 : %08lX  T1 : %08lX\n",
                    (unsigned long)
                        cpu->gpr[6],
                    (unsigned long)
                        cpu->gpr[9]
                );
            }


            /*
             * ARM
             */
            printf(
                "\n--- ARM RECOMP ---\n"
            );


            printf(
                "RUN         : %s\n",
                game_running
                    ? "OUI"
                    : "NON"
            );


            if (probe_ran)
            {
                printf(
                    "Stop ARM    : %s\n",
                    fm_runtime_stop_name(
                        probe.reason
                    )
                );


                printf(
                    "Dispatch    : %08lX / %d\n",
                    (unsigned long)
                        last_dispatch_address,
                    probe.dispatch_result
                );
            }


            /*
             * Interpreter
             */
            printf(
                "\n--- R3000A ---\n"
            );


            printf(
                "Utilise      : %s\n",
                interp_ran
                    ? "OUI"
                    : "NON"
            );


            if (interp_ran)
            {
                printf(
                    "Stop interp  : %s\n",
                    fm_interp_stop_name(
                        interp.reason
                    )
                );


                printf(
                    "PC/opcode    : %08lX %08lX\n",
                    (unsigned long)
                        interp.pc,
                    (unsigned long)
                        interp.instruction
                );
            }


            /*
             * GPU
             */
            printf(
                "\n--- GPU PS1 ---\n"
            );


            printf(
                "GP0 words    : %llu\n",
                (unsigned long long)
                    fm_gpu_gp0_count()
            );


            printf(
                "Frame VRAM   : %s\n",
                fm_gpu_has_frame()
                    ? "OUI"
                    : "NON"
            );


            printf(
                "Display XY   : %u,%u\n",
                fm_gpu_display_x(),
                fm_gpu_display_y()
            );


            printf(
                "GPUSTAT      : %08lX\n",
                (unsigned long)
                    fm_gpu_status()
            );


            printf(
                "Static miss  : %s\n",
                static_miss
                    ? "OUI"
                    : "NON"
            );


            printf(
                "\nA : RUN / PAUSE\n"
            );


            printf(
                "B : RESET JEU\n"
            );


            printf(
                "START+SELECT : quitter\n"
            );


            if (
                frame % 30 == 0
                &&
                frame != 0
                &&
                render_count != 0
            )
            {
                printf(
                    "\nRendu moyen : %.2f ms\n",
                    (double)
                        render_ticks
                        *
                        1000.0
                        /
                        SYSCLOCK_ARM11
                        /
                        render_count
                );


                render_ticks =
                    0;


                render_count =
                    0;
            }
        }


        old_pad =
            pad;


        ++frame;


        gfxFlushBuffers();

        gfxSwapBuffers();

        gspWaitForVBlank();
    }


    /*
     * ========================================================
     * Exit
     * ========================================================
     */

    fm_disc_close();


    free(vram);
    free(preview);
    free(ram);


    gfxExit();


    return 0;
}