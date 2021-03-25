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

%token            COLOR       "color_predef"

%token            KW_PRINT    "print"
%token            KW_FORWARD  "forward"
%token            KW_BACKWARD "backward"
%token            KW_POSITION "position"
%token            KW_UP       "up" 
%token            KW_DOWN     "down"
%token            KW_RIGHT    "right"
%token            KW_LEFT     "left"
%token            KW_HEADING  "heading"
%token            KW_COLOR    "color"
%token            KW_HOME     "home"
%token            KW_SET      "set"
%token            KW_REPEAT   "repeat"

%token            KW_PROC     "proc"
%token            KW_CALL     "call"

%token            KW_RED      "red"
%token            KW_GREEN    "green"
%token            KW_BLUE     "blue"
%token            KW_CYAN     "cyan"
%token            KW_MAGENTA  "magenta"
%token            KW_YELLOW   "yellow"
%token            KW_BLACK    "black"
%token            KW_GRAY     "gray"
%token            KW_WHITE    "white"

%token            KW_SIN      "sin"
%token            KW_COS      "cos"
%token            KW_TAN      "tan"
%token            KW_SQRT     "sqrt"
%token            KW_RANDOM   "random"

%type <node> unit cmds cmd expr

%precedence NEG
%right '^'
%left '*' '/'
%left '+' '-'

%%

unit:
    cmds              { $$ = $1; ret->unit = $$; }
;

cmds:
    cmd cmds          { $1->next = $2; $$ = $1; }
  | /* empty */       { $$ = NULL; }
;

cmd:
    KW_FORWARD expr     {  $$ = make_cmd_forward($2);  }
  | KW_BACKWARD expr    {  $$ = make_cmd_backward($2);  }
  | KW_POSITION expr','expr    {  $$ = make_cmd_position($2, $4);  }
  | KW_UP               {  $$ = make_cmd_up();  }
  | KW_DOWN             {  $$ = make_cmd_down();  }
  | KW_RIGHT expr       {  $$ = make_cmd_right($2);  }
  | KW_LEFT expr        {  $$ = make_cmd_left($2);  }
  | KW_HEADING expr     {  $$ = make_cmd_heading($2);  }
  | KW_COLOR KW_RED     {  $$ = make_cmd_color(make_expr_value(1), make_expr_value(0), make_expr_value(0));  }
  | KW_COLOR KW_GREEN   {  $$ = make_cmd_color(make_expr_value(0), make_expr_value(1), make_expr_value(0));  }
  | KW_COLOR KW_BLUE    {  $$ = make_cmd_color(make_expr_value(0), make_expr_value(0), make_expr_value(1));  }
  | KW_COLOR KW_CYAN    {  $$ = make_cmd_color(make_expr_value(0), make_expr_value(1), make_expr_value(1));  }
  | KW_COLOR KW_MAGENTA {  $$ = make_cmd_color(make_expr_value(1), make_expr_value(0), make_expr_value(1));  }
  | KW_COLOR KW_YELLOW  {  $$ = make_cmd_color(make_expr_value(1), make_expr_value(1), make_expr_value(0));  }
  | KW_COLOR KW_BLACK   {  $$ = make_cmd_color(make_expr_value(0), make_expr_value(0), make_expr_value(0));  }
  | KW_COLOR KW_GRAY    {  $$ = make_cmd_color(make_expr_value(0.5), make_expr_value(0.5), make_expr_value(0.5));  }
  | KW_COLOR KW_WHITE   {  $$ = make_cmd_color(make_expr_value(1), make_expr_value(1), make_expr_value(1));  }
  | KW_COLOR expr','expr','expr       {  $$ = make_cmd_color($2, $4, $6);  }
  | KW_HOME expr        {  $$ = make_cmd_home($2);  }
  | KW_PRINT expr       {  $$ = make_cmd_print($2);  }
  | KW_SET expr','expr    {  $$ = make_cmd_set($2, $4);  }
  | KW_REPEAT expr cmd  {  $$ = make_cmd_repeat($2, $3);  }
  | '{' cmd cmds '}'    {  $$ = make_cmd_block($2, $3);  }
  | KW_PROC expr cmd    {  $$ = make_proc($2, $3);  }
  | KW_CALL expr        {  $$ = make_proc_call($2);  }
;

expr:
    VALUE               { $$ = make_expr_value($1); }
    | NAME              { $$ = make_name_value($1); }
    | '(' expr ')'      { $$ = $2; }
    | '-' expr %prec NEG     { $$ = make_unop($2, '-'); }
    | expr '/' expr     { $$ = make_binop($1, $3, '/'); }
    | expr '*' expr     { $$ = make_binop($1, $3, '*'); }
    | expr '^' expr     { $$ = make_binop($1, $3, '^'); }
    | expr '+' expr     { $$ = make_binop($1, $3, '+'); }
    | expr '-' expr     { $$ = make_binop($1, $3, '-'); }
    | KW_SIN '(' expr ')'      { $$ = make_intern_expr($3, "sin"); }
    | KW_COS '(' expr ')'      { $$ = make_intern_expr($3, "cos"); }
    | KW_TAN '(' expr ')'      { $$ = make_intern_expr($3, "tan"); } 
    | KW_SQRT '(' expr ')'      { $$ = make_intern_expr($3, "sqrt"); }
    | KW_RANDOM '('expr','expr')'   { $$ = make_intern_expr_rd($3, $5); }
;

%%

void yyerror(struct ast *ret, const char *msg) {
  (void) ret;
  fprintf(stderr, "%s\n", msg);
}
