#include "memory.h"

#if defined(__ENV_PLATFORM_UNIX__)

void *mem_alloc_page(size_t size) {
    void *ptr = mmap(0, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (ptr == MAP_FAILED) {
        return NULL;
    }
    return ptr;
}

void mem_free_page(void *ptr, size_t size) {
    munmap(ptr, size);
}

void mem_protect_page(void *ptr, size_t size) {
    mprotect(ptr, size, PROT_READ | PROT_EXEC);
}

#endif
