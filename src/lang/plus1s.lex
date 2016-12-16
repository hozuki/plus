%{
#include <stdio.h>
#include "plus1s.tab.h"

#define ECHO printf("Reading: [%s]\n", yytext)
%}

plus1s              \+1s
integer             [1-9][0-9]*
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
{integer}               {ECHO; return TOK_INTEGER;}
{people}                {ECHO; return TOK_PEOPLE;}
{do}                    {ECHO; return TOK_DO;}
{done}                  {ECHO; return TOK_DONE;}
.                       {printf("Unexpected: %s\n", yytext);}
%%
