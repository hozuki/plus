#include <stdio.h>
#include <stdlib.h>
#include "plus1s.h"
#include "lang/plus1s.tab.h"

void yyset_in(FILE *_in_str);

int main(int argc, const char *argv[]) {
    machine_code_template *template = init_machine_code_template();
    size_t size = template->init_code_len + template->return_code_len + template->function_call_code_len;
    uint8_t imm[sizeof(nint)] = {0};
    // Any number you like.
    util_nint_to_endian_bytes((nint)12345678, imm, endian_type_little_endian);
    native_code_block *block = create_native_block();
    block->code_as_data = (uint8_t *)malloc(size);
    block->size = size;
    uint8_t *data = block->code_as_data;
    memcpy(data, template->init_code, template->init_code_len);
    memcpy(data + template->init_code_len, template->function_call_code, template->function_call_code_len);
    memcpy(data + template->init_code_len + (template->function_call_code_len - sizeof(imm)), imm, sizeof(imm));
    memcpy(data + template->init_code_len + template->function_call_code_len, template->return_code, template->return_code_len);
    make_native_block_executable(block);
    plus1s_func func = (plus1s_func)block->code_exec;
    nint p = func();
    // Expected output: the number you entered.
    printf("p = %u\n", p);
    destroy_native_block(block);

    FILE *fp = NULL;
    if (argc == 2) {
        fp = fopen(argv[1], "r");
        yyset_in(fp);
        int yy = yyparse(); // 0=success
        printf("Parse result: %d\n", yy);
        fclose(fp);
    }
    return 0;
}
