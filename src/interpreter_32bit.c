#include <malloc.h>
#include <stdio.h>
#include "interpreter.h"
#include "types.h"

#if defined(__ENV_BIT_32__)

size_t interpreter_compute_machine_code_length() {
    size_t len = g_machine_code.init_code_len + g_machine_code.return_code_len;
    bytecode_block *block = g_compiler.first_block;
    while (block) {
        switch (block->instruction) {
            case vm_instr_increment:
                len += g_machine_code.increment_code_len;
                break;
            case vm_instr_loop_start:
                // Naive optimization.
                if (block->operands.loop_start.number_of_increment == 0 || block->operands.loop_start.number_of_loop == 0) {
                    while (block->instruction != vm_instr_loop_end) {
                        block = block->next;
                    }
                    break;
                }
                len += g_machine_code.loop_begin_code_len;
                break;
            case vm_instr_loop_end:
                len += g_machine_code.loop_end_code_len;
                break;
            default:
                break;
        }
        block = block->next;
    }
    return len;
}

native_code_block *interpreter_generate_machine_code() {
    native_code_block *native = create_native_block();
    native->size = interpreter_compute_machine_code_length();
    if (native->size == 0) {
        return native;
    }

    alloc_page_for_native_block(native);
    memset(native->code_as_data, 0, native->size);

    size_t loop_begin_address = 0;
    size_t current_offset = 0;
    memcpy(native->code_as_data + current_offset, g_machine_code.init_code, g_machine_code.init_code_len);
    current_offset += g_machine_code.init_code_len;
    bytecode_block *bytecode = g_compiler.first_block;
    uint8_t nint_buffer[sizeof(nint)] = {0};
    while (bytecode) {
        nint address_offset;
        switch (bytecode->instruction) {
            case vm_instr_increment:
                memcpy(native->code_as_data + current_offset, g_machine_code.increment_code, g_machine_code.increment_code_len);
                current_offset += g_machine_code.increment_code_len;
                break;
            case vm_instr_loop_start:
                if (bytecode->operands.loop_start.number_of_increment == 0 || bytecode->operands.loop_start.number_of_loop == 0) {
                    while (bytecode->instruction != vm_instr_loop_end) {
                        bytecode = bytecode->next;
                    }
                    break;
                }
                memcpy(native->code_as_data + current_offset, g_machine_code.loop_begin_code, g_machine_code.loop_begin_code_len);
                util_nint_to_endian_bytes(bytecode->operands.loop_start.number_of_loop, nint_buffer, endian_type_little_endian);
                memcpy(native->code_as_data + current_offset + 0x1, nint_buffer, sizeof(nint));
                current_offset += g_machine_code.loop_begin_code_len;
                loop_begin_address = current_offset;
                break;
            case vm_instr_loop_end:
                // potential overflow (uintptr_t -> nint) bug
                address_offset = (nint)loop_begin_address - (nint)(current_offset + 0x0a);
                memcpy(native->code_as_data + current_offset, g_machine_code.loop_end_code, g_machine_code.loop_end_code_len);
                util_nint_to_endian_bytes(address_offset, nint_buffer, endian_type_little_endian);
                memcpy(native->code_as_data + current_offset + 0x6, nint_buffer, sizeof(nint));
                current_offset += g_machine_code.loop_end_code_len;
                loop_begin_address = 0;
                break;
            default:
                break;
        }
        bytecode = bytecode->next;
    }
    memcpy(native->code_as_data + current_offset, g_machine_code.return_code, g_machine_code.return_code_len);
    current_offset += g_machine_code.return_code_len;

    printf("Code data: ");
    for (int i = 0; i < native->size; ++i) {
        printf("%02x ", ((uint32_t)native->code_as_data[i] & 0xff));
    }
    printf("\n");

    make_native_block_executable(native);
    return native;
}

#endif
