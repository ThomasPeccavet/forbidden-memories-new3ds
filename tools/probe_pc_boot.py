#!/usr/bin/env python3
"""Bounded headless boot probe. Requires a PSX_DEBUG_TOOLS=ON runtime.
Writes diagnostic JSON, a runtime log and a screenshot; does not infer success.
"""
import argparse
import hashlib
import importlib.util
import json
import subprocess
import re
import time
from pathlib import Path

DISC_SHA='9ef0d0ba5e42b838bd8312ecfe4071b09c44bc08ee896f6b76f913a41fe4b835'
DISC_BYTES=548427600

def verify_disc(path):
    """This probe targets the verified single-track French BIN/CUE only."""
    image=path.resolve()
    if image.suffix.lower()=='.cue':
        files=re.findall(r'^\s*FILE\s+"([^"]+)"\s+BINARY\s*$',image.read_text(),re.I|re.M)
        if len(files)!=1:raise ValueError('Expected a single FILE "..." BINARY in the French CUE')
        image=image.parent/files[0]
    if image.stat().st_size!=DISC_BYTES:raise ValueError('French disc size mismatch; re-extract the original archive')
    h=hashlib.sha256()
    with image.open('rb') as f:
        for block in iter(lambda:f.read(1024*1024),b''):h.update(block)
    if h.hexdigest()!=DISC_SHA:raise ValueError('French disc SHA-256 mismatch; do not debug using this image')
    return {'bin':str(image),'bytes':DISC_BYTES,'sha256':h.hexdigest()}

def main():
    p=argparse.ArgumentParser(description=__doc__)
    for name in ('runtime','framework','config','bios','disc','output'):
        p.add_argument('--'+name,type=Path,required=True)
    p.add_argument('--port',type=int,default=4370)
    p.add_argument('--samples',type=int,default=3)
    p.add_argument('--interval',type=float,default=5)
    p.add_argument('--press-start',action='store_true',help='Press Start after the third sample (separate input experiment)')
    p.add_argument('--start-samples',type=int,nargs='+',default=[2],help='Zero-based samples after which to press Start; requires --press-start')
    p.add_argument('--input-script',type=Path,help='JSON array of actions: seconds, optional buttons (active-low hex string), frames')
    a=p.parse_args()
    if not 1 <= a.samples <= 24 or not 0 < a.interval <= 10:p.error('samples 1..24, interval >0..10')
    actions=None
    if a.input_script:
        actions=json.loads(a.input_script.read_text())
        if not isinstance(actions,list) or not 1 <= len(actions) <= 100:p.error('input-script must contain 1..100 actions')
        for v in actions:
            if not 0 < v.get('seconds',2) <= 30:p.error('action seconds must be >0..30')
            if 'buttons' in v and not 0 <= int(v['buttons'],0) <= 65535:p.error('invalid button mask')
            if not 1 <= v.get('frames',10) <= 600:p.error('frames must be 1..600')
    for name in ('runtime','config','bios','disc'):
        if not getattr(a,name).is_file():p.error(name+' file missing')
    try:disc_check=verify_disc(a.disc)
    except (OSError,ValueError) as e:p.error(str(e))
    out=a.output.resolve();out.mkdir(parents=True,exist_ok=False)
    spec=importlib.util.spec_from_file_location('psx_debug_client',a.framework.resolve()/'tools/debug_client.py')
    client=importlib.util.module_from_spec(spec);spec.loader.exec_module(client)
    args=[str(a.runtime.resolve()),'--game',str(a.config.resolve()),'--bios',str(a.bios.resolve()),
          '--disc',str(a.disc.resolve()),'--headless','--renderer','software','--debug-port',str(a.port),
          '--memcard-dir',str(out/'player-data')]
    report={'command':args,'observations':[],'visual_verdict':'not_evaluated_by_script',
            'disc_verification':disc_check,
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
            report['input_actions']=actions
            for i in range(len(actions) if actions is not None else a.samples):
                if actions is not None:
                    action=actions[i]
                    if 'buttons' in action:query('press',buttons=int(action['buttons'],0),frames=action.get('frames',10))
                    time.sleep(action.get('seconds',2))
                else:time.sleep(a.interval)
                query('ping');query('get_registers');query('gpu_state')
                query('pad_status');query('pad_probe')
                query('screenshot_file',path=str(out/('display-%02d.png'%i)))
                if actions is None and a.press_start and i in a.start_samples:query('press',buttons=0xFFF7,frames=10)
            # This pinned runtime deliberately removed pause/continue/step.
            # These are sequential live observations, not an atomic snapshot.
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
