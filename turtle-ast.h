#ifndef TURTLE_AST_H
#define TURTLE_AST_H

#include <stddef.h>
#include <stdbool.h>

// simple commands
enum ast_cmd {
  CMD_UP,
  CMD_DOWN,
  CMD_RIGHT,
  CMD_LEFT,
  CMD_HEADING,
  CMD_FORWARD,
  CMD_BACKWARD,
  CMD_POSITION,
  CMD_HOME,
  CMD_COLOR,
  CMD_PRINT,
};

// internal functions
enum ast_func {
  FUNC_COS,
  FUNC_RANDOM,
  FUNC_SIN,
  FUNC_SQRT,
  FUNC_TAN,
};

// kind of a node in the abstract syntax tree
enum ast_kind {
  KIND_CMD_SIMPLE,
  KIND_CMD_REPEAT,
  KIND_CMD_BLOCK,
  KIND_CMD_PROC,
  KIND_CMD_CALL,
  KIND_CMD_SET,

  KIND_EXPR_FUNC,
  KIND_EXPR_VALUE,
  KIND_EXPR_UNOP,
  KIND_EXPR_BINOP,
  KIND_EXPR_BLOCK,
  KIND_EXPR_NAME,
};

#define AST_CHILDREN_MAX 3

// a node in the abstract syntax tree
struct ast_node {
  enum ast_kind kind; // kind of the node

  union {
    enum ast_cmd cmd;   // kind == KIND_CMD_SIMPLE
    double value;       // kind == KIND_EXPR_VALUE, for literals
    char op;            // kind == KIND_EXPR_BINOP or kind == KIND_EXPR_UNOP, for operators in expressions
    char *name;         // kind == KIND_EXPR_NAME, the name of procedures and variables
    enum ast_func func; // kind == KIND_EXPR_FUNC, a function
  } u;

  size_t children_count;  // the number of children of the node
  struct ast_node *children[AST_CHILDREN_MAX];  // the children of the node (arguments of commands, etc)
  struct ast_node *next;  // the next node in the sequence
};


// Constructors to use in parser.y
struct ast_node *make_expr_value(double value);
struct ast_node *make_name_value(char* value);
struct ast_node *make_cmd_forward(struct ast_node *expr);
struct ast_node *make_cmd_backward(struct ast_node *expr);
struct ast_node *make_cmd_position(struct ast_node *expr);
struct ast_node *make_cmd_up(struct ast_node *expr);
struct ast_node *make_cmd_down(struct ast_node *expr);
struct ast_node *make_cmd_right(struct ast_node *expr);
struct ast_node *make_cmd_left(struct ast_node *expr);
struct ast_node *make_cmd_heading(struct ast_node *expr);
struct ast_node *make_cmd_color(struct ast_node *expr, struct ast_node *expr2, struct ast_node *expr3);
struct ast_node *make_cmd_home(struct ast_node *expr);
struct ast_node *make_cmd_print(struct ast_node *expr);

struct ast_node *make_cmd_set(struct ast_node *name, struct ast_node *expr);

struct ast_node *make_unop(struct ast_node *right, char c);
struct ast_node *make_binop(struct ast_node *left, struct ast_node *right, char c);
struct ast_node *make_intern_expr(struct ast_node *expr, char* func);
struct ast_node *make_cmd_repeat(struct ast_node *expr, struct ast_node *fct);

// root of the abstract syntax tree
struct ast {
  struct ast_node *unit;
};

// do not forget to destroy properly! no leaks allowed!
void ast_destroy(struct ast *self);

// And recursivity isn't for LITTLE PLAYERS!
void ast_node_destroy(struct ast_node *self);

struct color {
  float r;
  float g;
  float b;
};


struct variable{
  char* name;
  float value; 
};

struct map{
  struct variable* map_values;
  size_t size;
  size_t capacity;
};

void map_add(struct map *self, char* name, float val);
void map_grow(struct map* self);
void map_destroy(struct map* self);
void map_create(struct map* self);
float get_value(struct map* self, char* name);

// the execution context
struct context {
  double x;
  double y;
  double angle;
  bool up;
  struct color col;
  struct map variables_map;
};


// create an initial context
void context_create(struct context *self);
void context_destroy(struct context *self);

// print the tree as if it was a Turtle program
void ast_print(const struct ast *self);
void ast_node_print(const struct ast_node *self);
void cmd_simple_eval_print(const struct ast_node *self);

// evaluate the tree and generate some basic primitives
void ast_eval(const struct ast *self, struct context *ctx);
void cmd_simple_eval(const struct ast_node *self, struct context *ctx);
void cmd_set_var(const struct ast_node *self, struct context *ctx);
float eval_expr(const struct ast_node *self, struct context *ctx);
float eval_expr_print(const struct ast_node *self);

#endif /* TURTLE_AST_H */
