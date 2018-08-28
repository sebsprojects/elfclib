#include "../include/elfc_vecf32.h"
#include "../include/elfc_math.h"

#include <stdlib.h>
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
    boundsErrorAndExit("vecf32_at", vector->size, index);
  }
  return &vector->data[index];
}


// --------------------------------------------------------------------------
// Operation
// --------------------------------------------------------------------------

f32 vecf32_max(Vecf32 *vector) {
  if(vector->size == 0) {
    errorAndExit("vecf32_max: No elements");
  }
  i32 i;
  f32 max = F32_MIN;
  for(i = 0; i < vector->size; i++) {
    max = f32_max(max, *vecf32_at(vector, i));
  }
  return max;
}

f32 vecf32_min(Vecf32 *vector) {
  if(vector->size == 0) {
    errorAndExit("vecf32_min: No elements");
  }
  i32 i;
  f32 min = F32_MAX;
  for(i = 0; i < vector->size; i++) {
    min = f32_min(min, *vecf32_at(vector, i));
  }
  return min;
}
