#include "fm_platform.h"

#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>


/*
 * French single-track MODE2/2352 profile.
 *
 * The disc is streamed sector by sector. It is never loaded
 * completely in RAM.
 */

static FILE *disc = NULL;


static uint32_t le32(
    const uint8_t *p
)
{
    return
        (uint32_t)p[0]
        |
        ((uint32_t)p[1] << 8)
        |
        ((uint32_t)p[2] << 16)
        |
        ((uint32_t)p[3] << 24);
}


void fm_disc_close(void)
{
    if (disc)
    {
        fclose(disc);
    }

    disc = NULL;
}


int fm_disc_open(
    const char *path
)
{
    fm_disc_close();

    disc =
        fopen(
            path,
            "rb"
        );

    if (!disc)
    {
        return -1;
    }


    /*
     * Exact French image size currently used by the project.
     */
    if (
        fseek(
            disc,
            0,
            SEEK_END
        )
        ||
        ftell(disc) != 548427600L
    )
    {
        fm_disc_close();

        return -2;
    }


    /*
     * Validate the ISO9660 Primary Volume Descriptor.
     */
    uint8_t pvd[2048];

    if (
        fm_disc_read_sector(
            16,
            pvd
        )
        ||
        pvd[0] != 1
        ||
        memcmp(
            pvd + 1,
            "CD001",
            5
        )
        ||
        pvd[6] != 1
    )
    {
        fm_disc_close();

        return -3;
    }


    return 0;
}


int fm_disc_read_sector(
    uint32_t lba,
    uint8_t out[2048]
)
{
    uint8_t sector[2352];

    static const uint8_t sync[12] =
    {
        0x00,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0x00
    };


    if (
        !disc
        ||
        lba >= 233175u
    )
    {
        return -1;
    }


    if (
        fseek(
            disc,
            (long)lba * 2352L,
            SEEK_SET
        )
        ||
        fread(
            sector,
            1,
            sizeof(sector),
            disc
        )
        !=
        sizeof(sector)
    )
    {
        return -2;
    }


    /*
     * MODE2/2352:
     *
     *  0..11  sync
     * 12..15  header
     * 16..19  XA subheader
     * 20..23  duplicated XA subheader
     * 24..    user data
     *
     * Form1 has 2048 bytes of user data.
     * Form2 has 2324 bytes.
     *
     * For the current bring-up API we expose the first 2048 bytes
     * for both forms.
     */
    if (
        memcmp(
            sector,
            sync,
            sizeof(sync)
        )
        ||
        sector[15] != 2
        ||
        memcmp(
            sector + 16,
            sector + 20,
            4
        )
    )
    {
        return -3;
    }


    memcpy(
        out,
        sector + 24,
        2048
    );


    return 0;
}


/*
 * ============================================================
 * ISO9660 helpers
 * ============================================================
 */

static int iso_name_equal(
    const uint8_t *iso_name,
    unsigned iso_len,
    const char *wanted
)
{
    unsigned iso_effective_len =
        iso_len;


    /*
     * ISO9660 files commonly end with ";1".
     */
    for (
        unsigned i = 0;
        i < iso_len;
        ++i
    )
    {
        if (iso_name[i] == ';')
        {
            iso_effective_len =
                i;

            break;
        }
    }


    unsigned wanted_len =
        (unsigned)strlen(
            wanted
        );


    /*
     * Be tolerant if the guest path itself includes ;1.
     */
    for (
        unsigned i = 0;
        i < wanted_len;
        ++i
    )
    {
        if (wanted[i] == ';')
        {
            wanted_len =
                i;

            break;
        }
    }


    if (
        iso_effective_len
        !=
        wanted_len
    )
    {
        return 0;
    }


    for (
        unsigned i = 0;
        i < iso_effective_len;
        ++i
    )
    {
        unsigned char a =
            (unsigned char)
                iso_name[i];

        unsigned char b =
            (unsigned char)
                wanted[i];


        if (
            toupper(a)
            !=
            toupper(b)
        )
        {
            return 0;
        }
    }


    return 1;
}


static int iso_find_in_directory(
    uint32_t dir_lba,
    uint32_t dir_size,
    const char *name,
    uint32_t *out_lba,
    uint32_t *out_size,
    uint8_t *out_flags
)
{
    uint8_t sector[2048];

    uint32_t offset =
        0;


    while (offset < dir_size)
    {
        uint32_t sector_index =
            offset
            /
            2048u;

        uint32_t sector_offset =
            offset
            %
            2048u;


        if (
            fm_disc_read_sector(
                dir_lba
                +
                sector_index,
                sector
            )
            !=
            0
        )
        {
            return 0;
        }


        uint8_t record_len =
            sector[
                sector_offset
            ];


        /*
         * Zero means padding until the next logical sector.
         */
        if (record_len == 0)
        {
            offset =
                (
                    sector_index
                    +
                    1u
                )
                *
                2048u;

            continue;
        }


        if (
            sector_offset
            +
            record_len
            >
            2048u
        )
        {
            return 0;
        }


        const uint8_t *record =
            &sector[
                sector_offset
            ];


        /*
         * Minimum ISO9660 directory-record size.
         */
        if (record_len < 34u)
        {
            return 0;
        }


        uint8_t name_len =
            record[32];


        if (
            33u
            +
            name_len
            >
            record_len
        )
        {
            return 0;
        }


        const uint8_t *iso_name =
            &record[33];


        /*
         * Skip "." and "..".
         */
        int special_entry =
            (
                name_len == 1u
                &&
                (
                    iso_name[0] == 0u
                    ||
                    iso_name[0] == 1u
                )
            );


        if (
            !special_entry
            &&
            iso_name_equal(
                iso_name,
                name_len,
                name
            )
        )
        {
            *out_lba =
                le32(
                    record + 2
                );


            *out_size =
                le32(
                    record + 10
                );


            *out_flags =
                record[25];


            return 1;
        }


        offset +=
            record_len;
    }


    return 0;
}


int fm_disc_find_file(
    const char *path,
    uint32_t *lba,
    uint32_t *size
)
{
    if (
        !disc
        ||
        !path
        ||
        !lba
        ||
        !size
    )
    {
        return 0;
    }


    uint8_t pvd[2048];


    if (
        fm_disc_read_sector(
            16,
            pvd
        )
        !=
        0
    )
    {
        return 0;
    }


    if (
        pvd[0] != 1
        ||
        memcmp(
            pvd + 1,
            "CD001",
            5
        )
        !=
        0
        ||
        pvd[6] != 1
    )
    {
        return 0;
    }


    /*
     * Root Directory Record starts at byte 156 of the PVD.
     */
    const uint8_t *root =
        pvd + 156;


    if (root[0] < 34u)
    {
        return 0;
    }


    uint32_t current_lba =
        le32(
            root + 2
        );


    uint32_t current_size =
        le32(
            root + 10
        );


    /*
     * Guest paths use backslashes, but accepting both slash forms
     * costs nothing and makes this helper more robust.
     */
    while (
        *path == '\\'
        ||
        *path == '/'
    )
    {
        ++path;
    }


    char component[128];


    while (*path)
    {
        unsigned length =
            0;


        while (
            *path
            &&
            *path != '\\'
            &&
            *path != '/'
        )
        {
            if (
                length
                <
                sizeof(component)
                -
                1u
            )
            {
                component[length++] =
                    *path;
            }


            ++path;
        }


        component[length] =
            '\0';


        while (
            *path == '\\'
            ||
            *path == '/'
        )
        {
            ++path;
        }


        if (length == 0)
        {
            continue;
        }


        uint32_t found_lba =
            0;

        uint32_t found_size =
            0;

        uint8_t found_flags =
            0;


        if (
            !iso_find_in_directory(
                current_lba,
                current_size,
                component,
                &found_lba,
                &found_size,
                &found_flags
            )
        )
        {
            return 0;
        }


        /*
         * If another path component follows, the matched record
         * must be a directory (ISO9660 flag bit 1).
         */
        if (*path)
        {
            if (
                (
                    found_flags
                    &
                    0x02u
                )
                ==
                0
            )
            {
                return 0;
            }


            current_lba =
                found_lba;


            current_size =
                found_size;
        }
        else
        {
            /*
             * Last component must be a file for DsSearchFile.
             */
            if (
                found_flags
                &
                0x02u
            )
            {
                return 0;
            }


            *lba =
                found_lba;


            *size =
                found_size;


            return 1;
        }
    }


    return 0;
}


/*
 * ============================================================
 * Initial PS-X EXE loader
 * ============================================================
 */

int fm_disc_load_exe(
    uint8_t *ram,
    uint32_t *entry
)
{
    uint8_t header[2048];
    uint8_t block[2048];


    if (
        fm_disc_read_sector(
            25,
            header
        )
        ||
        memcmp(
            header,
            "PS-X EXE",
            8
        )
    )
    {
        return -1;
    }


    uint32_t address =
        le32(
            header + 0x18
        );


    uint32_t size =
        le32(
            header + 0x1C
        );


    if (
        address != 0x80010000u
        ||
        size != 0x001D0000u
        ||
        le32(
            header + 0x10
        )
        !=
        0x800128CCu
    )
    {
        return -2;
    }


    memset(
        ram,
        0,
        2 * 1024 * 1024
    );


    for (
        uint32_t offset = 0;
        offset < size;
        offset += 2048u
    )
    {
        if (
            fm_disc_read_sector(
                26u
                +
                offset / 2048u,
                block
            )
        )
        {
            return -3;
        }


        memcpy(
            ram
            +
            0x10000u
            +
            offset,
            block,
            2048
        );
    }


    *entry =
        le32(
            header + 0x10
        );


    return 0;
}
