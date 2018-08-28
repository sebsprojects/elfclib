#include "../include/elfc_vecu16.h"
#include "../include/elfc_math.h"

#include <stdlib.h>
#include <stdarg.h>


// --------------------------------------------------------------------------
// Alloc / Free
// --------------------------------------------------------------------------

Vecu16 *vecu16_alloc(u32 size) {
  Vecu16 *vector = malloc(sizeof(Vecu16));
  vector->allocSize = size;
  vector->size = size;
  vector->data = malloc(size * sizeof(u16));
  return vector;
}

Vecu16 *vecu16_allocN(u32 n, ...) {
  Vecu16 *vector = vecu16_alloc(n);
  va_list args;
  va_start(args, n);
  i32 i;
  for(i = 0; i < n; i++) {
    vector->data[i] = va_arg(args, i32);
  }
  va_end(args);
  return vector;
}

void vecu16_free(Vecu16 *vector) {
  free(vector->data);
  free(vector);
}


// --------------------------------------------------------------------------
// Operation
// --------------------------------------------------------------------------

u16 *vecu16_at(Vecu16 *vector, u32 index) {
  if(index >= vector->size) {
    boundsErrorAndExit("vecu16_at", vector->size, index);
  }
  return &vector->data[index];
}

bool vecu16_indexOf(Vecu16 *vector, u16 value, u32 offset, u32 *index) {
  i32 i;
  for(i = offset; i < vector->size; i++) {
    if(*vecu16_at(vector, i) == value) {
      *index = i;
      return 1;
    }
  }
  return 0;
}

void vecu16_fill(Vecu16 *vector, u16 val) {
  i32 i;
  for(i = 0; i < vector->size; i++) {
    *vecu16_at(vector, i) = val;
  }
}

void vecu16_setToRange(Vecu16 *vector, u16 from, u16 to, u16 offset) {
  if(vector->size <= from || vector->size < to) {
    boundsErrorAndExit("vecu16_setToRange", vector->size, u16_max(from, to));
  }
  i32 i;
  for(i = from; i < to; i++) {
    *vecu16_at(vector, i) = i - from + offset;
  }
}

void vecu16_resize(Vecu16 *vector, u32 newSize) {
  if(vector->allocSize < newSize) {
    boundsErrorAndExit("vecu16_resize", vector->size, newSize);
  }
  vector->size = newSize;
}

Vecu16 *vecu16_copy(Vecu16 *vector) {
  Vecu16 *copy = vecu16_alloc(vector->allocSize);
  copy->size = vector->size;
  i32 i;
  for(i = 0; i < copy->allocSize; i++) {
    copy->data[i] = vector->data[i];
  }
  return copy;
}

void vecu16_copyInto(Vecu16 *to, Vecu16 *from) {
  if(to->size < from->size) {
    boundsErrorAndExit("vecu16_copyInto", to->size, from->size);
  }
  i32 i;
  for(i = 0; i < from->size; i++) {
    *vecu16_at(to, i) = *vecu16_at(from, i);
  }
}

void vecu16_sort(Vecu16 *vector, u32 start, u32 end) {
  if(start >=vector->size || end >= vector->size) {
    boundsErrorAndExit("vecu16_sort", vector->size, u16_max(start, end));
  }
  u16 *base = &vector->data[start];
  u32 num = end - start + 1;
  bool u16_lessThanCompare(const void *x, const void* y);
  qsort(base, num, sizeof(u16), u16_lessThanCompare);
}

bool vecu16_areEqualVectors(Vecu16 *a, Vecu16 *b) {
  if(a->size != b->size) {
    return 0;
  }
  i32 i;
  for(i = 0; i < a->size; i++) {
    if(*vecu16_at(a, i) != *vecu16_at(b, i)) {
      return 0;
    }
  }
  return 1;
}

bool vecu16_haveEqualContent(Vecu16 *a, Vecu16 *b) {
  errorAndExit("vecu16_haveEqualContent not implemented yet");
  return 0;
}

bool vecu16_hasDuplicates(Vecu16 *vector) {
  i32 i, j;
  u16 ele;
  for(i = 0; i < vector->size; i++) {
    ele = *vecu16_at(vector, i);
    for(j = 0; j < i; j++) {
      if(ele == *vecu16_at(vector, j)) {
        return 1;
      }
    }
  }
  return 0;
}

u16 vecu16_max(Vecu16 *vector) {
  if(vector->size == 0) {
    errorAndExit("vecu16_max: No elements");
  }
  i32 i;
  u16 max = U16_MIN;
  for(i = 0; i < vector->size; i++) {
    max = u16_max(max, *vecu16_at(vector, i));
  }
  return max;
}

u16 vecu16_min(Vecu16 *vector) {
  if(vector->size == 0) {
    errorAndExit("vecu16_min: No elements");
  }
  i32 i;
  u16 min = U16_MAX;
  for(i = 0; i < vector->size; i++) {
    min = u16_min(min, *vecu16_at(vector, i));
  }
  return min;
}

// ----------------------------------------------------------------------------

bool u16_lessThanCompare(const void *x, const void *y) {
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
