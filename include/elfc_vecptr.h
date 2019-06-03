#ifndef ELFC_VECPTR
#define ELFC_VECPTR

#include "elfc_common.h"


// ---------------------------------------------------------------------------
// Types
// ---------------------------------------------------------------------------

struct Vecptr {
  u32 allocSize;
  u32 size;
  void **data;
};
typedef struct Vecptr Vecptr;


// ---------------------------------------------------------------------------
// Alloc / Free
// ---------------------------------------------------------------------------

Vecptr *vecptr_alloc(u32 size);
void vecptr_free(Vecptr *vector);


// ---------------------------------------------------------------------------
// Operation
// ---------------------------------------------------------------------------

void vecptr_resize(Vecptr *vector, u32 newSize);


// ---------------------------------------------------------------------------
// Inlines
// ---------------------------------------------------------------------------

inline void **vecptr_at(Vecptr *vector, u32 index)
{
#ifdef BOUNDS_CHECK
  if(index >= vector->size) {
    boundsErrorAndExit("vecptr_at", vector->size, index);
  }
#endif
  return &vector->data[index];
}

#endif
