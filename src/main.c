#include <stdio.h>
#include <inttypes.h>
#include "plus1s.h"
#include "lang/plus1s.tab.h"

#define PRINT_PROGRAM_INSTRUCTIONS 0

void yyset_in(FILE *_in_str);

void print_help();

int main(int argc, const char *argv[]) {
    if (argc != 2) {
        print_help();
        return 0;
    }

    FILE *fp = NULL;
    fp = fopen(argv[1], "r");
    yyset_in(fp);
    compiler_init();
    init_machine_code_template();

    int yy = yyparse();
    fclose(fp);

    if (yy != 0) {
        printf("An error occurred during compiling. Exiting...\n");
        return yy;
    }

    native_code_block *native = interpreter_generate_machine_code();
    plus1s_func func = (plus1s_func)native->code_exec;
    if (func) {
        // Execute our generated function!
        nint seconds = func();
        printf("Crowdfunded %" PRIiN " seconds.\n", seconds);
    } else {
        printf("Failed to crowdfund time...\n");
    }
    destroy_native_block(native);

#if PRINT_PROGRAM_INSTRUCTIONS
    bytecode_block *bytecode = g_compiler.first_block;
    while (bytecode) {
        printf("instr: ");
        switch (bytecode->instruction) {
            case vm_instr_increment:
                printf("increment");
                break;
            case vm_instr_loop_start:
                printf("loop start (with %" PRIiN " increments)", bytecode->operands.loop_start.number_of_increment);
                break;
            case vm_instr_loop_end:
                printf("loop end");
                break;
            default:
                printf("unknown");
                break;
        }
        printf("\n");
        bytecode = bytecode->next;
    }
#endif
    compiler_destroy();

    return yy;
}

void print_help() {
    printf("Usage: plus1s <source>\n");
}
