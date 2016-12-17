#include <stdlib.h>
#include "utils.h"

endian_type get_system_endianess() {
    volatile uint32_t i = 0x12345678;
    return (*((uint8_t *)(&i))) == 0x78 ? endian_type_little_endian : endian_type_big_endian;
}

void util_nint_to_endian_bytes(nint num, uint8_t *buffer, endian_type endian) {
    size_t size = sizeof(nint);
    memcpy(buffer, &num, size);
    if (endian != get_system_endianess()) {
        // Reverse endianess.
        uint8_t v;
        for (size_t i = 0; i < size / 2; ++i) {
            v = buffer[i];
            buffer[i] = buffer[size - i];
            buffer[size - i] = v;
        }
    }
}

nint atoni(const char *str) {
#if defined(__LP64__) || defined(_LP64)
    return atol(str);
#else
#if defined(__ENV_BIT_32__)
    return atoi(str);
#elif defined(__ENV_BIT_64__)
    return atoll(str);
#else
#error Unsupported bits.
#endif
#endif
}
