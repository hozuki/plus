#pragma once

#include "plus1s.h"

#include <stddef.h>
#include <stdint.h>

#define DEFINE_TEMPLATE_ENTRY(name) uint8_t *name; \
                                    uint8_t name##_len
typedef struct _machine_code_template {
    DEFINE_TEMPLATE_ENTRY(init_code);
    DEFINE_TEMPLATE_ENTRY(function_call_code);
    DEFINE_TEMPLATE_ENTRY(return_code);
    DEFINE_TEMPLATE_ENTRY(loop_begin_code);
    DEFINE_TEMPLATE_ENTRY(loop_end_code);
} machine_code_template;

#undef DEFINE_TEMPLATE_ENTRY

typedef enum _vm_instruction {
    vm_instr_nop,
    vm_instr_exit,
    vm_instr_increment,
    vm_instr_jump
} vm_instruction;

typedef struct _bytecode_block {
    vm_instruction instruction;
    nint *operands;
} bytecode_block;

typedef struct _native_code_block {
    struct _native_code_block *prev;
    struct _native_code_block *next;
    uint8_t *code_as_data;
    void *code_exec;
    size_t size;
} native_code_block;

typedef enum _endian_type {
    endian_type_big_endian,
    endian_type_little_endian
} endian_type;
