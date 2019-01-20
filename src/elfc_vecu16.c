#include "../include/elfc_vecu16.h"

#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <math.h>


// ---------------------------------------------------------------------------
// Inline externs
// ---------------------------------------------------------------------------

extern u16 *vecu16_at(Vecu16 *vector, u32 index);


// ---------------------------------------------------------------------------
// Alloc / Free
// ---------------------------------------------------------------------------

Vecu16 *vecu16_alloc(u32 size)
{
#ifdef BOUNDS_CHECK
  if(size == 0) {
    boundsErrorAndExit("vecu16_alloc", 1, size);
  }
#endif
  Vecu16 *vector = malloc(sizeof(Vecu16));
  vector->allocSize = size;
  vector->size = size;
  vector->data = malloc(size * sizeof(u16));
  return vector;
}

Vecu16 *vecu16_allocN(u32 n, ...)
{
#ifdef BOUNDS_CHECK
  if(n == 0) {
    boundsErrorAndExit("vecu16_allocN", 1, n);
  }
#endif
  Vecu16 *vector = vecu16_alloc(n);
  va_list args;
  va_start(args, n);
  for(i32 i = 0; i < n; i++) {
    vector->data[i] = va_arg(args, i32);
  }
  va_end(args);
  return vector;
}

void vecu16_free(Vecu16 *vector)
{
  free(vector->data);
  free(vector);
}


// ---------------------------------------------------------------------------
// Operation
// ---------------------------------------------------------------------------

bool vecu16_indexOf(Vecu16 *vector, u16 value, u32 *index, u32 offset)
{
  for(i32 i = offset; i < vector->size; i++) {
    if(*vecu16_at(vector, i) == value) {
      *index = i;
      return 1;
    }
  }
  return 0;
}

bool vecu16_contains(Vecu16 *vector, u16 value, u32 offset)
{
  u32 *ind = 0;
  return vecu16_indexOf(vector, value, ind, offset);
}

void vecu16_fill(Vecu16 *vector, u16 val)
{
  for(i32 i = 0; i < vector->size; i++) {
    *vecu16_at(vector, i) = val;
  }
}

void vecu16_setToRange(Vecu16 *vector, u16 from, u16 to, u16 rangeOffset)
{
#ifdef BOUNDS_CHECK
  if(vector->size <= from || vector->size < to) {
    boundsErrorAndExit("vecu16_setToRange", vector->size, u16_max(from, to));
  }
#endif
  for(i32 i = from; i < to; i++) {
    *vecu16_at(vector, i) = i - from + rangeOffset;
  }
}

void vecu16_resize(Vecu16 *vector, u32 newSize)
{
#ifdef BOUNDS_CHECK
  if(vector->allocSize < newSize) {
    boundsErrorAndExit("vecu16_resize", vector->size, newSize);
  }
#endif
  vector->size = newSize;
}

Vecu16 *vecu16_copy(Vecu16 *vector)
{
  Vecu16 *copy = vecu16_alloc(vector->allocSize);
  copy->size = vector->size;
  for(i32 i = 0; i < copy->allocSize; i++) {
    copy->data[i] = vector->data[i];
  }
  return copy;
}

void vecu16_copyInto(Vecu16 *to, Vecu16 *from)
{
#ifdef BOUNDS_CHECK
  if(to->size < from->size) {
    boundsErrorAndExit("vecu16_copyInto", to->size, from->size);
  }
#endif
  for(i32 i = 0; i < from->size; i++) {
    *vecu16_at(to, i) = *vecu16_at(from, i);
  }
}

void vecu16_sort(Vecu16 *vector, u32 start, u32 end)
{
#ifdef BOUNDS_CHECK
  if(start > vector->size || end > vector->size) {
    boundsErrorAndExit("vecu16_sort", vector->size, u16_max(start, end));
  }
#endif
  u16 *base = &vector->data[start];
  u32 num = end - start;
  bool u16_lessThanCompare(const void *x, const void* y);
  qsort(base, num, sizeof(u16), u16_lessThanCompare);
}

bool vecu16_areEqualVectors(Vecu16 *a, Vecu16 *b)
{
  if(a->size != b->size) {
    return 0;
  }
  for(i32 i = 0; i < a->size; i++) {
    if(*vecu16_at(a, i) != *vecu16_at(b, i)) {
      return 0;
    }
  }
  return 1;
}

bool vecu16_areEqualSets(Vecu16 *a, Vecu16 *b)
{
  return vecu16_isSubset(a, b) && vecu16_isSubset(b, a);
}

bool vecu16_haveEqualContent(Vecu16 *a, Vecu16 *b)
{
  Vecu16 *ac = vecu16_copy(a);
  Vecu16 *bc = vecu16_copy(b);
  vecu16_sort(ac, 0, ac->size);
  vecu16_sort(bc, 0, bc->size);
  bool equal = vecu16_areEqualVectors(ac, bc);
  vecu16_free(bc);
  vecu16_free(ac);
  return equal;
}

bool vecu16_hasDuplicates(Vecu16 *vector)
{
  u16 ele;
  for(i32 i = 0; i < vector->size; i++) {
    ele = *vecu16_at(vector, i);
    for(i32 j = 0; j < i; j++) {
      if(ele == *vecu16_at(vector, j)) {
        return 1;
      }
    }
  }
  return 0;
}

bool vecu16_isSubset(Vecu16 *sub, Vecu16 *set)
{
  u32 ind;
  for(i32 i = 0; i < sub->size; i++) {
    if(!vecu16_indexOf(set, *vecu16_at(sub, i), &ind, 0)) {
      return 0;
    }
  }
  return 1;
}

u16 vecu16_max(Vecu16 *vector)
{
#ifdef BOUNDS_CHECK
  if(vector->size == 0) {
    errorAndExit("vecu16_max: No elements");
  }
#endif
  u16 max = U16_MIN;
  for(i32 i = 0; i < vector->size; i++) {
    max = u16_max(max, *vecu16_at(vector, i));
  }
  return max;
}

u16 vecu16_min(Vecu16 *vector)
{
#ifdef BOUNDS_CHECK
  if(vector->size == 0) {
    errorAndExit("vecu16_min: No elements");
  }
#endif
  u16 min = U16_MAX;
  for(i32 i = 0; i < vector->size; i++) {
    min = u16_min(min, *vecu16_at(vector, i));
  }
  return min;
}


// ---------------------------------------------------------------------------
// Print
// ---------------------------------------------------------------------------

void vecu16_sprint(char *pstring, Vecu16 *vector, u32 width)
{
  u16 viMin = vecu16_min(vector);
  u16 maxAbs = u16_max(vecu16_max(vector), viMin);
  u32 numDigits = maxAbs == 0 ? 1 : floor(log10(maxAbs)) + 1;
  u32 padTo = numDigits + (viMin < 0 ? 1 : 0);
  u32 perLine = width / (padTo + 2); // account for ', '
  char format[20]; format[0] = '\0';
  sprintf(format, "%s%u%s", "%", padTo, "i");
  sprintf(pstring, "vu16: len=%u\n", vector->size);
  for(i32 i = 0; i < vector->size; i++) {
    sprintf(pstring + strlen(pstring), format, *vecu16_at(vector, i), padTo);
    if(i < vector->size - 1) {
      sprintf(pstring + strlen(pstring), ", ");
      if((i + 1) % perLine == 0) {
        sprintf(pstring + strlen(pstring), "\n");
      }
    }
  }
}

void vecu16_print(Vecu16 *vector)
{
  u16 viMin = vecu16_min(vector);
  u16 maxAbs = i32_max(vecu16_max(vector), viMin);
  u32 numDigits = maxAbs == 0 ? 1 : floor(log10(maxAbs)) + 1;
  u32 width = 80;
  char *pstring = malloc(100 + (numDigits + 3) * vector->size);
  vecu16_sprint(pstring, vector, width);
  printf("%s\n", pstring);
  free(pstring);
}


// ---------------------------------------------------------------------------
// Local Functions
// ---------------------------------------------------------------------------

bool u16_lessThanCompare(const void *x, const void *y)
{
  u16 xx = *(u16*) x;
  u16 yy = *(u16*) y;
  if(xx < yy) {
    return -1;
  }
  if(xx > yy) {
    return 1;
  }
  return 0;
}
