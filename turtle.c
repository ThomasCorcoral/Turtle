#include <assert.h>
#include <stdlib.h>
#include <time.h>

#include "turtle-ast.h"
#include "turtle-lexer.h"
#include "turtle-parser.h"

struct context ctx;
struct ast root;
bool already_free;

static void exit_handler(void){
  if(!already_free){
    fprintf(stderr,"Inside exit_handler2()\n");
    context_destroy(&ctx);
    ast_destroy(&root);
  }
}

int main() {
  srand(time(NULL));
  atexit(exit_handler);
  already_free = false;
  int ret = yyparse(&root);

  if (ret != 0) {
    return ret;
  }

  yylex_destroy();

  assert(root.unit);

  context_create(&ctx);
  
  ast_eval(&root, &ctx);
  //ast_print(&root);
  context_destroy(&ctx);
  ast_destroy(&root);
  already_free = true;

  return ret;
}
