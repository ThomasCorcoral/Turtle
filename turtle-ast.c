#include "turtle-ast.h"

#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define PI 3.141592653589793

struct ast_node *make_expr_value(double value) {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_EXPR_VALUE;
  node->u.value = value;
  return node;
}

struct ast_node *make_binop(struct ast_node *left, struct ast_node *right, char c) {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_EXPR_BINOP;
  // node->u.value = value;
  node->u.op = c;
  node->children_count = 2;
  node->children[0] = left;
  node->children[1] = right;
  return node;
}

struct ast_node *make_unop(struct ast_node *right, char c) {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_EXPR_UNOP;
  // node->u.value = value;
  node->u.op = c; 
  node->children_count =2;
  node->children[0] = 0;
  node->children[1] = right;
  return node;
}

struct ast_node *make_cmd_backward(struct ast_node *expr) {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_SIMPLE;
  node->u.cmd = CMD_BACKWARD;
  node->children_count = 1;
  node->children[0] = expr;
  return node;
}

struct ast_node *make_cmd_forward(struct ast_node *expr) {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_SIMPLE;
  node->u.cmd = CMD_FORWARD;
  node->children_count = 1;
  node->children[0] = expr;
  return node;
}

struct ast_node *make_cmd_position(struct ast_node *expr) {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_SIMPLE;
  node->u.cmd = CMD_POSITION;
  node->children_count = 1;
  node->children[0] = expr;
  return node;
}

struct ast_node *make_cmd_up(struct ast_node *expr) {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_SIMPLE;
  node->u.cmd = CMD_UP;
  node->children_count = 1;
  node->children[0] = expr;
  return node;
}

struct ast_node *make_cmd_down(struct ast_node *expr) {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_SIMPLE;
  node->u.cmd = CMD_DOWN;
  node->children_count = 1;
  node->children[0] = expr;
  return node;
}

struct ast_node *make_cmd_right(struct ast_node *expr) {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_SIMPLE;
  node->u.cmd = CMD_RIGHT;
  node->children_count = 1;
  node->children[0] = expr;
  return node;
}

struct ast_node *make_cmd_left(struct ast_node *expr) {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_SIMPLE;
  node->u.cmd = CMD_LEFT;
  node->children_count = 1;
  node->children[0] = expr;
  return node;
}

struct ast_node *make_cmd_heading(struct ast_node *expr) {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_SIMPLE;
  node->u.cmd = CMD_HEADING;
  node->children_count = 1;
  node->children[0] = expr;
  return node;
}

struct ast_node *make_cmd_color(struct ast_node *expr, struct ast_node *expr2, struct ast_node *expr3) {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_SIMPLE;
  node->u.cmd = CMD_COLOR;
  node->children_count = 3;
  node->children[0] = expr;
  node->children[1] = expr2;
  node->children[2] = expr3;
  return node;
}

struct ast_node *make_cmd_home(struct ast_node *expr) {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_SIMPLE;
  node->u.cmd = CMD_HOME;
  node->children_count = 1;
  node->children[0] = expr;
  return node;
}

struct ast_node *make_cmd_print(struct ast_node *expr) {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_SIMPLE;
  node->u.cmd = CMD_PRINT;
  node->children_count = 1;
  node->children[0] = expr;
  return node;
}

struct ast_node *make_intern_expr(struct ast_node *expr, char* func){
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_EXPR_FUNC;
  if(strcmp(func, "sin") == 0){
    node->u.func = FUNC_SIN;
  }else if(strcmp(func, "cos") == 0){
    node->u.func = FUNC_COS;
  }else if(strcmp(func, "tan") == 0){
    node->u.func = FUNC_TAN;
  }else if(strcmp(func, "sqrt") == 0){
    node->u.func = FUNC_SQRT;
  }else{
    node->u.func = FUNC_RANDOM;
  }
  node->children_count = 1;
  node->children[0] = expr;
  return node;
}

/*
 * destroy
 */

void ast_destroy(struct ast *self) {
  ast_node_destroy(self->unit);
}

void ast_node_destroy(struct ast_node *self){
  self->kind = 0;
  self->u.cmd = 0;
  self->u.func = 0;
  self->u.name = "";
  self->u.op = '\0';
  self->u.value = 0;
  for(size_t i = 0; i<self->children_count; i++){
    ast_node_destroy(self->children[i]);
  }
  self->children_count = 0;
  if(self->next != NULL){
    ast_node_destroy(self->next);
  }
  free(self);
}

/*
 * context
 */

void context_create(struct context *self) {
  self->x = 0;
  self->y = 0;
  self->up = false;
  self->angle = 0;
  self->col.r = 0; 
  self->col.b = 0;
  self->col.g = 0;
}

/*
 * eval
 */
void cmd_simple_eval(const struct ast_node *self, struct context *ctx){
  switch (self->u.cmd){
    case CMD_UP:
      ctx->up = true;
      break;
    case CMD_DOWN:
      ctx->up = false;
      break;
    case CMD_RIGHT:
      ctx->angle = (int)(ctx->angle + eval_expr(self->children[0])) % 360;
      break;
    case CMD_LEFT:
      ctx->angle = (int)(ctx->angle - eval_expr(self->children[0])) % 360;
      break;
    case CMD_HEADING:
      ctx->angle = eval_expr(self->children[0]);
      break;
    case CMD_FORWARD:
    {
      float eval = eval_expr(self->children[0]);
      ctx->x = ctx->x + cos(ctx->angle * (PI/180)) * eval;
      ctx->y = ctx->y + sin(ctx->angle * (PI/180)) * eval;
      if(!ctx->up){
        fprintf(stdout, "LineTo %f %f\n", ctx->x, ctx->y);
      }else{
        fprintf(stdout, "MoveTo %f %f\n", ctx->x, ctx->y);
      }
      break;
    }
    case CMD_BACKWARD:
    {
      float eval = eval_expr(self->children[0]);
      ctx->x = ctx->x - cos(ctx->angle * (PI/180)) * eval;
      ctx->y = ctx->y - sin(ctx->angle * (PI/180)) * eval;
      if(!ctx->up){
        fprintf(stdout, "LineTo %f %f\n", ctx->x, ctx->y);
      }else{
        fprintf(stdout, "MoveTo %f %f\n", ctx->x, ctx->y);
      }
      break;
    }
    case CMD_POSITION:
      ctx->x = eval_expr(self->children[0]);
      ctx->y = eval_expr(self->children[1]);
      fprintf(stdout, "MoveTo %f %f\n", ctx->x, ctx->y);
      break;
    case CMD_HOME:
      context_create(ctx);
      fprintf(stdout, "MoveTo %f %f\n", ctx->x, ctx->y);
      fprintf(stdout, "Colro %f %f %f\n", ctx->col.r, ctx->col.g, ctx->col.b);
      break;
    case CMD_COLOR:
    {
      ctx->col.r = eval_expr(self->children[0]); 
      ctx->col.g = eval_expr(self->children[1]);
      ctx->col.b = eval_expr(self->children[2]);
      fprintf(stdout, "Color %f %f %f\n", ctx->col.r, ctx->col.g, ctx->col.b);
      break;
    }
    case CMD_PRINT:
    {
      fprintf(stderr, "%f\n", eval_expr(self->children[0]));
      break;
    }
  }
}

float eval_expr(const struct ast_node *self){
  switch(self->kind){
    case KIND_EXPR_FUNC: 
      switch (self->u.func)
      {
      case FUNC_COS:
        return cos(eval_expr(self->children[0]) * (PI/180));
      case FUNC_RANDOM:
        return rand() * eval_expr(self->children[0]);
      case FUNC_SIN:
        return sin(eval_expr(self->children[0]) * (PI/180));
      case FUNC_SQRT:
        return sqrt(eval_expr(self->children[0]));
      case FUNC_TAN:
        return tan(eval_expr(self->children[0]) * (PI/180));
      }
    case KIND_EXPR_VALUE: 
      return self->u.value;
    case KIND_EXPR_UNOP:
      return -eval_expr(self->children[0]);
    case KIND_EXPR_BINOP:
    {
      float first = eval_expr(self->children[0]);
      float second = eval_expr(self->children[1]); 
      switch(self->u.op){
        case '*':
          return first * second;
        case '/':
          return first / second;
        case '+':
          return first + second;
        case '-':
          return first - second;
        case '^':
          return pow(first, second);
      }
    }
    case KIND_EXPR_BLOCK: break;
    case KIND_EXPR_NAME: break;
    default:
      break;
  }
  return 0;
}

void ast_node_eval(const struct ast_node *self, struct context *ctx) {
  switch(self->kind){
    case KIND_CMD_SIMPLE: 
      cmd_simple_eval(self, ctx);
      break;
    case KIND_CMD_REPEAT: break;
    case KIND_CMD_BLOCK: break;
    case KIND_CMD_PROC: break;
    case KIND_CMD_CALL: break;
    case KIND_CMD_SET: break;
    default:
      break;
  }
  if(self->next != NULL){
    ast_node_eval(self->next, ctx);
  }
}

void ast_eval(const struct ast *self, struct context *ctx) {
  ast_node_eval(self->unit, ctx);
}

/*
 * print
 */

void cmd_simple_eval_print(const struct ast_node *self){
  switch (self->u.cmd){
    case CMD_UP:
      fprintf(stderr, "CMD_UP, put up to true\n");
      break;
    case CMD_DOWN:
      fprintf(stderr, "CMD_DOWN, put up to false\n");
      break;
    case CMD_RIGHT:
      fprintf(stderr, "CMD_RIGHT, turn angle to right add %f\n", eval_expr(self->children[0]));
      break;
    case CMD_LEFT:
      fprintf(stderr, "CMD_LEFT, turn angle to left substract %f\n", eval_expr(self->children[0]));
      break;
    case CMD_HEADING:
      fprintf(stderr, "CMD_HEADING, put the angle to the value : %f\n", eval_expr(self->children[0]));
      break;
    case CMD_FORWARD:
      fprintf(stderr, "CMD_FORWARD, forward with value : %f\n", eval_expr(self->children[0]));
      break;
    case CMD_BACKWARD:
      fprintf(stderr, "CMD_BACKWARD, backward with value : %f\n", eval_expr(self->children[0]));
      break;
    case CMD_POSITION:
      fprintf(stderr, "CMD_POSITION, set new position x : %f / y : %f\n", eval_expr(self->children[0]), eval_expr(self->children[1]));
      break;
    case CMD_HOME:
      fprintf(stderr, "CMD_HOME, reinitialise context\n");
      break;
    case CMD_COLOR:
      fprintf(stderr, "CMD_COLOR, new color : %f, %f, %f\n", eval_expr(self->children[0]), eval_expr(self->children[1]), eval_expr(self->children[2]));
      break;
    case CMD_PRINT:
      fprintf(stderr, "CMD_PRINT, print : %f\n", eval_expr(self->children[0]));
      break;
  }
}

void ast_node_print(const struct ast_node *self) {
  switch(self->kind){
    case KIND_CMD_SIMPLE: 
      cmd_simple_eval_print(self);
      break;
    case KIND_CMD_REPEAT: 
      fprintf(stderr, "KIND_CMD_REPEAT\n");
      break;
    case KIND_CMD_BLOCK: 
      fprintf(stderr, "KIND_CMD_BLOCK\n");
      break;
    case KIND_CMD_PROC:  
      fprintf(stderr, "KIND_CMD_PROC\n");
      break;
    case KIND_CMD_CALL:  
      fprintf(stderr, "KIND_CMD_CALL\n");
      break;
    case KIND_CMD_SET:  
      fprintf(stderr, "KIND_CMD_SET\n");
      break;
    default:
      break;
  }
  if(self->next != NULL){
    ast_node_print(self->next);
  }
}

void ast_print(const struct ast *self) {
  ast_node_print(self->unit);
}
