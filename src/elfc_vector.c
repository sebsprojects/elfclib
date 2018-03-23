#include "../include/elfc_vector.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>


// --------------------------------------------------------------------------
// Alloc / Free
// --------------------------------------------------------------------------

Vector_i32 *vi32_alloc(uint32_t size) {
  Vector_i32 *vector = malloc(sizeof(Vector_i32));
  vector->allocSize = size;
  vector->size = size;
  vector->data = malloc(size * sizeof(int32_t));
  return vector;
}

Vector_i32 *vi32_allocN(uint32_t n, ...) {
  Vector_i32 *vector = vi32_alloc(n);
  va_list args;
  va_start(args, n);
  uint32_t i;
  for(i = 0; i < n; i++) {
    vector->data[i] = va_arg(args, int32_t);
  }
  va_end(args);
  return vector;
}

void vi32_free(Vector_i32 *vector) {
  free(vector->data);
  free(vector);
}


// --------------------------------------------------------------------------
// Access
// --------------------------------------------------------------------------

int32_t *vi32_at(Vector_i32 *vector, uint32_t index) {
  if(index >= vector->size) {
    fprintf(stderr, "fatal: vi32_at access at index=%u whereas size=%u",
            index, vector->size);
    exit(1);
  }
  return &vector->data[index];
}

bool vi32_indexOf(Vector_i32 *vector, int32_t value, uint32_t offset,
                  uint32_t *index) {
  uint32_t i;
  for(i = offset; i < vector->size; i++) {
    if(*vi32_at(vector, i) == value) {
      *index = i;
      return 1;
    }
  }
  return 0;
}

void *vi32_push(Vector_i32 *vector, int32_t value) {

}

int32_t vi32_pop(Vector_i32 *vector, uint32_t index) {

}

void vi32_insert(Vector_i32 *vector, uint32_t index, int32_t value) {

}

int32_t vi32_delete(Vector_i32 *vector, uint32_t index) {

}
