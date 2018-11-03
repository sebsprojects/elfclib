#include "elfc_perm.h"


// ---------------------------------------------------------------------------
// Binomial Structures to represent combinations of u16
// ---------------------------------------------------------------------------

void binom_init(Vecu16 *vec, u16 n)
{
  vecu16_fill(vec, 0xffff);
  vecu16_setToRange(vec, 0, n, 0);
}

bool binom_shiftDefault(Vecu16 *vec, u16 max)
{
  return 0;
}

bool binom_shift(Vecu16 *vec, u16 min, u16 max, u16 offset, u16 n)
{
  u16 *ele_i, *ele_im1;
  for(i32 i = offset + 1; i < offset + n; i++) {
    ele_i = vecu16_at(vec, i);
    ele_im1 = vecu16_at(vec, i - 1);
    if(*ele_i - *ele_im1 > 1) {

    }
    if(i == offset + n - 1 && *ele_i < max) {

    }
  }
  return 0;
}

u32 binom_getKIndex(Vecu16 *vec)
{
  for(i32 i = 0; i < vec->size; i++) {
    if(*vecu16_at(vec, i) == 0xffff) {
      return i;
    }
  }
  return vec->size;
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

bool perm_shift(Vecu16 *vec, u16 from, u16 to)
{
  bool nextBiggestInd(Vecu16 *vec, u32 pos, u32 to, u32 *nbi);
  void switchElements(Vecu16 *vec, u32 ind1, u32 ind2);
  i32 pos = to - 2;
  u32 nbi;
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
bool nextBiggestInd(Vecu16 *vec, u32 pos, u32 to, u32 *nbi)
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

void switchElements(Vecu16 *vec, u32 ind1, u32 ind2)
{
  u16 ele = *vecu16_at(vec, ind1);
  *vecu16_at(vec, ind1) = *vecu16_at(vec, ind2);
  *vecu16_at(vec, ind2) = ele;
}
