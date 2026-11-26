#!/usr/bin/env bash
#
# Runs every Hack assembler test in this directory.
#
# Each test is a pair of files with the same name:
#   <name>.asm   - Hack assembly source
#   <name>.hack  - expected binary output, one 16-bit instruction per line
#
# Usage:
#   ./tests/run-tests.sh                # build, then run all tests
#   ./tests/run-tests.sh label          # only tests whose name contains "label"
#   ./tests/run-tests.sh --no-build     # skip building the assembler
#
# The assembler writes to output/out.hack relative to the repository root,
# so tests are always run from there.

set -u

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ROOT_DIR="$(cd "$SCRIPT_DIR/.." && pwd)"
ASM_BIN="${ASM_BIN:-$ROOT_DIR/build/hack-asm}"
OUT_FILE="$ROOT_DIR/output/out.hack"

build=1
filter=""

for arg in "$@"; do
    case "$arg" in
        --no-build) build=0 ;;
        -h|--help)
            sed -n '2,16p' "$0" | sed 's/^# \{0,1\}//'
            exit 0
            ;;
        -*)
            echo "unknown option: $arg" >&2
            exit 2
            ;;
        *) filter="$arg" ;;
    esac
done

mkdir -p "$ROOT_DIR/build" "$ROOT_DIR/output"

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

pass=0
fail=0
failed_tests=()

for asm in "$SCRIPT_DIR"/*.asm; do
    [ -e "$asm" ] || continue
    name="$(basename "$asm" .asm)"

    if [ -n "$filter" ] && [[ "$name" != *"$filter"* ]]; then
        continue
    fi

    expected="$SCRIPT_DIR/$name.hack"

    if [ ! -f "$expected" ]; then
        printf 'FAIL %s (missing %s.hack)\n' "$name" "$name"
        fail=$((fail + 1))
        failed_tests+=("$name")
        continue
    fi

    # Never let a previous run's output mask a missing/failed write.
    rm -f "$OUT_FILE"
    log="$(mktemp)"

    # stdout carries the debug symbol table, so only keep stderr.
    (
        cd "$ROOT_DIR" || exit 1
        "$ASM_BIN" "$asm"
    ) >/dev/null 2>"$log"
    status=$?

    if [ "$status" -ne 0 ] || [ ! -f "$OUT_FILE" ]; then
        printf 'FAIL %s (assembler exited with %d, no output written)\n' "$name" "$status"
        if [ -s "$log" ]; then
            tail -n 20 "$log" | sed 's/^/     /'
        fi
        fail=$((fail + 1))
        failed_tests+=("$name")
        rm -f "$log"
        continue
    fi

    if diff -q "$expected" "$OUT_FILE" >/dev/null 2>&1; then
        printf 'PASS %s\n' "$name"
        pass=$((pass + 1))
    else
        printf 'FAIL %s\n' "$name"
        diff -u "$expected" "$OUT_FILE" | head -n 40 | sed 's/^/     /'
        fail=$((fail + 1))
        failed_tests+=("$name")
    fi

    rm -f "$log"
done

echo
echo "-----------------------------"
echo "Passed: $pass  Failed: $fail"

if [ "$fail" -ne 0 ]; then
    echo "Failed tests: ${failed_tests[*]}"
    exit 1
fi
