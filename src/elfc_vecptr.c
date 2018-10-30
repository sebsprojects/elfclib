#include "../include/elfc_vecptr.h"

#include <stdlib.h>
#include <stdarg.h>


// ---------------------------------------------------------------------------
// Inlines
// ---------------------------------------------------------------------------

extern void **vecptr_at(Vecptr *vector, u32 index);


// ---------------------------------------------------------------------------
// Alloc / Free
// ---------------------------------------------------------------------------

Vecptr *vecptr_alloc(u32 size)
{
#ifdef BOUNDS_CHECK
  if(size == 0) {
    boundsErrorAndExit("vecptr_alloc", 1, size);
  }
#endif
  Vecptr *vector = malloc(sizeof(Vecptr));
  vector->allocSize = size;
  vector->size = size;
  vector->data = malloc(size * sizeof(void*));
  return vector;
}

void vecptr_free(Vecptr *vector)
{
  free(vector->data);
  free(vector);
}
