#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./vec.h"

Vec *vec_new(size_t data_size)
{
  Vec *vec = malloc(sizeof(Vec));
  if (vec == NULL)
  {
    return NULL;
  }

  vec->len = 0;
  vec->cap = 0;
  vec->data_size = data_size;
  vec->data = NULL;
  return vec;
}

int vec_push(Vec *vec, void *value)
{
  if (vec->len == vec->cap)
  {
    size_t cap = vec->cap ? vec->cap * 2 : VEC_INIT_CAP;
    void *tmp = realloc(vec->data, vec->data_size * cap);
    if (tmp == NULL)
    {
      return -1;
    }

    vec->data = tmp;
    vec->cap = cap;
  }

  void *target = (char *)vec->data + (vec->len * vec->data_size);
  memcpy(target, value, vec->data_size);
  vec->len++;
  return 0;
}

void *vec_get(Vec *vec, size_t idx)
{
  if (idx < 0 || idx >= vec->len)
  {
    fprintf(stderr, "Index out of bounds: %d\n", idx);
    return NULL;
  }

  return (char *)vec->data + (idx * vec->data_size);
}

void vec_free(Vec *vec)
{
  if (vec)
  {
    free(vec->data);
    free(vec);
  }
}

int vec_len(Vec *vec)
{
  return vec->len;
}

void *vec_pop(Vec *vec)
{
  if (vec->len > 0)
  {
    vec->len -= 1;
    return (char *)vec->data + (vec->len * vec->data_size);
  }

  return NULL;
}

int vec_is_empty(Vec *vec)
{
  return !(vec->len > 0);
}

