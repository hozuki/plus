#include "machine_code.h"

#if defined(__ENV_BIT_32__)

/* Function init:
 * push ebp
 * mov  ebp, esp
 * sub  esp, N ; imm32
 *             ; N is the size of all local variables (in bytes) - the stack
 *             ; N is in little endian (e.g. what we want: 0x12345678 -> in memory: 78h 56h 34h 12h)
 * push ecx ; store the loop counter
 * xor  eax, eax
 */
uint8_t machine_code_function_init[] = {
        0x55,
        0x89, 0xE5,
        0x81, 0xEC, 0x00, 0x00, 0x00, 0x00,
        0x51,
        0x31, 0xC0
};

/* Function return:
 * pop  ecx
 * mov  esp, ebp
 * pop  ebp
 * ret
 */

uint8_t machine_code_function_return[] = {
        0x59,
        0x89, 0xEC,
        0x5D,
        0xC3
};

/**
 * mov  ecx, N ; N is the number of loops, in little endian
 */
uint8_t machine_code_loop_begin[] = {
        0xB9, 0x00, 0x00, 0x00, 0x00
};

/**
 * dec  ecx
 * cmp  ecx, 0
 * jg   N ; N = offset (32-bit signed), in little endian
 */
uint8_t machine_code_loop_end[] = {
        0x49,
        0x83, 0xF9, 0x00,
        0x0F, 0x8F, 0x00, 0x00, 0x00, 0x00
};

/**
 * inc  eax
 */
uint8_t machine_code_increment[] = {
        0x40
};

machine_code_template *init_machine_code_template() {
    g_machine_code.init_code = machine_code_function_init;
    g_machine_code.init_code_len = sizeof(machine_code_function_init);
    g_machine_code.return_code = machine_code_function_return;
    g_machine_code.return_code_len = sizeof(machine_code_function_return);
    g_machine_code.loop_begin_code = machine_code_loop_begin;
    g_machine_code.loop_begin_code_len = sizeof(machine_code_loop_begin);
    g_machine_code.loop_end_code = machine_code_loop_end;
    g_machine_code.loop_end_code_len = sizeof(machine_code_loop_end);
    g_machine_code.increment_code = machine_code_increment;
    g_machine_code.increment_code_len = sizeof(machine_code_increment);
    return &g_machine_code;
}

#endif
