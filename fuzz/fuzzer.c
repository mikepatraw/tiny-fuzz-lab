#include "record.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    const unsigned seed = argc > 1 ? (unsigned)strtoul(argv[1], NULL, 10) : 1U;
    srand(seed);

    for (unsigned run = 0; run < 1000; ++run) {
        uint8_t input[67] = {1};
        const size_t payload_len = (size_t)(rand() % 64);
        input[1] = (uint8_t)(payload_len >> 8);
        input[2] = (uint8_t)payload_len;
        for (size_t i = 0; i < payload_len; ++i) {
            input[i + 3] = (uint8_t)rand();
        }

        FILE *reproducer = fopen("last-case.bin", "wb");
        if (reproducer == NULL) {
            return 2;
        }
        const size_t written = fwrite(input, 1, payload_len + 3, reproducer);
        const int close_status = fclose(reproducer);
        if (written != payload_len + 3 || close_status != 0) {
            return 2;
        }

        struct record out = {0};
        record_decode(input, payload_len + 3, &out);
    }

    puts("No crash found");
    return 0;
}
