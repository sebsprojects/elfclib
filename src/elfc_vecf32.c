#include "../include/elfc_vecf32.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>


// --------------------------------------------------------------------------
// Alloc / Free
// --------------------------------------------------------------------------

Vecf32 *vecf32_alloc(u32 size) {
  Vecf32 *vector = malloc(sizeof(Vecf32));
  vector->allocSize = size;
  vector->size = size;
  vector->data = malloc(size * sizeof(f32));
  return vector;
}

Vecf32 *vecf32_allocN(u32 n, ...) {
  Vecf32 *vector = vecf32_alloc(n);
  va_list args;
  va_start(args, n);
  i32 i;
  for(i = 0; i < n; i++) {
    vector->data[i] = (float) va_arg(args, double);
  }
  va_end(args);
  return vector;
}

void vecf32_free(Vecf32 *vector) {
  free(vector->data);
  free(vector);
}


// --------------------------------------------------------------------------
// Access
// --------------------------------------------------------------------------

f32 *vecf32_at(Vecf32 *vector, u32 index) {
  if(index >= vector->size) {
    fprintf(stderr, "fatal: vecf32_at access at index=%u whereas size=%u",
            index, vector->size);
    exit(1);
  }
  return &vector->data[index];
}
