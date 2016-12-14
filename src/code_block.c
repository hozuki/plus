#include <stdlib.h>
#include "code_block.h"

native_code_block *create_native_block() {
    native_code_block *block = malloc(sizeof(native_code_block));
    block->size = 0;
    block->code_as_data = NULL;
    block->code_exec = NULL;
    block->prev = block->next = NULL;
    return block;
}

void destroy_native_block(native_code_block *block) {
    if (block->code_as_data) {
        free(block->code_as_data);
        block->code_as_data = NULL;
    }
    if (block->code_exec) {
        mem_free_page(block->code_exec, ROUND_TO_PAGE(block->size));
        block->code_exec = NULL;
    }
    block->prev = block->next = NULL;
    free(block);
}

void *make_native_block_executable(native_code_block *block) {
    size_t size = ROUND_TO_PAGE(block->size); // round up to nearest page size
    void *ptr = mem_alloc_page(size);
    memcpy(ptr, block->code_as_data, block->size);
    mem_protect_page(ptr, size);
    block->code_exec = ptr;
    return ptr;
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
    block->operands = NULL;
    return block;
}

void destroy_bytecode_block(bytecode_block *block) {
    if (block->operands) {
        free(block->operands);
        block->operands = NULL;
    }
    free(block);
}
