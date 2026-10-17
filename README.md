# tiny-fuzz-lab

A compact C fuzzing lab that demonstrates deterministic input generation, crash preservation, and sanitizer-backed bug discovery.

The target parses a tiny length-prefixed record:

- byte `0`: format version (`1`)
- bytes `1-2`: big-endian payload length
- remaining bytes: payload

Normal builds reject payloads larger than the destination buffer. The fuzz build intentionally disables that check with `FUZZ_DEMO_BUG`, giving AddressSanitizer a realistic stack overflow to find.

## Requirements

- GCC or Clang
- GNU Make
- AddressSanitizer and UndefinedBehaviorSanitizer support

## Build and test

```sh
make test
```

The test suite checks the safe decoder and confirms that deterministic seed `1` discovers the demo overflow while preserving the triggering input as `last-case.bin`.

## Run the fuzzer

```sh
make build/fuzzer
./build/fuzzer 1
```

A sanitizer report and non-zero exit are expected. Change the numeric seed to explore a different deterministic input sequence.

## Safety

The unsafe behavior is compiled only into the fuzz target. Do not reuse `FUZZ_DEMO_BUG` in production code.

## Author

Mike Patraw
