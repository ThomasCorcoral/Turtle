#include "turtle-ast.h"

#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define PI 3.14159265358979323846

struct ast_node *make_expr_value(double value) {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_EXPR_VALUE;
  node->u.value = value;
  return node;
}

struct ast_node *make_name_value(char* value){
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_EXPR_NAME;
  char* copy = calloc(strlen(value)+1, sizeof(char)); 
  strcpy(copy, value);
  node->u.name = copy;
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
  node->u.op = c; 
  node->children_count = 1;
  node->children[0] = right;
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

struct ast_node *make_cmd_position(struct ast_node *expr, struct ast_node *expr2) {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_SIMPLE;
  node->u.cmd = CMD_POSITION;
  node->children_count = 2;
  node->children[0] = expr;
  node->children[1] = expr2;
  return node;
}

struct ast_node *make_cmd_up() {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_SIMPLE;
  node->u.cmd = CMD_UP;
  node->children_count = 0;
  return node;
}

struct ast_node *make_cmd_down() {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_SIMPLE;
  node->u.cmd = CMD_DOWN;
  node->children_count = 0;
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

struct ast_node *make_cmd_set(struct ast_node *name, struct ast_node *expr){
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_SET;
  node->children_count = 2;
  node->children[0] = name;
  node->children[1] = expr;
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
  }
  node->children_count = 1;
  node->children[0] = expr;
  return node;
}

struct ast_node *make_intern_expr_rd(struct ast_node *expr, struct ast_node *expr2){
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_EXPR_FUNC;
  node->u.func = FUNC_RANDOM;
  node->children_count = 2;
  node->children[0] = expr;
  node->children[1] = expr2;
  return node;
}

struct ast_node *make_cmd_repeat(struct ast_node *expr, struct ast_node *fct){
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_REPEAT;
  node->children_count = 2;
  node->children[0] = expr;
  node->children[1] = fct;
  return node;
}

struct ast_node *make_cmd_block(struct ast_node *fct, struct ast_node *fcts){
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_EXPR_BLOCK;
  node->children_count = 2;
  node->children[0] = fct;
  node->children[1] = fcts;
  return node;
}

struct ast_node *make_proc(struct ast_node *name, struct ast_node *block){
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_PROC;
  node->children_count = 2;
  node->children[0] = name;
  node->children[1] = block;
  return node;
}

struct ast_node *make_proc_call(struct ast_node *name){
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_CALL;
  node->children_count = 1;
  node->children[0] = name;
  return node;
}

/*
 * destroy
 */

void ast_destroy(struct ast *self) {
  ast_node_destroy(self->unit);
}

void ast_node_destroy(struct ast_node *self){
  if(self->kind == KIND_EXPR_NAME){
    free(self->u.name);
  }
  self->u.cmd = 0;
  self->u.func = 0;
  self->kind = 0;
  self->u.op = '\0';
  self->u.value = 0;
  for(size_t i = 0; i<self->children_count; i++){
    if(self->children[i] != NULL){
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
  map_create(&(self->variables_map));
  map_add(&(self->variables_map), "PI", 3.14159265358979323846);
  map_add(&(self->variables_map), "SQRT2", 1.41421356237309504880);
  map_add(&(self->variables_map), "SQRT3", 1.7320508075688772935);
  map_proc_create(&(self->proc_map));
}

void context_destroy(struct context *self){
  self->x = 0;
  self->y = 0;
  self->up = false;
  self->angle = 0;
  self->col.r = 0; 
  self->col.b = 0;
  self->col.g = 0;
  map_destroy(&(self->variables_map));
  map_proc_destroy(&(self->proc_map));
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
      ctx->angle = (int)(ctx->angle + eval_expr(self->children[0], ctx)) % 360;
      break;
    case CMD_LEFT:
      ctx->angle = (int)(ctx->angle - eval_expr(self->children[0], ctx)) % 360;
      break;
    case CMD_HEADING:
      ctx->angle = eval_expr(self->children[0], ctx);
      break;
    case CMD_FORWARD:
    {
      float eval = eval_expr(self->children[0], ctx);
      ctx->x = ctx->x + cos(((int)(ctx->angle - 90) % 360) * (PI/180)) * eval;
      ctx->y = ctx->y + sin(((int)(ctx->angle - 90) % 360) * (PI/180)) * eval;
      if(!ctx->up){
        fprintf(stdout, "LineTo %f %f\n", ctx->x, ctx->y);
      }else{
        fprintf(stdout, "MoveTo %f %f\n", ctx->x, ctx->y);
      }
      break;
    }
    case CMD_BACKWARD:
    {
      float eval = eval_expr(self->children[0], ctx);
      ctx->x = ctx->x - cos(((int)(ctx->angle - 90) % 360) * (PI/180)) * eval;
      ctx->y = ctx->y - sin(((int)(ctx->angle - 90) % 360) * (PI/180)) * eval;
      if(!ctx->up){
        fprintf(stdout, "LineTo %f %f\n", ctx->x, ctx->y);
      }else{
        fprintf(stdout, "MoveTo %f %f\n", ctx->x, ctx->y);
      }
      break;
    }
    case CMD_POSITION:
      ctx->x = eval_expr(self->children[0], ctx);
      ctx->y = eval_expr(self->children[1], ctx);
      fprintf(stdout, "MoveTo %f %f\n", ctx->x, ctx->y);
      break;
    case CMD_HOME:
      context_create(ctx);
      fprintf(stdout, "MoveTo %f %f\n", ctx->x, ctx->y);
      fprintf(stdout, "Color %f %f %f\n", ctx->col.r, ctx->col.g, ctx->col.b);
      break;
    case CMD_COLOR:
    {
      ctx->col.r = eval_expr(self->children[0], ctx); 
      ctx->col.g = eval_expr(self->children[1], ctx);
      ctx->col.b = eval_expr(self->children[2], ctx);
      fprintf(stdout, "Color %f %f %f\n", ctx->col.r, ctx->col.g, ctx->col.b);
      break;
    }
    case CMD_PRINT:
    {
      fprintf(stderr, "%f\n", eval_expr(self->children[0], ctx));
      break;
    }
  }
}

void cmd_set_var(const struct ast_node *self, struct context *ctx){
  map_add(&(ctx->variables_map), self->children[0]->u.name, self->children[1]->u.value);
}

void cmd_set_proc(const struct ast_node *self, struct context *ctx){
  map_proc_add(&(ctx->proc_map), self->children[0]->u.name, self->children[1]);
}

float eval_expr(const struct ast_node *self, struct context *ctx){
  switch(self->kind){
    case KIND_EXPR_FUNC: 
      switch (self->u.func)
      {
      case FUNC_COS:
        return cos(eval_expr(self->children[0], ctx) * (PI/180));
      case FUNC_RANDOM:{
        float low = eval_expr(self->children[0], ctx);
        float hight = eval_expr(self->children[1], ctx);
        return (float)rand()/(float)(RAND_MAX) * (hight-low) + low;}
      case FUNC_SIN:
        return sin(eval_expr(self->children[0], ctx) * (PI/180));
      case FUNC_SQRT:{
        float num = eval_expr(self->children[0], ctx);
        if(num < 0){
          // TODO break the program
        }
        return sqrt(num);}
      case FUNC_TAN:
        return tan(eval_expr(self->children[0], ctx) * (PI/180));
      }
    case KIND_EXPR_VALUE: 
      return self->u.value;
    case KIND_EXPR_UNOP:
      return -eval_expr(self->children[0], ctx);
    case KIND_EXPR_BINOP:
    {
      float first = eval_expr(self->children[0], ctx);
      float second = eval_expr(self->children[1], ctx); 
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
    case KIND_EXPR_NAME:
      return get_value(&(ctx->variables_map), self->u.name);
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
    case KIND_CMD_REPEAT: 
      for(size_t i = 0; i < floor(self->children[0]->u.value); i++){
        if(self->children[1]->kind == KIND_CMD_SIMPLE){
          cmd_simple_eval(self->children[1], ctx);
        }else{
          ast_node_eval(self->children[1], ctx);
        }
      }
      break;
    case KIND_EXPR_BLOCK: 
      if(self->children[0]->kind == KIND_CMD_SIMPLE){
        cmd_simple_eval(self->children[0], ctx);
      }else{
        ast_node_eval(self->children[0], ctx);
      }
      if(self->children[1] != NULL){
        ast_node_eval(self->children[1], ctx);
      }
      break;
    case KIND_CMD_PROC: 
      cmd_set_proc(self, ctx);
      break;
    case KIND_CMD_CALL: 
      ast_node_eval(get_block(&(ctx->proc_map), self->children[0]->u.name), ctx);
      break;
    case KIND_CMD_SET: 
      cmd_set_var(self, ctx);
      break;
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

float eval_expr_print(const struct ast_node *self){
  switch(self->kind){
    case KIND_EXPR_FUNC: 
      switch (self->u.func)
      {
      case FUNC_COS:
        return cos(eval_expr_print(self->children[0]) * (PI/180));
      case FUNC_RANDOM:
        return rand() * eval_expr_print(self->children[0]);
      case FUNC_SIN:
        return sin(eval_expr_print(self->children[0]) * (PI/180));
      case FUNC_SQRT:
        return sqrt(eval_expr_print(self->children[0]));
      case FUNC_TAN:
        return tan(eval_expr_print(self->children[0]) * (PI/180));
      }
    case KIND_EXPR_VALUE: 
      return self->u.value;
    case KIND_EXPR_UNOP:
      return -eval_expr_print(self->children[0]);
    case KIND_EXPR_BINOP:
    {
      float first = eval_expr_print(self->children[0]);
      float second = eval_expr_print(self->children[1]); 
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
    case KIND_EXPR_NAME: 
      break;
    default:
      break;
  }
  return 0;
}

void cmd_simple_eval_print(const struct ast_node *self){
  switch (self->u.cmd){
    case CMD_UP:
      fprintf(stderr, "CMD_UP, put up to true\n");
      break;
    case CMD_DOWN:
      fprintf(stderr, "CMD_DOWN, put up to false\n");
      break;
    case CMD_RIGHT:
      fprintf(stderr, "CMD_RIGHT, turn angle to right add %f\n", eval_expr_print(self->children[0]));
      break;
    case CMD_LEFT:
      fprintf(stderr, "CMD_LEFT, turn angle to left substract %f\n", eval_expr_print(self->children[0]));
      break;
    case CMD_HEADING:
      fprintf(stderr, "CMD_HEADING, put the angle to the value : %f\n", eval_expr_print(self->children[0]));
      break;
    case CMD_FORWARD:
      fprintf(stderr, "CMD_FORWARD, forward with value : %f\n", eval_expr_print(self->children[0]));
      break;
    case CMD_BACKWARD:
      fprintf(stderr, "CMD_BACKWARD, backward with value : %f\n", eval_expr_print(self->children[0]));
      break;
    case CMD_POSITION:
      fprintf(stderr, "CMD_POSITION, set new position x : %f / y : %f\n", eval_expr_print(self->children[0]), eval_expr_print(self->children[1]));
      break;
    case CMD_HOME:
      fprintf(stderr, "CMD_HOME, reinitialise context\n");
      break;
    case CMD_COLOR:
      fprintf(stderr, "CMD_COLOR, new color : %f, %f, %f\n", eval_expr_print(self->children[0]), eval_expr_print(self->children[1]), eval_expr_print(self->children[2]));
      break;
    case CMD_PRINT:
      fprintf(stderr, "CMD_PRINT, print : %f\n", eval_expr_print(self->children[0]));
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

/**
 * Map management for procedures
 */

struct ast_node* get_block(struct map_proc* self, char* name){
  for(size_t i = 0; i < self->size; i++){
    if(strcmp(name, self->map_procedures[i].name) == 0){
      return self->map_procedures[i].block;
    }
  }
  return 0;
}

void map_proc_create(struct map_proc* self){
	self->size = 0;
	self->capacity = 10;
	self->map_procedures = calloc(self->capacity, sizeof(struct procedure));
}

void map_proc_grow(struct map_proc* self){
	self->capacity *= 2;	//O(1) amorti
	struct procedure* new_data = calloc(self->capacity, sizeof(struct procedure));	// nouveau tableau
	memcpy(new_data, self->map_procedures, self->size * sizeof(struct procedure));	// Copie
	free(self->map_procedures);	// Suppression de l'ancien
	self->map_procedures = new_data;	// Copie du nouveau dans la structure
}

void map_proc_add(struct map_proc *self, char* name, struct ast_node* block){
	if (self->size == self->capacity){
		map_proc_grow(self);
	}
	self->map_procedures[self->size].name = name;
	self->map_procedures[self->size].block = block;
	self->size += 1;
}

void map_proc_destroy(struct map_proc* self) {
  self->size = 0;
	self->capacity = 0;
	//ast_node_destroy(self->map_procedures->block);
  free(self->map_procedures);
}

/**
 * Map management for variables
 */

float get_value(struct map* self, char* name){
  for(size_t i = 0; i < self->size; i++){
    if(strcmp(name, self->map_values[i].name) == 0){
      return self->map_values[i].value;
    }
  }
  return 0;
}

void map_create(struct map* self){
	self->size = 0;
	self->capacity = 10;
	self->map_values = calloc(self->capacity, sizeof(struct variable));
}

void map_grow(struct map* self){
	self->capacity *= 2;	//O(1) amorti
	struct variable* new_data = calloc(self->capacity, sizeof(struct variable));	// nouveau tableau
	memcpy(new_data, self->map_values, self->size * sizeof(struct variable));	// Copie
	free(self->map_values);	// Suppression de l'ancien
	self->map_values = new_data;	// Copie du nouveau dans la structure
}

void map_add(struct map *self, char* name, float val){
	if (self->size == self->capacity){
		map_grow(self);
	}
	self->map_values[self->size].name = name;
	self->map_values[self->size].value = val;
	self->size += 1;
}

void map_destroy(struct map* self) {
  self->size = 0;
	self->capacity = 0;
	free(self->map_values);
}
