#!/usr/bin/env python3
"""Build the pinned MIPS-to-C tool and exercise it. Does not boot the game.
Python 3.11+, Git, CMake 3.20+, C/C++20 compiler. Windows: Developer Command Prompt.
Without --exe, generates an original synthetic PS-X EXE returning 42.
"""

import argparse
import datetime
import hashlib
import json
import re
import shutil
import struct
import subprocess
import uuid

from pathlib import Path


PIN = '1965b2df424da03483a5370340433a862f78f103'

URL = 'https://github.com/Unchiga/psxrecomp.git'

EXE_SHA = (
    '57ecdfb9a9e1faf8b342fe7c7304c237'
    '23810861f3ab2fa3bef9eb27b5146b44'
)


# ============================================================
# Analyse résidente du EXE français
# ============================================================

#
# Le startup efface la mémoire à partir de 0x8009C408.
#
# 0x8D000 correspond à la limite d'analyse statique actuelle.
#
# Les overlays dynamiques NE sont volontairement PAS inclus ici.
#
FR_ANALYSIS_SIZE = 0x8D000


ROOT = Path(__file__).resolve().parents[1]


# ============================================================
# Seeds Forbidden Memories FR
# ============================================================

SEEDS = [

    # --------------------------------------------------------
    # Entry / startup
    # --------------------------------------------------------

    0x800128CC,
    0x8001296C,
    0x800129DC,
    0x80012A44,


    # --------------------------------------------------------
    # Fonctions déjà identifiées
    # --------------------------------------------------------

    0x8002CFDC,
    0x8002D354,
    0x8002D038,
    0x8002D0BC,
    0x8002D2B4,
    0x8002D4AC,
    0x8002D5CC,
    0x8002D544,
    0x8002D75C,
    0x8002D800,
    0x8002D858,
    0x8002D89C,
    0x8002D8F4,
    0x8002D988,
    0x8002D990,
    0x8002DBE0,
    0x8002DE14,


    # --------------------------------------------------------
    # B135.20 - Pharaoh map hot resident entries / continuations
    #
    # B135.19 measured ~1.9M interpreted MIPS instructions per
    # 120 host loops in 0x800342B0..0x80035AC8.  These addresses
    # are reached as computed/internal continuations, so ordinary
    # direct-JAL discovery does not make them dispatcher entries.
    #
    # Force them into the static recompiler.  The generator knows
    # how to turn valid mid-function seeds into CPS continuations
    # or split pieces while preserving fall-through.
    # --------------------------------------------------------

    0x800342B0,
    0x80034A14,
    0x80034BE4,
    0x80034C74,
    0x80035794,
    0x80035988,

    # B135.26 - B135.25 IRGN profiling showed that every expensive
    # interpreter entry starts at 0x80034D7C, inside FUN_80034D30.
    # Across 120 host loops this continuation accounts for essentially
    # the whole ~660K interpreted-instruction load. Expose it directly
    # to the static dispatcher so the existing resident chain can keep
    # this path native.
    0x80034D7C,

    # B135.22 - hot CPS continuation in FUN_8008A0D8.
    #
    # The verified PC runtime repeatedly shows $ra=0x8008A1C0 while the
    # Pharaoh-map callback loop is active.  On 3DS B135.21 also lands on
    # CPU=8008A1C0 while the scheduler still spends ~38 ms in a slice.
    # Expose that interior return continuation to the static dispatcher.
    0x8008A1C0,

    # B135.23 - next hot exits reported by CHAIN3.
    #
    # 0x80057B80 is the hot loop continuation inside FUN_8005721C after
    # the model/primitive callback returns.
    #
    # 0x80089DA8 is the special primitive callback stub/sentinel used by
    # several primitive dispatch tables and was by far the hottest CHAIN3
    # exit on B135.22.
    0x80057B80,
    0x80089DA8,


    # --------------------------------------------------------
    # libapi / interruptions
    #
    # Une partie de ces fonctions est atteinte par pointeurs
    # de fonctions / callbacks et n'est donc pas toujours
    # découverte automatiquement par l'analyse reachable.
    # --------------------------------------------------------

    0x80074A6C,
    0x80074B44,
    0x80074D14,
    0x80074E5C,
    0x80074EFC,
    0x80074F74,
    0x80074FA0,
    0x80074FC8,
    0x80074FD8,

    0x80075040,
    0x80075154,
]


def main():

    p = argparse.ArgumentParser(
        description=__doc__
    )


    p.add_argument(
        '--framework',
        type=Path,
        default=ROOT / 'work/psxrecomp'
    )


    p.add_argument(
        '--build-dir',
        type=Path
    )


    p.add_argument(
        '--cmake',
        default='cmake'
    )


    p.add_argument(
        '--generator',
        help='Optional CMake generator, e.g. Ninja'
    )


    p.add_argument(
        '--jobs',
        type=int,
        default=4
    )


    p.add_argument(
        '--exe',
        type=Path,
        help='Original extracted SLES_039.48 (not payload.bin)'
    )


    p.add_argument(
        '--analysis-size',
        type=lambda s: int(s, 0),
        help='Override static analysis size in bytes (e.g. 0x1d0000); experimental'
    )


    p.add_argument(
        '--cc',
        help='Optional GCC/Clang-compatible C compiler for object validation'
    )


    a = p.parse_args()


    if (
        not shutil.which('git')
        or
        not shutil.which(a.cmake)
    ):
        p.error(
            'Git and CMake must be available; '
            'use a compiler Developer Command Prompt on Windows'
        )


    if a.jobs < 1:
        p.error(
            '--jobs must be positive'
        )


    if (
        a.cc
        and
        not shutil.which(a.cc)
    ):
        p.error(
            '--cc compiler not found'
        )


    source = (
        a.framework.resolve()
    )


    build = (
        a.build_dir.resolve()
        if a.build_dir
        else source / 'recompiler/build-pc'
    )


    if a.exe:

        exe = (
            a.exe.resolve()
        )


        if (
            not exe.is_file()
            or
            hashlib.sha256(
                exe.read_bytes()
            ).hexdigest() != EXE_SHA
        ):
            p.error(
                'Expected the verified French SLES_039.48 EXE, '
                'with its 2048-byte header'
            )


    stamp = (
        datetime.datetime.now(
            datetime.timezone.utc
        ).strftime(
            '%Y%m%dT%H%M%SZ'
        )
        +
        '-'
        +
        uuid.uuid4().hex[:8]
    )


    run = (
        ROOT
        /
        'work/pc-bootstrap'
        /
        stamp
    )


    evidence = (
        ROOT
        /
        'research/pc-bootstrap'
        /
        stamp
    )


    run.mkdir(
        parents=True
    )


    evidence.mkdir(
        parents=True
    )


    result = {

        'framework_commit':
            PIN,

        'mode':
            'french-main-exe'
            if a.exe
            else 'synthetic-smoke',

        'steps':
            [],

        'status':
            'running',

        'game_booted':
            False,
    }


    def save():

        (
            evidence
            /
            'result.json'
        ).write_text(
            json.dumps(
                result,
                indent=2
            )
            +
            '\n',
            encoding='utf-8'
        )


    def command(
        label,
        args,
        cwd=None
    ):

        print(
            label,
            flush=True
        )


        log = (
            evidence
            /
            (
                label
                +
                '.log'
            )
        )


        with log.open(
            'w',
            encoding='utf-8'
        ) as f:

            proc = subprocess.run(

                [
                    str(x)
                    for x in args
                ],

                cwd=cwd,

                stdout=f,

                stderr=subprocess.STDOUT
            )


        result[
            'steps'
        ].append({

            'step':
                label,

            'exit_code':
                proc.returncode,

            'log':
                log.name,
        })


        save()


        if proc.returncode:

            raise RuntimeError(
                label
                +
                ' failed; see '
                +
                str(log)
            )


    try:

        # ====================================================
        # PSXRecomp checkout
        # ====================================================

        if not source.exists():

            source.mkdir(
                parents=True
            )


            command(
                'git-init',
                [
                    'git',
                    'init',
                    source
                ]
            )


            command(
                'git-remote',
                [
                    'git',
                    'remote',
                    'add',
                    'origin',
                    URL
                ],
                source
            )


            command(
                'git-fetch',
                [
                    'git',
                    'fetch',
                    '--depth',
                    '1',
                    'origin',
                    PIN
                ],
                source
            )


            command(
                'git-checkout',
                [
                    'git',
                    'checkout',
                    '--detach',
                    PIN
                ],
                source
            )


        head = subprocess.check_output(
            [
                'git',
                'rev-parse',
                'HEAD'
            ],
            cwd=source,
            text=True
        ).strip()


        dirty = subprocess.check_output(
            [
                'git',
                'status',
                '--porcelain',
                '--untracked-files=no'
            ],
            cwd=source,
            text=True
        )


        if (
            head != PIN
            or
            dirty
        ):
            raise RuntimeError(
                'Existing framework must be clean at '
                +
                PIN
                +
                '; nothing was reset'
            )


        # ====================================================
        # Build PSXRecomp
        # ====================================================

        args = [

            a.cmake,

            '-S',
            source / 'recompiler',

            '-B',
            build,

            '-DCMAKE_BUILD_TYPE=Release',

            '-DPSXRECOMP_ENABLE_CHD=OFF',

            '-DBUILD_TESTING=OFF',

            '-DCMAKE_POLICY_VERSION_MINIMUM=3.5'
        ]


        if a.generator:

            args += [
                '-G',
                a.generator
            ]


        command(
            'configure',
            args
        )


        command(
            'build',
            [
                a.cmake,
                '--build',
                build,
                '--config',
                'Release',
                '--target',
                'psxrecomp-game',
                'psxrecomp-toml',
                '--parallel',
                a.jobs
            ]
        )


        # ====================================================
        # Locate emitter
        # ====================================================

        candidates = [

            build
            /
            'psxrecomp-game',

            build
            /
            'psxrecomp-game.exe',

            build
            /
            'Release/psxrecomp-game.exe'
        ]


        tool = next(
            (
                x
                for x in candidates
                if x.is_file()
            ),
            None
        )


        if tool is None:

            raise RuntimeError(
                'Built emitter not found'
            )


        command(
            'emitter-version',
            [
                tool,
                '--codegen-hash'
            ]
        )


        # ====================================================
        # Input
        # ====================================================

        if a.exe:

            seeds = SEEDS

        else:

            exe = (
                run
                /
                'SMOKE.EXE'
            )


            h = bytearray(
                2048
            )


            h[:8] = (
                b'PS-X EXE'
            )


            for o, v in [

                (
                    16,
                    0x80010000
                ),

                (
                    24,
                    0x80010000
                ),

                (
                    28,
                    2048
                ),

                (
                    48,
                    0x801FFFF0
                ),

            ]:

                struct.pack_into(
                    '<I',
                    h,
                    o,
                    v
                )


            b = bytearray(
                2048
            )


            struct.pack_into(
                '<III',
                b,
                0,
                0x2402002A,
                0x03E00008,
                0
            )


            exe.write_bytes(
                h
                +
                b
            )


            seeds = [
                0x80010000
            ]


        # ====================================================
        # EXE metadata
        # ====================================================

        data = (
            exe.read_bytes()
        )


        def read(offset):

            return struct.unpack_from(
                '<I',
                data,
                offset
            )[0]


        analysis_size = (

            a.analysis_size

            if a.analysis_size is not None

            else (

                FR_ANALYSIS_SIZE

                if a.exe

                else read(28)
            )
        )


        if (
            analysis_size <= 0
            or
            analysis_size > read(28)
        ):
            raise RuntimeError(
                'Analysis size must be positive '
                'and within the payload'
            )


        result.update(

            input_sha256=
                hashlib.sha256(
                    data
                ).hexdigest(),

            payload_size=
                read(28),

            analysis_size=
                analysis_size,

            analysis_end=
                '0x%08X'
                %
                (
                    read(24)
                    +
                    analysis_size
                ),

            overlays_integrated=
                False,

            runtime_linked=
                False
        )


        # ====================================================
        # Seeds
        # ====================================================

        seedfile = (
            run
            /
            'seeds.txt'
        )


        seedfile.write_text(

            ''.join(

                '0x%08X\n'
                %
                s

                for s in seeds
            )
        )


        # ====================================================
        # Generated C
        # ====================================================

        generated = (
            run
            /
            'generated'
        )


        def q(path):

            return json.dumps(
                Path(
                    path
                ).as_posix(),
                ensure_ascii=False
            )


        config = (
            run
            /
            'game.toml'
        )


        config.write_text(

            '[game]\n'

            'name="FM French experiment"\n'

            'id="'
            +
            (
                'SLES-03948'
                if a.exe
                else 'SMOKE'
            )
            +
            '"\n'

            'exe='
            +
            q(exe)
            +
            '\n'

            +
            ''.join(

                k
                +
                '="0x%08X"\n'
                %
                v

                for k, v in [

                    (
                        'load_address',
                        read(24)
                    ),

                    (
                        'entry_pc',
                        read(16)
                    ),

                    (
                        'text_size',
                        analysis_size
                    ),

                    (
                        'stack_base',
                        read(48)
                    ),
                ]
            )

            +
            '[recompiler]\n'

            'seeds='
            +
            q(seedfile)
            +
            '\n'

            'out_dir='
            +
            q(generated)
            +
            '\n'

            'strict=true\n'

            'discovery="reachable"\n'

            'bios_config='
            +
            q(
                source
                /
                'bios/OpenBIOS.toml'
            )
            +
            '\n'

            +
            (
                '\n'
                '[controller]\n'
                'p1_mode="digital"\n'
                'lock_mode=true\n'

                if a.exe

                else ''
            ),

            encoding='utf-8'
        )


        # ====================================================
        # Generate
        # ====================================================

        command(
            'generate',
            [
                tool,
                '--config',
                config
            ],
            source
        )


        shards = list(
            generated.glob(
                '*_full_*.c'
            )
        )


        if not shards:

            raise RuntimeError(
                'No generated C shards'
            )


        result[
            'generated_c_files'
        ] = len(
            shards
        )


        result[
            'generated_c_bytes'
        ] = sum(
            x.stat().st_size
            for x in shards
        )


        logtext = (
            evidence
            /
            'generate.log'
        ).read_text(
            encoding='utf-8',
            errors='replace'
        )


        warnings = [

            line

            for line
            in logtext.splitlines()

            if re.search(
                r'\bwarning\b',
                line,
                re.I
            )
        ]


        result[
            'generation_warning_lines'
        ] = len(
            warnings
        )


        manifests = list(
            generated.glob(
                '*_full.ranges'
            )
        )


        result[
            'generated_functions'
        ] = sum(

            sum(

                line.startswith(
                    'F '
                )

                for line
                in f.read_text().splitlines()
            )

            for f
            in manifests
        )


        result[
            'status'
        ] = (

            'generation-with-warnings'

            if warnings

            else 'generation-complete'
        )


        # ====================================================
        # Optional host compilation
        # ====================================================

        if a.cc:

            objects = (
                run
                /
                'objects'
            )


            objects.mkdir()


            command(
                'compiler-version',
                [
                    a.cc,
                    '--version'
                ]
            )


            files = sorted(
                generated.glob(
                    '*.c'
                )
            )


            for f in files:

                command(

                    'compile-'
                    +
                    f.stem,

                    [
                        a.cc,
                        '-std=c11',
                        '-O0',
                        '-DPSX_NO_DEBUG_TOOLS',
                        '-I',
                        source / 'runtime/include',
                        '-c',
                        f,
                        '-o',
                        objects
                        /
                        (
                            f.stem
                            +
                            '.o'
                        )
                    ]
                )


            result[
                'compiled_c_files'
            ] = len(
                files
            )


            result[
                'status'
            ] = (

                'objects-compiled-with-generation-warnings'

                if warnings

                else 'objects-compiled'
            )


        print(
            'Generation warnings:',
            len(warnings)
        )


        print(
            'C generation complete. '
            'Object compilation, when requested, '
            'does NOT validate game behavior.'
        )


        print(
            'This is NOT a linked or booted game. '
            'Dynamic overlays are not integrated.'
        )


        print(
            'Report to commit:',
            evidence
        )


        return 0


    except (
        OSError,
        subprocess.SubprocessError,
        RuntimeError
    ) as e:

        result[
            'status'
        ] = 'failed'


        result[
            'error'
        ] = str(e)


        print(
            e
        )


        print(
            'Diagnostic report:',
            evidence
        )


        return 1


    finally:

        save()


if __name__ == '__main__':

    raise SystemExit(
        main()
    )