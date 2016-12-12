#include <stdlib.h>
#include "plus1s.h"

struct native_code_block *create_native_block() {
    struct native_code_block *block = malloc(sizeof(struct native_code_block));
    block->capacity = 1;
    block->size = 0;
    block->code_as_data = NULL;
    block->code_exec = NULL;
    return block;
}

void destroy_native_block(struct native_code_block *block) {
    if (block->code_as_data) {
        free(block->code_as_data);
        block->code_as_data = NULL;
    }
    if (block->code_exec) {
        mem_free_page(block->code_exec, ROUND_TO_PAGE(block->size));
        block->code_exec = NULL;
    }
    free(block);
}

void *make_native_block_executable(struct native_code_block *block) {
    size_t size = ROUND_TO_PAGE(block->size); // round up to nearest page size
    void *ptr = mem_alloc_page(size);
    memcpy(ptr, block->code_as_data, block->size);
    mem_protect_page(ptr, size);
    block->code_exec = ptr;
    return ptr;
}

struct bytecode_block *create_bytecode_block() {
    struct bytecode_block *block = malloc(sizeof(struct bytecode_block));
    block->instruction = vm_instr_nop;
    block->operands = NULL;
    return block;
}

void destroy_bytecode_block(struct bytecode_block *block) {
    if (block->operands) {
        free(block->operands);
        block->operands = NULL;
    }
    free(block);
}
