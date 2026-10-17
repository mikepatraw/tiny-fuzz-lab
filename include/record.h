#ifndef RECORD_H
#define RECORD_H

#include <stddef.h>
#include <stdint.h>

enum record_status {
    RECORD_OK = 0,
    RECORD_TOO_SHORT,
    RECORD_BAD_VERSION,
    RECORD_TRUNCATED,
    RECORD_TOO_LARGE
};

struct record {
    uint8_t payload[32];
    size_t payload_len;
};

int record_decode(const uint8_t *data, size_t size, struct record *out);

#endif
