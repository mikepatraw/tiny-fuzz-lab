CC ?= cc
CFLAGS := -std=c11 -Wall -Wextra -Wpedantic -Werror -Iinclude
SANITIZERS := -fsanitize=address,undefined -fno-omit-frame-pointer

.PHONY: all test fuzz

all: test

build/test_record: tests/test_record.c src/record.c include/record.h
	mkdir -p build
	$(CC) $(CFLAGS) $(SANITIZERS) tests/test_record.c src/record.c -o $@

build/fuzzer: fuzz/fuzzer.c src/record.c include/record.h
	mkdir -p build
	$(CC) $(CFLAGS) $(SANITIZERS) -DFUZZ_DEMO_BUG fuzz/fuzzer.c src/record.c -o $@

test: build/test_record build/fuzzer
	./build/test_record
	sh tests/test_fuzzer.sh

fuzz: build/fuzzer
	./build/fuzzer $(SEED)
