#include <stdlib.h>
#include "code_block.h"
#include "types.h"

native_code_block *create_native_block() {
    native_code_block *block = malloc(sizeof(native_code_block));
    block->size = 0;
    block->code_as_data = NULL;
    block->code_exec = NULL;
    block->prev = block->next = NULL;
    return block;
}

native_code_block *alloc_page_for_native_block(native_code_block *block) {
    block->code_exec = mem_alloc_page(block->size);
    return block;
}

void destroy_native_block(native_code_block *block) {
    if (block->code_exec) {
        mem_free_page(block->code_exec, block->size);
        block->code_exec = NULL;
    }
    if (block->prev) {
        block->prev->next = block->next;
    }
    if (block->next) {
        block->next->prev = block->prev;
    }
    block->prev = block->next = NULL;
    free(block);
}

void *make_native_block_executable(native_code_block *block) {
    mem_protect_page(block->code_exec, block->size);
    return block;
}

void destroy_all_native_blocks(native_code_block *start) {
    native_code_block *block = start;
    native_code_block *next;
    while (block) {
        next = block->next;
        destroy_native_block(block);
        block = next;
    }
}

void link_native_block(native_code_block *this, native_code_block *next) {
    this->next = next;
    next->prev = this;
}

bytecode_block *create_bytecode_block() {
    bytecode_block *block = malloc(sizeof(bytecode_block));
    block->instruction = vm_instr_nop;
    memset(&block->operands, 0, sizeof(block->operands));
    block->prev = block->next = NULL;
    return block;
}

void destroy_bytecode_block(bytecode_block *block) {
    if (block->prev) {
        block->prev->next = block->next;
    }
    if (block->next) {
        block->next->prev = block->prev;
    }
    block->prev = block->next = NULL;
    free(block);
}

void destroy_all_bytecode_blocks(bytecode_block *start) {
    bytecode_block *block = start;
    bytecode_block *next;
    while (block) {
        next = block->next;
        destroy_bytecode_block(block);
        block = next;
    }
}

void link_bytecode_block(bytecode_block *this, bytecode_block *next) {
    this->next = next;
    next->prev = this;
}
