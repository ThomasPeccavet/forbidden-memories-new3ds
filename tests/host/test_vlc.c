#include "fm_vlc.h"
#include "fm_memory.h"
#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
typedef uint32_t uint, undefined4;
typedef uint16_t ushort, undefined2;
#define CONCAT22(a,b) ((uint)(ushort)(a) << 16 | (ushort)(b))
static uint32_t DAT_8009b458, DAT_8009b464, DAT_8009b468, DAT_8009b46c, DAT_8009b470;
static uint32_t DAT_8009b474, DAT_8009b478, DAT_8009b47c;
static uint *DAT_8009b45c, *DAT_8009b480;
static ushort *DAT_8009b460;
/* NATIVE_REFERENCE */
static uint8_t ram[2 * 1024 * 1024];
static uint32_t native_input[512], native_output[512], native_table[0x11000 / 4];
const uint8_t *fm_memory_ram_span(uint32_t a, size_t n)
{ unsigned off = a & 0x1FFFFFFF; return off <= sizeof(ram) && n <= sizeof(ram) - off ? ram + off : NULL; }
int fm_memory_copy_to_ram(uint32_t a, const void *p, size_t n)
{ const uint8_t *dest = fm_memory_ram_span(a, n); if (!dest) return 0; memcpy((void *)dest, p, n); return 1; }
uint32_t fm_memory_read_word(uint32_t a) { uint32_t v; const uint8_t *p = fm_memory_ram_span(a, 4); assert(p); memcpy(&v, p, 4); return v; }
void fm_memory_write_word(uint32_t a, uint32_t v) { assert(fm_memory_copy_to_ram(a, &v, 4)); }
#define IN 0x80010000u
#define OUT 0x80020000u
#define TABLE 0x80030000u
static unsigned bitpos, expected_halfwords;
static void put_bits(unsigned bits, unsigned n)
{
    for (unsigned i = n; i > 0; --i) {
        unsigned half = bitpos / 16, shift = 15 - bitpos % 16;
        uint16_t *stream = (uint16_t *)((uint8_t *)native_input + 8);
        stream[half] |= ((bits >> (i - 1)) & 1u) << shift;
        ++bitpos;
    }
}
static void tables(void)
{
    memset(native_table, 0, sizeof(native_table));
    for (unsigned i = 0; i < 512; ++i) native_table[i] = 0x00020001; /* DC prefix=1, magnitude=2. */
    for (unsigned i = 0; i < 8192; ++i) {
        unsigned prefix = i >> 10, off = 0x800 / 4 + i * 2;
        if (prefix >= 4 && prefix <= 5) native_table[off] = 0xFE000002;
        else if (prefix >= 2 && prefix <= 3) native_table[off] = 0x04010002;
        else if (prefix == 6) native_table[off] = 0x7C1F0003;
        else if (prefix == 7) { native_table[off] = 0x04010003; native_table[off + 1] = 0xFE000702; }
    }
    for (unsigned i = 0; i < 512; ++i) native_table[0x10800 / 4 + i] = 0xFE000002;
}
static void fixture(unsigned version, unsigned variant, unsigned blocks)
{
    memset(native_input, 0, sizeof(native_input)); bitpos = expected_halfwords = 0;
    native_input[1] = version << 16 | (1 + variant % 63);
    for (unsigned b = 0; b < blocks; ++b) {
        if (version < 3) put_bits((b * 37 + variant * 9) & 0x3FE, 10);
        else { put_bits(0, 1); put_bits((b + variant) % 3 + 1, 2); }
        ++expected_halfwords;
        switch ((b + variant) % 5) {
            case 0: put_bits(2, 2); ++expected_halfwords; break;
            case 1: put_bits(1, 2); put_bits(2, 2); expected_halfwords += 2; break;
            case 2: put_bits(6, 3); put_bits(0xA2F3, 16); put_bits(2, 2); expected_halfwords += 2; break;
            case 3: put_bits(7, 3); expected_halfwords += 3; break;
            case 4: put_bits(0, 8); put_bits(2, 2); ++expected_halfwords; break;
        }
    }
    put_bits(version < 3 ? 0x1FF : 0x3FF, 10);
    native_input[0] = 0x30000000 | ((expected_halfwords + 1) / 2);
}
static void compare(unsigned version, unsigned variant, unsigned chunk)
{
    fixture(version, variant, 6 + variant % 20);
    memset(native_output, 0x55, sizeof(native_output));
    memcpy(ram + (IN & 0x1FFFFFFF), native_input, sizeof(native_input));
    memcpy(ram + (OUT & 0x1FFFFFFF), native_output, sizeof(native_output));
    memcpy(ram + (TABLE & 0x1FFFFFFF), native_table, sizeof(native_table));
    DAT_8009b458 = chunk; fm_memory_write_word(0x8009B458, chunk);
    CPUState cpu = {0}; cpu.gpr[4] = IN; cpu.gpr[5] = OUT; cpu.gpr[6] = TABLE; cpu.gpr[31] = 0x8006A650;
    unsigned ret, pass = 0;
    do {
        assert(++pass < 100);
        ret = native_vlc(pass == 1 ? native_input : NULL, native_output, (intptr_t)native_table);
        assert(fm_vlc_try(&cpu));
        assert(cpu.gpr[2] == ret && cpu.pc == cpu.gpr[31]);
        if (memcmp(ram + (OUT & 0x1FFFFFFF), native_output, sizeof(native_output))) {
            for (unsigned j = 0; j < sizeof(native_output) / 2; ++j) {
                uint16_t actual; memcpy(&actual, ram + (OUT & 0x1FFFFFFF) + j * 2, 2);
                if (actual != ((uint16_t *)native_output)[j]) {
                    fprintf(stderr, "v=%u variant=%u chunk=%u pass=%u ret=%u half=%u got=%04X ref=%04X\n",
                        version, variant, chunk, pass, ret, j, actual, ((uint16_t *)native_output)[j]); break;
                }
            }
            assert(0);
        }
        assert(fm_memory_read_word(0x8009B480) == OUT + ((uint8_t *)DAT_8009b480 - (uint8_t *)native_output));
        if (ret) {
            assert(fm_memory_read_word(0x8009B45C) == IN + ((uint8_t *)DAT_8009b45c - (uint8_t *)native_input));
            assert(fm_memory_read_word(0x8009B460) == OUT + ((uint8_t *)DAT_8009b460 - (uint8_t *)native_output));
            const uint32_t saved[] = {DAT_8009b464,DAT_8009b468,DAT_8009b46c,DAT_8009b470,DAT_8009b474,DAT_8009b478,DAT_8009b47c};
            for (unsigned i = 0; i < 7; ++i) assert(fm_memory_read_word(0x8009B464 + i * 4) == saved[i]);
        }
        cpu.gpr[4] = 0;
    } while (ret);
}
int main(void)
{
    tables();
    for (unsigned v = 1; v <= 3; ++v) for (unsigned n = 0; n < 35; ++n) {
        compare(v, n, 0x00FFFFFF); compare(v, n, 0x10000); compare(v, n, 0); compare(v, n, 4); compare(v, n, 9);
    }
    uint8_t snapshot[sizeof(ram)]; memcpy(snapshot, ram, sizeof(ram));
    CPUState cpu = {0}; cpu.gpr[4] = IN; cpu.gpr[5] = 0x801FFFFC; cpu.gpr[6] = TABLE;
    CPUState before = cpu; assert(!fm_vlc_try(&cpu));
    assert(!memcmp(&cpu, &before, sizeof(cpu)) && !memcmp(snapshot, ram, sizeof(ram)));
    cpu.gpr[5] = OUT; cpu.gpr[6] = 0x1F801820;
    before = cpu; assert(!fm_vlc_try(&cpu));
    assert(!memcmp(&cpu, &before, sizeof(cpu)) && !memcmp(snapshot, ram, sizeof(ram)));
    /* Failure after the temporary header was written must also be atomic. */
    fixture(3, 0, 6); memcpy(ram + (IN & 0x1FFFFFFF), native_input, sizeof(native_input));
    memset(ram + (TABLE & 0x1FFFFFFF), 0, sizeof(native_table));
    memcpy(snapshot, ram, sizeof(ram)); cpu.gpr[6] = TABLE; before = cpu;
    assert(!fm_vlc_try(&cpu));
    assert(!memcmp(&cpu, &before, sizeof(cpu)) && !memcmp(snapshot, ram, sizeof(ram)));
    tables(); memcpy(ram + (TABLE & 0x1FFFFFFF), native_table, sizeof(native_table));
    fm_memory_write_word(0x8009B458, UINT32_MAX); memcpy(snapshot, ram, sizeof(ram));
    before = cpu; assert(!fm_vlc_try(&cpu));
    assert(!memcmp(&cpu, &before, sizeof(cpu)) && !memcmp(snapshot, ram, sizeof(ram)));
    return 0;
}
