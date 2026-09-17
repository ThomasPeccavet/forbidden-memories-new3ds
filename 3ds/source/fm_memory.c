#include "fm_memory.h"
#include "fm_gpu.h"

#include <stddef.h>
#include <stdint.h>
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
#define PSX_IRQ_DMA         0x0008u
#define PSX_IRQ_VALID_MASK  0x07FFu


/*
 * ============================================================
 * DMA controller
 * ============================================================
 *
 * Canal 2 = GPU.
 */

#define PSX_DMA2_MADR       0x1F8010A0u
#define PSX_DMA2_BCR        0x1F8010A4u
#define PSX_DMA2_CHCR       0x1F8010A8u

#define PSX_DMA_DPCR        0x1F8010F0u
#define PSX_DMA_DICR        0x1F8010F4u


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

static uint8_t g_scratch[PSX_SCRATCH_SIZE];


/*
 * ============================================================
 * Interrupt controller state
 * ============================================================
 */

static uint16_t g_i_stat = 0;
static uint16_t g_i_mask = 0;


/*
 * ============================================================
 * DMA state
 * ============================================================
 */

static uint32_t g_dma2_madr = 0;
static uint32_t g_dma2_bcr = 0;
static uint32_t g_dma2_chcr = 0;

static uint32_t g_dma_dpcr = 0;
static uint32_t g_dma_dicr = 0;

/*
 * Diagnostics internes. Ils pourront être exposés plus tard
 * dans fm_memory.h si on veut les afficher sur l'écran inférieur.
 */
static uint32_t g_dma2_transfer_count = 0;
static uint64_t g_dma2_word_count = 0;


/*
 * ============================================================
 * Diagnostics
 * ============================================================
 */

static uint32_t g_last_unmapped = 0;
static unsigned g_unmapped_count = 0;


/*
 * ============================================================
 * Generic helpers
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
 * Raw RAM helpers used by DMA
 * ============================================================
 *
 * DMA addresses are physical RAM addresses.
 * Keep these helpers independent from fm_memory_read_word()
 * so DMA cannot recursively hit MMIO.
 */

static uint32_t fm_dma_ram_read_word(
    uint32_t addr
)
{
    uint32_t offset =
        addr
        &
        0x001FFFFCu;

    if (
        !g_ram
        ||
        g_ram_size < 4
        ||
        offset > g_ram_size - 4
    )
    {
        return 0;
    }

    return
        (uint32_t)g_ram[offset + 0]
        |
        ((uint32_t)g_ram[offset + 1] << 8)
        |
        ((uint32_t)g_ram[offset + 2] << 16)
        |
        ((uint32_t)g_ram[offset + 3] << 24);
}


/*
 * ============================================================
 * DMA IRQ helpers
 * ============================================================
 */

static int fm_dma_irq_active(void)
{
    /*
     * DICR:
     *
     * bit 15     force IRQ
     * bits 16-22 IRQ enable channel 0..6
     * bit 23     master IRQ enable
     * bits 24-30 IRQ flags channel 0..6
     * bit 31     master IRQ flag (read-only, derived)
     */

    uint32_t force_irq =
        (
            g_dma_dicr
            >>
            15
        )
        &
        1u;

    uint32_t master_enable =
        (
            g_dma_dicr
            >>
            23
        )
        &
        1u;

    uint32_t enables =
        (
            g_dma_dicr
            >>
            16
        )
        &
        0x7Fu;

    uint32_t flags =
        (
            g_dma_dicr
            >>
            24
        )
        &
        0x7Fu;

    return
        force_irq
        ||
        (
            master_enable
            &&
            (
                enables
                &
                flags
            )
            !=
            0
        );
}


static uint32_t fm_dma_dicr_read(void)
{
    uint32_t value =
        g_dma_dicr
        &
        0x7FFFFFFFu;

    if (fm_dma_irq_active())
    {
        value |=
            0x80000000u;
    }

    return value;
}


static void fm_dma_update_irq(void)
{
    /*
     * L'IRQ DMA est latchée dans I_STAT.
     *
     * Elle restera présente jusqu'à ce que le guest acquitte
     * I_STAT bit 3, même si DICR n'est plus actif ensuite.
     */
    if (fm_dma_irq_active())
    {
        g_i_stat |=
            PSX_IRQ_DMA;
    }
}


/*
 * ============================================================
 * DMA2 completion
 * ============================================================
 */

static void fm_dma2_complete(void)
{
    /*
     * CHCR bit 24 = START/BUSY.
     * CHCR bit 28 = trigger manuel.
     *
     * Le hardware les relâche lorsque le DMA se termine.
     */
    g_dma2_chcr &=
        ~(
            0x01000000u
            |
            0x10000000u
        );

    /*
     * DICR flag canal 2 = bit 26.
     */
    g_dma_dicr |=
        1u
        <<
        26;

    ++g_dma2_transfer_count;

    fm_dma_update_irq();
}


/*
 * ============================================================
 * DMA2 linked-list RAM -> GPU
 * ============================================================
 *
 * Chaque noeud :
 *
 *   31........24 = nombre de mots GP0
 *   23.........0 = pointeur vers le noeud suivant
 *
 * En pratique, un next avec bit 23 positionné termine la liste.
 * 0x00FFFFFF est la valeur de fin la plus classique.
 */

static int fm_dma2_linked_list(void)
{
    uint32_t addr =
        g_dma2_madr
        &
        0x001FFFFCu;

    for (
        unsigned node = 0;
        node < 65536u;
        ++node
    )
    {
        uint32_t header =
            fm_dma_ram_read_word(
                addr
            );

        uint32_t count =
            header
            >>
            24;

        uint32_t next =
            header
            &
            0x00FFFFFFu;

        uint32_t command_addr =
            (
                addr
                +
                4u
            )
            &
            0x001FFFFCu;

        for (
            uint32_t i = 0;
            i < count;
            ++i
        )
        {
            uint32_t command =
                fm_dma_ram_read_word(
                    command_addr
                );

            fm_gpu_gp0_write(
                command
            );

            ++g_dma2_word_count;

            command_addr =
                (
                    command_addr
                    +
                    4u
                )
                &
                0x001FFFFCu;
        }

        /*
         * Linked-list terminator.
         *
         * La documentation PS1 utilise le bit 23 comme marqueur
         * de fin. Cela couvre notamment 0x00FFFFFF.
         */
        if (
            next
            &
            0x00800000u
        )
        {
            g_dma2_madr =
                next;

            return 1;
        }

        addr =
            next
            &
            0x001FFFFCu;

        g_dma2_madr =
            addr;
    }

    /*
     * Protection contre une liste cyclique/corrompue.
     */
    return 0;
}


/*
 * ============================================================
 * DMA2 block/request RAM -> GPU
 * ============================================================
 */

static int fm_dma2_block(void)
{
    uint32_t direction =
        g_dma2_chcr
        &
        1u;

    /*
     * Pour l'instant :
     *
     * 1 = RAM -> GPU supporté
     * 0 = GPU -> RAM nécessite GPUREAD et n'est pas encore supporté
     */
    if (!direction)
    {
        return 0;
    }

    uint32_t step_backward =
        (
            g_dma2_chcr
            >>
            1
        )
        &
        1u;

    uint32_t sync =
        (
            g_dma2_chcr
            >>
            9
        )
        &
        3u;

    uint32_t words =
        0;

    /*
     * Sync 0 = manual.
     */
    if (sync == 0u)
    {
        words =
            g_dma2_bcr
            &
            0xFFFFu;

        /*
         * Taille zéro = 0x10000 mots sur le DMA PS1.
         */
        if (words == 0)
        {
            words =
                0x10000u;
        }
    }
    /*
     * Sync 1 = request.
     *
     * BCR low 16  = block size
     * BCR high 16 = number of blocks
     */
    else if (sync == 1u)
    {
        uint32_t block_size =
            g_dma2_bcr
            &
            0xFFFFu;

        uint32_t block_count =
            (
                g_dma2_bcr
                >>
                16
            )
            &
            0xFFFFu;

        if (block_size == 0)
        {
            block_size =
                0x10000u;
        }

        if (block_count == 0)
        {
            block_count =
                0x10000u;
        }

        uint64_t total =
            (uint64_t)block_size
            *
            (uint64_t)block_count;

        /*
         * Bring-up guard.
         *
         * Empêche un BCR corrompu de bloquer le homebrew pendant
         * des millions de commandes GP0.
         */
        if (total > 0x200000u)
        {
            total =
                0x200000u;
        }

        words =
            (uint32_t)total;
    }
    else
    {
        return 0;
    }

    uint32_t addr =
        g_dma2_madr
        &
        0x001FFFFCu;

    for (
        uint32_t i = 0;
        i < words;
        ++i
    )
    {
        uint32_t command =
            fm_dma_ram_read_word(
                addr
            );

        fm_gpu_gp0_write(
            command
        );

        ++g_dma2_word_count;

        if (step_backward)
        {
            addr =
                (
                    addr
                    -
                    4u
                )
                &
                0x001FFFFCu;
        }
        else
        {
            addr =
                (
                    addr
                    +
                    4u
                )
                &
                0x001FFFFCu;
        }
    }

    g_dma2_madr =
        addr;

    return 1;
}


/*
 * ============================================================
 * DMA2 start
 * ============================================================
 */

static void fm_dma2_try_start(void)
{
    /*
     * Bit 24 = START/BUSY.
     */
    if (
        (
            g_dma2_chcr
            &
            0x01000000u
        )
        ==
        0
    )
    {
        return;
    }

    uint32_t sync =
        (
            g_dma2_chcr
            >>
            9
        )
        &
        3u;

    int completed =
        0;

    /*
     * Sync 2 = linked-list.
     *
     * Valeur GPU classique :
     * CHCR = 0x01000401.
     */
    if (
        sync == 2u
        &&
        (
            g_dma2_chcr
            &
            1u
        )
    )
    {
        completed =
            fm_dma2_linked_list();
    }
    else
    {
        completed =
            fm_dma2_block();
    }

    if (completed)
    {
        fm_dma2_complete();
    }
}



/*
 * ============================================================
 * DMA sub-word access helpers
 * ============================================================
 *
 * Forbidden Memories accède aussi à certains registres DMA
 * en 8/16 bits (notamment CHCR+2 = 0x1F8010AA).
 *
 * Les helpers ci-dessous reconstruisent la valeur 32 bits,
 * appliquent l'écriture au bon sous-champ puis déclenchent les
 * effets de bord nécessaires.
 */

static int fm_dma_is_register(
    uint32_t phys
)
{
    return
        (
            phys >= PSX_DMA2_MADR
            &&
            phys < PSX_DMA2_MADR + 4u
        )
        ||
        (
            phys >= PSX_DMA2_BCR
            &&
            phys < PSX_DMA2_BCR + 4u
        )
        ||
        (
            phys >= PSX_DMA2_CHCR
            &&
            phys < PSX_DMA2_CHCR + 4u
        )
        ||
        (
            phys >= PSX_DMA_DPCR
            &&
            phys < PSX_DMA_DPCR + 4u
        )
        ||
        (
            phys >= PSX_DMA_DICR
            &&
            phys < PSX_DMA_DICR + 4u
        );
}


static uint32_t fm_dma_register_read32(
    uint32_t base
)
{
    switch (base)
    {
        case PSX_DMA2_MADR:
            return g_dma2_madr;

        case PSX_DMA2_BCR:
            return g_dma2_bcr;

        case PSX_DMA2_CHCR:
            return g_dma2_chcr;

        case PSX_DMA_DPCR:
            return g_dma_dpcr;

        case PSX_DMA_DICR:
            return fm_dma_dicr_read();

        default:
            return 0;
    }
}


static uint32_t fm_dma_register_base(
    uint32_t phys
)
{
    if (
        phys >= PSX_DMA2_MADR
        &&
        phys < PSX_DMA2_MADR + 4u
    )
    {
        return PSX_DMA2_MADR;
    }

    if (
        phys >= PSX_DMA2_BCR
        &&
        phys < PSX_DMA2_BCR + 4u
    )
    {
        return PSX_DMA2_BCR;
    }

    if (
        phys >= PSX_DMA2_CHCR
        &&
        phys < PSX_DMA2_CHCR + 4u
    )
    {
        return PSX_DMA2_CHCR;
    }

    if (
        phys >= PSX_DMA_DPCR
        &&
        phys < PSX_DMA_DPCR + 4u
    )
    {
        return PSX_DMA_DPCR;
    }

    if (
        phys >= PSX_DMA_DICR
        &&
        phys < PSX_DMA_DICR + 4u
    )
    {
        return PSX_DMA_DICR;
    }

    return 0;
}


static void fm_dma_dicr_write_masked(
    uint32_t value,
    uint32_t write_mask
)
{
    /*
     * DICR bits 0..23 : écriture normale.
     * DICR bits 24..30: W1C.
     * DICR bit 31     : lecture seule / calculé.
     */

    uint32_t programmable_mask =
        write_mask
        &
        0x00FFFFFFu;

    g_dma_dicr =
        (
            g_dma_dicr
            &
            ~programmable_mask
        )
        |
        (
            value
            &
            programmable_mask
        );


    uint32_t clear_flags =
        value
        &
        write_mask
        &
        0x7F000000u;

    g_dma_dicr &=
        ~clear_flags;


    /*
     * Bit 31 n'est jamais stocké.
     */
    g_dma_dicr &=
        0x7FFFFFFFu;


    fm_dma_update_irq();
}


static void fm_dma_register_write32_masked(
    uint32_t base,
    uint32_t value,
    uint32_t write_mask
)
{
    switch (base)
    {
        case PSX_DMA2_MADR:
        {
            uint32_t merged =
                (
                    g_dma2_madr
                    &
                    ~write_mask
                )
                |
                (
                    value
                    &
                    write_mask
                );

            g_dma2_madr =
                merged
                &
                0x00FFFFFFu;

            return;
        }


        case PSX_DMA2_BCR:
            g_dma2_bcr =
                (
                    g_dma2_bcr
                    &
                    ~write_mask
                )
                |
                (
                    value
                    &
                    write_mask
                );

            return;


        case PSX_DMA2_CHCR:
            g_dma2_chcr =
                (
                    g_dma2_chcr
                    &
                    ~write_mask
                )
                |
                (
                    value
                    &
                    write_mask
                );

            /*
             * Une écriture du demi-mot haut peut positionner
             * START/BUSY (bit 24), donc il faut tester après
             * chaque écriture partielle.
             */
            fm_dma2_try_start();

            return;


        case PSX_DMA_DPCR:
            g_dma_dpcr =
                (
                    g_dma_dpcr
                    &
                    ~write_mask
                )
                |
                (
                    value
                    &
                    write_mask
                );

            return;


        case PSX_DMA_DICR:
            fm_dma_dicr_write_masked(
                value,
                write_mask
            );

            return;


        default:
            return;
    }
}


static uint8_t fm_dma_read_byte(
    uint32_t phys
)
{
    uint32_t base =
        fm_dma_register_base(
            phys
        );

    uint32_t value =
        fm_dma_register_read32(
            base
        );

    unsigned shift =
        (
            phys
            -
            base
        )
        *
        8u;

    return
        (uint8_t)(
            value
            >>
            shift
        );
}


static void fm_dma_write_byte(
    uint32_t phys,
    uint8_t value
)
{
    uint32_t base =
        fm_dma_register_base(
            phys
        );

    unsigned shift =
        (
            phys
            -
            base
        )
        *
        8u;

    uint32_t mask =
        0xFFu
        <<
        shift;

    uint32_t expanded =
        (uint32_t)value
        <<
        shift;

    fm_dma_register_write32_masked(
        base,
        expanded,
        mask
    );
}


static uint16_t fm_dma_read_half(
    uint32_t phys
)
{
    uint32_t base =
        fm_dma_register_base(
            phys
        );

    uint32_t value =
        fm_dma_register_read32(
            base
        );

    unsigned shift =
        (
            phys
            -
            base
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


static void fm_dma_write_half(
    uint32_t phys,
    uint16_t value
)
{
    uint32_t base =
        fm_dma_register_base(
            phys
        );

    unsigned shift =
        (
            phys
            -
            base
        )
        *
        8u;

    uint32_t mask =
        0xFFFFu
        <<
        shift;

    uint32_t expanded =
        (uint32_t)value
        <<
        shift;

    fm_dma_register_write32_masked(
        base,
        expanded,
        mask
    );
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
     * DMA reset.
     */
    g_dma2_madr =
        0;

    g_dma2_bcr =
        0;

    g_dma2_chcr =
        0;

    g_dma_dpcr =
        0;

    g_dma_dicr =
        0;

    g_dma2_transfer_count =
        0;

    g_dma2_word_count =
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
     * DMA controller - byte access
     * --------------------------------------------------------
     */

    if (fm_dma_is_register(phys))
    {
        return
            fm_dma_read_byte(
                phys
            );
    }

    /*
     * --------------------------------------------------------
     * GPUSTAT
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
     * I_STAT / I_MASK / DMA MMIO are intentionally handled
     * as half/word registers for now.
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
     * DMA controller - byte access
     * --------------------------------------------------------
     */

    if (fm_dma_is_register(phys))
    {
        fm_dma_write_byte(
            phys,
            value
        );

        return;
    }

    /*
     * --------------------------------------------------------
     * GPU ports are 32-bit.
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
     * DMA controller - half access
     *
     * Exemple important observé :
     * 0x1F8010AA = demi-mot haut de DMA2 CHCR.
     * --------------------------------------------------------
     */

    if (
        fm_dma_is_register(phys)
        &&
        (
            phys
            &
            1u
        )
        ==
        0
        &&
        (
            phys
            &
            3u
        )
        !=
        3u
    )
    {
        return
            fm_dma_read_half(
                phys
            );
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
     * 0 = acquitter le bit.
     * 1 = conserver son état.
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
     * DMA controller - half access
     * --------------------------------------------------------
     */

    if (
        fm_dma_is_register(phys)
        &&
        (
            phys
            &
            1u
        )
        ==
        0
    )
    {
        fm_dma_write_half(
            phys,
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
     * GPU ports remain 32-bit.
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
     * DMA2 GPU
     * --------------------------------------------------------
     */

    if (phys == PSX_DMA2_MADR)
    {
        return
            g_dma2_madr;
    }

    if (phys == PSX_DMA2_BCR)
    {
        return
            g_dma2_bcr;
    }

    if (phys == PSX_DMA2_CHCR)
    {
        return
            g_dma2_chcr;
    }

    /*
     * --------------------------------------------------------
     * DMA global registers
     * --------------------------------------------------------
     */

    if (phys == PSX_DMA_DPCR)
    {
        return
            g_dma_dpcr;
    }

    if (phys == PSX_DMA_DICR)
    {
        return
            fm_dma_dicr_read();
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
     * DMA2 GPU
     * --------------------------------------------------------
     */

    if (phys == PSX_DMA2_MADR)
    {
        g_dma2_madr =
            value
            &
            0x00FFFFFFu;

        return;
    }

    if (phys == PSX_DMA2_BCR)
    {
        g_dma2_bcr =
            value;

        return;
    }

    if (phys == PSX_DMA2_CHCR)
    {
        g_dma2_chcr =
            value;

        fm_dma2_try_start();

        return;
    }

    /*
     * --------------------------------------------------------
     * DMA global control
     * --------------------------------------------------------
     */

    if (phys == PSX_DMA_DPCR)
    {
        g_dma_dpcr =
            value;

        return;
    }

    if (phys == PSX_DMA_DICR)
    {
        /*
         * Les flags IRQ des canaux (bits 24..30) sont W1C :
         * écrire 1 efface le flag correspondant.
         */
        uint32_t old_flags =
            g_dma_dicr
            &
            0x7F000000u;

        uint32_t clear_flags =
            value
            &
            0x7F000000u;

        old_flags &=
            ~clear_flags;

        /*
         * bits 0..23 sont programmables.
         * bit 31 est calculé à la lecture.
         */
        g_dma_dicr =
            old_flags
            |
            (
                value
                &
                0x00FFFFFFu
            );

        fm_dma_update_irq();

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
