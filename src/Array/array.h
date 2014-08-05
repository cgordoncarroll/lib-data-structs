#ifndef _Array_h
#define _Array_h
#include <stdlib.h>
#include <assert.h>
#include <shared/dbg.h>

typedef struct Array{
  int end;
  int max;
  size_t element_size;
  size_t growth_rate;
  void **contents;
} Array;

Array *Array_create(size_t element_size, size_t initial_size);
void Array_destroy(Array *array);
void Array_clear(Array *array);
int Array_expand(Array *array);
int Array_contract(Array *array);
int Array_push(Array *array, void *element);
void *Array_pop(Array *array);
void Array_clear_destroy(Array *array);

#define Array_last(A) ((A)->contents[(A)->end - 1])
#define Array_first(A) ((A)->contents[0])
#define Array_end(A) ((A)->end)
#define Array_count(A) Array_end(A)
#define Array_max(A) ((A)->max)

#define INIT_GROWTH_RATE 300

static inline void Array_set(Array *array, int i, void *element)
{
  check(i < array->max, "Array attempted to set value outside bounds.");
  if(i > array->end) array->end = i;
  array->contents[i] = element;
error:
  return;
}

static inline void *Array_get(Array *array, int i)
{
  check(i < array->max, "Array attempted to get value outside bounds.");
  return array->contents[i];
error:
  return NULL;
}

static inline void *Array_remove(Array *array, int i)
{
  void *element = array->contents[i];
  array->contents[i] = NULL;

  return element;
}

static inline void *Array_new(Array *array)
{
  check(array->element_size > 0, "Can't use Array_new on arrays of size 0.");

  return calloc(1, array->element_size);

error:
  return NULL;
}

#define Array_free(E) free((E))

#endif
