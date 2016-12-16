%{
#include <stdio.h>

extern int yylineno;
extern char *yytext;

void yyerror(const char *str) {
    fprintf(stderr, "error: <%s> at line <%d>, string \"%s\"\n", str, yylineno, yytext);
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

loop_body:
    | plus_chain;

loop: TOK_INTEGER TOK_PEOPLE TOK_DO loop_body TOK_DONE;

plus1s: TOK_PLUS1S;
