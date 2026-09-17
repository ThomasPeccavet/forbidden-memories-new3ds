#include "fm_memory.h"
#include "fm_gpu.h"

#include <stdint.h>
#include <stddef.h>
#include <string.h>


/*
 * ============================================================
 * PS1 memory
 * ============================================================
 */

#define PSX_RAM_SIZE        (2u * 1024u * 1024u)
#define PSX_RAM_MIRROR_END  0x00800000u

#define PSX_SCRATCH_BASE    0x1F800000u
#define PSX_SCRATCH_SIZE    0x00000400u


/*
 * ============================================================
 * Interrupt controller
 * ============================================================
 */

#define PSX_I_STAT          0x1F801070u
#define PSX_I_MASK          0x1F801074u

#define PSX_IRQ_VBLANK      0x0001u
#define PSX_IRQ_VALID_MASK  0x07FFu


/*
 * ============================================================
 * GPU
 * ============================================================
 */

#define PSX_GPU_GP0         0x1F801810u
#define PSX_GPU_GP1         0x1F801814u


/*
 * ============================================================
 * RAM / scratchpad
 * ============================================================
 */

static uint8_t *g_ram = NULL;

static size_t g_ram_size = 0;


static uint8_t g_scratch[
    PSX_SCRATCH_SIZE
];


/*
 * ============================================================
 * Interrupt controller state
 * ============================================================
 */

static uint16_t g_i_stat = 0;

static uint16_t g_i_mask = 0;


/*
 * ============================================================
 * Diagnostics
 * ============================================================
 */

static uint32_t g_last_unmapped = 0;

static unsigned g_unmapped_count = 0;


/*
 * ============================================================
 * Helpers
 * ============================================================
 */

static inline uint32_t fm_phys(
    uint32_t addr
)
{
    /*
     * KSEG0 / KSEG1 -> physical.
     */
    return
        addr
        &
        0x1FFFFFFFu;
}


static void fm_note_unmapped(
    uint32_t addr
)
{
    g_last_unmapped =
        addr;


    ++g_unmapped_count;
}


/*
 * ============================================================
 * RAM pointer
 * ============================================================
 */

static uint8_t *fm_ram_ptr(
    uint32_t phys
)
{
    /*
     * Les 2 Mio de RAM PS1 sont répétés quatre fois
     * entre 0x00000000 et 0x007FFFFF.
     */
    if (
        g_ram
        &&
        g_ram_size != 0
        &&
        phys < PSX_RAM_MIRROR_END
    )
    {
        uint32_t offset =
            phys
            &
            0x001FFFFFu;


        if (offset < g_ram_size)
        {
            return
                &g_ram[offset];
        }
    }


    return NULL;
}


/*
 * ============================================================
 * Scratchpad pointer
 * ============================================================
 */

static uint8_t *fm_scratch_ptr(
    uint32_t phys
)
{
    if (
        phys >= PSX_SCRATCH_BASE
        &&
        phys <
        (
            PSX_SCRATCH_BASE
            +
            PSX_SCRATCH_SIZE
        )
    )
    {
        return
            &g_scratch[
                phys
                -
                PSX_SCRATCH_BASE
            ];
    }


    return NULL;
}


/*
 * ============================================================
 * Init
 * ============================================================
 */

void fm_memory_init(
    uint8_t *ram,
    size_t ram_size
)
{
    g_ram =
        ram;


    g_ram_size =
        ram_size;


    memset(
        g_scratch,
        0,
        sizeof(g_scratch)
    );


    /*
     * Interrupt controller reset.
     */
    g_i_stat =
        0;


    g_i_mask =
        0;


    /*
     * Diagnostics reset.
     */
    g_last_unmapped =
        0;


    g_unmapped_count =
        0;
}


/*
 * ============================================================
 * BYTE READ
 * ============================================================
 */

uint8_t fm_memory_read_byte(
    uint32_t addr
)
{
    uint32_t phys =
        fm_phys(
            addr
        );


    /*
     * --------------------------------------------------------
     * RAM
     * --------------------------------------------------------
     */

    uint8_t *p =
        fm_ram_ptr(
            phys
        );


    if (p)
    {
        return
            *p;
    }


    /*
     * --------------------------------------------------------
     * Scratchpad
     * --------------------------------------------------------
     */

    p =
        fm_scratch_ptr(
            phys
        );


    if (p)
    {
        return
            *p;
    }


    /*
     * --------------------------------------------------------
     * GPUSTAT
     *
     * Lecture byte permise pour les éventuels LBU guest.
     * --------------------------------------------------------
     */

    if (
        phys >= PSX_GPU_GP1
        &&
        phys < PSX_GPU_GP1 + 4u
    )
    {
        uint32_t status =
            fm_gpu_status();


        unsigned shift =
            (
                phys
                -
                PSX_GPU_GP1
            )
            *
            8u;


        return
            (uint8_t)(
                status
                >>
                shift
            );
    }


    /*
     * --------------------------------------------------------
     * GPUREAD
     *
     * Pas encore implémenté.
     * --------------------------------------------------------
     */

    if (
        phys >= PSX_GPU_GP0
        &&
        phys < PSX_GPU_GP0 + 4u
    )
    {
        return 0;
    }


    /*
     * IMPORTANT :
     *
     * Pas d'accès byte pour I_STAT / I_MASK pour le moment.
     *
     * Ils seront volontairement signalés comme unmapped
     * si le jeu tente d'utiliser LB/LBU/SB dessus.
     */


    fm_note_unmapped(
        addr
    );


    return 0;
}


/*
 * ============================================================
 * BYTE WRITE
 * ============================================================
 */

void fm_memory_write_byte(
    uint32_t addr,
    uint8_t value
)
{
    uint32_t phys =
        fm_phys(
            addr
        );


    /*
     * --------------------------------------------------------
     * RAM
     * --------------------------------------------------------
     */

    uint8_t *p =
        fm_ram_ptr(
            phys
        );


    if (p)
    {
        *p =
            value;


        return;
    }


    /*
     * --------------------------------------------------------
     * Scratchpad
     * --------------------------------------------------------
     */

    p =
        fm_scratch_ptr(
            phys
        );


    if (p)
    {
        *p =
            value;


        return;
    }


    /*
     * --------------------------------------------------------
     * GPU
     *
     * GP0 / GP1 sont des ports 32 bits.
     *
     * On ignore volontairement les écritures byte afin
     * de ne pas fabriquer une commande GP0/GP1 incorrecte.
     * --------------------------------------------------------
     */

    if (
        (
            phys >= PSX_GPU_GP0
            &&
            phys < PSX_GPU_GP0 + 4u
        )
        ||
        (
            phys >= PSX_GPU_GP1
            &&
            phys < PSX_GPU_GP1 + 4u
        )
    )
    {
        return;
    }


    /*
     * Pas d'accès byte pour I_STAT / I_MASK actuellement.
     */


    fm_note_unmapped(
        addr
    );
}


/*
 * ============================================================
 * HALF READ
 * ============================================================
 */

uint16_t fm_memory_read_half(
    uint32_t addr
)
{
    uint32_t phys =
        fm_phys(
            addr
        );


    /*
     * --------------------------------------------------------
     * Interrupt controller
     * --------------------------------------------------------
     */

    if (phys == PSX_I_STAT)
    {
        return
            g_i_stat;
    }


    if (phys == PSX_I_MASK)
    {
        return
            g_i_mask;
    }


    /*
     * --------------------------------------------------------
     * RAM
     * --------------------------------------------------------
     */

    uint8_t *p =
        fm_ram_ptr(
            phys
        );


    if (
        p
        &&
        g_ram_size >= 2
        &&
        (
            phys
            &
            0x001FFFFFu
        )
        <=
        g_ram_size - 2
    )
    {
        return
            (uint16_t)p[0]
            |
            (
                (uint16_t)p[1]
                <<
                8
            );
    }


    /*
     * --------------------------------------------------------
     * Scratchpad
     * --------------------------------------------------------
     */

    p =
        fm_scratch_ptr(
            phys
        );


    if (
        p
        &&
        phys
        <=
        PSX_SCRATCH_BASE
        +
        PSX_SCRATCH_SIZE
        -
        2
    )
    {
        return
            (uint16_t)p[0]
            |
            (
                (uint16_t)p[1]
                <<
                8
            );
    }


    /*
     * --------------------------------------------------------
     * GPUSTAT
     * --------------------------------------------------------
     */

    if (
        phys == PSX_GPU_GP1
        ||
        phys == PSX_GPU_GP1 + 2u
    )
    {
        uint32_t value =
            fm_gpu_status();


        unsigned shift =
            (
                phys
                -
                PSX_GPU_GP1
            )
            *
            8u;


        return
            (uint16_t)(
                value
                >>
                shift
            );
    }


    /*
     * --------------------------------------------------------
     * GPUREAD
     * --------------------------------------------------------
     */

    if (
        phys == PSX_GPU_GP0
        ||
        phys == PSX_GPU_GP0 + 2u
    )
    {
        return 0;
    }


    fm_note_unmapped(
        addr
    );


    return 0;
}


/*
 * ============================================================
 * HALF WRITE
 * ============================================================
 */

void fm_memory_write_half(
    uint32_t addr,
    uint16_t value
)
{
    uint32_t phys =
        fm_phys(
            addr
        );


    /*
     * --------------------------------------------------------
     * I_STAT
     *
     * Écrire 0 sur un bit = acquitter l'IRQ.
     * Écrire 1 sur un bit = conserver son état.
     * --------------------------------------------------------
     */

    if (phys == PSX_I_STAT)
    {
        g_i_stat &=
            value
            &
            PSX_IRQ_VALID_MASK;


        return;
    }


    /*
     * --------------------------------------------------------
     * I_MASK
     * --------------------------------------------------------
     */

    if (phys == PSX_I_MASK)
    {
        g_i_mask =
            value
            &
            PSX_IRQ_VALID_MASK;


        return;
    }


    /*
     * --------------------------------------------------------
     * RAM
     * --------------------------------------------------------
     */

    uint8_t *p =
        fm_ram_ptr(
            phys
        );


    if (
        p
        &&
        g_ram_size >= 2
        &&
        (
            phys
            &
            0x001FFFFFu
        )
        <=
        g_ram_size - 2
    )
    {
        p[0] =
            (uint8_t)value;


        p[1] =
            (uint8_t)(
                value
                >>
                8
            );


        return;
    }


    /*
     * --------------------------------------------------------
     * Scratchpad
     * --------------------------------------------------------
     */

    p =
        fm_scratch_ptr(
            phys
        );


    if (
        p
        &&
        phys
        <=
        PSX_SCRATCH_BASE
        +
        PSX_SCRATCH_SIZE
        -
        2
    )
    {
        p[0] =
            (uint8_t)value;


        p[1] =
            (uint8_t)(
                value
                >>
                8
            );


        return;
    }


    /*
     * --------------------------------------------------------
     * GPU
     *
     * GP0 / GP1 restent 32 bits.
     * --------------------------------------------------------
     */

    if (
        phys == PSX_GPU_GP0
        ||
        phys == PSX_GPU_GP0 + 2u
        ||
        phys == PSX_GPU_GP1
        ||
        phys == PSX_GPU_GP1 + 2u
    )
    {
        return;
    }


    fm_note_unmapped(
        addr
    );
}


/*
 * ============================================================
 * WORD READ
 * ============================================================
 */

uint32_t fm_memory_read_word(
    uint32_t addr
)
{
    uint32_t phys =
        fm_phys(
            addr
        );


    /*
     * --------------------------------------------------------
     * Interrupt controller
     * --------------------------------------------------------
     */

    if (phys == PSX_I_STAT)
    {
        return
            g_i_stat;
    }


    if (phys == PSX_I_MASK)
    {
        return
            g_i_mask;
    }


    /*
     * --------------------------------------------------------
     * GPU
     * --------------------------------------------------------
     */

    if (phys == PSX_GPU_GP0)
    {
        /*
         * GPUREAD non encore implémenté.
         */
        return 0;
    }


    if (phys == PSX_GPU_GP1)
    {
        return
            fm_gpu_status();
    }


    /*
     * --------------------------------------------------------
     * RAM
     * --------------------------------------------------------
     */

    uint8_t *p =
        fm_ram_ptr(
            phys
        );


    if (
        p
        &&
        g_ram_size >= 4
        &&
        (
            phys
            &
            0x001FFFFFu
        )
        <=
        g_ram_size - 4
    )
    {
        return
            (uint32_t)p[0]
            |
            (
                (uint32_t)p[1]
                <<
                8
            )
            |
            (
                (uint32_t)p[2]
                <<
                16
            )
            |
            (
                (uint32_t)p[3]
                <<
                24
            );
    }


    /*
     * --------------------------------------------------------
     * Scratchpad
     * --------------------------------------------------------
     */

    p =
        fm_scratch_ptr(
            phys
        );


    if (
        p
        &&
        phys
        <=
        PSX_SCRATCH_BASE
        +
        PSX_SCRATCH_SIZE
        -
        4
    )
    {
        return
            (uint32_t)p[0]
            |
            (
                (uint32_t)p[1]
                <<
                8
            )
            |
            (
                (uint32_t)p[2]
                <<
                16
            )
            |
            (
                (uint32_t)p[3]
                <<
                24
            );
    }


    fm_note_unmapped(
        addr
    );


    return 0;
}


/*
 * ============================================================
 * WORD WRITE
 * ============================================================
 */

void fm_memory_write_word(
    uint32_t addr,
    uint32_t value
)
{
    uint32_t phys =
        fm_phys(
            addr
        );


    /*
     * --------------------------------------------------------
     * Interrupt controller
     * --------------------------------------------------------
     */

    if (phys == PSX_I_STAT)
    {
        g_i_stat &=
            (uint16_t)value
            &
            PSX_IRQ_VALID_MASK;


        return;
    }


    if (phys == PSX_I_MASK)
    {
        g_i_mask =
            (uint16_t)value
            &
            PSX_IRQ_VALID_MASK;


        return;
    }


    /*
     * --------------------------------------------------------
     * GPU GP0
     * --------------------------------------------------------
     */

    if (phys == PSX_GPU_GP0)
    {
        fm_gpu_gp0_write(
            value
        );


        return;
    }


    /*
     * --------------------------------------------------------
     * GPU GP1
     * --------------------------------------------------------
     */

    if (phys == PSX_GPU_GP1)
    {
        fm_gpu_gp1_write(
            value
        );


        return;
    }


    /*
     * --------------------------------------------------------
     * RAM
     * --------------------------------------------------------
     */

    uint8_t *p =
        fm_ram_ptr(
            phys
        );


    if (
        p
        &&
        g_ram_size >= 4
        &&
        (
            phys
            &
            0x001FFFFFu
        )
        <=
        g_ram_size - 4
    )
    {
        p[0] =
            (uint8_t)value;


        p[1] =
            (uint8_t)(
                value
                >>
                8
            );


        p[2] =
            (uint8_t)(
                value
                >>
                16
            );


        p[3] =
            (uint8_t)(
                value
                >>
                24
            );


        return;
    }


    /*
     * --------------------------------------------------------
     * Scratchpad
     * --------------------------------------------------------
     */

    p =
        fm_scratch_ptr(
            phys
        );


    if (
        p
        &&
        phys
        <=
        PSX_SCRATCH_BASE
        +
        PSX_SCRATCH_SIZE
        -
        4
    )
    {
        p[0] =
            (uint8_t)value;


        p[1] =
            (uint8_t)(
                value
                >>
                8
            );


        p[2] =
            (uint8_t)(
                value
                >>
                16
            );


        p[3] =
            (uint8_t)(
                value
                >>
                24
            );


        return;
    }


    fm_note_unmapped(
        addr
    );
}


/*
 * ============================================================
 * VBlank / IRQ helpers
 * ============================================================
 */

void fm_memory_vblank_tick(void)
{
    /*
     * VBlank est latché dans I_STAT.
     *
     * I_MASK ne contrôle pas l'existence de l'événement,
     * seulement sa visibilité côté CPU.
     *
     * L'injection réelle dans COP0 arrivera ensuite.
     */
    g_i_stat |=
        PSX_IRQ_VBLANK;
}


uint16_t fm_memory_i_stat(void)
{
    return
        g_i_stat;
}


uint16_t fm_memory_i_mask(void)
{
    return
        g_i_mask;
}


/*
 * ============================================================
 * Self-test
 * ============================================================
 */

int fm_memory_self_test(void)
{
    if (
        !g_ram
        ||
        g_ram_size < PSX_RAM_SIZE
    )
    {
        return 1;
    }


    /*
     * Sauvegarder les valeurs originales.
     */

    uint32_t old_ram =
        fm_memory_read_word(
            0x80001000u
        );


    uint32_t old_scratch =
        fm_memory_read_word(
            0x1F800100u
        );


    /*
     * --------------------------------------------------------
     * KSEG0
     * --------------------------------------------------------
     */

    fm_memory_write_word(
        0x80001000u,
        0x12345678u
    );


    if (
        fm_memory_read_word(
            0x80001000u
        )
        !=
        0x12345678u
    )
    {
        return 2;
    }


    /*
     * --------------------------------------------------------
     * Physical alias
     * --------------------------------------------------------
     */

    if (
        fm_memory_read_word(
            0x00001000u
        )
        !=
        0x12345678u
    )
    {
        return 3;
    }


    /*
     * --------------------------------------------------------
     * KSEG1 alias
     * --------------------------------------------------------
     */

    if (
        fm_memory_read_word(
            0xA0001000u
        )
        !=
        0x12345678u
    )
    {
        return 4;
    }


    /*
     * --------------------------------------------------------
     * RAM mirror
     * --------------------------------------------------------
     */

    if (
        fm_memory_read_word(
            0x00201000u
        )
        !=
        0x12345678u
    )
    {
        return 5;
    }


    /*
     * --------------------------------------------------------
     * Scratchpad
     * --------------------------------------------------------
     */

    fm_memory_write_word(
        0x1F800100u,
        0xCAFEBABEu
    );


    if (
        fm_memory_read_word(
            0x1F800100u
        )
        !=
        0xCAFEBABEu
    )
    {
        return 6;
    }


    /*
     * Restaurer les données originales.
     */

    fm_memory_write_word(
        0x80001000u,
        old_ram
    );


    fm_memory_write_word(
        0x1F800100u,
        old_scratch
    );


    return 0;
}


/*
 * ============================================================
 * Diagnostics
 * ============================================================
 */

uint32_t fm_memory_last_unmapped(void)
{
    return
        g_last_unmapped;
}


unsigned fm_memory_unmapped_count(void)
{
    return
        g_unmapped_count;
}