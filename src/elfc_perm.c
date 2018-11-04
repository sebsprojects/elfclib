#include "elfc_perm.h"

#include <stdio.h>


// ---------------------------------------------------------------------------
// Binomial Structures to represent combinations of u16
// ---------------------------------------------------------------------------

void binom_initDefault(Vecu16 *vec, i32 k)
{
  binom_init(vec, 0, k, 0);
}

void binom_init(Vecu16 *vec, i32 min, i32 k, i32 offset)
{
  vecu16_fill(vec, 0xffff);
  vecu16_setToRange(vec, offset, k + offset, min);
}

bool binom_shiftDefault(Vecu16 *vec, i32 n)
{
  return binom_shift(vec, n, binom_getKIndex(vec), 0);
}

bool binom_shift(Vecu16 *vec, i32 n, i32 k, i32 offset)
{
  i32 lastIndex = offset + k - 1;
  i32 pos = lastIndex;
  u16 *ele;
  while(pos >= offset) {
    ele = vecu16_at(vec, pos);
    // Check if we can increase the current position
    if(*ele >= n - (lastIndex - pos)) {
      // We cannot, so move further left
      pos--;
    } else {
      // We can, so do it and set the right to a range starting with ele+1
      (*ele)++;
      if(pos < lastIndex) {
        vecu16_setToRange(vec, pos + 1, lastIndex + 1, (*ele) + 1);
      }
      return 1;
    }
  }
  return 0;
}

u32 binom_getKIndex(Vecu16 *vec)
{
  u32 ind = vec->size;
  vecu16_indexOf(vec, 0xffff, &ind, 0);
  return ind;
}


// ---------------------------------------------------------------------------
// Permutations
// ---------------------------------------------------------------------------

void perm_init(Vecu16 *vec)
{
  vecu16_setToRange(vec, 0, vec->size, 0);
}

bool perm_shiftDefault(Vecu16 *vec)
{
  return perm_shift(vec, 0, vec->size);
}

bool perm_shift(Vecu16 *vec, i32 from, i32 to)
{
  bool nextBiggestInd(Vecu16 *vec, i32 pos, i32 to, i32 *nbi);
  void switchElements(Vecu16 *vec, i32 ind1, i32 ind2);
  i32 pos = to - 2;
  i32 nbi;
  // starting from the back end of the array with size 2, check if we can
  // find a next biggest element than vec[pos] (the start of the segment).
  // If yes, switch vec[pos] and the next biggest element and sort the
  // remaining segment
  // If not, increase the segment by 1 until impossible.
  while(pos >= from) { // covers the case to - 2 < from
    if(nextBiggestInd(vec, pos, to, &nbi)) {
      switchElements(vec, pos, nbi);
      vecu16_sort(vec, pos + 1, to);
      return 1;
    } else {
      pos--;
    }
  }
  return 0;
}


// ---------------------------------------------------------------------------
// Local Functions
// ---------------------------------------------------------------------------

// Returns the index to an element between [pos + 1, to) that is bigger
// than vec[pos] but closest to it. If none are bigger than
// vec[pos] 0xffff is returned.
bool nextBiggestInd(Vecu16 *vec, i32 pos, i32 to, i32 *nbi)
{
  u16 curr = *vecu16_at(vec, pos);
  u16 nextBig = 0xffff;
  u16 ele;
  bool success = 0;
  for(u32 i = pos + 1; i < to; i++) {
    ele = *vecu16_at(vec, i);
    if(ele > curr && ele < nextBig) {
      nextBig = ele;
      *nbi = i;
      success = 1;
    }
  }
  return success;
}

void switchElements(Vecu16 *vec, i32 ind1, i32 ind2)
{
  u16 ele = *vecu16_at(vec, ind1);
  *vecu16_at(vec, ind1) = *vecu16_at(vec, ind2);
  *vecu16_at(vec, ind2) = ele;
}
