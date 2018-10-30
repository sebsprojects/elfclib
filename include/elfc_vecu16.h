#ifndef ELFC_VECU16
#define ELFC_VECU16

#include "elfc_common.h"


// ---------------------------------------------------------------------------
// Types
// ---------------------------------------------------------------------------

struct Vecu16 {
  u32 allocSize;
  u32 size;
  u16 *data;
};
typedef struct Vecu16 Vecu16;


// ---------------------------------------------------------------------------
// Alloc / Free
// ---------------------------------------------------------------------------

Vecu16 *vecu16_alloc(u32 size);
Vecu16 *vecu16_allocN(u32 n, ...);
void vecu16_free(Vecu16 *vector);


// ---------------------------------------------------------------------------
// Operation
// ---------------------------------------------------------------------------

/*
 * If value is not found, 0 is returned and index left unchanged
 */
bool vecu16_indexOf(Vecu16 *vector, u16 value, u32 *index, u32 offset);

void vecu16_fill(Vecu16 *vector, u16 val);

/*
 * Sets vector[from]-vector[to-1] to the values 0+offset - (to-from-1)+offset
 */
void vecu16_setToRange(Vecu16 *vector, u16 from, u16 to, u16 offset);

/*
 * Set size to newSize
 */
void vecu16_resize(Vecu16 *vector, u32 newSize);

/*
 * Makes an exact copy of vector (up to allocSize, not just size)
 */
Vecu16 *vecu16_copy(Vecu16 *vector);

/*
 * Copys the contents of from to to (only up to size)
 * Fails if to->size too small
 * Leaves anything in exceeding to[from->size] unchanged
 */
void vecu16_copyInto(Vecu16 *to, Vecu16 *from);

/*
 * Sorts between [start, end] using stdlib qsort
 */
void vecu16_sort(Vecu16 *vector, u32 start, u32 end);

/*
 * Tests if two vectors are equal but disregards order
 * Duplactes have impact
 */
bool vecu16_haveEqualContent(Vecu16 *a, Vecu16 *b);

/*
 * Tests if two vectors are equal up to size. allocSize has no impact
 * Duplicates have impact. Order has impact
 */
bool vecu16_areEqualVectors(Vecu16 *a, Vecu16 *b);

/*
 * Test if two vectors are equal as sets up to size. allocSize has no impact
 * Duplicates have no impact. Vector is treated as a mathematical set
 */
bool vecu16_areEqualSets(Vecu16 *a, Vecu16 *b);

/*
 * Tests if the vector has duplicates
 */
bool vecu16_hasDuplicates(Vecu16 *vector);

/*
 * Tests if set contains sub
 */
bool vecu16_isSubset(Vecu16 *sub, Vecu16 *set);

u16 vecu16_max(Vecu16 *vector);
u16 vecu16_min(Vecu16 *vector);


// ---------------------------------------------------------------------------
// Print
// ---------------------------------------------------------------------------

void vecu16_sprint(char *pstring, Vecu16 *vector, u32 width);
void vecu16_print(Vecu16 *vector);


// ---------------------------------------------------------------------------
// Inline
// ---------------------------------------------------------------------------

inline u16 *vecu16_at(Vecu16 *vector, u32 index) {
#ifdef BOUNDS_CHECK
  if(index >= vector->size) {
    boundsErrorAndExit("vecu16_at", vector->size, index);
  }
#endif
  return &vector->data[index];
}

#endif
