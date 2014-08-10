#include <List/list.h>
#include <shared/dbg.h>

List *List_create()
{
    return calloc(1, sizeof(List));
}

void List_destroy(List *list)
{
    LIST_ITERATOR(list){
        if(cur->prev){
            free(cur->prev);
        }
    }
    free(list->first);
    free(list);
}

void List_clear(List *list)
{
    LIST_ITERATOR(list){
        if(cur->value){
            free(cur->value);
        }
    }
}

void List_clear_destroy(List *list)
{
    List_clear(list);
    List_destroy(list);
}

void List_push(List *list, void *value)
{
    ListNode *node = calloc(1, sizeof(ListNode));
    check_mem(node);

    node->value = value;

    if(list->last == NULL){
        list->last = node;
        list->first = node;
    } else {
        list->last->next = node;
        node->prev = list->last;
        list->last = node;
    }

    list->size++;

error:
    return;
}

void *List_pop(List *list)
{
    ListNode *node = list->last;
    return node != NULL ? List_remove(list, node) : NULL;
}

void List_unshift(List *list, void*value)
{
    ListNode *node = calloc(1, sizeof(ListNode));
    check_mem(node);

    node->value = value;

    if(list->first == NULL){
        list->first = node;
        list->last = node;
    } else {
        list->first->prev = node;
        node->next = list->first;
        list->first = node;
    }

    list->size++;

error:
    return;
}

void *List_shift(List *list)
{
    ListNode *node = list->first;
    return node != NULL ? List_remove(list, node) : NULL;
}

void *List_remove(List *list, ListNode *node)
{
    void *retval = NULL;
    check(list->first != NULL && list->last !=NULL, "Invalid List");
    check(node, "Can't remove a null");

    if(node == list->first && node == list->last){
        list->first = NULL;
        list->last = NULL;
    } else if(node == list->first){
        list->first = node->next;
        list->first->prev = NULL;
    } else if(node == list->last){
        list->last = node->prev;
        list->last->next = NULL;
    } else {
        ListNode *tmpA = node->prev;
        ListNode *tmpB = node->next;
        tmpA->next = tmpB;
        tmpB->prev = tmpA;
    }

    list->size--;
    retval = node->value;
    free(node);

error:
    return retval;
}
