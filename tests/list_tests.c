#include "minunit.h"
#include <List/list.h>
#include <assert.h>

static List *list = NULL;
char *tv1 = "test value1";
char *tv2 = "test value2";
char *tv3 = "test value3";

char *test_create()
{
    list = List_create();
    mu_assert(list != NULL, "Failed to create list.");

    return NULL;
}

char *test_clear()
{
    List_clear(list);
    return NULL;
}

char *test_destroy()
{
    List_destroy(list);
    return NULL;
}

char *test_push_pop()
{
    List_push(list, tv1);
    mu_assert(List_last(list) == tv1, "Bad last value.");

    List_push(list, tv2);
    mu_assert(List_last(list) == tv2, "Bad last value.");

    List_push(list, tv3);
    mu_assert(List_last(list) == tv3, "Bad last value.");
    mu_assert(List_size(list) == 3, "Wrong size");

    char *out = List_pop(list);
    mu_assert(out == tv3, "Bad popped value.");

    out = List_pop(list);
    mu_assert(out == tv2, "Bad popped value.");

    out = List_pop(list);
    mu_assert(out == tv1, "Bad popped value.");
    mu_assert(List_size(list) == 0, "Wrong size");

    return NULL;
}

char *test_unshift_shift()
{
    List_unshift(list, tv1);
    mu_assert(List_first(list) == tv1, "Bad first value.");

    List_unshift(list, tv2);
    mu_assert(List_first(list) == tv2, "Bad first value.");

    List_unshift(list, tv3);
    mu_assert(List_first(list) == tv3, "Bad first value.");
    mu_assert(List_size(list) == 3, "Wrong size");

    char *out = List_shift(list);
    mu_assert(out == tv3, "Bad shifted value.");

    out = List_shift(list);
    mu_assert(out == tv2, "Bad shifted value.");

    out = List_shift(list);
    mu_assert(out == tv1, "Bad shifted value.");
    mu_assert(List_size(list) == 0, "Wrong size");

    return NULL;
}

char *test_remove()
{
    List_push(list, tv1);
    List_push(list, tv2);
    List_push(list, tv3);
    char *out = List_remove(list, list->first->next);
    mu_assert(out == tv2, "Removed wrong thing.");
    mu_assert(List_first(list) == tv1, "Wrong first ref.");
    mu_assert(List_last(list) == tv3, "Wrong last ref.");

    return NULL;
}

char *all_tests() {
    mu_suite_start();

    mu_run_test(test_create);
    mu_run_test(test_push_pop);
    mu_run_test(test_unshift_shift);
    mu_run_test(test_remove);
    mu_run_test(test_clear);
    mu_run_test(test_destroy);

    return NULL;
}

RUN_TESTS(all_tests);
