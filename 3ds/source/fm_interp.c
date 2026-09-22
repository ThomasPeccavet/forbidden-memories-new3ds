#include "fm_interp.h"

#include <stdint.h>

/*
 * B135.1 - le GPF de la scene Simon peut etre repris par le fallback
 * R3000A apres un stop du code ARM recompile. On reutilise exactement
 * le meme helper GTE que le chemin natif, mais uniquement pour GPF.
 */
extern void gte_execute(
    CPUState *cpu,
    uint32_t cmd
);

extern uint32_t gte_read_data(
    CPUState *cpu,
    uint8_t reg
);

extern uint32_t gte_read_ctrl(
    CPUState *cpu,
    uint8_t reg
);

extern void gte_write_data(
    CPUState *cpu,
    uint8_t reg,
    uint32_t value
);

extern void gte_write_ctrl(
    CPUState *cpu,
    uint8_t reg,
    uint32_t value
);


/*
 * ============================================================
 * Helpers
 * ============================================================
 */

static inline uint32_t rs_value(
    CPUState *cpu,
    uint32_t instruction
)
{
    return cpu->gpr[
        (instruction >> 21) & 31u
    ];
}


static inline uint32_t rt_value(
    CPUState *cpu,
    uint32_t instruction
)
{
    return cpu->gpr[
        (instruction >> 16) & 31u
    ];
}


static inline uint32_t sign_extend16(
    uint32_t value
)
{
    return (uint32_t)(
        (int32_t)(
            (int16_t)(
                value & 0xFFFFu
            )
        )
    );
}


static inline void set_reg(
    CPUState *cpu,
    uint32_t reg,
    uint32_t value
)
{
    /*
     * $zero n'est jamais modifiable.
     */
    if (reg != 0)
    {
        cpu->gpr[reg] =
            value;
    }


    cpu->gpr[0] =
        0;
}


/*
 * ============================================================
 * Résultat helper
 * ============================================================
 */

static FMInterpResult make_result(
    FMInterpStopReason reason,
    uint32_t pc,
    uint32_t instruction,
    uint32_t count
)
{
    FMInterpResult result;


    result.reason =
        reason;


    result.pc =
        pc;


    result.instruction =
        instruction;


    result.instructions =
        count;


    return result;
}


/*
 * ============================================================
 * Instruction normale
 *
 * Retour :
 *
 * 0 = OK
 * 1 = opcode unsupported
 * 2 = syscall
 * 3 = GTE
 *
 * Les instructions de contrôle de flux NE passent pas ici.
 * ============================================================
 */

static int exec_normal(
    CPUState *cpu,
    uint32_t pc,
    uint32_t instruction
)
{
    uint32_t opcode =
        instruction >> 26;


    uint32_t rs =
        (instruction >> 21) & 31u;


    uint32_t rt =
        (instruction >> 16) & 31u;


    uint32_t rd =
        (instruction >> 11) & 31u;


    uint32_t sa =
        (instruction >> 6) & 31u;


    uint32_t funct =
        instruction & 63u;


    uint32_t rs_v =
        cpu->gpr[rs];


    uint32_t rt_v =
        cpu->gpr[rt];


    uint32_t imm =
        instruction & 0xFFFFu;


    uint32_t simm =
        sign_extend16(
            imm
        );


    /*
     * ========================================================
     * SPECIAL
     * ========================================================
     */

    if (opcode == 0x00u)
    {
        switch (funct)
        {
            /*
             * SLL
             */
            case 0x00:
            {
                set_reg(
                    cpu,
                    rd,
                    rt_v << sa
                );

                return 0;
            }


            /*
             * SRL
             */
            case 0x02:
            {
                set_reg(
                    cpu,
                    rd,
                    rt_v >> sa
                );

                return 0;
            }


            /*
             * SRA
             */
            case 0x03:
            {
                set_reg(
                    cpu,
                    rd,
                    (uint32_t)(
                        (int32_t)rt_v
                        >>
                        sa
                    )
                );

                return 0;
            }


            /*
             * SLLV
             */
            case 0x04:
            {
                set_reg(
                    cpu,
                    rd,
                    rt_v
                    <<
                    (rs_v & 31u)
                );

                return 0;
            }


            /*
             * SRLV
             */
            case 0x06:
            {
                set_reg(
                    cpu,
                    rd,
                    rt_v
                    >>
                    (rs_v & 31u)
                );

                return 0;
            }


            /*
             * SRAV
             */
            case 0x07:
            {
                set_reg(
                    cpu,
                    rd,
                    (uint32_t)(
                        (int32_t)rt_v
                        >>
                        (rs_v & 31u)
                    )
                );

                return 0;
            }


            /*
             * SYSCALL
             */
            case 0x0C:
            {
                return 2;
            }


            /*
             * BREAK
             */
            case 0x0D:
            {
                return 1;
            }


            /*
             * SYNC
             *
             * Pas significatif pour notre RAM guest actuelle.
             */
            case 0x0F:
            {
                return 0;
            }


            /*
             * MFHI
             */
            case 0x10:
            {
                set_reg(
                    cpu,
                    rd,
                    cpu->hi
                );

                return 0;
            }


            /*
             * MTHI
             */
            case 0x11:
            {
                cpu->hi =
                    rs_v;

                return 0;
            }


            /*
             * MFLO
             */
            case 0x12:
            {
                set_reg(
                    cpu,
                    rd,
                    cpu->lo
                );

                return 0;
            }


            /*
             * MTLO
             */
            case 0x13:
            {
                cpu->lo =
                    rs_v;

                return 0;
            }


            /*
             * MULT
             */
            case 0x18:
            {
                int64_t value =
                    (int64_t)(int32_t)rs_v
                    *
                    (int64_t)(int32_t)rt_v;


                cpu->lo =
                    (uint32_t)value;


                cpu->hi =
                    (uint32_t)(
                        ((uint64_t)value)
                        >>
                        32
                    );


                return 0;
            }


            /*
             * MULTU
             */
            case 0x19:
            {
                uint64_t value =
                    (uint64_t)rs_v
                    *
                    (uint64_t)rt_v;


                cpu->lo =
                    (uint32_t)value;


                cpu->hi =
                    (uint32_t)(
                        value >> 32
                    );


                return 0;
            }


            /*
             * DIV
             */
            case 0x1A:
            {
                int32_t a =
                    (int32_t)rs_v;


                int32_t b =
                    (int32_t)rt_v;


                if (b == 0)
                {
                    cpu->lo =
                        a >= 0
                            ? 0xFFFFFFFFu
                            : 1u;


                    cpu->hi =
                        (uint32_t)a;
                }
                else if (
                    a == (int32_t)0x80000000u
                    &&
                    b == -1
                )
                {
                    cpu->lo =
                        0x80000000u;


                    cpu->hi =
                        0;
                }
                else
                {
                    cpu->lo =
                        (uint32_t)(
                            a / b
                        );


                    cpu->hi =
                        (uint32_t)(
                            a % b
                        );
                }


                return 0;
            }


            /*
             * DIVU
             */
            case 0x1B:
            {
                if (rt_v == 0)
                {
                    cpu->lo =
                        0xFFFFFFFFu;


                    cpu->hi =
                        rs_v;
                }
                else
                {
                    cpu->lo =
                        rs_v / rt_v;


                    cpu->hi =
                        rs_v % rt_v;
                }


                return 0;
            }


            /*
             * ADD / ADDU
             *
             * Overflow exception ignorée pour le bring-up.
             */
            case 0x20:
            case 0x21:
            {
                set_reg(
                    cpu,
                    rd,
                    rs_v + rt_v
                );

                return 0;
            }


            /*
             * SUB / SUBU
             */
            case 0x22:
            case 0x23:
            {
                set_reg(
                    cpu,
                    rd,
                    rs_v - rt_v
                );

                return 0;
            }


            /*
             * AND
             */
            case 0x24:
            {
                set_reg(
                    cpu,
                    rd,
                    rs_v & rt_v
                );

                return 0;
            }


            /*
             * OR
             */
            case 0x25:
            {
                set_reg(
                    cpu,
                    rd,
                    rs_v | rt_v
                );

                return 0;
            }


            /*
             * XOR
             */
            case 0x26:
            {
                set_reg(
                    cpu,
                    rd,
                    rs_v ^ rt_v
                );

                return 0;
            }


            /*
             * NOR
             */
            case 0x27:
            {
                set_reg(
                    cpu,
                    rd,
                    ~(rs_v | rt_v)
                );

                return 0;
            }


            /*
             * SLT
             */
            case 0x2A:
            {
                set_reg(
                    cpu,
                    rd,
                    (
                        (int32_t)rs_v
                        <
                        (int32_t)rt_v
                    )
                        ? 1u
                        : 0u
                );

                return 0;
            }


            /*
             * SLTU
             */
            case 0x2B:
            {
                set_reg(
                    cpu,
                    rd,
                    rs_v < rt_v
                        ? 1u
                        : 0u
                );

                return 0;
            }


            /*
             * JR / JALR sont traités dans run_block().
             */
            case 0x08:
            case 0x09:
            {
                return 1;
            }


            default:
            {
                return 1;
            }
        }
    }


    /*
     * ========================================================
     * Immediate arithmetic
     * ========================================================
     */

    switch (opcode)
    {
        /*
         * ADDI / ADDIU
         */
        case 0x08:
        case 0x09:
        {
            set_reg(
                cpu,
                rt,
                rs_v + simm
            );

            return 0;
        }


        /*
         * SLTI
         */
        case 0x0A:
        {
            set_reg(
                cpu,
                rt,
                (
                    (int32_t)rs_v
                    <
                    (int32_t)simm
                )
                    ? 1u
                    : 0u
            );

            return 0;
        }


        /*
         * SLTIU
         */
        case 0x0B:
        {
            set_reg(
                cpu,
                rt,
                rs_v < simm
                    ? 1u
                    : 0u
            );

            return 0;
        }


        /*
         * ANDI
         */
        case 0x0C:
        {
            set_reg(
                cpu,
                rt,
                rs_v & imm
            );

            return 0;
        }


        /*
         * ORI
         */
        case 0x0D:
        {
            set_reg(
                cpu,
                rt,
                rs_v | imm
            );

            return 0;
        }


        /*
         * XORI
         */
        case 0x0E:
        {
            set_reg(
                cpu,
                rt,
                rs_v ^ imm
            );

            return 0;
        }


        /*
         * LUI
         */
        case 0x0F:
        {
            set_reg(
                cpu,
                rt,
                imm << 16
            );

            return 0;
        }


        /*
         * ====================================================
         * COP0
         * ====================================================
         */
        case 0x10:
        {
            uint32_t cop_rs =
                rs;


            /*
             * MFC0
             */
            if (cop_rs == 0x00)
            {
                set_reg(
                    cpu,
                    rt,
                    cpu->cop0[rd]
                );

                return 0;
            }


            /*
             * MTC0
             */
            if (cop_rs == 0x04)
            {
                cpu->cop0[rd] =
                    rt_v;

                return 0;
            }


            /*
             * RFE
             */
            if (
                cop_rs == 0x10
                &&
                funct == 0x10
            )
            {
                uint32_t sr =
                    cpu->cop0[12];


                cpu->cop0[12] =
                    (sr & ~0x0Fu)
                    |
                    (
                        (sr >> 2)
                        &
                        0x0Fu
                    );


                return 0;
            }


            return 1;
        }


        /*
         * ====================================================
         * COP2 / GTE
         * ====================================================
         */
        case 0x12:
        {
            uint32_t cop_rs =
                rs;


            /*
             * MFC2
             */
            if (cop_rs == 0x00)
            {
                set_reg(
                    cpu,
                    rt,
                    gte_read_data(cpu, (uint8_t)rd)
                );

                return 0;
            }


            /*
             * CFC2
             */
            if (cop_rs == 0x02)
            {
                set_reg(
                    cpu,
                    rt,
                    gte_read_ctrl(cpu, (uint8_t)rd)
                );

                return 0;
            }


            /*
             * MTC2
             */
            if (cop_rs == 0x04)
            {
                gte_write_data(
                    cpu,
                    (uint8_t)rd,
                    rt_v
                );

                return 0;
            }


            /*
             * CTC2
             */
            if (cop_rs == 0x06)
            {
                gte_write_ctrl(
                    cpu,
                    (uint8_t)rd,
                    rt_v
                );

                return 0;
            }


            /*
             * Commande GTE.
             *
             * B135.1 : la scene Simon atteint GPF (fonction 0x3D)
             * dans FUN_80088BD8. Le code ARM recompile peut s'arreter
             * sur cette commande puis reprendre exactement au PC GPF
             * dans l'interpreteur. Si on renvoie simplement FM_INTERP_GTE,
             * main.c classe alors l'instruction 0x4B98003D comme STOP:4.
             *
             * Executer GPF ici preserve aussi correctement les delay slots,
             * car exec_normal() reste dans le flot normal de run_block().
             *
             * Les autres commandes restent volontairement non supportees :
             * on veut voir le prochain vrai verrou au lieu de le masquer.
             */
            if (cop_rs >= 0x10)
            {
                switch (instruction & 0x3Fu)
                {
                    case 0x01u: /* RTPS  */
                    case 0x06u: /* NCLIP */
                    case 0x12u: /* MVMVA */
                    case 0x13u: /* NCDS  */
                    case 0x2Du: /* AVSZ3 */
                    case 0x2Eu: /* AVSZ4 */
                    case 0x30u: /* RTPT  */
                    case 0x3Du: /* GPF   */
                        gte_execute(
                            cpu,
                            instruction
                        );

                        return 0;

                    default:
                        return 3;
                }
            }


            return 1;
        }


        /*
         * ====================================================
         * Loads
         * ====================================================
         */

        /*
         * LB
         */
        case 0x20:
        {
            uint32_t addr =
                rs_v + simm;


            int8_t value =
                (int8_t)
                    cpu->read_byte(
                        addr
                    );


            set_reg(
                cpu,
                rt,
                (uint32_t)(
                    (int32_t)value
                )
            );

            return 0;
        }


        /*
         * LH
         */
        case 0x21:
        {
            uint32_t addr =
                rs_v + simm;


            int16_t value =
                (int16_t)
                    cpu->read_half(
                        addr
                    );


            set_reg(
                cpu,
                rt,
                (uint32_t)(
                    (int32_t)value
                )
            );

            return 0;
        }


        /*
         * LWL
         */
        case 0x22:
        {
            uint32_t addr =
                rs_v + simm;


            uint32_t aligned =
                addr & ~3u;


            uint32_t mem =
                cpu->read_word(
                    aligned
                );


            uint32_t old =
                rt_v;


            switch (addr & 3u)
            {
                case 0:
                    old =
                        (old & 0x00FFFFFFu)
                        |
                        (mem << 24);
                    break;

                case 1:
                    old =
                        (old & 0x0000FFFFu)
                        |
                        (mem << 16);
                    break;

                case 2:
                    old =
                        (old & 0x000000FFu)
                        |
                        (mem << 8);
                    break;

                case 3:
                    old =
                        mem;
                    break;
            }


            set_reg(
                cpu,
                rt,
                old
            );

            return 0;
        }


        /*
         * LW
         */
        case 0x23:
        {
            uint32_t addr =
                rs_v + simm;


            set_reg(
                cpu,
                rt,
                cpu->read_word(
                    addr
                )
            );

            return 0;
        }


        /*
         * LBU
         */
        case 0x24:
        {
            uint32_t addr =
                rs_v + simm;


            set_reg(
                cpu,
                rt,
                cpu->read_byte(
                    addr
                )
            );

            return 0;
        }


        /*
         * LHU
         */
        case 0x25:
        {
            uint32_t addr =
                rs_v + simm;


            set_reg(
                cpu,
                rt,
                cpu->read_half(
                    addr
                )
            );

            return 0;
        }


        /*
         * LWR
         */
        case 0x26:
        {
            uint32_t addr =
                rs_v + simm;


            uint32_t aligned =
                addr & ~3u;


            uint32_t mem =
                cpu->read_word(
                    aligned
                );


            uint32_t old =
                rt_v;


            switch (addr & 3u)
            {
                case 0:
                    old =
                        mem;
                    break;

                case 1:
                    old =
                        (old & 0xFF000000u)
                        |
                        (mem >> 8);
                    break;

                case 2:
                    old =
                        (old & 0xFFFF0000u)
                        |
                        (mem >> 16);
                    break;

                case 3:
                    old =
                        (old & 0xFFFFFF00u)
                        |
                        (mem >> 24);
                    break;
            }


            set_reg(
                cpu,
                rt,
                old
            );

            return 0;
        }


        /*
         * ====================================================
         * Stores
         * ====================================================
         */

        /*
         * SB
         */
        case 0x28:
        {
            cpu->write_byte(
                rs_v + simm,
                (uint8_t)rt_v
            );

            return 0;
        }


        /*
         * SH
         */
        case 0x29:
        {
            cpu->write_half(
                rs_v + simm,
                (uint16_t)rt_v
            );

            return 0;
        }


        /*
         * SWL
         */
        case 0x2A:
        {
            uint32_t addr =
                rs_v + simm;


            uint32_t aligned =
                addr & ~3u;


            uint32_t mem =
                cpu->read_word(
                    aligned
                );


            switch (addr & 3u)
            {
                case 0:
                    mem =
                        (mem & 0xFFFFFF00u)
                        |
                        (rt_v >> 24);
                    break;

                case 1:
                    mem =
                        (mem & 0xFFFF0000u)
                        |
                        (rt_v >> 16);
                    break;

                case 2:
                    mem =
                        (mem & 0xFF000000u)
                        |
                        (rt_v >> 8);
                    break;

                case 3:
                    mem =
                        rt_v;
                    break;
            }


            cpu->write_word(
                aligned,
                mem
            );

            return 0;
        }


        /*
         * SW
         */
        case 0x2B:
        {
            cpu->write_word(
                rs_v + simm,
                rt_v
            );

            return 0;
        }


        /*
         * SWR
         */
        case 0x2E:
        {
            uint32_t addr =
                rs_v + simm;


            uint32_t aligned =
                addr & ~3u;


            uint32_t mem =
                cpu->read_word(
                    aligned
                );


            switch (addr & 3u)
            {
                case 0:
                    mem =
                        rt_v;
                    break;

                case 1:
                    mem =
                        (mem & 0x000000FFu)
                        |
                        (rt_v << 8);
                    break;

                case 2:
                    mem =
                        (mem & 0x0000FFFFu)
                        |
                        (rt_v << 16);
                    break;

                case 3:
                    mem =
                        (mem & 0x00FFFFFFu)
                        |
                        (rt_v << 24);
                    break;
            }


            cpu->write_word(
                aligned,
                mem
            );

            return 0;
        }


        /*
         * CACHE
         *
         * Pas de cache guest à maintenir dans ce prototype.
         */
        case 0x2F:
        {
            return 0;
        }


        /*
         * LWC2
         */
        case 0x32:
        {
            uint32_t addr =
                rs_v + simm;


            gte_write_data(
                cpu,
                (uint8_t)rt,
                cpu->read_word(
                    addr
                )
            );


            return 0;
        }


        /*
         * SWC2
         */
        case 0x3A:
        {
            uint32_t addr =
                rs_v + simm;


            cpu->write_word(
                addr,
                gte_read_data(
                    cpu,
                    (uint8_t)rt
                )
            );


            return 0;
        }


        default:
        {
            (void)pc;

            return 1;
        }
    }
}


/*
 * ============================================================
 * Delay slot
 * ============================================================
 */

static int exec_delay_slot(
    CPUState *cpu,
    uint32_t pc,
    uint32_t *instruction_out
)
{
    uint32_t instruction =
        cpu->read_word(
            pc
        );


    if (instruction_out)
    {
        *instruction_out =
            instruction;
    }


    uint32_t opcode =
        instruction >> 26;


    uint32_t funct =
        instruction & 63u;


    /*
     * Un contrôle de flux dans un delay slot est volontairement
     * refusé pour l'instant.
     */
    if (
        opcode == 0x02
        ||
        opcode == 0x03
        ||
        opcode == 0x01
        ||
        opcode == 0x04
        ||
        opcode == 0x05
        ||
        opcode == 0x06
        ||
        opcode == 0x07
        ||
        (
            opcode == 0x00
            &&
            (
                funct == 0x08
                ||
                funct == 0x09
            )
        )
    )
    {
        return 1;
    }


    return
        exec_normal(
            cpu,
            pc,
            instruction
        );
}


/*
 * ============================================================
 * Interprétation d'un basic block
 * ============================================================
 */

FMInterpResult fm_interp_run_block(
    CPUState *cpu,
    uint32_t max_instructions
)
{
    if (!cpu)
    {
        return
            make_result(
                FM_INTERP_UNSUPPORTED,
                0,
                0,
                0
            );
    }


    if (max_instructions == 0)
    {
        max_instructions =
            1024;
    }


    uint32_t count =
        0;


    while (
        count
        <
        max_instructions
    )
    {
        uint32_t pc =
            cpu->pc;


        uint32_t instruction =
            cpu->read_word(
                pc
            );


        uint32_t opcode =
            instruction >> 26;


        uint32_t rs =
            (instruction >> 21) & 31u;


        uint32_t rt =
            (instruction >> 16) & 31u;


        uint32_t rd =
            (instruction >> 11) & 31u;


        uint32_t funct =
            instruction & 63u;


        uint32_t rs_v =
            cpu->gpr[rs];


        uint32_t rt_v =
            cpu->gpr[rt];


        uint32_t simm =
            sign_extend16(
                instruction
                &
                0xFFFFu
            );


        ++count;


        /*
         * ====================================================
         * JR / JALR
         * ====================================================
         */

        if (
            opcode == 0x00
            &&
            (
                funct == 0x08
                ||
                funct == 0x09
            )
        )
        {
            uint32_t target =
                rs_v;


            /*
             * JALR
             */
            if (funct == 0x09)
            {
                uint32_t link_reg =
                    rd != 0
                        ? rd
                        : 31u;


                set_reg(
                    cpu,
                    link_reg,
                    pc + 8
                );
            }


            uint32_t delay_instruction =
                0;


            int delay_status =
                exec_delay_slot(
                    cpu,
                    pc + 4,
                    &delay_instruction
                );


            ++count;


            if (delay_status == 2)
            {
                return
                    make_result(
                        FM_INTERP_SYSCALL,
                        pc + 4,
                        delay_instruction,
                        count
                    );
            }


            if (delay_status == 3)
            {
                return
                    make_result(
                        FM_INTERP_GTE,
                        pc + 4,
                        delay_instruction,
                        count
                    );
            }


            if (delay_status != 0)
            {
                return
                    make_result(
                        FM_INTERP_UNSUPPORTED,
                        pc + 4,
                        delay_instruction,
                        count
                    );
            }


            cpu->pc =
                target;


            cpu->gpr[0] =
                0;


            return
                make_result(
                    FM_INTERP_BLOCK_DONE,
                    pc,
                    instruction,
                    count
                );
        }


        /*
         * ====================================================
         * J / JAL
         * ====================================================
         */

        if (
            opcode == 0x02
            ||
            opcode == 0x03
        )
        {
            uint32_t target =
                (
                    (pc + 4)
                    &
                    0xF0000000u
                )
                |
                (
                    (instruction & 0x03FFFFFFu)
                    <<
                    2
                );


            /*
             * JAL
             */
            if (opcode == 0x03)
            {
                cpu->gpr[31] =
                    pc + 8;
            }


            uint32_t delay_instruction =
                0;


            int delay_status =
                exec_delay_slot(
                    cpu,
                    pc + 4,
                    &delay_instruction
                );


            ++count;


            if (delay_status == 2)
            {
                return
                    make_result(
                        FM_INTERP_SYSCALL,
                        pc + 4,
                        delay_instruction,
                        count
                    );
            }


            if (delay_status == 3)
            {
                return
                    make_result(
                        FM_INTERP_GTE,
                        pc + 4,
                        delay_instruction,
                        count
                    );
            }


            if (delay_status != 0)
            {
                return
                    make_result(
                        FM_INTERP_UNSUPPORTED,
                        pc + 4,
                        delay_instruction,
                        count
                    );
            }


            cpu->pc =
                target;


            cpu->gpr[0] =
                0;


            return
                make_result(
                    FM_INTERP_BLOCK_DONE,
                    pc,
                    instruction,
                    count
                );
        }


        /*
         * ====================================================
         * REGIMM
         *
         * BLTZ
         * BGEZ
         * BLTZAL
         * BGEZAL
         * ====================================================
         */

        if (opcode == 0x01)
        {
            uint32_t type =
                rt;


            int taken =
                0;


            switch (type)
            {
                case 0x00:
                    taken =
                        (int32_t)rs_v < 0;
                    break;


                case 0x01:
                    taken =
                        (int32_t)rs_v >= 0;
                    break;


                case 0x10:
                    taken =
                        (int32_t)rs_v < 0;

                    cpu->gpr[31] =
                        pc + 8;
                    break;


                case 0x11:
                    taken =
                        (int32_t)rs_v >= 0;

                    cpu->gpr[31] =
                        pc + 8;
                    break;


                default:
                    return
                        make_result(
                            FM_INTERP_UNSUPPORTED,
                            pc,
                            instruction,
                            count
                        );
            }


            uint32_t target =
                pc
                +
                4
                +
                (simm << 2);


            uint32_t delay_instruction =
                0;


            int delay_status =
                exec_delay_slot(
                    cpu,
                    pc + 4,
                    &delay_instruction
                );


            ++count;


            if (delay_status != 0)
            {
                return
                    make_result(
                        delay_status == 3
                            ? FM_INTERP_GTE
                            : (
                                delay_status == 2
                                    ? FM_INTERP_SYSCALL
                                    : FM_INTERP_UNSUPPORTED
                            ),
                        pc + 4,
                        delay_instruction,
                        count
                    );
            }


            cpu->pc =
                taken
                    ? target
                    : pc + 8;


            cpu->gpr[0] =
                0;


            return
                make_result(
                    FM_INTERP_BLOCK_DONE,
                    pc,
                    instruction,
                    count
                );
        }


        /*
         * ====================================================
         * BEQ / BNE / BLEZ / BGTZ
         * ====================================================
         */

        if (
            opcode == 0x04
            ||
            opcode == 0x05
            ||
            opcode == 0x06
            ||
            opcode == 0x07
        )
        {
            int taken =
                0;


            if (opcode == 0x04)
            {
                taken =
                    rs_v == rt_v;
            }
            else if (opcode == 0x05)
            {
                taken =
                    rs_v != rt_v;
            }
            else if (opcode == 0x06)
            {
                taken =
                    (int32_t)rs_v <= 0;
            }
            else
            {
                taken =
                    (int32_t)rs_v > 0;
            }


            uint32_t target =
                pc
                +
                4
                +
                (simm << 2);


            uint32_t delay_instruction =
                0;


            int delay_status =
                exec_delay_slot(
                    cpu,
                    pc + 4,
                    &delay_instruction
                );


            ++count;


            if (delay_status != 0)
            {
                return
                    make_result(
                        delay_status == 3
                            ? FM_INTERP_GTE
                            : (
                                delay_status == 2
                                    ? FM_INTERP_SYSCALL
                                    : FM_INTERP_UNSUPPORTED
                            ),
                        pc + 4,
                        delay_instruction,
                        count
                    );
            }


            cpu->pc =
                taken
                    ? target
                    : pc + 8;


            cpu->gpr[0] =
                0;


            return
                make_result(
                    FM_INTERP_BLOCK_DONE,
                    pc,
                    instruction,
                    count
                );
        }


        /*
         * ====================================================
         * Instruction normale
         * ====================================================
         */

        int status =
            exec_normal(
                cpu,
                pc,
                instruction
            );


        if (status == 2)
        {
            return
                make_result(
                    FM_INTERP_SYSCALL,
                    pc,
                    instruction,
                    count
                );
        }


        if (status == 3)
        {
            return
                make_result(
                    FM_INTERP_GTE,
                    pc,
                    instruction,
                    count
                );
        }


        if (status != 0)
        {
            return
                make_result(
                    FM_INTERP_UNSUPPORTED,
                    pc,
                    instruction,
                    count
                );
        }


        cpu->pc =
            pc + 4;


        cpu->gpr[0] =
            0;
    }


    return
        make_result(
            FM_INTERP_BUDGET,
            cpu->pc,
            cpu->read_word(
                cpu->pc
            ),
            count
        );
}


/*
 * ============================================================
 * Diagnostic
 * ============================================================
 */

const char *fm_interp_stop_name(
    FMInterpStopReason reason
)
{
    switch (reason)
    {
        case FM_INTERP_BLOCK_DONE:
            return "BLOCK";


        case FM_INTERP_BUDGET:
            return "BUDGET";


        case FM_INTERP_SYSCALL:
            return "SYSCALL";


        case FM_INTERP_GTE:
            return "GTE";


        case FM_INTERP_UNSUPPORTED:
            return "UNSUPPORTED";


        default:
            return "NONE";
    }
}