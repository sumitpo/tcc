#include "misc/list.h"

void *
getNext(struct list_head *cur, size_t size) {
  char *list_n = (char *)cur->next;
  return (void *)(list_n + sizeof(struct list_head) - size);
}

void *
getPrev(struct list_head *cur, size_t size) {
  char *list_n = (char *)cur->prev;
  return (void *)(list_n + sizeof(struct list_head) - size);
}
