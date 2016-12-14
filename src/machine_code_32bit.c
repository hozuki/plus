#include "machine_code.h"

#if defined(__ENV_BIT_32__)

/* Function init:
 * push ebp
 * mov  ebp, esp
 * sub  esp, N ; imm32
 *             ; N is the size of all local variables (in bytes) - the stack
 *             ; N is in little endian (e.g. what we want: 0x12345678 -> in memory: 78h 56h 34h 12h)
 */
uint8_t machine_code_function_init[] = {
        0x55,
        0x89, 0xE5,
        0x81, 0xEC, 0x00, 0x00, 0x00, 0x00
};

/* Function return:
 * mov  esp, ebp
 * pop  ebp
 * ret
 */

uint8_t machine_code_function_return[] = {
        0x89, 0xEC,
        0x5D,
        0xC3
};

/**
 * xor eax, eax
 * add eax, N ; imm32
 *            ; N is in little endian
 */
uint8_t machine_code_eax_op[] = {
        0x31, 0xC0,
        0x05, 0x00, 0x00, 0x00, 0x00
};

machine_code_template *init_machine_code_template() {
    g_machine_code.init_code = machine_code_function_init;
    g_machine_code.init_code_len = sizeof(machine_code_function_init);
    g_machine_code.return_code = machine_code_function_return;
    g_machine_code.return_code_len = sizeof(machine_code_function_return);
    g_machine_code.function_call_code = machine_code_eax_op;
    g_machine_code.function_call_code_len = sizeof(machine_code_eax_op);
    return &g_machine_code;
}

#endif
