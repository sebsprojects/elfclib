#ifndef ELFC_VECU16
#define ELFC_VECU16

#include "elfc_common.h"


// --------------------------------------------------------------------------
// Types
// --------------------------------------------------------------------------

struct Vecu16 {
  u32 allocSize;
  u32 size;
  u16 *data;
};
typedef struct Vecu16 Vecu16;


// --------------------------------------------------------------------------
// Alloc / Free
// --------------------------------------------------------------------------

Vecu16 *vecu16_alloc(u32 size);
Vecu16 *vecu16_allocN(u32 n, ...);
void vecu16_free(Vecu16 *vector);


// --------------------------------------------------------------------------
// Access
// --------------------------------------------------------------------------

u16 *vecu16_at(Vecu16 *vector, u32 index);
bool vecu16_indexOf(Vecu16 *vector, u16 value, u32 offset, u32 *index);


#endif
