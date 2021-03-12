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
/* TODO: add other tokens */

%type <node> unit cmds cmd expr

%%

unit:
    cmds              { $$ = $1; ret->unit = $$; }
;

cmds:
    cmd cmds          { $1->next = $2; $$ = $1; }
  | /* empty */       { $$ = NULL; }
;

cmd:
    KW_FORWARD expr   {  $$ = make_cmd_forward($2); }
;

expr:
    VALUE             { $$ = make_expr_value($1); }
    /* TODO: add identifier */
;

%%

void yyerror(struct ast *ret, const char *msg) {
  (void) ret;
  fprintf(stderr, "%s\n", msg);
}
