#include "fm_platform.h"
#include <string.h>

/* French single-track MODE2/2352 profile. Streaming, never whole-disc RAM. */
static FILE *disc;
static uint32_t le32(const uint8_t *p) {
    return p[0] | (uint32_t)p[1] << 8 | (uint32_t)p[2] << 16 | (uint32_t)p[3] << 24;
}
void fm_disc_close(void) { if (disc) fclose(disc); disc = NULL; }
int fm_disc_open(const char *path) {
    fm_disc_close();
    disc = fopen(path, "rb");
    if (!disc) return -1;
    if (fseek(disc, 0, SEEK_END) || ftell(disc) != 548427600L) {
        fm_disc_close(); return -2;
    }
    uint8_t pvd[2048];
    if (fm_disc_read_sector(16, pvd) || pvd[0] != 1 ||
        memcmp(pvd + 1, "CD001", 5) || pvd[6] != 1) {
        fm_disc_close(); return -3;
    }
    return 0;
}
int fm_disc_read_sector(uint32_t lba, uint8_t out[2048]) {
    uint8_t sector[2352];
    static const uint8_t sync[12] = {0,255,255,255,255,255,255,255,255,255,255,0};
    if (!disc || lba >= 233175) return -1;
    if (fseek(disc, (long)lba * 2352L, SEEK_SET) ||
        fread(sector, 1, sizeof sector, disc) != sizeof sector) return -2;
    if (memcmp(sector, sync, 12) || sector[15] != 2 ||
        memcmp(sector + 16, sector + 20, 4) || (sector[18] & 0x20)) return -3;
    memcpy(out, sector + 24, 2048);
    return 0;
}
int fm_disc_load_exe(uint8_t *ram, uint32_t *entry) {
    uint8_t header[2048], block[2048];
    if (fm_disc_read_sector(25, header) || memcmp(header, "PS-X EXE", 8)) return -1;
    uint32_t address = le32(header + 0x18), size = le32(header + 0x1c);
    if (address != 0x80010000 || size != 0x1d0000 ||
        le32(header + 0x10) != 0x800128cc) return -2;
    memset(ram, 0, 2 * 1024 * 1024);
    for (uint32_t offset = 0; offset < size; offset += 2048) {
        if (fm_disc_read_sector(26 + offset / 2048, block)) return -3;
        memcpy(ram + 0x10000 + offset, block, 2048);
    }
    *entry = le32(header + 0x10);
    return 0;
}
