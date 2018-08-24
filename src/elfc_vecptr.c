#include "../include/elfc_vecptr.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>


// --------------------------------------------------------------------------
// Alloc / Free
// --------------------------------------------------------------------------

Vecptr *vecptr_alloc(u32 size) {
  Vecptr *vector = malloc(sizeof(Vecptr));
  vector->allocSize = size;
  vector->size = size;
  vector->data = malloc(size * sizeof(void*));
  return vector;
}

void vecptr_free(Vecptr *vector){
  free(vector->data);
  free(vector);
}


// --------------------------------------------------------------------------
// Access
// --------------------------------------------------------------------------

void **vecptr_at(Vecptr *vector, u32 index) {
  if(index >= vector->size) {
    fprintf(stderr, "fatal: vecptr_at access at index=%u whereas size=%u",
            index, vector->size);
    exit(1);
  }
  return &vector->data[index];
}
