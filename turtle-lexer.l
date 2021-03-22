%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "turtle-ast.h"
#include "turtle-parser.h"
%}

%option warn 8bit nodefault noyywrap

COMMENT     "#"+.*
DOUBLE      ([1-9]+[0-9]*|(0|[1-9]+[0-9]*)?("."[0-9]+|[1-9]+[0-9]*)(("e"|"E")?[0-9]+)?)|0
VARNAME     [A-Z]([A-Z]|[0-9])*

%%

{COMMENT}               /* Comments */
{DOUBLE}                { yylval.value = strtod(yytext, NULL); return VALUE; }
{VARNAME}               { yylval.name = strtok(yytext, " "); return NAME; }
"print"                 { return KW_PRINT; }
"forward"               { return KW_FORWARD; }
"fw"                    { return KW_FW; }
"backward"              { return KW_BACKWARD; }
"bw"                    { return KW_BW; }
"position"              { return KW_POSITION; }
"pos"                   { return KW_POS; }
"up"                    { return KW_UP; } 
"down"                  { return KW_DOWN; }
"right"                 { return KW_RIGHT; }
"rt"                    { return KW_RT; }
"left"                  { return KW_LEFT; }
"lt"                    { return KW_LT; }
"heading"               { return KW_HEADING; }
"hd"                    { return KW_HD; }
"color"                 { return KW_COLOR; }
"home"                  { return KW_HOME; }
"("                     { return '('; }
")"                     { return ')'; }
"^"                     { return '^'; }
"*"                     { return '*'; }
"/"                     { return '/'; }
"+"                     { return '+'; }
"-"                     { return '-'; }
"{"                     { return '{'; }
"}"                     { return '}'; }
"red"                   { return KW_RED; }
"green"                 { return KW_GREEN; }
"blue"                  { return KW_BLUE; }
"cyan"                  { return KW_CYAN; }
"magenta"               { return KW_MAGENTA; }
"yellow"                { return KW_YELLOW; }
"black"                 { return KW_BLACK; }
"gray"                  { return KW_GRAY; }
"white"                 { return KW_WHITE; }
"sin"                   { return KW_SIN; }
"cos"                   { return KW_COS; }
"tan"                   { return KW_TAN; }
"sqrt"                  { return KW_SQRT; }
"random"                { return KW_RANDOM; }
"set"                   { return KW_SET; }
[\n\t ]*                /* whitespace */
.                       { fprintf(stderr, "Unknown token: '%s'\n", yytext); exit(EXIT_FAILURE); }

%%
