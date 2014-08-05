#include <Array/array.h>
#include <assert.h>

Array *Array_create(size_t element_size, size_t initial_size)
{
  Array *array = malloc(sizeof(Array));
  check_mem(array);
  array->max = initial_size;
  check(array->max > 0, "You must set an initial size > 0.");

  array->contents = calloc(initial_size, sizeof(void *));
  check_mem(array->contents);

  array->end = 0;
  array->element_size = element_size;
  array->growth_rate = INIT_GROWTH_RATE;
  
  return array;

error:
  free(array);
  return NULL;
}

void Array_clear(Array *array)
{
  int i = 0;
  if(array->element_size > 0) {
    for(i = 0; i < array->max; i++) {
      if(array->contents[i] != NULL) {
        free(array->contents[i]);
      }
    }
  }
}

static inline int Array_resize(Array *array, size_t newsize)
{
  array->max = newsize;
  check(array->max > 0, "The newsize must be > 0.");

  void *contents = realloc(array->contents, array->max * sizeof(void *));

  //check contents and check realloc didn't fuck up
  check_mem(contents);

  array->contents = contents;

  return 0;
error:
  return -1;
}

int Array_expand(Array *array)
{
size_t old_max = array->max;
  check(Array_resize(array, array->max + array->growth_rate) == 0,
      "Failed to expand array to new size: %d",
      array->max + (int)array->growth_rate);
  memset(array->contents + old_max, 0, array->growth_rate + 1);
  return 0;

error:
  return -1;
}

int Array_contract(Array *array)
{
  //get new size based on current end and growth rate
  int new_size = array->end < (int)array->growth_rate ? (int)array->growth_rate : array->end;

  return Array_resize(array, new_size + 1);
}

void Array_destroy(Array *array)
{
  //free mem allocs
  if(array){
    free(array->contents);
    free(array);
  }
}

void Array_clear_destroy(Array *array)
{
  Array_clear(array);
  Array_destroy(array);
}

int Array_push(Array *array, void *element)
{
  //Add element to the end
  array->contents[array->end] = element;
  //Up the end element
  array->end++;

  if(Array_end(array) >= Array_max(array)) {
    return Array_expand(array);
  } else {
    return 0;
  }
}

void *Array_pop(Array *array)
{
  check(array->end -1 >= 0, "Cannot pop from empty array.");
  
  //Get out last element
  void *element = Array_remove(array, array->end - 1);
  //decrement current end
  array->end--;

  if(Array_end(array) > (int)array->growth_rate && Array_end(array) % array->growth_rate) {
    Array_contract(array);
  }
  // return element
  return element;
error:
  return NULL;
}
