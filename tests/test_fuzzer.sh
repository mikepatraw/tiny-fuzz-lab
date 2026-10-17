#!/bin/sh
set -eu

log=$(mktemp "${TMPDIR:-/tmp}/tiny-fuzz-run.XXXXXX")
trap 'rm -f "$log"' EXIT HUP INT TERM
rm -f last-case.bin

set +e
./build/fuzzer 1 >"$log" 2>&1
status=$?
set -e

[ "$status" -ne 0 ]
[ -s last-case.bin ]
grep -q "ERROR: AddressSanitizer: stack-buffer-overflow" "$log"
