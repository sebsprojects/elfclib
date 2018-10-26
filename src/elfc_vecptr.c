#include "../include/elfc_vecptr.h"

#include <stdlib.h>
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
#ifdef BOUNDS_CHECK
  if(index >= vector->size) {
    boundsErrorAndExit("vecptr_at", vector->size, index);
  }
#endif
  return &vector->data[index];
}
