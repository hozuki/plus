#include "../plus1s.h"

#if defined(__ENV_PLATFORM_WINDOWS__)

void *mem_alloc_page(size_t size) {
    // MSDN: "This handle has the PROCESS_ALL_ACCESS access right to the process object. For more information, see Process Security and Access Rights."
    HANDLE hProcess = GetCurrentProcess();
    PVOID *pMemory = VirtualAllocEx(hProcess, NULL, (DWORD)size, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    return pMemory;
}

void mem_free_page(void *ptr, size_t size) {
    HANDLE hProcess = GetCurrentProcess();
    VirtualFreeEx(hProcess, ptr, (DWORD)size, MEM_RELEASE);
}

void mem_protect_page(void *ptr, size_t size) {
    HANDLE hProcess = GetCurrentProcess();
    DWORD dwOldProtection;
    VirtualProtectEx(hProcess, ptr, (DWORD)size, PAGE_EXECUTE_READWRITE, &dwOldProtection);
}

#endif
