#include "compiler.h"
#include "types.h"

bytecode_compiler g_compiler;

void compiler_init() {
    g_compiler.processing_block = NULL;
    g_compiler.first_block = NULL;
    g_compiler.last_block = NULL;
    g_compiler.has_error = FALSE;
}

void compiler_destroy() {
    if (g_compiler.processing_block) {
        destroy_bytecode_block(g_compiler.processing_block);
        g_compiler.processing_block = NULL;
    }
    if (g_compiler.first_block) {
        destroy_all_bytecode_blocks(g_compiler.first_block);
        g_compiler.first_block = NULL;
        g_compiler.last_block = NULL;
    }
    g_compiler.has_error = FALSE;
}

void compiler_append_plus1s() {
    bytecode_block *block = create_bytecode_block();
    block->instruction = vm_instr_increment;
    if (g_compiler.first_block) {
        link_bytecode_block(g_compiler.last_block, block);
    } else {
        g_compiler.first_block = block;
    }
    g_compiler.last_block = block;
}

void compiler_enter_loop(const char *people_count) {
    bytecode_block *block = create_bytecode_block();
    block->instruction = vm_instr_loop_start;
    block->operands.loop_start.number_of_loop = atoni(people_count);
    if (g_compiler.first_block) {
        link_bytecode_block(g_compiler.last_block, block);
    } else {
        g_compiler.first_block = block;
    }
    g_compiler.last_block = block;
}

void compiler_exit_loop() {
    bytecode_block *block = create_bytecode_block();
    block->instruction = vm_instr_loop_end;
    bytecode_block *loop_start = g_compiler.last_block;
    nint increment_count = 0;
    while (loop_start && loop_start->instruction != vm_instr_loop_start) {
        ++increment_count;
        loop_start = loop_start->prev;
        if (loop_start->instruction == vm_instr_loop_start) {
            loop_start->operands.loop_start.number_of_increment = increment_count;
        }
    }
    link_bytecode_block(g_compiler.last_block, block);
    g_compiler.last_block = block;
}
