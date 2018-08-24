#include "../include/elfc_vecu16.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>


// --------------------------------------------------------------------------
// Alloc / Free
// --------------------------------------------------------------------------

Vecu16 *vecu16_alloc(u32 size) {
  Vecu16 *vector = malloc(sizeof(Vecu16));
  vector->allocSize = size;
  vector->size = size;
  vector->data = malloc(size * sizeof(u16));
  return vector;
}

Vecu16 *vecu16_allocN(u32 n, ...) {
  Vecu16 *vector = vecu16_alloc(n);
  va_list args;
  va_start(args, n);
  i32 i;
  for(i = 0; i < n; i++) {
    vector->data[i] = va_arg(args, i32);
  }
  va_end(args);
  return vector;
}

void vecu16_free(Vecu16 *vector) {
  free(vector->data);
  free(vector);
}


// --------------------------------------------------------------------------
// Access
// --------------------------------------------------------------------------

u16 *vecu16_at(Vecu16 *vector, u32 index) {
  if(index >= vector->size) {
    fprintf(stderr, "fatal: vecu16_at access at index=%u whereas size=%u",
            index, vector->size);
    exit(1);
  }
  return &vector->data[index];
}

bool vecu16_indexOf(Vecu16 *vector, u16 value, u32 offset, u32 *index) {
  i32 i;
  for(i = offset; i < vector->size; i++) {
    if(*vecu16_at(vector, i) == value) {
      *index = i;
      return 1;
    }
  }
  return 0;
}
