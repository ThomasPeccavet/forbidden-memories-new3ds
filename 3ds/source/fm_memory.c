#include "fm_memory.h"
#include "fm_gpu.h"

#include <3ds.h>
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
#define PSX_IRQ_TIMER0      0x0010u
#define PSX_IRQ_TIMER1      0x0020u
#define PSX_IRQ_TIMER2      0x0040u
#define PSX_IRQ_VALID_MASK  0x07FFu


/*
 * ============================================================
 * Root counters / timers
 * ============================================================
 */

#define PSX_TIMER0_COUNT    0x1F801100u
#define PSX_TIMER0_MODE     0x1F801104u
#define PSX_TIMER0_TARGET   0x1F801108u

#define PSX_TIMER1_COUNT    0x1F801110u
#define PSX_TIMER1_MODE     0x1F801114u
#define PSX_TIMER1_TARGET   0x1F801118u

#define PSX_TIMER2_COUNT    0x1F801120u
#define PSX_TIMER2_MODE     0x1F801124u
#define PSX_TIMER2_TARGET   0x1F801128u

#define PSX_TIMER_COUNT     3u


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

/*
 * Canal 6 = OTC (Ordering Table Clear).
 */
#define PSX_DMA6_MADR       0x1F8010E0u
#define PSX_DMA6_BCR        0x1F8010E4u
#define PSX_DMA6_CHCR       0x1F8010E8u

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
 * Root counter state
 * ============================================================
 */

typedef struct FMRootCounter
{
    uint16_t count;
    uint16_t mode;
    uint16_t target;
    uint8_t irq_fired_once;
} FMRootCounter;


static FMRootCounter g_timers[
    PSX_TIMER_COUNT
];


/*
 * ============================================================
 * DMA state
 * ============================================================
 */

static uint32_t g_dma2_madr = 0;
static uint32_t g_dma2_bcr = 0;
static uint32_t g_dma2_chcr = 0;

static uint32_t g_dma6_madr = 0;
static uint32_t g_dma6_bcr = 0;
static uint32_t g_dma6_chcr = 0;

static uint32_t g_dma_dpcr = 0;
static uint32_t g_dma_dicr = 0;

/*
 * Diagnostics internes. Ils pourront être exposés plus tard
 * dans fm_memory.h si on veut les afficher sur l'écran inférieur.
 */
static uint32_t g_dma2_transfer_count = 0;
static uint64_t g_dma2_word_count = 0;

static uint32_t g_dma2_linked_transfer_count = 0;
static uint32_t g_dma2_last_start_madr = 0;
static uint32_t g_dma2_last_chcr = 0;
static uint32_t g_dma2_last_nodes = 0;
static uint32_t g_dma2_last_words = 0;
static uint32_t g_dma2_last_first_header = 0;

/*
 * B120 - DMA2 hot path.
 *
 * B119 captures show ~4300 linked-list nodes for only ~400-500 GP0
 * words. B118 used a 64 KiB memset before EVERY list just for cycle
 * detection. Replace that with a generation table: no per-list clear,
 * O(1) cycle lookup, and only one byte touched per visited RAM word.
 *
 * The table is 2 MiB / 4 = 524288 bytes. It is cleared only when the
 * 8-bit generation wraps (once every 255 linked-list transfers).
 */
#define FM_DMA2_VISIT_SLOTS (PSX_RAM_SIZE / 4u)
static uint8_t g_dma2_visit_epoch[FM_DMA2_VISIT_SLOTS];
static uint8_t g_dma2_visit_generation = 1u;
static uint32_t g_dma2_visit_wrap_clears = 0u;

static uint32_t g_dma2_cycle_abort_count = 0;
static uint32_t g_dma2_last_cycle_addr = 0;
static uint32_t g_dma2_max_nodes = 0;
static uint32_t g_dma2_max_words = 0;

static uint32_t g_dma2_last_empty_ot_nodes = 0u;
static uint32_t g_dma2_max_empty_ot_nodes = 0u;

static uint32_t g_dma2_linked_last_ms = 0u;
static uint32_t g_dma2_linked_max_ms = 0u;
static uint64_t g_dma2_linked_total_ms = 0u;
static uint32_t g_dma2_linked_over20 = 0u;
static uint32_t g_dma2_linked_over33 = 0u;

/*
 * B121 - collapse canonical empty ordering-table runs.
 * These nodes carry no GP0 words and simply point to addr-4.
 */
static uint32_t g_dma2_empty_fast_runs = 0u;
static uint64_t g_dma2_empty_fast_nodes = 0u;
static uint32_t g_dma2_empty_fast_last = 0u;
static uint32_t g_dma2_empty_fast_max = 0u;

static uint32_t g_dma6_transfer_count = 0;
static uint64_t g_dma6_word_count = 0;


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
 * Root counter helpers
 * ============================================================
 *
 * MODE bits used by this bring-up implementation:
 *   3      reset counter on target
 *   4      IRQ on target
 *   5      IRQ on overflow
 *   6      IRQ repeat
 *   7      IRQ toggle
 *   8..9   clock source
 *   10     IRQ request state
 *   11     reached target
 *   12     reached FFFF
 *
 * The emulation is intentionally deterministic rather than
 * cycle-perfect. Timers move on every host VBlank and also make
 * a small amount of progress when COUNT is polled repeatedly.
 */

static uint16_t fm_timer_irq_bit(
    unsigned index
)
{
    switch (index)
    {
        case 0:
            return PSX_IRQ_TIMER0;

        case 1:
            return PSX_IRQ_TIMER1;

        default:
            return PSX_IRQ_TIMER2;
    }
}


static void fm_timer_raise_irq(
    unsigned index
)
{
    FMRootCounter *timer =
        &g_timers[index];


    if (
        (
            timer->mode
            &
            0x0040u
        )
        ==
        0
        &&
        timer->irq_fired_once
    )
    {
        return;
    }


    timer->irq_fired_once =
        1;


    if (
        timer->mode
        &
        0x0080u
    )
    {
        timer->mode ^=
            0x0400u;
    }
    else
    {
        timer->mode &=
            (uint16_t)~0x0400u;
    }


    g_i_stat |=
        fm_timer_irq_bit(
            index
        );
}


static void fm_timer_mark_target(
    unsigned index
)
{
    FMRootCounter *timer =
        &g_timers[index];


    timer->mode |=
        0x0800u;


    if (
        timer->mode
        &
        0x0010u
    )
    {
        fm_timer_raise_irq(
            index
        );
    }
}


static void fm_timer_mark_overflow(
    unsigned index
)
{
    FMRootCounter *timer =
        &g_timers[index];


    timer->mode |=
        0x1000u;


    if (
        timer->mode
        &
        0x0020u
    )
    {
        fm_timer_raise_irq(
            index
        );
    }
}


static void fm_timer_advance(
    unsigned index,
    uint32_t delta
)
{
    if (
        index >= PSX_TIMER_COUNT
        ||
        delta == 0
    )
    {
        return;
    }


    FMRootCounter *timer =
        &g_timers[index];


    /*
     * In pulse mode, bit10 returns high on the next timer step.
     */
    if (
        (
            timer->mode
            &
            0x0080u
        )
        ==
        0
        &&
        (
            timer->mode
            &
            0x0400u
        )
        ==
        0
    )
    {
        timer->mode |=
            0x0400u;
    }


    uint32_t old_count =
        timer->count;


    uint32_t target =
        timer->target;


    if (
        timer->mode
        &
        0x0008u
    )
    {
        uint32_t period =
            target
            +
            1u;


        if (period == 0u)
        {
            period =
                0x10000u;
        }


        old_count %=
            period;


        uint64_t total =
            (uint64_t)old_count
            +
            (uint64_t)delta;


        if (
            total
            >=
            period
        )
        {
            fm_timer_mark_target(
                index
            );


            if (target == 0xFFFFu)
            {
                fm_timer_mark_overflow(
                    index
                );
            }
        }


        timer->count =
            (uint16_t)(
                total
                %
                period
            );


        return;
    }


    uint64_t total =
        (uint64_t)old_count
        +
        (uint64_t)delta;


    uint32_t new_count =
        (uint32_t)total
        &
        0xFFFFu;


    int overflowed =
        total
        >
        0xFFFFu;


    int reached_target =
        0;


    if (!overflowed)
    {
        if (
            old_count < target
            &&
            new_count >= target
        )
        {
            reached_target =
                1;
        }
    }
    else
    {
        if (
            target > old_count
            ||
            target <= new_count
        )
        {
            reached_target =
                1;
        }
    }


    if (reached_target)
    {
        fm_timer_mark_target(
            index
        );
    }


    if (overflowed)
    {
        fm_timer_mark_overflow(
            index
        );
    }


    timer->count =
        (uint16_t)new_count;
}



static uint32_t fm_timer_vblank_delta(
    unsigned index
)
{
    FMRootCounter *timer =
        &g_timers[index];


    /*
     * PAL-oriented approximations for bring-up.
     */
    if (index == 1u)
    {
        uint32_t source =
            (
                timer->mode
                >>
                8
            )
            &
            3u;


        if (
            source == 1u
            ||
            source == 3u
        )
        {
            return 314u;
        }


        return 4096u;
    }


    if (index == 2u)
    {
        return
            (
                timer->mode
                &
                0x0200u
            )
                ? 4096u
                : 32768u;
    }


    return 4096u;
}


static int fm_timer_decode(
    uint32_t phys,
    unsigned *out_index,
    unsigned *out_reg,
    unsigned *out_byte
)
{
    if (
        phys < PSX_TIMER0_COUNT
        ||
        phys >=
        (
            PSX_TIMER2_TARGET
            +
            4u
        )
    )
    {
        return 0;
    }


    uint32_t relative =
        phys
        -
        PSX_TIMER0_COUNT;


    unsigned index =
        (unsigned)(
            relative
            /
            0x10u
        );


    if (index >= PSX_TIMER_COUNT)
    {
        return 0;
    }


    uint32_t within =
        relative
        %
        0x10u;


    unsigned reg;


    if (within < 4u)
    {
        reg = 0u;
    }
    else if (within < 8u)
    {
        reg = 1u;
    }
    else if (within < 12u)
    {
        reg = 2u;
    }
    else
    {
        return 0;
    }


    *out_index =
        index;


    *out_reg =
        reg;


    *out_byte =
        (unsigned)(
            within
            &
            3u
        );


    return 1;
}


static uint16_t fm_timer_read16(
    unsigned index,
    unsigned reg
)
{
    FMRootCounter *timer =
        &g_timers[index];


    switch (reg)
    {
        case 0:
        {
            /*
             * IMPORTANT:
             *
             * Une lecture COUNT doit être sans effet de bord.
             *
             * Forbidden Memories lit parfois deux fois le même
             * compteur de suite afin d'obtenir une valeur stable.
             * Si on incrémente ici, ces deux lectures ne peuvent
             * jamais être égales et le jeu boucle jusqu'au watchdog.
             *
             * Les compteurs avancent dans fm_memory_vblank_tick().
             */
            return
                timer->count;
        }


        case 1:
        {
            uint16_t value =
                timer->mode;


            /*
             * Reached-target / reached-FFFF clear on MODE read.
             */
            timer->mode &=
                (uint16_t)~(
                    0x0800u
                    |
                    0x1000u
                );


            return
                value;
        }


        default:
            return
                timer->target;
    }
}


static void fm_timer_write16(
    unsigned index,
    unsigned reg,
    uint16_t value
)
{
    FMRootCounter *timer =
        &g_timers[index];


    switch (reg)
    {
        case 0:
            timer->count =
                value;

            return;


        case 1:
            /*
             * Writing MODE resets COUNT and status bits.
             */
            timer->mode =
                (
                    value
                    &
                    0x03FFu
                )
                |
                0x0400u;


            timer->count =
                0;


            timer->irq_fired_once =
                0;


            return;


        default:
            timer->target =
                value;

            return;
    }
}


static uint8_t fm_timer_read_byte(
    uint32_t phys
)
{
    unsigned index;
    unsigned reg;
    unsigned byte_index;


    if (
        !fm_timer_decode(
            phys,
            &index,
            &reg,
            &byte_index
        )
        ||
        byte_index >= 2u
    )
    {
        return 0;
    }


    uint16_t value =
        fm_timer_read16(
            index,
            reg
        );


    return
        (uint8_t)(
            value
            >>
            (
                byte_index
                *
                8u
            )
        );
}


static void fm_timer_write_byte(
    uint32_t phys,
    uint8_t value
)
{
    unsigned index;
    unsigned reg;
    unsigned byte_index;


    if (
        !fm_timer_decode(
            phys,
            &index,
            &reg,
            &byte_index
        )
        ||
        byte_index >= 2u
    )
    {
        return;
    }


    uint16_t old_value;


    switch (reg)
    {
        case 0:
            old_value =
                g_timers[index].count;
            break;

        case 1:
            old_value =
                g_timers[index].mode;
            break;

        default:
            old_value =
                g_timers[index].target;
            break;
    }


    unsigned shift =
        byte_index
        *
        8u;


    uint16_t mask =
        (uint16_t)(
            0x00FFu
            <<
            shift
        );


    uint16_t merged =
        (uint16_t)(
            (
                old_value
                &
                (uint16_t)~mask
            )
            |
            (
                (uint16_t)value
                <<
                shift
            )
        );


    fm_timer_write16(
        index,
        reg,
        merged
    );
}


static uint16_t fm_timer_read_half(
    uint32_t phys
)
{
    unsigned index;
    unsigned reg;
    unsigned byte_index;


    if (
        !fm_timer_decode(
            phys,
            &index,
            &reg,
            &byte_index
        )
        ||
        byte_index != 0u
    )
    {
        return 0;
    }


    return
        fm_timer_read16(
            index,
            reg
        );
}


static void fm_timer_write_half(
    uint32_t phys,
    uint16_t value
)
{
    unsigned index;
    unsigned reg;
    unsigned byte_index;


    if (
        !fm_timer_decode(
            phys,
            &index,
            &reg,
            &byte_index
        )
        ||
        byte_index != 0u
    )
    {
        return;
    }


    fm_timer_write16(
        index,
        reg,
        value
    );
}


static uint32_t fm_timer_read_word(
    uint32_t phys
)
{
    return
        (uint32_t)
            fm_timer_read_half(
                phys
            );
}


static void fm_timer_write_word(
    uint32_t phys,
    uint32_t value
)
{
    fm_timer_write_half(
        phys,
        (uint16_t)value
    );
}


static int fm_timer_is_register(
    uint32_t phys
)
{
    unsigned index;
    unsigned reg;
    unsigned byte_index;


    return
        fm_timer_decode(
            phys,
            &index,
            &reg,
            &byte_index
        );
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

    /*
     * B120: alias-safe native 32-bit load after -O3.
     */
    uint32_t value;
    memcpy(&value, g_ram + offset, sizeof(value));
    return value;
}



static void fm_dma_ram_write_word(
    uint32_t addr,
    uint32_t value
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
        return;
    }

    /*
     * B120: alias-safe native 32-bit store after -O3.
     */
    memcpy(g_ram + offset, &value, sizeof(value));
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

static void fm_dma2_linked_profile_finish(uint64_t start_ms)
{
    /*
     * B135.29 - coarse linked-list timing.
     *
     * Time the whole DMA2 list once, rather than timing individual GP0
     * commands. This keeps diagnostic overhead negligible while measuring
     * exactly the combined cost we care about here:
     *   OT traversal + GP0 parsing + software rasterization.
     */
    uint32_t elapsed_ms =
        (uint32_t)(osGetTime() - start_ms);

    g_dma2_linked_last_ms =
        elapsed_ms;

    g_dma2_linked_total_ms +=
        elapsed_ms;

    if (elapsed_ms > g_dma2_linked_max_ms)
    {
        g_dma2_linked_max_ms =
            elapsed_ms;
    }

    if (elapsed_ms > 20u)
    {
        ++g_dma2_linked_over20;
    }

    if (elapsed_ms > 33u)
    {
        ++g_dma2_linked_over33;
    }

    if (g_dma2_last_empty_ot_nodes > g_dma2_max_empty_ot_nodes)
    {
        g_dma2_max_empty_ot_nodes = g_dma2_last_empty_ot_nodes;
    }
}


static int fm_dma2_linked_list(void)
{
    uint64_t b120_start_ms =
        osGetTime();

    /*
     * B135.32: GHOT/GHOT2 must describe THIS linked list.  The previous
     * cumulative profile mixed boot/menu/map traffic and made one-time
     * sprites look like current frame hotspots.
     */
    fm_gpu_b13532_profile_reset();

    /*
     * Skipped canonical ranges are remembered so a later malformed link
     * back into one of them is still detected as a cycle.
     */
    uint32_t b121_skip_lo[16];
    uint32_t b121_skip_hi[16];
    uint32_t b121_skip_ranges = 0u;

    uint32_t addr =
        g_dma2_madr
        &
        0x001FFFFCu;


    g_dma2_last_start_madr =
        g_dma2_madr;

    g_dma2_last_chcr =
        g_dma2_chcr;

    g_dma2_last_nodes =
        0;

    g_dma2_last_words =
        0;

    g_dma2_last_empty_ot_nodes =
        0;

    g_dma2_last_first_header =
        fm_dma_ram_read_word(
            addr
        );

    ++g_dma2_linked_transfer_count;

    /*
     * B120: advance the visit generation instead of clearing 64 KiB.
     */
    ++g_dma2_visit_generation;

    if (g_dma2_visit_generation == 0u)
    {
        memset(
            g_dma2_visit_epoch,
            0,
            sizeof(g_dma2_visit_epoch)
        );

        g_dma2_visit_generation = 1u;
        ++g_dma2_visit_wrap_clears;
    }


    for (
        unsigned node = 0;
        node < 65536u;
        ++node
    )
    {
        for (uint32_t r = 0u; r < b121_skip_ranges; ++r)
        {
            if (
                addr >= b121_skip_lo[r]
                &&
                addr <= b121_skip_hi[r]
            )
            {
                ++g_dma2_cycle_abort_count;
                g_dma2_last_cycle_addr = addr;

                if (g_dma2_last_nodes > g_dma2_max_nodes)
                {
                    g_dma2_max_nodes = g_dma2_last_nodes;
                }

                if (g_dma2_last_words > g_dma2_max_words)
                {
                    g_dma2_max_words = g_dma2_last_words;
                }

                fm_dma2_linked_profile_finish(
                    b120_start_ms
                );

                return 1;
            }
        }

        uint32_t visit_index = addr >> 2;

        if (
            g_dma2_visit_epoch[visit_index]
            ==
            g_dma2_visit_generation
        )
        {
            ++g_dma2_cycle_abort_count;
            g_dma2_last_cycle_addr = addr;

            if (g_dma2_last_nodes > g_dma2_max_nodes)
            {
                g_dma2_max_nodes = g_dma2_last_nodes;
            }

            if (g_dma2_last_words > g_dma2_max_words)
            {
                g_dma2_max_words = g_dma2_last_words;
            }

            fm_dma2_linked_profile_finish(
                b120_start_ms
            );

            return 1;
        }

        g_dma2_visit_epoch[visit_index] =
            g_dma2_visit_generation;

        uint32_t header =
            fm_dma_ram_read_word(
                addr
            );


        ++g_dma2_last_nodes;


        uint32_t count =
            header
            >>
            24;

        uint32_t next =
            header
            &
            0x00FFFFFFu;

        if (
            count == 0u
            &&
            next
            ==
            ((addr - 4u) & 0x00FFFFFFu)
        )
        {
            ++g_dma2_last_empty_ot_nodes;

            /*
             * B121 fast path.
             *
             * Once an empty OT bucket points exactly to addr-4, consume
             * the following identical buckets in a tight loop. They have
             * no GPU payload, so there is no observable GPU work to do.
             *
             * We leave the first non-canonical node for the normal loop,
             * preserving packet ordering and terminator handling exactly.
             */
            if (b121_skip_ranges < 16u)
            {
                uint32_t scan_addr =
                    next
                    &
                    0x001FFFFCu;

                uint32_t first_skipped =
                    scan_addr;

                uint32_t last_skipped =
                    scan_addr;

                uint32_t extra =
                    0u;

                while (
                    (node + 1u + extra) < 65536u
                )
                {
                    uint32_t scan_header =
                        fm_dma_ram_read_word(
                            scan_addr
                        );

                    uint32_t scan_count =
                        scan_header
                        >>
                        24;

                    uint32_t scan_next =
                        scan_header
                        &
                        0x00FFFFFFu;

                    if (
                        scan_count != 0u
                        ||
                        scan_next
                        !=
                        ((scan_addr - 4u) & 0x00FFFFFFu)
                    )
                    {
                        break;
                    }

                    last_skipped =
                        scan_addr;

                    ++extra;

                    scan_addr =
                        scan_next
                        &
                        0x001FFFFCu;
                }

                if (extra != 0u)
                {
                    b121_skip_lo[b121_skip_ranges] =
                        last_skipped;

                    b121_skip_hi[b121_skip_ranges] =
                        first_skipped;

                    ++b121_skip_ranges;

                    g_dma2_last_nodes +=
                        extra;

                    g_dma2_last_empty_ot_nodes +=
                        extra;

                    ++g_dma2_empty_fast_runs;

                    g_dma2_empty_fast_nodes +=
                        extra;

                    g_dma2_empty_fast_last =
                        extra;

                    if (extra > g_dma2_empty_fast_max)
                    {
                        g_dma2_empty_fast_max =
                            extra;
                    }

                    node +=
                        extra;

                    addr =
                        scan_addr;

                    g_dma2_madr =
                        addr;

                    continue;
                }
            }
        }

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

            ++g_dma2_last_words;

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

            if (g_dma2_last_nodes > g_dma2_max_nodes)
            {
                g_dma2_max_nodes = g_dma2_last_nodes;
            }

            if (g_dma2_last_words > g_dma2_max_words)
            {
                g_dma2_max_words = g_dma2_last_words;
            }

            fm_dma2_linked_profile_finish(
                b120_start_ms
            );

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
     * Protection de dernier recours. With the visited bitset, reaching this
     * point means an enormous acyclic/corrupt chain rather than a short cycle.
     * Finish the DMA to avoid pinning the guest in a permanent busy wait.
     */
    if (g_dma2_last_nodes > g_dma2_max_nodes)
    {
        g_dma2_max_nodes = g_dma2_last_nodes;
    }

    if (g_dma2_last_words > g_dma2_max_words)
    {
        g_dma2_max_words = g_dma2_last_words;
    }

    ++g_dma2_cycle_abort_count;
    g_dma2_last_cycle_addr = addr;

    fm_dma2_linked_profile_finish(
        b120_start_ms
    );

    return 1;
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
 * DMA6 OTC - Ordering Table Clear
 * ============================================================
 *
 * Le canal OTC construit en RAM une chaîne inverse :
 *
 *   [addr]     = addr - 4
 *   [addr - 4] = addr - 8
 *   ...
 *   dernier    = 00FFFFFF
 *
 * Cette table est ensuite utilisée par le DMA2 GPU en linked-list.
 */

static void fm_dma6_complete(void)
{
    g_dma6_chcr &=
        ~(
            0x01000000u
            |
            0x10000000u
        );

    /*
     * DICR flag canal 6 = bit 30.
     */
    g_dma_dicr |=
        1u
        <<
        30;

    ++g_dma6_transfer_count;

    fm_dma_update_irq();
}


static int fm_dma6_otc(void)
{
    uint32_t words =
        g_dma6_bcr
        &
        0xFFFFu;

    if (words == 0u)
    {
        words =
            0x10000u;
    }

    /*
     * Garde-fou : une OT réelle du jeu est très largement
     * inférieure à 65536 entrées.
     */
    if (words > 0x10000u)
    {
        words =
            0x10000u;
    }

    uint32_t addr =
        g_dma6_madr
        &
        0x001FFFFCu;

    for (
        uint32_t i = 0;
        i < words;
        ++i
    )
    {
        uint32_t value;

        if (i + 1u == words)
        {
            value =
                0x00FFFFFFu;
        }
        else
        {
            value =
                (
                    addr
                    -
                    4u
                )
                &
                0x001FFFFFu;
        }

        fm_dma_ram_write_word(
            addr,
            value
        );

        ++g_dma6_word_count;

        addr =
            (
                addr
                -
                4u
            )
            &
            0x001FFFFCu;
    }

    g_dma6_madr =
        addr;

    return 1;
}


static void fm_dma6_try_start(void)
{
    /*
     * CHCR bit24 = START/BUSY.
     */
    if (
        (
            g_dma6_chcr
            &
            0x01000000u
        )
        ==
        0
    )
    {
        return;
    }

    /*
     * OTC est un DMA vers RAM, pas de transfert GP0.
     *
     * Le jeu utilise le mode manuel classique
     * (souvent CHCR=0x11000002).
     */
    if (fm_dma6_otc())
    {
        fm_dma6_complete();
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
            phys >= PSX_DMA6_MADR
            &&
            phys < PSX_DMA6_MADR + 4u
        )
        ||
        (
            phys >= PSX_DMA6_BCR
            &&
            phys < PSX_DMA6_BCR + 4u
        )
        ||
        (
            phys >= PSX_DMA6_CHCR
            &&
            phys < PSX_DMA6_CHCR + 4u
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

        case PSX_DMA6_MADR:
            return g_dma6_madr;

        case PSX_DMA6_BCR:
            return g_dma6_bcr;

        case PSX_DMA6_CHCR:
            return g_dma6_chcr;

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
        phys >= PSX_DMA6_MADR
        &&
        phys < PSX_DMA6_MADR + 4u
    )
    {
        return PSX_DMA6_MADR;
    }

    if (
        phys >= PSX_DMA6_BCR
        &&
        phys < PSX_DMA6_BCR + 4u
    )
    {
        return PSX_DMA6_BCR;
    }

    if (
        phys >= PSX_DMA6_CHCR
        &&
        phys < PSX_DMA6_CHCR + 4u
    )
    {
        return PSX_DMA6_CHCR;
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


        case PSX_DMA6_MADR:
        {
            uint32_t merged =
                (
                    g_dma6_madr
                    &
                    ~write_mask
                )
                |
                (
                    value
                    &
                    write_mask
                );

            g_dma6_madr =
                merged
                &
                0x00FFFFFFu;

            return;
        }


        case PSX_DMA6_BCR:
            g_dma6_bcr =
                (
                    g_dma6_bcr
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


        case PSX_DMA6_CHCR:
            g_dma6_chcr =
                (
                    g_dma6_chcr
                    &
                    ~write_mask
                )
                |
                (
                    value
                    &
                    write_mask
                );

            fm_dma6_try_start();

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
     * Root counters reset.
     */
    memset(
        g_timers,
        0,
        sizeof(g_timers)
    );


    for (
        unsigned i = 0;
        i < PSX_TIMER_COUNT;
        ++i
    )
    {
        g_timers[i].mode =
            0x0400u;


        g_timers[i].target =
            0xFFFFu;
    }


    /*
     * DMA reset.
     */
    g_dma2_madr =
        0;

    g_dma2_bcr =
        0;

    g_dma2_chcr =
        0;

    g_dma6_madr =
        0;

    g_dma6_bcr =
        0;

    g_dma6_chcr =
        0;

    g_dma_dpcr =
        0;

    g_dma_dicr =
        0;

    g_dma2_transfer_count =
        0;

    g_dma2_word_count =
        0;

    g_dma2_linked_transfer_count =
        0;

    g_dma2_last_start_madr =
        0;

    g_dma2_last_chcr =
        0;

    g_dma2_last_nodes =
        0;

    g_dma2_last_words =
        0;

    g_dma2_last_first_header =
        0;

    memset(
        g_dma2_visit_epoch,
        0,
        sizeof(g_dma2_visit_epoch)
    );

    g_dma2_visit_generation =
        1u;

    g_dma2_visit_wrap_clears =
        0u;

    g_dma2_cycle_abort_count =
        0;

    g_dma2_last_cycle_addr =
        0;

    g_dma2_max_nodes =
        0;

    g_dma2_max_words =
        0;

    g_dma2_last_empty_ot_nodes =
        0u;

    g_dma2_max_empty_ot_nodes =
        0u;

    g_dma2_linked_last_ms =
        0u;

    g_dma2_linked_max_ms =
        0u;

    g_dma2_linked_total_ms =
        0u;

    g_dma2_linked_over20 =
        0u;

    g_dma2_linked_over33 =
        0u;

    g_dma2_empty_fast_runs =
        0u;

    g_dma2_empty_fast_nodes =
        0u;

    g_dma2_empty_fast_last =
        0u;

    g_dma2_empty_fast_max =
        0u;

    g_dma6_transfer_count =
        0;

    g_dma6_word_count =
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
     * ========================================================
     * B92 - hot RAM fast path
     * ========================================================
     *
     * La RAM PS1 et les MMIO ne se chevauchent pas. Les fonctions
     * recompilees (notamment 0x800917F8) font des milliers de petits
     * acces RAM ; eviter fm_ram_ptr() + tous les tests MMIO sur ce
     * chemin reduit fortement le cout sans changer la semantique.
     */
    if (
        g_ram
        &&
        g_ram_size != 0u
        &&
        phys < PSX_RAM_MIRROR_END
    )
    {
        uint32_t offset =
            phys & 0x001FFFFFu;

        if (offset < g_ram_size)
        {
            return g_ram[offset];
        }
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
     * Root counters - byte access
     * --------------------------------------------------------
     */

    if (fm_timer_is_register(phys))
    {
        return
            fm_timer_read_byte(
                phys
            );
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

    /* B92 - hot RAM fast path. */
    if (
        g_ram
        &&
        g_ram_size != 0u
        &&
        phys < PSX_RAM_MIRROR_END
    )
    {
        uint32_t offset =
            phys & 0x001FFFFFu;

        if (offset < g_ram_size)
        {
            g_ram[offset] = value;
            return;
        }
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
     * Root counters - byte access
     * --------------------------------------------------------
     */

    if (fm_timer_is_register(phys))
    {
        fm_timer_write_byte(
            phys,
            value
        );

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

    /* B92 - hot RAM fast path before timer/DMA decoding. */
    if (
        g_ram
        &&
        g_ram_size >= 2u
        &&
        phys < PSX_RAM_MIRROR_END
    )
    {
        uint32_t offset =
            phys & 0x001FFFFFu;

        if (offset <= g_ram_size - 2u)
        {
            return
                (uint16_t)g_ram[offset + 0u]
                |
                ((uint16_t)g_ram[offset + 1u] << 8);
        }
    }

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
     * Root counters - half access
     * --------------------------------------------------------
     */

    if (
        fm_timer_is_register(phys)
        &&
        (phys & 3u) == 0u
    )
    {
        return
            fm_timer_read_half(
                phys
            );
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

    /* B92 - hot RAM fast path before timer/DMA decoding. */
    if (
        g_ram
        &&
        g_ram_size >= 2u
        &&
        phys < PSX_RAM_MIRROR_END
    )
    {
        uint32_t offset =
            phys & 0x001FFFFFu;

        if (offset <= g_ram_size - 2u)
        {
            g_ram[offset + 0u] = (uint8_t)value;
            g_ram[offset + 1u] = (uint8_t)(value >> 8);
            return;
        }
    }

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
     * Root counters - half access
     * --------------------------------------------------------
     */

    if (
        fm_timer_is_register(phys)
        &&
        (phys & 3u) == 0u
    )
    {
        fm_timer_write_half(
            phys,
            value
        );

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

    /* B92 - hot RAM fast path before all MMIO tests. */
    if (
        g_ram
        &&
        g_ram_size >= 4u
        &&
        phys < PSX_RAM_MIRROR_END
    )
    {
        uint32_t offset =
            phys & 0x001FFFFFu;

        if (offset <= g_ram_size - 4u)
        {
            return
                (uint32_t)g_ram[offset + 0u]
                |
                ((uint32_t)g_ram[offset + 1u] << 8)
                |
                ((uint32_t)g_ram[offset + 2u] << 16)
                |
                ((uint32_t)g_ram[offset + 3u] << 24);
        }
    }

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
     * Root counters
     * --------------------------------------------------------
     */

    if (
        fm_timer_is_register(phys)
        &&
        (phys & 3u) == 0u
    )
    {
        return
            fm_timer_read_word(
                phys
            );
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
     * DMA6 OTC
     * --------------------------------------------------------
     */

    if (phys == PSX_DMA6_MADR)
    {
        return
            g_dma6_madr;
    }

    if (phys == PSX_DMA6_BCR)
    {
        return
            g_dma6_bcr;
    }

    if (phys == PSX_DMA6_CHCR)
    {
        return
            g_dma6_chcr;
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

    /* B92 - hot RAM fast path before all MMIO tests. */
    if (
        g_ram
        &&
        g_ram_size >= 4u
        &&
        phys < PSX_RAM_MIRROR_END
    )
    {
        uint32_t offset =
            phys & 0x001FFFFFu;

        if (offset <= g_ram_size - 4u)
        {
            g_ram[offset + 0u] = (uint8_t)value;
            g_ram[offset + 1u] = (uint8_t)(value >> 8);
            g_ram[offset + 2u] = (uint8_t)(value >> 16);
            g_ram[offset + 3u] = (uint8_t)(value >> 24);
            return;
        }
    }

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
     * Root counters
     * --------------------------------------------------------
     */

    if (
        fm_timer_is_register(phys)
        &&
        (phys & 3u) == 0u
    )
    {
        fm_timer_write_word(
            phys,
            value
        );

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
     * DMA6 OTC
     * --------------------------------------------------------
     */

    if (phys == PSX_DMA6_MADR)
    {
        g_dma6_madr =
            value
            &
            0x00FFFFFFu;

        return;
    }

    if (phys == PSX_DMA6_BCR)
    {
        g_dma6_bcr =
            value;

        return;
    }

    if (phys == PSX_DMA6_CHCR)
    {
        g_dma6_chcr =
            value;

        fm_dma6_try_start();

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


    /*
     * Faire progresser les trois Root Counters.
     */
    for (
        unsigned i = 0;
        i < PSX_TIMER_COUNT;
        ++i
    )
    {
        fm_timer_advance(
            i,
            fm_timer_vblank_delta(
                i
            )
        );
    }
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



void fm_memory_dma_debug(
    FMDmaDebugStats *out
)
{
    if (!out)
    {
        return;
    }


    memset(
        out,
        0,
        sizeof(*out)
    );


    out->dma2_transfer_count =
        g_dma2_transfer_count;

    out->dma2_word_count =
        g_dma2_word_count;

    out->dma2_linked_transfer_count =
        g_dma2_linked_transfer_count;

    out->dma2_madr =
        g_dma2_madr;

    out->dma2_bcr =
        g_dma2_bcr;

    out->dma2_chcr =
        g_dma2_chcr;

    out->dma2_last_start_madr =
        g_dma2_last_start_madr;

    out->dma2_last_chcr =
        g_dma2_last_chcr;

    out->dma2_last_nodes =
        g_dma2_last_nodes;

    out->dma2_last_words =
        g_dma2_last_words;

    out->dma2_last_first_header =
        g_dma2_last_first_header;

    out->dma2_cycle_abort_count =
        g_dma2_cycle_abort_count;

    out->dma2_last_cycle_addr =
        g_dma2_last_cycle_addr;

    out->dma2_max_nodes =
        g_dma2_max_nodes;

    out->dma2_max_words =
        g_dma2_max_words;

    out->dma2_visit_wrap_clears =
        g_dma2_visit_wrap_clears;

    out->dma2_last_empty_ot_nodes =
        g_dma2_last_empty_ot_nodes;

    out->dma2_max_empty_ot_nodes =
        g_dma2_max_empty_ot_nodes;

    out->dma2_linked_last_ms =
        g_dma2_linked_last_ms;

    out->dma2_linked_max_ms =
        g_dma2_linked_max_ms;

    out->dma2_linked_total_ms =
        g_dma2_linked_total_ms;

    out->dma2_linked_over20 =
        g_dma2_linked_over20;

    out->dma2_linked_over33 =
        g_dma2_linked_over33;

    out->dma2_empty_fast_runs =
        g_dma2_empty_fast_runs;

    out->dma2_empty_fast_nodes =
        g_dma2_empty_fast_nodes;

    out->dma2_empty_fast_last =
        g_dma2_empty_fast_last;

    out->dma2_empty_fast_max =
        g_dma2_empty_fast_max;


    out->dma6_transfer_count =
        g_dma6_transfer_count;

    out->dma6_word_count =
        g_dma6_word_count;

    out->dma6_madr =
        g_dma6_madr;

    out->dma6_bcr =
        g_dma6_bcr;

    out->dma6_chcr =
        g_dma6_chcr;
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


/*
 * ============================================================
 * B135 - quick-state MMIO
 * ============================================================
 */
void fm_memory_quick_save(
    FMMemoryQuickState *out
)
{
    if (!out)
    {
        return;
    }

    memset(out, 0, sizeof(*out));

    memcpy(
        out->scratch,
        g_scratch,
        sizeof(g_scratch)
    );

    out->i_stat = g_i_stat;
    out->i_mask = g_i_mask;

    for (unsigned i = 0u; i < PSX_TIMER_COUNT; ++i)
    {
        out->timers[i].count = g_timers[i].count;
        out->timers[i].mode = g_timers[i].mode;
        out->timers[i].target = g_timers[i].target;
        out->timers[i].irq_fired_once = g_timers[i].irq_fired_once;
    }

    out->dma2_madr = g_dma2_madr;
    out->dma2_bcr = g_dma2_bcr;
    out->dma2_chcr = g_dma2_chcr;

    out->dma6_madr = g_dma6_madr;
    out->dma6_bcr = g_dma6_bcr;
    out->dma6_chcr = g_dma6_chcr;

    out->dma_dpcr = g_dma_dpcr;
    out->dma_dicr = g_dma_dicr;
}


void fm_memory_quick_load(
    const FMMemoryQuickState *in
)
{
    if (!in)
    {
        return;
    }

    memcpy(
        g_scratch,
        in->scratch,
        sizeof(g_scratch)
    );

    g_i_stat = in->i_stat;
    g_i_mask = in->i_mask;

    for (unsigned i = 0u; i < PSX_TIMER_COUNT; ++i)
    {
        g_timers[i].count = in->timers[i].count;
        g_timers[i].mode = in->timers[i].mode;
        g_timers[i].target = in->timers[i].target;
        g_timers[i].irq_fired_once = in->timers[i].irq_fired_once;
    }

    g_dma2_madr = in->dma2_madr;
    g_dma2_bcr = in->dma2_bcr;
    g_dma2_chcr = in->dma2_chcr;

    g_dma6_madr = in->dma6_madr;
    g_dma6_bcr = in->dma6_bcr;
    g_dma6_chcr = in->dma6_chcr;

    g_dma_dpcr = in->dma_dpcr;
    g_dma_dicr = in->dma_dicr;

    /*
     * La table de detection de boucle DMA est purement host/debug.
     * Repartir d'une generation propre evite de reutiliser des marques
     * qui appartiennent au run precedent.
     */
    memset(
        g_dma2_visit_epoch,
        0,
        sizeof(g_dma2_visit_epoch)
    );

    g_dma2_visit_generation = 1u;
}
