#ifndef _LIST_h
#define _LIST_h

#include <stdlib.h>

typedef struct ListNode {
    struct ListNode *next;
    struct ListNode *prev;
    void *value;
} ListNode;

typedef struct List {
    int size;
    ListNode *first;
    ListNode *last;
} List;

List *List_create();
void List_destroy(List *list);

#define List_size(A) ((A)->size)
#define List_first(A) ((A)->first != NULL ? (A)->first->value : NULL)
#define List_last(A) ((A)->last != NULL ? (A)->last->value : NULL)

void List_push(List *list, void *value);
void *List_pop(List *list);
void List_unshift(List *list, void *value);
void *List_shift(List *list);
void *List_remove(List *list, ListNode *node);

#define LIST_ITERATOR(A) ListNode *_node = NULL;\
    ListNode *current = NULL;\
    for(current = _node = A->first; _node != NULL; current = _node = _node->next)

#endif
