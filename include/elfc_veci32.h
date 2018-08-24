#ifndef ELFC_VECI32
#define ELFC_VECI32

#include "elfc_common.h"


// --------------------------------------------------------------------------
// Types
// --------------------------------------------------------------------------

struct Veci32 {
  u32 allocSize;
  u32 size;
  i32 *data;
};
typedef struct Veci32 Veci32;


// --------------------------------------------------------------------------
// Alloc / Free
// --------------------------------------------------------------------------

Veci32 *veci32_alloc(u32 size);
Veci32 *veci32_allocN(u32 n, ...);
void veci32_free(Veci32 *vector);


// --------------------------------------------------------------------------
// Access
// --------------------------------------------------------------------------

i32 *veci32_at(Veci32 *vector, u32 index);
bool veci32_indexOf(Veci32 *vector, i32 value, u32 offset, u32 *index);


#endif
