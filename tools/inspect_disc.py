#!/usr/bin/env python3
"""Inspect a single-track MODE2/2352 PS1 BIN; extract the boot EXE only.
XA/STR files are inventoried but never converted to 2048-byte sectors.
Usage: python inspect_disc.py disc.bin output_dir
"""
import argparse, hashlib, json, pathlib, struct

def main():
    ap=argparse.ArgumentParser(description=__doc__)
    ap.add_argument('disc',type=pathlib.Path);ap.add_argument('out',type=pathlib.Path)
    a=ap.parse_args();a.out.mkdir(parents=True,exist_ok=True)
    size=a.disc.stat().st_size
    if size%2352: raise ValueError('BIN must contain full 2352-byte sectors')
    with a.disc.open('rb') as f:
        def read(lba,n):
            result=bytearray()
            while len(result)<n:
                f.seek(lba*2352);s=f.read(2352)
                if len(s)!=2352 or s[:12]!=b'\0'+b'\xff'*10+b'\0' or s[15]!=2:
                    raise ValueError('Invalid MODE2 sector at LBA %d'%lba)
                if s[16:20]!=s[20:24] or s[18]&0x20:
                    raise ValueError('Expected XA Form 1 at LBA %d'%lba)
                result.extend(s[24:2072]);lba+=1
            return bytes(result[:n])
        pvd=read(16,2048)
        if pvd[:7]!=b'\x01CD001\x01':raise ValueError('Missing ISO9660 PVD')
        u32=lambda b,o:struct.unpack_from('<I',b,o)[0]
        entries=[];visited=set()
        def walk(lba,n,prefix=''):
            if lba in visited:raise ValueError('Directory cycle')
            visited.add(lba);d=read(lba,n);i=0
            while i<len(d):
                length=d[i]
                if not length:i=(i//2048+1)*2048;continue
                r=d[i:i+length];i+=length
                if len(r)<34:raise ValueError('Truncated directory record')
                name=r[33:33+r[32]]
                if name in (b'\0',b'\1'):continue
                name=name.decode('ascii');path=prefix+name
                if r[25]&2:walk(u32(r,2),u32(r,10),path+'/')
                else:entries.append(dict(path=path,lba=u32(r,2),iso_size=u32(r,10)))
        walk(u32(pvd,158),u32(pvd,166))
        cnf=next(e for e in entries if e['path']=='SYSTEM.CNF;1')
        system=read(cnf['lba'],cnf['iso_size']).decode('ascii')
        boot=next(x for x in system.splitlines() if x.startswith('BOOT')).split('\\')[-1].strip()
        e=next(e for e in entries if e['path']==boot)
        exe=read(e['lba'],e['iso_size'])
        if exe[:8]!=b'PS-X EXE':raise ValueError('Boot file is not a PS-X EXE')
        fields={k:u32(exe,o) for k,o in [('pc',0x10),('gp',0x14),('load_address',0x18),('payload_size',0x1c),('bss_address',0x28),('bss_size',0x2c),('stack_base',0x30),('stack_offset',0x34)]}
        if len(exe)<2048+fields['payload_size']:raise ValueError('Truncated EXE payload')
        if not fields['load_address']<=fields['pc']<fields['load_address']+fields['payload_size']:raise ValueError('Entry point outside payload')
        (a.out/boot.split(';')[0]).write_bytes(exe)
        payload=exe[2048:2048+fields['payload_size']]
        (a.out/'payload.bin').write_bytes(payload)
        (a.out/'SYSTEM.CNF').write_text(system)
    with a.disc.open('rb') as f: disc_hash=hashlib.file_digest(f,'sha256').hexdigest()
    report=dict(disc_bytes=size,disc_sectors=size//2352,disc_sha256=disc_hash,files=entries,boot=boot,exe_sha256=hashlib.sha256(exe).hexdigest(),header=fields)
    (a.out/'inventory.json').write_text(json.dumps(report,indent=2)+'\n')
    try:
        from capstone import Cs,CS_ARCH_MIPS,CS_MODE_MIPS32,CS_MODE_LITTLE_ENDIAN
        cs=Cs(CS_ARCH_MIPS,CS_MODE_MIPS32|CS_MODE_LITTLE_ENDIAN)
        offset=fields['pc']-fields['load_address']
        lines=['# Linear disassembly of 512 bytes at entry; not decompiled C.']
        for ins in cs.disasm(payload[offset:offset+512],fields['pc']):
            lines.append('%08x  %-12s %s %s'%(ins.address,ins.bytes.hex(),ins.mnemonic,ins.op_str))
        (a.out/'entry.asm').write_text('\n'.join(lines)+'\n')
    except ImportError: pass
    print(json.dumps(report,indent=2))
if __name__=='__main__':main()
