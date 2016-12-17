#pragma once

#include "plus1s.h"

void util_nint_to_endian_bytes(nint num, uint8_t *buffer, endian_type endian);

nint atoni(const char *str);
