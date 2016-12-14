#include "utils.h"

void util_nint_to_endian_bytes(nint num, uint8_t *buffer, endian_type endian) {
    size_t size = sizeof(nint);
    size_t i;
    uint8_t v;
    switch (endian) {
        case endian_type_big_endian:
            for (i = 0; i < size; ++i) {
                v = (uint8_t)(num >> (8 * (size - i)) & 0xff);
                buffer[i] = v;
            }
            break;
        case endian_type_little_endian:
            for (i = 0; i < size; ++i) {
                v = (uint8_t)((num >> (8 * i)) & 0xff);
                buffer[i] = v;
            }
            break;
        default:
            break;
    }
}
