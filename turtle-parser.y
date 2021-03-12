%{
#include <stdio.h>

#include "turtle-ast.h"

int yylex();
void yyerror(struct ast *ret, const char *);

%}

%debug
%defines

%define parse.error verbose

%parse-param { struct ast *ret }

%union {
  double value;
  char *name;
  struct ast_node *node;
}

%token <value>    VALUE       "value"
%token <name>     NAME        "name"

%token            KW_PRINT    "print"
%token            KW_FORWARD  "forward"
%token            KW_FW       "fw"
%token            KW_BACKWARD "backward"
%token            KW_BW       "bw"
%token            KW_POSITION "position"
%token            KW_POS      "pos"
%token            KW_UP       "up" 
%token            KW_DOWN     "down"
%token            KW_RIGHT    "right"
%token            KW_RT       "rt"
%token            KW_LEFT     "left"
%token            KW_LT       "lt"
%token            KW_HEADING  "heading"
%token            KW_HD       "hd"
%token            KW_COLOR    "color"
%token            KW_HOME     "home"

%type <node> unit cmds cmd expr

%left '+' '-'
%left '*' '/'

%%

unit:
    cmds              { $$ = $1; ret->unit = $$; }
;

cmds:
    cmd cmds          { $1->next = $2; $$ = $1; }
  | /* empty */       { $$ = NULL; }
;

cmd:
    KW_FORWARD expr     {  $$ = make_cmd_forward($2); }
  | KW_FW expr          {  $$ = make_cmd_forward($2); }
  | KW_BACKWARD expr    {  $$ = make_cmd_backward($2); }
  | KW_BW expr          {  $$ = make_cmd_backward($2); }
  | KW_POSITION expr    {  $$ = make_cmd_position($2); }
  | KW_POS expr         {  $$ = make_cmd_position($2); }
  | KW_UP expr          {  $$ = make_cmd_up($2); }
  | KW_DOWN expr        {  $$ = make_cmd_down($2); }
  | KW_RIGHT expr       {  $$ = make_cmd_right($2); }
  | KW_RT expr          {  $$ = make_cmd_right($2); }
  | KW_LEFT expr        {  $$ = make_cmd_left($2); }
  | KW_LT expr          {  $$ = make_cmd_left($2); }
  | KW_HEADING expr     {  $$ = make_cmd_heading($2); }
  | KW_HD expr          {  $$ = make_cmd_heading($2); }
  | KW_COLOR expr       {  $$ = make_cmd_color($2); }
  | KW_HOME expr        {  $$ = make_cmd_home($2); }
  | KW_PRINT expr       {  $$ = make_cmd_print($2); }
;

expr:
    VALUE               { $$ = make_expr_value($1); }
    | expr '+' expr     { $$ = $1 + $3; }
    | expr '-' expr     { $$ = $1 - $3; }
    | expr '*' expr     { $$ = $1 * $3; }
    | expr '/' expr     { $$ = $1 / $3; }
    | expr '^' expr     { $$ = $1 ^ $3; }
    | '('expr')'        { $$ = $2; }
    /* TODO: add identifier */
;

%%

void yyerror(struct ast *ret, const char *msg) {
  (void) ret;
  fprintf(stderr, "%s\n", msg);
}
