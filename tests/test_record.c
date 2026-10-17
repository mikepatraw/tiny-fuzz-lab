#include "record.h"

#include <assert.h>
#include <string.h>

static void decodes_valid_record(void) {
    const uint8_t input[] = {1, 0, 3, 'c', 'a', 't'};
    struct record out = {0};

    assert(record_decode(input, sizeof(input), &out) == RECORD_OK);
    assert(out.payload_len == 3);
    assert(memcmp(out.payload, "cat", 3) == 0);
}

static void rejects_truncated_payload(void) {
    const uint8_t input[] = {1, 0, 4, 'c', 'a', 't'};
    struct record out = {0};

    assert(record_decode(input, sizeof(input), &out) == RECORD_TRUNCATED);
}

static void rejects_oversized_payload(void) {
    uint8_t input[36] = {1, 0, 33};
    struct record out = {0};

    assert(record_decode(input, sizeof(input), &out) == RECORD_TOO_LARGE);
}

int main(void) {
    decodes_valid_record();
    rejects_truncated_payload();
    rejects_oversized_payload();
    return 0;
}
