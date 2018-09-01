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
// Operation
// --------------------------------------------------------------------------

u16 *vecu16_at(Vecu16 *vector, u32 index);
bool vecu16_indexOf(Vecu16 *vector, u16 value, u32 offset, u32 *index);

void vecu16_fill(Vecu16 *vector, u16 val);

// Sets vector[from]-vector[to-1] to the values 0+offset - (to-from-1)+offset
void vecu16_setToRange(Vecu16 *vector, u16 from, u16 to, u16 offset);

// Set size to newSize
void vecu16_resize(Vecu16 *vector, u32 newSize);

// Makes an exact copy of vector (up to allocSize, not just size)
Vecu16 *vecu16_copy(Vecu16 *vector);

// Copys the contents of from to to (only up to size). Fails if size too small
void vecu16_copyInto(Vecu16 *to, Vecu16 *from);

// Sorts between [start, end] using stdlib qsort
void vecu16_sort(Vecu16 *vector, u32 start, u32 end);

// Tests if two vectors are equal up to size. allocSize has no impact on that
bool vecu16_areEqualVectors(Vecu16 *a, Vecu16 *b);

// Tests if two vectors are equal but disregards order
bool vecu16_haveEqualContent(Vecu16 *a, Vecu16 *b);

// Tests if the vector has duplicates
bool vecu16_hasDuplicates(Vecu16 *vector);

u16 vecu16_max(Vecu16 *vector);
u16 vecu16_min(Vecu16 *vector);



#endif
