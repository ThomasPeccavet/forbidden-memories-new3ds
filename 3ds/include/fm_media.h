#pragma once
#include <stdint.h>
#include <stdio.h>
#include "cpu_state.h"
void fm_media_reset(void);
void fm_media_command(uint32_t cmd, uint32_t params, int raw_mode, uint32_t lba);
void fm_media_poll(uint32_t target_lba, int running);
void fm_media_guest_entry(CPUState *cpu, uint32_t phys);
void fm_media_cd_write(uint32_t address, uint8_t value);
uint8_t fm_media_cd_read(uint32_t address);
void fm_media_dump(FILE *file);
/* Returns 1=published/accepted, 0=backpressure, -1=invalid frame. */
int fm_media_str_sector(const uint8_t raw[2352]);

#include "fm_xa.h"
typedef struct FMStrSnapshot {
    uint8_t headers[20][32], data[20][2016];
    uint32_t number, count, seen, last_published;
    int32_t complete;
} FMStrSnapshot;
typedef struct FMMediaSnapshot {
    FMStrSnapshot str;
    FMXaDecoder xa;
    int32_t active;
    uint8_t mode, filter_file, filter_channel, index_reg;
    uint8_t pending_volume[4], volume[4];
    uint32_t next_lba;
} FMMediaSnapshot;
void fm_media_snapshot_save(FMMediaSnapshot *out);
int fm_media_snapshot_valid(const FMMediaSnapshot *in);
void fm_media_snapshot_load(const FMMediaSnapshot *in);
