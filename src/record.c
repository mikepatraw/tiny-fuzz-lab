#include "record.h"

#include <string.h>

int record_decode(const uint8_t *data, size_t size, struct record *out) {
    if (size < 3) {
        return RECORD_TOO_SHORT;
    }
    if (data[0] != 1) {
        return RECORD_BAD_VERSION;
    }

    const size_t payload_len = ((size_t)data[1] << 8) | data[2];
    if (payload_len > size - 3) {
        return RECORD_TRUNCATED;
    }
#ifndef FUZZ_DEMO_BUG
    if (payload_len > sizeof(out->payload)) {
        return RECORD_TOO_LARGE;
    }
#endif

    memcpy(out->payload, data + 3, payload_len);
    out->payload_len = payload_len;
    return RECORD_OK;
}
