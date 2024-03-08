#ifndef LIST_H
#define LIST_H

#include <stddef.h>
struct list_head {
  struct list_head *next;
  struct list_head *prev;
};

void *getNext(struct list_head *cur, size_t size);
void *getPrev(struct list_head *cur, size_t size);

#endif /* LIST_H */
