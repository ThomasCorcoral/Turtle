%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "turtle-ast.h"
#include "turtle-parser.h"
%}

%option warn 8bit nodefault noyywrap

DIGIT [0-9]

%%

{DIGIT}+              { yylval.value = strtod(yytext, NULL); return VALUE; }
"forward"             { return KW_FORWARD; }
"fw"             { return KW_FORWARD; }
[\n\t ]*              /* whitespace */
.                     { fprintf(stderr, "Unknown token: '%s'\n", yytext); exit(EXIT_FAILURE); }

%%
