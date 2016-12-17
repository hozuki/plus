#pragma once

#include "plus1s.h"

native_code_block *create_native_block();

native_code_block *alloc_page_for_native_block(native_code_block *block);

void destroy_native_block(native_code_block *block);

void destroy_all_native_blocks(native_code_block *start);

void link_native_block(native_code_block *this, native_code_block *next);

void *make_native_block_executable(native_code_block *block);

bytecode_block *create_bytecode_block();

void destroy_bytecode_block(bytecode_block *block);

void destroy_all_bytecode_blocks(bytecode_block *start);

void link_bytecode_block(bytecode_block *this, bytecode_block *next);
