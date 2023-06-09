#ifndef ELFC_VECI32
#define ELFC_VECI32

#include "elfc_common.h"


// ---------------------------------------------------------------------------
// Types
// ---------------------------------------------------------------------------

struct Veci32 {
  u32 allocSize;
  u32 size;
  i32 *data;
};
typedef struct Veci32 Veci32;


// ---------------------------------------------------------------------------
// Alloc / Free
// ---------------------------------------------------------------------------

Veci32 *veci32_alloc(u32 size);
Veci32 *veci32_allocN(u32 n, ...);
void veci32_free(Veci32 *vector);


// ---------------------------------------------------------------------------
// Operation
// ---------------------------------------------------------------------------

bool veci32_indexOf(Veci32 *vector, i32 value, u32 offset, u32 *index);

i32 veci32_max(Veci32 *vector);
i32 veci32_min(Veci32 *vector);

void veci32_fill(Veci32 *vector, i32 val);

// ---------------------------------------------------------------------------
// Print
// ---------------------------------------------------------------------------

void veci32_sprint(char *pstring, Veci32 *vector, u32 width);
void veci32_print(Veci32 *vector);


// ---------------------------------------------------------------------------
// Inlines
// ---------------------------------------------------------------------------

inline i32 *veci32_at(Veci32 *vector, u32 index)
{
#ifdef BOUNDS_CHECK
  if(index >= vector->size) {
    boundsErrorAndExit("vecu16_at", vector->size, index);
  }
#endif
  return &vector->data[index];
}

#endif
