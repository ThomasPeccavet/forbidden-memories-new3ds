#!/usr/bin/env bash
set -euo pipefail

# ============================================================
# B107b - rebuild generated PS1 core in RELEASE
# Robust devkitARM compiler auto-detection for Windows/MSYS
# ============================================================

ROOT="$(pwd)"

if [[ ! -d "$ROOT/work" || ! -d "$ROOT/3ds" ]]; then
    echo "ERROR: run this script from forbidden-memories-new3ds root."
    exit 1
fi

RUNTIME="$ROOT/work/upstream-psxrecomp/runtime"
OUT="$ROOT/work/arm-generated-objects"
REL="$ROOT/work/arm-generated-release"

if [[ ! -d "$RUNTIME/include" ]]; then
    echo "ERROR: runtime headers not found:"
    echo "  $RUNTIME/include"
    exit 1
fi

# ------------------------------------------------------------
# Find arm-none-eabi-gcc
# ------------------------------------------------------------

find_cc()
{
    # Explicit CC wins.
    if [[ -n "${CC:-}" ]] && command -v "$CC" >/dev/null 2>&1; then
        command -v "$CC"
        return 0
    fi

    # Existing PATH.
    if command -v arm-none-eabi-gcc >/dev/null 2>&1; then
        command -v arm-none-eabi-gcc
        return 0
    fi

    # DEVKITARM exported.
    if [[ -n "${DEVKITARM:-}" && -x "$DEVKITARM/bin/arm-none-eabi-gcc" ]]; then
        printf '%s\n' "$DEVKITARM/bin/arm-none-eabi-gcc"
        return 0
    fi

    # Common devkitPro MSYS2 layout.
    if [[ -x /opt/devkitpro/devkitARM/bin/arm-none-eabi-gcc ]]; then
        printf '%s\n' /opt/devkitpro/devkitARM/bin/arm-none-eabi-gcc
        return 0
    fi

    # Git-Bash view of a standard Windows devkitPro install.
    if [[ -x /c/devkitPro/devkitARM/bin/arm-none-eabi-gcc.exe ]]; then
        printf '%s\n' /c/devkitPro/devkitARM/bin/arm-none-eabi-gcc.exe
        return 0
    fi

    if [[ -x /c/devkitPro/devkitARM/bin/arm-none-eabi-gcc ]]; then
        printf '%s\n' /c/devkitPro/devkitARM/bin/arm-none-eabi-gcc
        return 0
    fi

    return 1
}

CC_BIN="$(find_cc || true)"

if [[ -z "$CC_BIN" ]]; then
    echo "ERROR: arm-none-eabi-gcc not found."
    echo
    echo "This shell does not have devkitARM in PATH."
    echo "Use the devkitPro/MSYS2 terminal, or export:"
    echo
    echo '  export DEVKITPRO=/opt/devkitpro'
    echo '  export DEVKITARM=$DEVKITPRO/devkitARM'
    echo '  export PATH=$DEVKITARM/bin:$PATH'
    echo
    echo "Then run this script again."
    exit 1
fi

export DEVKITARM="${DEVKITARM:-$(cd "$(dirname "$CC_BIN")/.." && pwd)}"
export DEVKITPRO="${DEVKITPRO:-$(cd "$DEVKITARM/.." && pwd)}"
export PATH="$DEVKITARM/bin:$PATH"

echo "devkitPro:"
echo "  DEVKITPRO=$DEVKITPRO"
echo "  DEVKITARM=$DEVKITARM"
echo "  CC=$CC_BIN"
echo

# ------------------------------------------------------------
# Find newest compatible generated French C directory
# ------------------------------------------------------------

GEN=""

while IFS= read -r -d '' d; do
    if [[ -f "$d/SLES_039.48_full_00.c" && -f "$d/SLES_039.48_dispatch.c" ]]; then
        GEN="$d"
    fi
done < <(find "$ROOT/work/pc-bootstrap" -mindepth 2 -maxdepth 2 -type d -name generated -print0 2>/dev/null | sort -z)

if [[ -z "$GEN" ]]; then
    echo "ERROR: no generated French C shards found under:"
    echo "  work/pc-bootstrap/*/generated"
    exit 1
fi

echo "B107b generated source:"
echo "  $GEN"
echo

mkdir -p "$OUT"
rm -rf "$REL"
mkdir -p "$REL"

COMMON_FLAGS=(
    -std=gnu11
    -O3
    -DNDEBUG
    -DPSX_NO_DEBUG_TOOLS
    -fomit-frame-pointer
    -mword-relocations
    -march=armv6k
    -mtune=mpcore
    -mfloat-abi=hard
    -mtp=soft
    -ffunction-sections
    -fdata-sections
    -I"$RUNTIME/include"
)

echo "Compiler:"
"$CC_BIN" --version | head -1
echo

count=0

for f in "$GEN"/SLES_039.48_*.c; do
    [[ -f "$f" ]] || continue

    base="$(basename "$f" .c)"
    obj="$REL/$base.o"

    count=$((count + 1))
    echo "[$count] $base.c"

    "$CC_BIN" \
        "${COMMON_FLAGS[@]}" \
        -c "$f" \
        -o "$obj"
done

if [[ "$count" -lt 16 ]]; then
    echo
    echo "ERROR: only $count generated C files were compiled; expected at least 16."
    exit 1
fi

NEW="$OUT/fm-generated-combined.o.b107-new"
FINAL="$OUT/fm-generated-combined.o"

rm -f "$NEW"

"$CC_BIN" \
    -r \
    "$REL"/SLES_039.48_*.o \
    -o "$NEW"

if [[ ! -s "$NEW" ]]; then
    echo "ERROR: combined release object was not produced."
    exit 1
fi

if [[ -f "$FINAL" ]]; then
    BACKUP="$OUT/fm-generated-combined.o.pre-b107"
    cp -p "$FINAL" "$BACKUP"

    echo
    echo "Backup:"
    echo "  $BACKUP"
fi

mv -f "$NEW" "$FINAL"

echo
echo "B107b release core created:"
ls -lh "$FINAL"

echo
echo "Undefined symbols (normal runtime imports):"
"$DEVKITARM/bin/arm-none-eabi-nm" -u "$FINAL" | sort

echo
echo "Done."
echo "Now build the 3DS project:"
echo "  make -C 3ds clean"
echo "  make -C 3ds -j4"
