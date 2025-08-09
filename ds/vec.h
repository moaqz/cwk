#ifndef VEC_H
#define VEC_H

#include <stddef.h>

#define VEC_INIT_CAP 2
#define vec_get_as(vec, idx, type) (*(type *)vec_get(vec, idx))

typedef struct
{
  size_t len;
  size_t cap;
  size_t data_size;
  void *data;
} Vec;

Vec *vec_new(size_t data_size);
int vec_push(Vec *vec, void *value);
void *vec_get(Vec *vec, size_t idx);
void vec_free(Vec *vec);
int vec_len(Vec *vec);
void *vec_pop(Vec *vec);
int vec_is_empty(Vec *vec);

#endif
