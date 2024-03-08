#ifndef TOKEN_H
#define TOKEN_H

enum token_type { ident, keyword, op, num };
typedef struct token_node_t {
  char *token_val;
  enum token_type tok_type;
  struct token_node_t *prev;
  struct token_node_t *next;
} token_node;

token_node *token_init();
token_node *token_next(token_node *cur);
token_node *token_prev(token_node *cur);
int token_destory();

#endif /* TOKEN_H */
