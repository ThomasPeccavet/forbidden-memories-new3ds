#include "fm_snapshot.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

typedef struct {
    uint32_t magic, version, header_bytes, payload_bytes, schema, build;
    uint64_t disc;
    uint32_t crc, reserved;
} Envelope;
uint32_t fm_snapshot_crc(const void *data, size_t bytes)
{
    const uint8_t *p=data;
    uint32_t crc=0xFFFFFFFFu;
    /* Four-bit lookup: bounded linear pass, no per-byte 8-bit loop on ARM. */
    static const uint32_t t[16]={0,0x1DB71064,0x3B6E20C8,0x26D930AC,
        0x76DC4190,0x6B6B51F4,0x4DB26158,0x5005713C,0xEDB88320,
        0xF00F9344,0xD6D6A3E8,0xCB61B38C,0x9B64C2B0,0x86D3D2D4,
        0xA00AE278,0xBDBDF21C};
    while (bytes--) { crc^=*p++; crc=(crc>>4)^t[crc&15]; crc=(crc>>4)^t[crc&15]; }
    return ~crc;
}
int fm_snapshot_write(const char *path,const void *payload,uint32_t bytes,
    uint32_t schema,uint64_t disc,uint32_t build)
{
    char temp[512], backup[512];
    if (!path || !payload || !disc || bytes>FM_SNAPSHOT_MAX
        || snprintf(temp,sizeof(temp),"%s.tmp",path)>=(int)sizeof(temp)
        || snprintf(backup,sizeof(backup),"%s.bak",path)>=(int)sizeof(backup)) return -1;
    Envelope h={0}; h.magic=FM_SNAPSHOT_MAGIC; h.version=FM_SNAPSHOT_VERSION;
    h.header_bytes=sizeof(h); h.payload_bytes=bytes; h.schema=schema; h.build=build;
    h.disc=disc; h.crc=fm_snapshot_crc(payload,bytes);
    FILE *f=fopen(temp,"wb"); if (!f) return -2;
    int ok=fwrite(&h,sizeof(h),1,f)==1 && fwrite(payload,bytes,1,f)==1;
    if (fflush(f)) ok=0;
    if (fclose(f)) ok=0;
    if (!ok) { remove(temp); return -3; }
    /* Keep the previous valid file until the replacement is complete. FAT
     * does not guarantee POSIX rename-overwrite; use recoverable rotation. */
    FILE *old=fopen(path,"rb");
    int had_old=old!=NULL; if (old) fclose(old);
    if (had_old) {
        if (remove(backup) && errno!=ENOENT) { remove(temp); return -4; }
        if (rename(path,backup)) { remove(temp); return -4; }
    }
    if (rename(temp,path)) {
        if (had_old) (void)rename(backup,path);
        remove(temp); return -4;
    }
    return 0;
}
static int read_one(const char *path,void **payload,uint32_t *bytes,
    uint32_t schema,uint64_t disc,int *legacy)
{
    FILE *f=fopen(path,"rb"); if (!f) return -2;
    if (fseek(f,0,SEEK_END)) { fclose(f); return -3; }
    long len=ftell(f);
    if (len<8 || len>(long)(FM_SNAPSHOT_MAX+sizeof(Envelope)) || fseek(f,0,SEEK_SET)) {
        fclose(f); return -3;
    }
    uint32_t magic;
    if (fread(&magic,sizeof(magic),1,f)!=1 || fseek(f,0,SEEK_SET)) { fclose(f); return -3; }
    Envelope h={0}; int old=magic==0x35333142u;
    uint32_t n=(uint32_t)len;
    if (!old) {
        if (fread(&h,sizeof(h),1,f)!=1 || h.magic!=FM_SNAPSHOT_MAGIC
            || h.version!=FM_SNAPSHOT_VERSION || h.header_bytes!=sizeof(h)
            || h.schema!=schema || !disc || h.disc!=disc
            || h.payload_bytes>FM_SNAPSHOT_MAX || len!=(long)(sizeof(h)+h.payload_bytes)) {
            fclose(f); return -4;
        }
        n=h.payload_bytes;
    }
    void *p=malloc(n); if (!p) { fclose(f); return -6; }
    int ok=fread(p,n,1,f)==1; if (fclose(f)) ok=0;
    if (!ok || (!old && fm_snapshot_crc(p,n)!=h.crc)) { free(p); return -5; }
    *payload=p; *bytes=n; *legacy=old; return 0;
}
int fm_snapshot_read(const char *path,void **payload,uint32_t *bytes,
    uint32_t schema,uint64_t disc,int *legacy)
{
    if (!path || !payload || !bytes || !legacy) return -1;
    *payload=NULL; *bytes=0; *legacy=0;
    int rc=read_one(path,payload,bytes,schema,disc,legacy);
    /* Only recover a interrupted rotation when the primary is absent.
     * Corrupt primary files are explicitly rejected, never silently replaced. */
    if (rc==-2) {
        char backup[512];
        if (snprintf(backup,sizeof(backup),"%s.bak",path)>=(int)sizeof(backup)) return -1;
        rc=read_one(backup,payload,bytes,schema,disc,legacy);
    }
    return rc;
}
