#pragma once
#include <stdint.h>
#include <stddef.h>
#define FM_SNAPSHOT_MAGIC 0x53514D46u
#define FM_SNAPSHOT_VERSION 4u
#define FM_SNAPSHOT_MAX (24u * 1024u * 1024u)
/* Explicit envelope: format/schema/disc checks and CRC before any mutation. */
int fm_snapshot_write(const char *path, const void *payload, uint32_t bytes,
    uint32_t schema, uint64_t disc, uint32_t build);
/* Returned storage is owned by the caller. Legacy v3 has no integrity CRC. */
int fm_snapshot_read(const char *path, void **payload, uint32_t *bytes,
    uint32_t schema, uint64_t disc, int *legacy);
uint32_t fm_snapshot_crc(const void *data, size_t bytes);
