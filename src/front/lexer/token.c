#include "front/lexer/token.h"

#include <stddef.h>
#include <stdlib.h>

token_node*
token_init() {
  return NULL;
}

token_node*
token_next(token_node* cur) {
  return cur->next;
}

token_node*
token_prev(token_node* cur) {
  return cur->prev;
}

int
token_destory(token_node* cur) {
  for (;;) {
    if (cur == NULL) {
      break;
    }
    token_node* del = cur;
    cur = cur->next;

    del->next->prev = NULL;

    if (del->token_val != NULL) {
      free(del->token_val);
    }
    free(del);
  }
  return 0;
}

int
token_append(token_node* head, char* token_val, enum token_type tkType) {
  token_node* end_node = head->prev;

  // set new node attr
  token_node* new_node = (token_node*)malloc(sizeof(token_node));
  new_node->token_val = token_val;
  new_node->tok_type = tkType;
  new_node->next = end_node->next;
  new_node->prev = end_node;

  end_node->next = new_node;
  head->prev = new_node;
  return 0;
}
