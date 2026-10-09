#pragma once
#include <stdint.h>
/* CPU fields used by the production interpreter in host integration tests. */
typedef struct CPUState {
    uint32_t gpr[32], pc, hi, lo, cop0[32];
    uint32_t gte_data[32], gte_ctrl[32];
    uint64_t muldiv_ts_done, gte_ts_done;
    uint8_t read_absorb[33], read_absorb_which, read_fudge, ld_which_t;
    uint32_t ld_absorb;
    uint8_t (*read_byte)(uint32_t);
    uint16_t (*read_half)(uint32_t);
    uint32_t (*read_word)(uint32_t);
    void (*write_byte)(uint32_t, uint8_t);
    void (*write_half)(uint32_t, uint16_t);
    void (*write_word)(uint32_t, uint32_t);
} CPUState;
