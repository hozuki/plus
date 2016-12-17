%{
#include <stdio.h>
#include <stdlib.h>

#define YYSTYPE char *
#include "plus1s.tab.h"

#define PRINT_TOKENS 0

#if PRINT_TOKENS
#define ECHO printf("Reading: [%s]\n", yytext)
#else
#define ECHO
#endif
%}

plus1s              \+1s
integer             [0-9]+
people              people
do                  do
done                done
blank               [ \t]+
new_line            (\r\n|[\r]|[\n])
line_comment        \/\/[^\r\n]*

%%
{blank}
{line_comment}          {ECHO;}
{new_line}              {++yylineno;}
{plus1s}                {ECHO; return TOK_PLUS1S;}
{integer}               {ECHO; yylval = strdup(yytext); return TOK_INTEGER;}
{people}                {ECHO; return TOK_PEOPLE;}
{do}                    {ECHO; return TOK_DO;}
{done}                  {ECHO; return TOK_DONE;}
.                       {printf("Unexpected \"%s\" at line <%d>\n", yytext, yylineno); exit(EXIT_FAILURE);}
%%
