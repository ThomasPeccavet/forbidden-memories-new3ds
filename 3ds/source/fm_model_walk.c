#include "fm_model_walk.h"
#include "fm_native_memory.h"

/* B136.64: whole resident group/table traversal, with explicit guest callback
 * boundaries. No host continuation survives a call: the guest stack and
 * s0..s4 are the complete continuation, including across snapshot restores.
 * Work is bounded even for cyclic lists or oversized parameter tables.
 * Primitive callbacks retain the existing renderer/GTE implementation. */
int fm_model_walk_try(CPUState *c, uint32_t address)
{
    uint32_t p=address & 0x1fffffffu;
    if (!c || (p!=0x8a0d8u && p!=0x8a134u && p!=0x8a1c0u)) return 0;
#ifdef PSX_ENABLE_BLOCK_CYCLES
    return 0; /* The cycle-accounted core keeps its instruction interlocks. */
#endif
    /* Verify the resident ABI every time; no stale guard after a quick-load. */
    if (fm_native_read_word(c,0x8008a0d8u)!=0x27bdffd8u
        || fm_native_read_word(c,0x8008a0f8u)!=0x00c08821u
        || fm_native_read_word(c,0x8008a1b8u)!=0x0040f809u
        || fm_native_read_word(c,0x8008a1c0u)!=0x3c038010u
        || fm_native_read_word(c,0x8008a200u)!=0x27bd0028u) return 0;
#define R(n) c->gpr[n]
#define LD(a) fm_native_read_word(c,(a))
#define ST(a,v) fm_native_write_word(c,(a),(v))
    unsigned groups=0, copies=0;
    if (p==0x8a1c0u) goto callback_return;
    if (p==0x8a134u) goto group;

    R(29)-=40u;
    ST(R(29)+36,R(31)); ST(R(29)+32,R(20)); ST(R(29)+28,R(19));
    ST(R(29)+24,R(18)); ST(R(29)+20,R(17)); ST(R(29)+16,R(16));
    R(2)=LD(R(4)+4); R(17)=R(6); ST(R(17),R(2));
    R(19)=LD(R(4)+4); ST(R(17)+4,R(5)); R(3)=LD(R(5));
    R(2)=14u-R(3); ST(R(17)+8,R(2)); R(3)=LD(R(5)+8);
    R(2)=LD(0x800ff5c4u); R(20)=0xffffffffu;
    ST(R(17)+16,R(2)); ST(R(17)+12,R(3)); R(2)=R(19);
group:
    ST(R(17),R(19)); R(19)=LD(R(19)); R(3)=R(2)+4;
    ST(R(17),R(3)); R(5)=LD(R(2)+4); R(2)=LD(R(5)); R(16)=0;
    if (R(2)) {
        R(4)=R(17)+20; R(3)=R(5);
        do {
            /* Preserve overlapping source/destination semantics: the table
             * length is re-read after each write, exactly as in the guest. */
            R(2)=LD(R(3)+4); R(3)+=4; ++R(16); ST(R(4),R(2));
            R(2)=LD(R(5)); R(2)=R(16)<R(2); R(4)+=4;
            if (++copies>=128u && R(2)) {
                c->pc=0x8008a164u; return 1;
            }
        } while (R(2));
    }
    R(3)=LD(R(17)); R(16)=0; R(2)=R(3)+4; ST(R(17),R(2));
    R(18)=LD(R(3)+4); R(3)+=8; ST(R(17),R(3));
    if (!R(18)) goto group_end;
callback:
    R(3)=LD(R(17)); R(4)=R(17); R(2)=LD(R(3)); R(3)+=4;
    R(31)=0x8008a1c0u; ST(R(17),R(3));
    c->pc=R(2); return 1;
callback_return:
    R(3)=LD(0x800ff5c4u); ++R(16); ST(R(17),R(2));
    R(2)=R(16)<R(18); ST(R(17)+16,R(3));
    if (R(2)) goto callback;
group_end:
    R(2)=R(19);
    if (R(19)!=R(20)) {
        if (++groups==8u) {c->pc=0x8008a134u; return 1;}
        goto group;
    }
    R(31)=LD(R(29)+36); R(20)=LD(R(29)+32); R(19)=LD(R(29)+28);
    R(18)=LD(R(29)+24); R(17)=LD(R(29)+20); R(16)=LD(R(29)+16);
    c->pc=R(31); R(29)+=40u;
    return 1;
#undef R
#undef LD
#undef ST
}
