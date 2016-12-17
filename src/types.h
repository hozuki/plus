#pragma once

#include "plus1s.h"

#include <stddef.h>
#include <stdint.h>

#define DEFINE_TEMPLATE_ENTRY(name) uint8_t *name; \
                                    size_t name##_len
typedef struct _machine_code_template {
    DEFINE_TEMPLATE_ENTRY(init_code);
    DEFINE_TEMPLATE_ENTRY(return_code);
    DEFINE_TEMPLATE_ENTRY(loop_begin_code);
    DEFINE_TEMPLATE_ENTRY(loop_end_code);
    DEFINE_TEMPLATE_ENTRY(increment_code);
} machine_code_template;

#undef DEFINE_TEMPLATE_ENTRY

typedef enum _vm_instruction {
    vm_instr_nop,
    vm_instr_exit,
    vm_instr_increment,
    vm_instr_loop_start,
    vm_instr_loop_end
} vm_instruction;

typedef struct _bytecode_block {
    vm_instruction instruction;
    union {
        struct {
            nint number_of_loop;
            nint number_of_increment;
        } loop_start;
    } operands;
    struct _bytecode_block *prev;
    struct _bytecode_block *next;
} bytecode_block;

typedef struct _native_code_block {
    struct _native_code_block *prev;
    struct _native_code_block *next;
    union {
        uint8_t *code_as_data;
        void *code_exec;
    };
    size_t size;
} native_code_block;

typedef enum _endian_type {
    endian_type_big_endian,
    endian_type_little_endian
} endian_type;

typedef struct _bytecode_compiler {
    bytecode_block *first_block;
    bytecode_block *last_block;
    bytecode_block *processing_block;
    uint8_t has_error;
} bytecode_compiler;
