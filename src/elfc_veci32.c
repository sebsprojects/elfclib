#include "../include/elfc_veci32.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>


// --------------------------------------------------------------------------
// Alloc / Free
// --------------------------------------------------------------------------

Veci32 *veci32_alloc(u32 size) {
  Veci32 *vector = malloc(sizeof(Veci32));
  vector->allocSize = size;
  vector->size = size;
  vector->data = malloc(size * sizeof(i32));
  return vector;
}

Veci32 *veci32_allocN(u32 n, ...) {
  Veci32 *vector = veci32_alloc(n);
  va_list args;
  va_start(args, n);
  i32 i;
  for(i = 0; i < n; i++) {
    vector->data[i] = va_arg(args, i32);
  }
  va_end(args);
  return vector;
}

void veci32_free(Veci32 *vector) {
  free(vector->data);
  free(vector);
}


// --------------------------------------------------------------------------
// Access
// --------------------------------------------------------------------------

i32 *veci32_at(Veci32 *vector, u32 index) {
  if(index >= vector->size) {
    fprintf(stderr, "fatal: veci32_at access at index=%u whereas size=%u",
            index, vector->size);
    exit(1);
  }
  return &vector->data[index];
}

bool veci32_indexOf(Veci32 *vector, i32 value, u32 offset, u32 *index) {
  i32 i;
  for(i = offset; i < vector->size; i++) {
    if(*veci32_at(vector, i) == value) {
      *index = i;
      return 1;
    }
  }
  return 0;
}
