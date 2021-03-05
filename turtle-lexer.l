%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "turtle-ast.h"
#include "turtle-parser.h"
%}

%option warn 8bit nodefault noyywrap

COMMENT "#"+.*
DOUBLE ("+"|"-")?[0-9]*"."?[0-9]*(("e"|"E")("+"|"-")?[0-9]*)?

%%

{COMMENT}             /* Comments */
{DOUBLE}              { yylval.value = strtod(yytext, NULL); return VALUE; }
"print"               { return KW_PRINT; }
"forward"             { return KW_FORWARD; }
"fw"                  { return KW_FW; }
"backward"            { return KW_BACKWARD; }
"bw"                  { return KW_BW; }
"position"            { return KW_POSITION; }
"pos"                 { return KW_POS; }
"up"                  { return KW_UP; }
"down"                { return KW_DOWN; }
"right"               { return KW_RIGHT; }
"rt"                  { return KW_RT; }
"left"                { return KW_LEFT; }
"lt"                  { return KW_LT; }
"heading"             { return KW_HEADING; }
"hd"                  { return KW_HD; }
"color"               { return KW_COLOR; }
"home"                { return KW_HOME; }
"PI"                  { yylval.value = strtod("3.14159265358979323846", NULL); return VALUE; }
"SQRT2"               { yylval.value = strtod("1.41421356237309504880", NULL); return VALUE; }
"SQRT3"               { yylval.value = strtod("1.7320508075688772935", NULL); return VALUE; }
[\n\t ]*              /* whitespace */
.                     { fprintf(stderr, "Unknown token: '%s'\n", yytext); exit(EXIT_FAILURE); }

%%
