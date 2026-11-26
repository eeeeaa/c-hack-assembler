#!/usr/bin/env bash
#
# Assembles every .asm file under n2tetris-tests/ and writes the result to
# n2tetris-tests/output/<Name>.hack. Existing files are replaced on re-run.
#
# Usage:
#   ./n2tetris-tests/generate-hack.sh              # build, then assemble all
#   ./n2tetris-tests/generate-hack.sh Pong         # only names containing "Pong"
#   ./n2tetris-tests/generate-hack.sh --no-build   # skip building the assembler
#
# The assembler always writes output/out.hack relative to the repository root,
# so it is run from there and the result is moved into n2tetris-tests/output.

set -u

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ROOT_DIR="$(cd "$SCRIPT_DIR/.." && pwd)"
ASM_BIN="${ASM_BIN:-$ROOT_DIR/build/hack-asm}"
TMP_OUT="$ROOT_DIR/output/out.hack"
DEST_DIR="$SCRIPT_DIR/output"

build=1
filter=""

for arg in "$@"; do
    case "$arg" in
        --no-build) build=0 ;;
        -h|--help)
            sed -n '2,12p' "$0" | sed 's/^# \{0,1\}//'
            exit 0
            ;;
        -*)
            echo "unknown option: $arg" >&2
            exit 2
            ;;
        *) filter="$arg" ;;
    esac
done

mkdir -p "$ROOT_DIR/build" "$ROOT_DIR/output" "$DEST_DIR"

if [ "$build" -eq 1 ]; then
    echo "Building assembler..."
    if ! make -s -C "$ROOT_DIR"; then
        echo "Build failed." >&2
        exit 1
    fi
fi

if [ ! -x "$ASM_BIN" ]; then
    echo "Assembler not found: $ASM_BIN" >&2
    echo "Run 'make' first, or omit --no-build." >&2
    exit 1
fi

ok=0
fail=0
failed=()

for asm in "$SCRIPT_DIR"/*/*.asm; do
    [ -e "$asm" ] || continue
    # Skip our own output directory, if it ever holds .asm files.
    [ "$(dirname "$asm")" = "$DEST_DIR" ] && continue

    name="$(basename "$asm" .asm)"

    if [ -n "$filter" ] && [[ "$name" != *"$filter"* ]]; then
        continue
    fi

    dest="$DEST_DIR/$name.hack"

    # Drop stale results so a failed run can't leave old output behind.
    rm -f "$TMP_OUT" "$dest"

    (
        cd "$ROOT_DIR" || exit 1
        "$ASM_BIN" "$asm"
    ) >/dev/null 2>&1
    status=$?

    if [ "$status" -ne 0 ] || [ ! -f "$TMP_OUT" ]; then
        printf 'FAIL %s (assembler exited with %d, no output written)\n' "$name" "$status"
        fail=$((fail + 1))
        failed+=("$name")
        continue
    fi

    mv -f "$TMP_OUT" "$dest"
    printf 'OK   %s -> %s\n' "$name" "${dest#"$ROOT_DIR"/}"
    ok=$((ok + 1))
done

rm -f "$TMP_OUT"

echo
echo "Generated: $ok  Failed: $fail"

if [ "$fail" -ne 0 ]; then
    echo "Failed: ${failed[*]}"
    exit 1
fi
