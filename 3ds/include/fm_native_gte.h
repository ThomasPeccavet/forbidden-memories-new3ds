#ifndef FM_NATIVE_GTE_H
#define FM_NATIVE_GTE_H
#include "cpu_state.h"
/* B136.62: single COP2 transfer contract shared by the shim and generated
 * build copies. Constant register numbers eliminate the generic switch.
 * GTE commands, flags, FIFOs and snapshot canonicalization stay unchanged. */
static inline uint32_t fm_b136_gte_sign_extend_16(uint32_t value)
{
    return (uint32_t)(int32_t)(int16_t)(value & 0xFFFFu);
}


static inline uint32_t fm_b136_gte_lzcr(uint32_t value)
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


static inline uint32_t fm_b136_gte_irgb_component(uint32_t value)
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


static inline uint32_t fm_b136_gte_pack_irgb(const CPUState *cpu)
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


static inline uint32_t fm_native_gte_read_data(
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


static inline uint32_t fm_native_gte_read_ctrl(
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


static inline void fm_native_gte_write_data(
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


static inline void fm_native_gte_write_ctrl(
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

#endif
