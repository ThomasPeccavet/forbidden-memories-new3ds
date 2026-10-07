/* B136.17: direct translation of the resident FR DecDCTvlc (800914A8).
 * Uses the game's expanded lookup tables, chunk size and continuation words.
 * Decode into a temporary buffer: invalid addresses/tables leave guest state
 * untouched, allowing the native path to run. No frame skipping or clock edit. */
#include "fm_vlc.h"
#include "fm_memory.h"
#include <3ds.h>
#include <stdlib.h>
#include <string.h>
static uint32_t calls, failures;
static uint32_t last_table, last_limit;
static uint64_t elapsed_ms;
static uint16_t rd16(const uint8_t *p) { return p[0] | (uint16_t)p[1] << 8; }
static uint32_t rd32(const uint8_t *p) { return rd16(p) | (uint32_t)rd16(p + 2) << 16; }
static uint32_t shl(uint32_t v, uint32_t n) { return v << (n & 31u); }
static uint32_t shr(uint32_t v, uint32_t n) { return v >> (n & 31u); }
void fm_vlc_reset(void) { calls = failures = last_table = last_limit = 0; elapsed_ms = 0; }
void fm_vlc_dump(FILE *f)
{ fprintf(f, "vlc_hle=calls:%lu fallback:%lu ms:%llu table:%08lX limit:%08lX\n", (unsigned long)calls,
    (unsigned long)failures, (unsigned long long)elapsed_ms,
    (unsigned long)last_table, (unsigned long)last_limit); }
int fm_vlc_try(CPUState *cpu)
{
    if (!cpu) return 0;
    uint64_t started = osGetTime();
    uint32_t input = cpu->gpr[4], output = cpu->gpr[5], table = cpu->gpr[6];
    const uint8_t *lut = fm_memory_ram_span(table, 0x11000u);
    uint32_t limit = fm_memory_read_word(0x8009B458u);
    last_table = table; last_limit = limit;
    uint32_t bits, fraction, src, p, end, qscale, block, cr, cb, y, chunk_end, base;
    uint8_t *buffer = NULL;
    uint32_t size, ret = 0;
    if (!lut || (table & 1u)) goto fail;
    if (input) {
        const uint8_t *header = fm_memory_ram_span(input, 12u);
        if (!header || (input & 1u) || (output & 3u)) goto fail;
        uint32_t command = rd32(header);
        size = ((command & 0xFFFFu) + 1u) * 4u;
        if (size < 8u || !fm_memory_ram_span(output, size)) goto fail;
        base = output; end = base + size; p = base + 2u;
        bits = rd32(header + 8u); bits = bits << 16 | bits >> 16;
        fraction = cr = cb = y = 0;
        qscale = rd16(header + 4u) << 10;
        block = rd16(header + 6u) >= 3u ? 1u : 0u;
        src = input + 12u;
        chunk_end = output + limit * 2u;
    } else {
        p = fm_memory_read_word(0x8009B460u) - 4u;
        base = p; end = fm_memory_read_word(0x8009B480u);
        if (end <= base || end - base > 0x40000u || !fm_memory_ram_span(base, end - base)) goto fail;
        size = end - base;
        src = fm_memory_read_word(0x8009B45Cu);
        bits = fm_memory_read_word(0x8009B464u);
        fraction = fm_memory_read_word(0x8009B468u);
        qscale = fm_memory_read_word(0x8009B46Cu);
        block = fm_memory_read_word(0x8009B470u);
        cr = fm_memory_read_word(0x8009B474u);
        cb = fm_memory_read_word(0x8009B478u);
        y = fm_memory_read_word(0x8009B47Cu);
        chunk_end = p + 4u + limit * 2u;
        if (fraction > 15u || block > 6u || (p & 1u) || (src & 1u)) goto fail;
    }
    if (limit > 0x20000u || size > 0x40000u || chunk_end < base) goto fail;
    const uint8_t *destination = fm_memory_ram_span(base, size);
    if (destination < lut + 0x11000u && lut < destination + size) goto fail;
    const uint8_t *controls = fm_memory_ram_span(0x8009B458u, 44u);
    if (controls && destination < controls + 44u && controls < destination + size) goto fail;
    uint32_t source_start = input ? input : src;
    buffer = malloc(size);
    if (!buffer) goto fail;
    memcpy(buffer, fm_memory_ram_span(base, size), size);
#define PUT(at, v) do { uint32_t a_ = (at); if (a_ < base || a_ > end - 2u) goto fail; \
    uint16_t v_ = (v); buffer[a_ - base] = v_; buffer[a_ - base + 1u] = v_ >> 8; } while (0)
#define REFILL(n) do { uint32_t f_ = fraction + (n); fraction = f_ & 15u; \
    if (f_ & 16u) { const uint8_t *r_ = fm_memory_ram_span(src, 2u); \
        if (!r_) goto fail; bits |= (uint32_t)rd16(r_) << fraction; src += 2u; } } while (0)
    unsigned watchdog = 0;
    if (input) {
        uint32_t command = fm_memory_read_word(input);
        PUT(base, command); PUT(base + 2u, command >> 16);
        goto dc;
    }
    p += 4u;
    for (; watchdog < 0x40000u; ++watchdog) {
        uint32_t offset = 0x800u + (bits >> 19) * 8u;
        uint32_t code = rd32(lut + offset), extra = 0;
        if (!code) {
            bits <<= 8; REFILL(8u);
            code = rd32(lut + 0x10800u + (bits >> 23) * 4u);
        } else extra = rd32(lut + offset + 4u);
        if (!(code & 0xFFu) || (code & 0xFFu) > 16u) goto fail;
        bits = shl(bits, code); REFILL(code & 0xFFu);
        uint32_t token = code >> 16;
        for (unsigned lane = 0; lane < 3u; ++lane) {
            if (token == 0x7C1Fu) {
                PUT(p, bits >> 16); bits <<= 16; REFILL(16u); p += 2u;
                break; /* Escape terminates this table entry. */
            }
            PUT(p, token);
            if (token == 0xFE00u) goto dc;
            p += 2u;
            if (!lane) token = extra & 0xFFFFu;
            else if (lane == 1u) token = extra >> 16;
            else break;
            if (!token) break;
        }
        continue;
dc:
        if (bits >> 22 == (block ? 0x3FFu : 0x1FFu)) {
            while ((p += 2u) < end) PUT(p, 0xFE00u);
            ret = 0; goto commit;
        }
        if (!block) {
            uint32_t dc_value = bits >> 22;
            bits <<= 10; REFILL(10u);
            PUT(p + 2u, qscale | dc_value);
        } else {
            uint32_t offset = (block >= 3u ? 0u : 0x400u) + (bits >> 24) * 4u;
            uint32_t n = rd16(lut + offset), width = rd16(lut + offset + 2u), delta = 0;
            if (!n || n > 16u || width > 16u || n + width > 16u) goto fail;
            bits = shl(bits, n);
            if (width) {
                delta = shr(bits, 32u - width);
                if (!(bits & 0x80000000u)) delta -= shr(UINT32_MAX, 32u - width);
                bits = shl(bits, width); fraction += width;
            }
            REFILL(n);
            uint32_t dc_value;
            if (block == 1u) dc_value = cr += delta;
            else if (block == 2u) dc_value = cb += delta;
            else dc_value = y += delta;
            PUT(p + 2u, qscale | ((dc_value & 0xFFu) << 2));
            block = block == 6u ? 1u : block + 1u;
        }
        p += 4u;
        if (p - 2u >= chunk_end) { ret = 1; goto commit; }
    }
    goto fail;
commit:
    /* Native output writes must not affect bytes this HLE read speculatively. */
    if (src < source_start) goto fail;
    const uint8_t *compressed = fm_memory_ram_span(source_start, src - source_start);
    if (!compressed || (destination < compressed + (src - source_start)
        && compressed < destination + size)) goto fail;
    fm_memory_copy_to_ram(base, buffer, size);
    if (input) fm_memory_write_word(0x8009B480u, end);
    if (ret) {
        fm_memory_write_word(0x8009B45Cu, src); fm_memory_write_word(0x8009B460u, p);
        fm_memory_write_word(0x8009B464u, bits); fm_memory_write_word(0x8009B468u, fraction);
        fm_memory_write_word(0x8009B46Cu, qscale); fm_memory_write_word(0x8009B470u, block);
        fm_memory_write_word(0x8009B474u, cr); fm_memory_write_word(0x8009B478u, cb);
        fm_memory_write_word(0x8009B47Cu, y);
    }
    free(buffer); cpu->gpr[2] = ret; cpu->gpr[0] = 0; cpu->pc = cpu->gpr[31];
    ++calls; elapsed_ms += osGetTime() - started;
    return 1;
fail:
    free(buffer); ++failures; return 0;
#undef PUT
#undef REFILL
}
