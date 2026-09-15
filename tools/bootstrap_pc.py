#!/usr/bin/env python3
"""Build the pinned MIPS-to-C tool and exercise it. Does not boot the game.
Python 3.11+, Git, CMake 3.20+, C/C++20 compiler. Windows: Developer Command Prompt.
Without --exe, generates an original synthetic PS-X EXE returning 42.
"""
import argparse
import datetime
import hashlib
import json
import shutil
import struct
import subprocess
import uuid
from pathlib import Path

PIN = '1965b2df424da03483a5370340433a862f78f103'
URL = 'https://github.com/Unchiga/psxrecomp.git'
EXE_SHA = '57ecdfb9a9e1faf8b342fe7c7304c23723810861f3ab2fa3bef9eb27b5146b44'
ROOT = Path(__file__).resolve().parents[1]
SEEDS = [0x800128cc, 0x80012a44, 0x8002cfdc, 0x8002d354, 0x8002d038,
         0x8002d0bc, 0x8002d2b4, 0x8002d4ac, 0x8002d5cc, 0x8002d544,
         0x8002d75c, 0x8002d800, 0x8002d858, 0x8002d89c, 0x8002d8f4,
         0x8002d988, 0x8002d990, 0x8002dbe0, 0x8002de14]

def main():
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument('--framework', type=Path, default=ROOT/'work/psxrecomp')
    p.add_argument('--build-dir', type=Path)
    p.add_argument('--cmake', default='cmake')
    p.add_argument('--generator', help='Optional CMake generator, e.g. Ninja')
    p.add_argument('--jobs', type=int, default=4)
    p.add_argument('--exe', type=Path, help='Original extracted SLES_039.48 (not payload.bin)')
    a = p.parse_args()
    if not shutil.which('git') or not shutil.which(a.cmake):
        p.error('Git and CMake must be available; use a compiler Developer Command Prompt on Windows')
    if a.jobs < 1: p.error('--jobs must be positive')
    source = a.framework.resolve()
    build = a.build_dir.resolve() if a.build_dir else source/'recompiler/build-pc'
    if a.exe:
        exe = a.exe.resolve()
        if not exe.is_file() or hashlib.sha256(exe.read_bytes()).hexdigest() != EXE_SHA:
            p.error('Expected the verified French SLES_039.48 EXE, with its 2048-byte header')
    stamp = datetime.datetime.now(datetime.timezone.utc).strftime('%Y%m%dT%H%M%SZ')+'-'+uuid.uuid4().hex[:8]
    run = ROOT/'work/pc-bootstrap'/stamp
    evidence = ROOT/'research/pc-bootstrap'/stamp
    run.mkdir(parents=True); evidence.mkdir(parents=True)
    result = {'framework_commit':PIN, 'mode':'french-main-exe' if a.exe else 'synthetic-smoke',
              'steps':[], 'status':'running', 'game_booted':False}
    def save():
        (evidence/'result.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf-8')
    def command(label, args, cwd=None):
        print(label, flush=True)
        log = evidence/(label+'.log')
        with log.open('w',encoding='utf-8') as f:
            proc = subprocess.run([str(x) for x in args],cwd=cwd,stdout=f,stderr=subprocess.STDOUT)
        result['steps'].append({'step':label,'exit_code':proc.returncode,'log':log.name})
        save()
        if proc.returncode: raise RuntimeError(label+' failed; see '+str(log))
    try:
        if not source.exists():
            source.mkdir(parents=True)
            command('git-init',['git','init',source])
            command('git-remote',['git','remote','add','origin',URL],source)
            command('git-fetch',['git','fetch','--depth','1','origin',PIN],source)
            command('git-checkout',['git','checkout','--detach',PIN],source)
        head = subprocess.check_output(['git','rev-parse','HEAD'],cwd=source,text=True).strip()
        dirty = subprocess.check_output(['git','status','--porcelain','--untracked-files=no'],cwd=source,text=True)
        if head != PIN or dirty: raise RuntimeError('Existing framework must be clean at '+PIN+'; nothing was reset')
        args = [a.cmake,'-S',source/'recompiler','-B',build,'-DCMAKE_BUILD_TYPE=Release',
                '-DPSXRECOMP_ENABLE_CHD=OFF','-DBUILD_TESTING=OFF','-DCMAKE_POLICY_VERSION_MINIMUM=3.5']
        if a.generator: args += ['-G',a.generator]
        command('configure',args)
        command('build',[a.cmake,'--build',build,'--config','Release','--target',
                         'psxrecomp-game','psxrecomp-toml','--parallel',a.jobs])
        candidates = [build/'psxrecomp-game',build/'psxrecomp-game.exe',build/'Release/psxrecomp-game.exe']
        tool = next((x for x in candidates if x.is_file()),None)
        if tool is None: raise RuntimeError('Built emitter not found')
        command('emitter-version',[tool,'--codegen-hash'])
        if a.exe:
            seeds=SEEDS
        else:
            exe=run/'SMOKE.EXE'; h=bytearray(2048);h[:8]=b'PS-X EXE'
            for o,v in [(16,0x80010000),(24,0x80010000),(28,2048),(48,0x801ffff0)]:struct.pack_into('<I',h,o,v)
            b=bytearray(2048);struct.pack_into('<III',b,0,0x2402002a,0x03e00008,0)
            exe.write_bytes(h+b);seeds=[0x80010000]
        data=exe.read_bytes()
        read=lambda offset:struct.unpack_from('<I',data,offset)[0]
        seedfile=run/'seeds.txt';seedfile.write_text(''.join('0x%08X\n'%s for s in seeds))
        generated=run/'generated'
        # Absolute forward-slash paths avoid upstream project-root inference and TOML backslash escapes.
        q=lambda path:json.dumps(Path(path).as_posix(),ensure_ascii=False)
        config=run/'game.toml'
        config.write_text('[game]\nname="FM French experiment"\nid="'+('SLES-03948' if a.exe else 'SMOKE')+'"\nexe='+q(exe)+'\n'+
            ''.join(k+'="0x%08X"\n'%read(o) for k,o in [('load_address',24),('entry_pc',16),('text_size',28),('stack_base',48)])+
            '[recompiler]\nseeds='+q(seedfile)+'\nout_dir='+q(generated)+'\nstrict=true\ndiscovery="reachable"\nbios_config='+q(source/'bios/OpenBIOS.toml')+'\n',encoding='utf-8')
        command('generate',[tool,'--config',config],source)
        shards=list(generated.glob('*_full_*.c'))
        if not shards: raise RuntimeError('No generated C shards')
        result['generated_c_files']=len(shards)
        result['generated_c_bytes']=sum(x.stat().st_size for x in shards)
        result['input_sha256']=hashlib.sha256(data).hexdigest()
        result['status']='generation-complete'
        print('C generation complete. This is NOT a linked or booted game.')
        print('Report to commit:',evidence)
        return 0
    except (OSError,subprocess.SubprocessError,RuntimeError) as e:
        result['status']='failed';result['error']=str(e)
        print(e); print('Diagnostic report:',evidence)
        return 1
    finally: save()

if __name__=='__main__':raise SystemExit(main())
