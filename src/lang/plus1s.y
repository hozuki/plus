%{
#include <stdio.h>
#include "../compiler.h"

extern int yylineno;
extern char *yytext;

#define YYSTYPE char *

void yyerror(const char *str) {
    fprintf(stderr, "error: <%s> at line <%d>, string \"%s\"\n", str, yylineno, yytext);
    compiler_destroy();
}

int yyparse(void);

int yylex(void); 

int yywrap() {
    return 1;
}
%}

%token TOK_PLUS1S TOK_INTEGER TOK_PEOPLE TOK_DO TOK_DONE

%%

program: statement
    | program statement;

statement: plus1s
    | loop;

/* Eliminate ambiguity of loop_body's empty branch */
plus_chain: plus1s
    | plus_chain plus1s;

loop_start: TOK_INTEGER TOK_PEOPLE TOK_DO { compiler_enter_loop($1); };

loop_end: TOK_DONE { compiler_exit_loop(); };

loop: loop_start loop_end /* empty loop */
    | loop_start plus_chain loop_end;

plus1s: TOK_PLUS1S { compiler_append_plus1s(); };
