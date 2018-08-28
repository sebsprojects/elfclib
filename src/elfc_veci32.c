#include "../include/elfc_veci32.h"
#include "../include/elfc_math.h"

#include <stdlib.h>
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
    boundsErrorAndExit("veci32_at", vector->size, index);
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


// --------------------------------------------------------------------------
// Operation
// --------------------------------------------------------------------------

i32 veci32_max(Veci32 *vector) {
  if(vector->size == 0) {
    errorAndExit("veci32_max: No elements");
  }
  i32 i;
  i32 max = I32_MIN;
  for(i = 0; i < vector->size; i++) {
    max = i32_max(max, *veci32_at(vector, i));
  }
  return max;
}

i32 veci32_min(Veci32 *vector) {
  if(vector->size == 0) {
    errorAndExit("veci32_min: No elements");
  }
  i32 i;
  i32 min = I32_MAX;
  for(i = 0; i < vector->size; i++) {
    min = i32_min(min, *veci32_at(vector, i));
  }
  return min;
}
