#ifndef ELFC_VECF32
#define ELFC_VECF32

#include "elfc_common.h"


// ---------------------------------------------------------------------------
// Types
// ---------------------------------------------------------------------------

struct Vecf32 {
  u32 allocSize;
  u32 size;
  f32 *data;
};
typedef struct Vecf32 Vecf32;


// ---------------------------------------------------------------------------
// Alloc / Free
// ---------------------------------------------------------------------------

Vecf32 *vecf32_alloc(u32 size);
Vecf32 *vecf32_allocN(u32 n, ...);
void vecf32_free(Vecf32 *vector);


// ---------------------------------------------------------------------------
// Operation
// ---------------------------------------------------------------------------

f32 vecf32_max(Vecf32 *vector);
f32 vecf32_min(Vecf32 *vector);


// ---------------------------------------------------------------------------
// Print
// ---------------------------------------------------------------------------

void vecf32_sprint(char *pstring, Vecf32 *vector, u32 width, u32 numDecimal);
void vecf32_print(Vecf32 *vector);


// ---------------------------------------------------------------------------
// Inlines
// ---------------------------------------------------------------------------

inline f32 *vecf32_at(Vecf32 *vector, u32 index) 
{
#ifdef BOUNDS_CHECK
  if(index >= vector->size) {
    boundsErrorAndExit("vecf32_at", vector->size, index);
  }
#endif
  return &vector->data[index];
}

#endif
