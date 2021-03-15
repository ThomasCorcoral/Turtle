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

struct ast_node *make_cmd_color(struct ast_node *expr) {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_SIMPLE;
  node->u.cmd = CMD_COLOR;
  node->children_count = 1;
  node->children[0] = expr;
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

/*
 * destroy
 */

void ast_destroy(struct ast *self) {
  ast_node_destroy(self->unit);
  free(self->unit);
}

void ast_node_destroy(struct ast_node *self){
  self->kind = 0;
  self->u.cmd = 0;
  self->u.func = 0;
  if(self->u.name != NULL){
    free(self->u.name);
  }
  self->u.op = '\0';
  self->u.value = 0;
  if(self->children != NULL){
    for(size_t i = 0; i<self->children_count; i++){
      ast_node_destroy(self->children[i]);
    }
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
    if(ctx->angle >= 270 || ctx->angle <= 90){
      ctx->angle = (ctx->angle + self->u.value) % 360;
    }else{
      ctx->angle = (ctx->angle - self->u.value) % 360;
    }
    break;
  case CMD_LEFT:
    /* code */
    break;
  case CMD_HEADING:
    /* code */
    break;
  case CMD_FORWARD:
    /* code */
    break;
  case CMD_BACKWARD:
    /* code */
    break;
  case CMD_POSITION:
    /* code */
    break;
  case CMD_HOME:
    /* code */
    break;
  case CMD_COLOR:
    /* code */
    break;
  case CMD_PRINT:
    /* code */
    break;
  }
}

void ast_eval(const struct ast *self, struct context *ctx) {
  switch(self->unit->kind){
    case KIND_CMD_SIMPLE: break;
    case KIND_CMD_REPEAT: break;
    case KIND_CMD_BLOCK: break;
    case KIND_CMD_PROC: break;
    case KIND_CMD_CALL: break;
    case KIND_CMD_SET: break;
    case KIND_EXPR_FUNC: break;
    case KIND_EXPR_VALUE: break;
    case KIND_EXPR_UNOP: break;
    case KIND_EXPR_BINOP: break;
    case KIND_EXPR_BLOCK: break;
    case KIND_EXPR_NAME: break;
  }
}

/*
 * print
 */

void ast_print(const struct ast *self) {
  
}
