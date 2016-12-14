#pragma once

#include "plus1s.h"

void *mem_alloc_page(size_t size);

void mem_free_page(void *ptr, size_t size);

void mem_protect_page(void *ptr, size_t size);
