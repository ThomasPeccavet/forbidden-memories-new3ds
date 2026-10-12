#ifndef FM_GEOMETRY_CACHE_H
#define FM_GEOMETRY_CACHE_H
#include "cpu_state.h"
#include <stdint.h>
#include <string.h>

/* Exact, host-only memoization of one vertex projection. The original GTE
 * arithmetic remains the miss path. No guest pointer or mutable RAM input
 * participates: all dependencies are the vertex, sf/lm and these controls. */
#define FM_GEOMETRY_CACHE_SLOTS 128u
#ifndef FM_GEOMETRY_CACHE
#define FM_GEOMETRY_CACHE 1
#endif

typedef struct FMGeometryProjection {
    uint32_t generation;
    int32_t vertex[3];
    uint32_t mac[3], ir[3], sz, sxy, mac0, ir0, flags;
    unsigned depth;
} FMGeometryProjection;

typedef struct FMGeometryCache {
    uint32_t controls[13], mode, generation;
    FMGeometryProjection slots[FM_GEOMETRY_CACHE_SLOTS];
    uint64_t hits, misses, contexts;
} FMGeometryCache;

static inline void fm_geometry_cache_prepare(FMGeometryCache *cache,
                                             const CPUState *cpu, uint32_t cmd)
{
    uint32_t mode=cmd & ((1u<<19)|(1u<<10));
    if (!cache->generation || cache->mode!=mode
        || memcmp(cache->controls,cpu->gte_ctrl,8u*sizeof(uint32_t))
        || memcmp(cache->controls+8,cpu->gte_ctrl+24,5u*sizeof(uint32_t))) {
        memcpy(cache->controls,cpu->gte_ctrl,8u*sizeof(uint32_t));
        memcpy(cache->controls+8,cpu->gte_ctrl+24,5u*sizeof(uint32_t));
        cache->mode=mode;
        if (++cache->generation==0u) {
            memset(cache->slots,0,sizeof cache->slots);
            cache->generation=1u;
        }
        ++cache->contexts;
    }
}

static inline FMGeometryProjection *fm_geometry_cache_slot(
    FMGeometryCache *cache,const int32_t vertex[3],unsigned depth)
{
    uint32_t hash=(uint32_t)vertex[0]*0x9e3779b1u
        ^ (uint32_t)vertex[1]*0x85ebca6bu
        ^ (uint32_t)vertex[2]*0xc2b2ae35u ^ depth*0x27d4eb2du;
    return &cache->slots[(hash ^ (hash>>16)) & (FM_GEOMETRY_CACHE_SLOTS-1u)];
}

static inline int fm_geometry_cache_apply(FMGeometryCache *cache,
    FMGeometryProjection *entry,CPUState *cpu,const int32_t vertex[3],
    unsigned depth,uint32_t *flags)
{
    if (entry->generation!=cache->generation || entry->depth!=depth
        || entry->vertex[0]!=vertex[0] || entry->vertex[1]!=vertex[1]
        || entry->vertex[2]!=vertex[2]) {
        ++cache->misses;
        return 0;
    }
    /* Replaying the projection result must still advance both hardware
     * FIFOs from their CURRENT contents, not those present at cache fill. */
    cpu->gte_data[16]=cpu->gte_data[17] & 0xffffu;
    cpu->gte_data[17]=cpu->gte_data[18] & 0xffffu;
    cpu->gte_data[18]=cpu->gte_data[19] & 0xffffu;
    cpu->gte_data[19]=entry->sz;
    cpu->gte_data[12]=cpu->gte_data[13];
    cpu->gte_data[13]=cpu->gte_data[14];
    cpu->gte_data[14]=entry->sxy;
    cpu->gte_data[15]=entry->sxy;
    for(unsigned i=0;i<3;++i) {
        cpu->gte_data[25+i]=entry->mac[i];
        cpu->gte_data[9+i]=entry->ir[i];
    }
    if(depth) {
        cpu->gte_data[24]=entry->mac0;
        cpu->gte_data[8]=entry->ir0;
    }
    *flags |= entry->flags;
    ++cache->hits;
    return 1;
}

static inline void fm_geometry_cache_store(FMGeometryCache *cache,
    FMGeometryProjection *entry,const CPUState *cpu,const int32_t vertex[3],
    unsigned depth,uint32_t flags)
{
    entry->generation=cache->generation;
    entry->depth=depth;
    memcpy(entry->vertex,vertex,sizeof entry->vertex);
    for(unsigned i=0;i<3;++i) {
        entry->mac[i]=cpu->gte_data[25+i];
        entry->ir[i]=cpu->gte_data[9+i];
    }
    entry->sz=cpu->gte_data[19];entry->sxy=cpu->gte_data[14];
    entry->mac0=cpu->gte_data[24];entry->ir0=cpu->gte_data[8];
    entry->flags=flags;
}
#endif
