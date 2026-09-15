#!/usr/bin/env python3
"""Bounded headless boot probe. Requires a PSX_DEBUG_TOOLS=ON runtime.
Writes diagnostic JSON, a runtime log and a screenshot; does not infer success.
"""
import argparse
import importlib.util
import json
import subprocess
import time
from pathlib import Path

def main():
    p=argparse.ArgumentParser(description=__doc__)
    for name in ('runtime','framework','config','bios','disc','output'):
        p.add_argument('--'+name,type=Path,required=True)
    p.add_argument('--port',type=int,default=4370)
    p.add_argument('--samples',type=int,default=3)
    p.add_argument('--interval',type=float,default=5)
    p.add_argument('--press-start',action='store_true',help='Press Start after the third sample (separate input experiment)')
    p.add_argument('--start-samples',type=int,nargs='+',default=[2],help='Zero-based samples after which to press Start; requires --press-start')
    a=p.parse_args()
    if not 1 <= a.samples <= 24 or not 0 < a.interval <= 10:p.error('samples 1..24, interval >0..10')
    for name in ('runtime','config','bios','disc'):
        if not getattr(a,name).is_file():p.error(name+' file missing')
    out=a.output.resolve();out.mkdir(parents=True,exist_ok=False)
    spec=importlib.util.spec_from_file_location('psx_debug_client',a.framework.resolve()/'tools/debug_client.py')
    client=importlib.util.module_from_spec(spec);spec.loader.exec_module(client)
    args=[str(a.runtime.resolve()),'--game',str(a.config.resolve()),'--bios',str(a.bios.resolve()),
          '--disc',str(a.disc.resolve()),'--headless','--renderer','software','--debug-port',str(a.port),
          '--memcard-dir',str(out/'player-data')]
    report={'command':args,'observations':[],'visual_verdict':'not_evaluated_by_script',
            'samples':a.samples,'interval':a.interval,
            'start_samples':a.start_samples if a.press_start else []}
    def save():
        (out/'probe.json').write_text(json.dumps(report,indent=2)+'\n')
    def query(cmd,**kw):
        with client.connect(port=a.port,timeout=4) as sock:
            response=client.send_cmd(sock,{'id':1,'cmd':cmd,**kw})
        report['observations'].append({'elapsed':round(time.monotonic()-start,3),'cmd':cmd,'response':response})
        save();return response
    # Avoid querying a different runtime already listening on the chosen port.
    import socket
    with socket.socket() as s:
        s.bind(('127.0.0.1',a.port))
    start=time.monotonic()
    with (out/'runtime.log').open('w') as log:
        proc=subprocess.Popen(args,cwd=a.runtime.resolve().parent,stdout=log,stderr=subprocess.STDOUT)
        try:
            ready=False
            for _ in range(20):
                if proc.poll() is not None:break
                try:query('ping');ready=True;break
                except (OSError,ValueError):time.sleep(0.25)
            if not ready:raise RuntimeError('Debug server did not become available')
            query('fntrace_arm',target='0xFFFFFFFF')
            for i in range(a.samples):
                time.sleep(a.interval)
                query('ping');query('get_registers');query('gpu_state')
                query('screenshot_file',path=str(out/('display-%02d.png'%i)))
                if a.press_start and i in a.start_samples:query('press',buttons=0xFFF7,frames=10)
            query('pause')
            query('get_registers')
            query('read_ram',addr='0x80010000',len=32)
            query('read_ram',addr='0x8009C608',len=16)
            query('read_ram',addr='0x80180000',len=32)
            query('read_ram',addr='0x800F70D0',len=64)
            query('dispatch_stats')
            query('cdrom_state')
            query('fntrace_dump',count=64)
            query('screenshot_file',path=str(out/'display.png'))
            query('quit')
        except Exception as e:
            report['error']=str(e)
        finally:
            try:proc.wait(timeout=3)
            except subprocess.TimeoutExpired:
                report['terminated_by_probe']=True;proc.terminate()
                try:proc.wait(timeout=3)
                except subprocess.TimeoutExpired:proc.kill();proc.wait()
            report['exit_code']=proc.returncode;save()
    print(out/'probe.json')
    return 1 if 'error' in report else 0

if __name__=='__main__':raise SystemExit(main())
