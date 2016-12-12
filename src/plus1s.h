#pragma once

#include <stddef.h>
#include <stdint.h>
#include "env.h"

#define DEFINE_TEMPLATE_ENTRY(name) uint8_t *name; \
                                    uint8_t name##_len
struct machine_code_template {
    DEFINE_TEMPLATE_ENTRY(init_code);
    DEFINE_TEMPLATE_ENTRY(function_call_code);
    DEFINE_TEMPLATE_ENTRY(return_code);
    DEFINE_TEMPLATE_ENTRY(loop_begin_code);
    DEFINE_TEMPLATE_ENTRY(loop_end_code);
};

#undef DEFINE_TEMPLATE_ENTRY

enum vm_instruction {
    vm_instr_nop,
    vm_instr_exit,
    vm_instr_increment,
    vm_instr_jump
};

struct bytecode_block {
    enum vm_instruction instruction;
    nint *operands;
};

struct native_code_block {
    uint8_t *code_as_data;
    void *code_exec;
    size_t capacity;
    size_t size;
};

/* Machine code*/
// We want cdecl function explicitly.
typedef __cdecl nint (*my_func)();

extern struct machine_code_template g_machine_code;

struct machine_code_template *init_machine_code_template();

/* Memory functions */

void *mem_alloc_page(size_t size);

void mem_free_page(void *ptr, size_t size);

void mem_protect_page(void *ptr, size_t size);

/* Code block functions */

struct native_code_block *create_native_block();

void destroy_native_block(struct native_code_block *block);

void *make_native_block_executable(struct native_code_block *block);

struct bytecode_block *create_bytecode_block();

void destroy_bytecode_block(struct bytecode_block *block);

#if defined(__ENV_PLATFORM_WINDOWS__)
#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>

#endif
