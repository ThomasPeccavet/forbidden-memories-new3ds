#include <3ds.h>

#include <stdbool.h>
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
 * CD-ROM HLE bring-up state
 * ============================================================
 */

static uint8_t g_cd_sector[2048];

static uint32_t g_cd_lba = 0;
static uint32_t g_cd_pos = 2048;
static uint32_t g_cd_last_cmd = 0;
static uint32_t g_cd_sector_count = 0;

static int g_cd_reading = 0;
static int g_cd_error = 0;


/*
 * Dernière recherche ISO9660 effectuée par DsSearchFile.
 */
static char g_cd_search_path[256];

static uint32_t g_cd_search_lba = 0;
static uint32_t g_cd_search_size = 0;

static int g_cd_search_ok = 0;


/*
 * Dernier appel BIOS observé.
 *
 * result:
 *  -1 = aucun appel
 *   0 = non traité par fm_bios_try_hle()
 *   1 = traité par fm_bios_try_hle()
 *   2 = traité directement par main.c (bring-up)
 */
static uint32_t g_bios_debug_addr = 0;
static uint32_t g_bios_debug_fn = 0;
static int g_bios_debug_result = -1;


static uint32_t fm_bcd_to_u32(uint8_t value)
{
    return
        ((value >> 4) * 10u)
        +
        (value & 0x0Fu);
}


static void fm_cd_hle_reset(void)
{
    memset(
        g_cd_sector,
        0,
        sizeof(g_cd_sector)
    );

    g_cd_lba = 0;
    g_cd_pos = 2048;
    g_cd_last_cmd = 0;
    g_cd_sector_count = 0;
    g_cd_reading = 0;
    g_cd_error = 0;

    g_cd_search_path[0] = '\0';
    g_cd_search_lba = 0;
    g_cd_search_size = 0;
    g_cd_search_ok = 0;

    g_bios_debug_addr = 0;
    g_bios_debug_fn = 0;
    g_bios_debug_result = -1;
}


/*
 * ============================================================
 * Preview
 * ============================================================
 */

static int load_preview(uint16_t *pixels)
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
    gfxSet3D(false);

    consoleInit(
        GFX_BOTTOM,
        NULL
    );

    bool is_new = false;

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
            * 256
            * sizeof(uint16_t)
        );

    uint8_t *ram =
        malloc(
            2
            * 1024
            * 1024
        );

    if (
        !vram
        || !preview
        || !ram
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
                & KEY_START
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

    int crop = 0;
    int x = 160;
    int y = 128;


    /*
     * ========================================================
     * Disc / EXE
     * ========================================================
     */

    uint32_t entry = 0;

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

    int memory_status = -1;

    CPUState *cpu = NULL;

    uint32_t first_instruction = 0;

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
     * Runtime state
     * ========================================================
     */

    int probe_ran = 0;
    int game_running = 0;
    int static_miss = 0;

    uint32_t last_dispatch_address = 0;

    uint32_t low_jump_from = 0;
    uint32_t low_jump_target = 0;
    uint32_t low_jump_ra = 0;
    uint32_t low_jump_t1 = 0;
    uint32_t low_jump_opcode = 0;

    FMRuntimeProbeResult probe;

    memset(
        &probe,
        0,
        sizeof(probe)
    );

    int interp_ran = 0;

    FMInterpResult interp;

    memset(
        &interp,
        0,
        sizeof(interp)
    );

    unsigned frame = 0;
    uint16_t old_pad = 0;
    uint64_t render_ticks = 0;
    unsigned render_count = 0;

    fm_cd_hle_reset();


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
            && exe_status == 0
            && memory_status == 0
        )
        {
            game_running =
                !game_running;

            static_miss = 0;

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
            game_running = 0;
            static_miss = 0;
            last_dispatch_address = 0;

            low_jump_from = 0;
            low_jump_target = 0;
            low_jump_ra = 0;
            low_jump_t1 = 0;
            low_jump_opcode = 0;

            fm_cd_hle_reset();

            if (exe_status == 0)
            {
                /*
                 * Réinitialise les registres IRQ / scratchpad
                 * tout en conservant le contenu RAM du jeu.
                 */
                fm_memory_init(
                    ram,
                    2 * 1024 * 1024
                );

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

            probe_ran = 0;
            interp_ran = 0;
        }


        /*
         * ====================================================
         * EXECUTION
         * ====================================================
         */

        if (
            game_running
            && cpu
            && exe_status == 0
            && memory_status == 0
        )
        {
            /*
             * Plusieurs passages ARM / BIOS / R3000A
             * dans la même frame.
             */
            for (
                unsigned handoff = 0;
                handoff < 128
                && game_running;
                ++handoff
            )
            {
                uint32_t dispatch_address =
                    cpu->pc;

                uint32_t phys =
                    dispatch_address
                    & 0x1FFFFFFFu;


                /*
                 * ============================================
                 * Diagnostic LOW RAM
                 * ============================================
                 *
                 * Capture la première entrée inattendue dans
                 * la zone kernel BIOS RAM.
                 *
                 * 0x884 / 0x894 sont des helpers PAD Psy-Q
                 * désormais gérés en HLE.
                 */
                if (
                    low_jump_target == 0
                    && phys >= 0x00000500u
                    && phys < 0x00008500u
                    && phys != 0x00000884u
                    && phys != 0x00000894u
                    &&
                    (
                        last_dispatch_address
                        & 0x1FFFFFFFu
                    )
                    >= 0x00008500u
                )
                {
                    low_jump_from =
                        last_dispatch_address;

                    low_jump_target =
                        dispatch_address;

                    low_jump_ra =
                        cpu->gpr[31];

                    low_jump_t1 =
                        cpu->gpr[9];

                    low_jump_opcode =
                        cpu->read_word(
                            dispatch_address
                        );

                    last_dispatch_address =
                        dispatch_address;

                    static_miss = 0;
                    game_running = 0;

                    break;
                }

                last_dispatch_address =
                    dispatch_address;


                /*
                 * ============================================
                 * TEMP HLE - B0:18 ResetEntryInt
                 *
                 * Le handler existe déjà dans
                 * fm_runtime_shim.c, mais sur le bring-up actuel
                 * fm_bios_try_hle() retourne malgré tout 0 pour
                 * cet appel. On le court-circuite ici afin de
                 * poursuivre le boot et d'exposer le prochain
                 * vrai verrou.
                 * ============================================
                 */
                if (
                    phys == 0x000000B0u
                    &&
                    (
                        cpu->gpr[9]
                        &
                        0xFFu
                    )
                    ==
                    0x18u
                )
                {
                    /*
                     * ResetEntryInt : pour le bring-up,
                     * considérer l'ancien hook comme NULL.
                     */
                    cpu->gpr[2] =
                        0;

                    cpu->pc =
                        cpu->gpr[31];

                    cpu->gpr[0] =
                        0;

                    g_bios_debug_addr =
                        0x000000B0u;

                    g_bios_debug_fn =
                        0x18u;

                    /*
                     * 2 = HLE temporaire réalisé par main.c.
                     */
                    g_bios_debug_result =
                        2;

                    static_miss =
                        0;

                    continue;
                }


                /*
                 * ============================================
                 * BIOS vectors / internal PAD helpers
                 * ============================================
                 */
                if (
                    phys == 0x000000A0u
                    || phys == 0x000000B0u
                    || phys == 0x000000C0u
                    || phys == 0x00000884u
                    || phys == 0x00000894u
                )
                {
                    g_bios_debug_addr =
                        dispatch_address;

                    g_bios_debug_fn =
                        cpu->gpr[9]
                        &
                        0xFFu;

                    g_bios_debug_result =
                        fm_bios_try_hle(
                            cpu,
                            dispatch_address
                        );

                    if (g_bios_debug_result)
                    {
                        static_miss = 0;
                        continue;
                    }

                    static_miss = 1;
                    game_running = 0;
                    break;
                }


                /*
                 * ============================================
                 * LibCD initialization HLE
                 *
                 * FUN_8007B53C
                 *
                 * Le code original initialise le contrôleur CD,
                 * ses callbacks et la couche IRQ Psy-Q.
                 *
                 * Notre backend CD est HLE : on expose donc
                 * directement l'état final attendu.
                 * ============================================
                 */
                if (phys == 0x0007B53Cu)
                {
                    /*
                     * DAT_80094CB0 = CD subsystem initialized.
                     */
                    cpu->write_word(
                        0x80094CB0u,
                        1
                    );


                    /*
                     * DAT_80094930 = CD interrupt layer ready.
                     */
                    cpu->write_word(
                        0x80094930u,
                        1
                    );


                    /*
                     * Callbacks internes Psy-Q.
                     */
                    cpu->write_word(
                        0x80094910u,
                        0x8007CA78u
                    );


                    cpu->write_word(
                        0x80094914u,
                        0x8007D0E0u
                    );


                    /*
                     * Callbacks utilisateur initialement NULL.
                     */
                    cpu->write_word(
                        0x800F7308u,
                        0
                    );


                    cpu->write_word(
                        0x800F730Cu,
                        0
                    );


                    cpu->write_word(
                        0x800F7310u,
                        0
                    );


                    /*
                     * Retour succès.
                     */
                    cpu->gpr[2] = 1;

                    cpu->pc =
                        cpu->gpr[31];

                    cpu->gpr[0] = 0;

                    static_miss = 0;

                    continue;
                }


                /*
                 * ============================================
                 * DsSearchFile HLE
                 *
                 * FUN_8007D988
                 *
                 * Cherche un chemin dans l'ISO9660 puis remplit
                 * le CdlFILE de sortie.
                 * ============================================
                 */
                if (phys == 0x0007D988u)
                {
                    uint32_t output =
                        cpu->gpr[4];

                    uint32_t guest_path =
                        cpu->gpr[5];

                    char path[256];

                    unsigned i = 0;


                    while (
                        i < sizeof(path) - 1
                    )
                    {
                        uint8_t c =
                            cpu->read_byte(
                                guest_path + i
                            );

                        path[i] =
                            (char)c;

                        ++i;

                        if (c == 0)
                        {
                            break;
                        }
                    }


                    path[
                        sizeof(path) - 1
                    ] =
                        '\0';


                    strncpy(
                        g_cd_search_path,
                        path,
                        sizeof(g_cd_search_path) - 1
                    );

                    g_cd_search_path[
                        sizeof(g_cd_search_path) - 1
                    ] =
                        '\0';


                    uint32_t file_lba = 0;
                    uint32_t file_size = 0;


                    g_cd_search_ok =
                        fm_disc_find_file(
                            path,
                            &file_lba,
                            &file_size
                        );


                    g_cd_search_lba =
                        file_lba;

                    g_cd_search_size =
                        file_size;


                    if (
                        g_cd_search_ok
                        &&
                        output != 0
                    )
                    {
                        /*
                         * CdlLOC attendu en MSF BCD.
                         */
                        uint32_t absolute =
                            file_lba
                            +
                            150u;

                        uint32_t minute =
                            absolute
                            /
                            (60u * 75u);

                        uint32_t second =
                            (
                                absolute
                                /
                                75u
                            )
                            %
                            60u;

                        uint32_t sector =
                            absolute
                            %
                            75u;


                        uint8_t minute_bcd =
                            (uint8_t)(
                                ((minute / 10u) << 4)
                                |
                                (minute % 10u)
                            );

                        uint8_t second_bcd =
                            (uint8_t)(
                                ((second / 10u) << 4)
                                |
                                (second % 10u)
                            );

                        uint8_t sector_bcd =
                            (uint8_t)(
                                ((sector / 10u) << 4)
                                |
                                (sector % 10u)
                            );


                        /*
                         * CdlFILE minimal :
                         *
                         * +0  CdlLOC
                         * +4  taille
                         * +8  nom[16]
                         */
                        cpu->write_byte(
                            output + 0,
                            minute_bcd
                        );

                        cpu->write_byte(
                            output + 1,
                            second_bcd
                        );

                        cpu->write_byte(
                            output + 2,
                            sector_bcd
                        );

                        cpu->write_byte(
                            output + 3,
                            0
                        );


                        cpu->write_word(
                            output + 4,
                            file_size
                        );


                        for (
                            unsigned n = 0;
                            n < 16;
                            ++n
                        )
                        {
                            cpu->write_byte(
                                output + 8 + n,
                                0
                            );
                        }


                        /*
                         * DsSearchFile retourne un pointeur non NULL.
                         */
                        cpu->gpr[2] =
                            output;
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

                    static_miss =
                        0;

                    continue;
                }


                /*
                 * ============================================
                 * LibCD command HLE
                 *
                 * FUN_8007A1D4
                 * ============================================
                 */
                if (phys == 0x0007A1D4u)
                {
                    uint32_t command =
                        cpu->gpr[4]
                        & 0xFFu;

                    uint32_t params =
                        cpu->gpr[5];

                    uint32_t result =
                        cpu->gpr[6];

                    g_cd_last_cmd =
                        command;


                    /*
                     * CdlSetloc = 02
                     */
                    if (
                        command == 0x02u
                        && params != 0
                    )
                    {
                        uint32_t minute =
                            fm_bcd_to_u32(
                                cpu->read_byte(
                                    params + 0
                                )
                            );

                        uint32_t second =
                            fm_bcd_to_u32(
                                cpu->read_byte(
                                    params + 1
                                )
                            );

                        uint32_t frame_cd =
                            fm_bcd_to_u32(
                                cpu->read_byte(
                                    params + 2
                                )
                            );

                        uint32_t absolute_sector =
                            (
                                (
                                    minute * 60u
                                    + second
                                )
                                * 75u
                            )
                            + frame_cd;

                        if (absolute_sector >= 150u)
                        {
                            g_cd_lba =
                                absolute_sector - 150u;
                        }
                        else
                        {
                            g_cd_lba = 0;
                        }

                        g_cd_pos = 2048;
                    }


                    /*
                     * CdlReadN = 06
                     */
                    if (command == 0x06u)
                    {
                        g_cd_reading = 1;
                        g_cd_pos = 2048;
                        g_cd_error = 0;
                    }


                    /*
                     * CdlPause = 09
                     */
                    if (command == 0x09u)
                    {
                        g_cd_reading = 0;
                    }


                    /*
                     * Commandes temporairement traitées en HLE.
                     */
                    if (
                        command == 0x01u
                        || command == 0x02u
                        || command == 0x06u
                        || command == 0x09u
                        || command == 0x0Au
                        || command == 0x0Cu
                        || command == 0x0Eu
                        || command == 0x15u
                        || command == 0x16u
                    )
                    {
                        if (result != 0)
                        {
                            cpu->write_byte(
                                result + 0,
                                0x02
                            );

                            for (
                                unsigned i = 1;
                                i < 8;
                                ++i
                            )
                            {
                                cpu->write_byte(
                                    result + i,
                                    0
                                );
                            }
                        }

                        /*
                         * Etat interne Psy-Q LibCD :
                         * Sync = Complete.
                         */
                        cpu->write_byte(
                            0x80094BECu,
                            2
                        );

                        cpu->write_byte(
                            0x80094BEDu,
                            0
                        );

                        cpu->write_byte(
                            0x80094BEEu,
                            0
                        );

                        cpu->write_byte(
                            0x8009491Cu,
                            0x02
                        );

                        cpu->gpr[2] = 0;
                        cpu->pc = cpu->gpr[31];
                        cpu->gpr[0] = 0;

                        static_miss = 0;
                        continue;
                    }
                }


                /*
                 * ============================================
                 * DMA3 CD-ROM HLE
                 *
                 * FUN_80079580
                 * ============================================
                 */
                if (
                    phys == 0x00079580u
                    && cpu->gpr[4] == 3u
                    && g_cd_reading
                )
                {
                    uint32_t destination =
                        cpu->gpr[5];

                    uint32_t words =
                        cpu->gpr[7];

                    uint32_t bytes =
                        words * 4u;

                    /*
                     * Protection bring-up.
                     * Les transferts vus ici doivent rester
                     * dans un secteur de 2048 octets.
                     */
                    if (bytes > 2048u)
                    {
                        bytes = 2048u;
                    }

                    for (
                        uint32_t i = 0;
                        i < bytes;
                        ++i
                    )
                    {
                        if (g_cd_pos >= 2048u)
                        {
                            int rc =
                                fm_disc_read_sector(
                                    g_cd_lba,
                                    g_cd_sector
                                );

                            if (rc != 0)
                            {
                                g_cd_error = rc;

                                memset(
                                    g_cd_sector,
                                    0,
                                    sizeof(g_cd_sector)
                                );
                            }
                            else
                            {
                                g_cd_error = 0;
                                ++g_cd_sector_count;
                            }

                            g_cd_pos = 0;
                        }

                        cpu->write_byte(
                            destination + i,
                            g_cd_sector[g_cd_pos]
                        );

                        ++g_cd_pos;

                        if (g_cd_pos >= 2048u)
                        {
                            ++g_cd_lba;
                        }
                    }

                    /*
                     * FUN_80079580 est void.
                     */
                    cpu->pc =
                        cpu->gpr[31];

                    cpu->gpr[0] = 0;
                    static_miss = 0;

                    continue;
                }


                /*
                 * ============================================
                 * ARM recompiled code
                 * ============================================
                 */
                probe =
                    fm_runtime_probe(
                        cpu,
                        dispatch_address,
                        250000
                    );

                probe_ran = 1;


                /*
                 * Time slice.
                 */
                if (
                    probe.reason
                    == FM_STOP_BUDGET
                )
                {
                    static_miss = 0;
                    break;
                }


                /*
                 * Normal dispatcher return.
                 */
                if (
                    probe.reason
                    == FM_STOP_RETURNED
                )
                {
                    /*
                     * Static ARM code found.
                     */
                    if (
                        probe.dispatch_result
                        == 1
                    )
                    {
                        if (
                            cpu->pc == 0
                            && cpu->gpr[31] != 0
                        )
                        {
                            cpu->pc =
                                cpu->gpr[31];
                        }

                        if (cpu->pc == 0)
                        {
                            game_running = 0;
                            static_miss = 0;
                            break;
                        }

                        static_miss = 0;
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

                    interp_ran = 1;

                    if (
                        interp.reason
                        == FM_INTERP_BLOCK_DONE
                    )
                    {
                        static_miss = 0;
                        continue;
                    }

                    if (
                        interp.reason
                        == FM_INTERP_BUDGET
                    )
                    {
                        static_miss = 0;
                        break;
                    }

                    /*
                     * Instruction actuellement non supportée.
                     */
                    static_miss = 0;
                    game_running = 0;
                    break;
                }


                /*
                 * Native runtime stop.
                 */
                game_running = 0;
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
            && have_preview
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

        if (fm_gpu_has_frame())
        {
            unsigned display_x =
                fm_gpu_display_x();

            unsigned display_y =
                fm_gpu_display_y();

            const uint16_t *game_frame =
                vram
                + display_y * 1024
                + display_x;

            fm_present_rgb555(
                game_frame,
                1024,
                crop
            );
        }
        else if (show_preview)
        {
            fm_present_rgb555(
                preview,
                320,
                crop
            );
        }
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
                (frame / 2)
                % 32;

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
            - render_start;

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
            || pad != old_pad
            || down
        )
        {
            printf(
                "\x1b[2J"
                "\x1b[H"
            );


            /*
             * =================================================
             * DEBUG COMPACT
             *
             * Volontairement dense afin de garder CPU, ARM,
             * R3000A, GPU, CD, ISO et BIOS visibles ensemble.
             * =================================================
             */

            printf(
                "RAM          : %s\n",
                memory_status == 0
                    ? "OK"
                    : "ERR"
            );


            printf(
                "I_STAT/MASK  : %04X / %04X\n",
                (unsigned)fm_memory_i_stat(),
                (unsigned)fm_memory_i_mask()
            );


            printf(
                "Last MMIO    : %08lX (%u)\n",
                (unsigned long)
                    fm_memory_last_unmapped(),
                fm_memory_unmapped_count()
            );


            printf(
                "\n--- CPU ---\n"
            );


            if (cpu)
            {
                printf(
                    "PC  : %08lX RA : %08lX\n",
                    (unsigned long)cpu->pc,
                    (unsigned long)cpu->gpr[31]
                );


                printf(
                    "A0  : %08lX A1 : %08lX\n",
                    (unsigned long)cpu->gpr[4],
                    (unsigned long)cpu->gpr[5]
                );


                printf(
                    "A2  : %08lX T1 : %08lX\n",
                    (unsigned long)cpu->gpr[6],
                    (unsigned long)cpu->gpr[9]
                );
            }


            printf(
                "--- ARM RECOMP --- RUN : %s\n",
                game_running
                    ? "OUI"
                    : "NON"
            );


            printf(
                "Stop ARM     : %s\n",
                probe_ran
                    ? fm_runtime_stop_name(
                        probe.reason
                    )
                    : "-"
            );


            printf(
                "Dispatch     : %08lX / %d\n",
                (unsigned long)
                    last_dispatch_address,
                probe_ran
                    ? probe.dispatch_result
                    : -1
            );


            printf(
                "--- R3000A --- Utilise : %s\n",
                interp_ran
                    ? "OUI"
                    : "NON"
            );


            printf(
                "Stop interp  : %s\n",
                interp_ran
                    ? fm_interp_stop_name(
                        interp.reason
                    )
                    : "-"
            );


            printf(
                "PC/opcode    : %08lX %08lX\n",
                interp_ran
                    ? (unsigned long)interp.pc
                    : 0ul,
                interp_ran
                    ? (unsigned long)interp.instruction
                    : 0ul
            );


            printf(
                "--- GPU PS1 --- GP0 words : %llu\n",
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
                "--- LOW RAM JUMP --- From/Target : %08lX / %08lX\n",
                (unsigned long)low_jump_from,
                (unsigned long)low_jump_target
            );


            printf(
                "Opcode       : %08lX\n",
                (unsigned long)low_jump_opcode
            );


            printf(
                "RA / T1      : %08lX / %02lX\n",
                (unsigned long)low_jump_ra,
                (unsigned long)low_jump_t1
            );


            printf(
                "--- CD HLE --- Cmd/LBA : %02lX / %lu\n",
                (unsigned long)g_cd_last_cmd,
                (unsigned long)g_cd_lba
            );


            printf(
                "Pos/sec      : %lu / %lu\n",
                (unsigned long)g_cd_pos,
                (unsigned long)g_cd_sector_count
            );


            printf(
                "Read/err     : %s / %d\n",
                g_cd_reading
                    ? "OUI"
                    : "NON",
                g_cd_error
            );


            printf(
                "--- ISO SEARCH --- OK : %s\n",
                g_cd_search_ok
                    ? "OUI"
                    : "NON"
            );


            printf(
                "LBA / size   : %lu / %lu\n",
                (unsigned long)g_cd_search_lba,
                (unsigned long)g_cd_search_size
            );


            printf(
                "Path         : %.34s\n",
                g_cd_search_path
            );


            printf(
                "BIOS dbg     : %08lX / %02lX / %d\n",
                (unsigned long)g_bios_debug_addr,
                (unsigned long)g_bios_debug_fn,
                g_bios_debug_result
            );


            /*
             * Reset des compteurs de mesure de rendu sans
             * consommer une ligne supplémentaire à l'écran.
             */
            if (
                frame % 30 == 0
                && frame != 0
                && render_count != 0
            )
            {
                render_ticks = 0;
                render_count = 0;
            }
        }

        old_pad =
            pad;

        ++frame;


        /*
         * Latch VBlank PS1 une fois par frame 3DS.
         */
        if (memory_status == 0)
        {
            fm_memory_vblank_tick();
        }


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
