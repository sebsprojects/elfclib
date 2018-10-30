#include "../include/elfc_veci32.h"

#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <math.h>


// ---------------------------------------------------------------------------
// Inlines
// ---------------------------------------------------------------------------

extern i32 *veci32_at(Veci32 *vector, u32 index);


// --------------------------------------------------------------------------
// Alloc / Free
// --------------------------------------------------------------------------

Veci32 *veci32_alloc(u32 size)
{
#ifdef BOUNDS_CHECK
  if(size == 0) {
    boundsErrorAndExit("veci32_alloc", 1, size);
  }
#endif
  Veci32 *vector = malloc(sizeof(Veci32));
  vector->allocSize = size;
  vector->size = size;
  vector->data = malloc(size * sizeof(i32));
  return vector;
}

Veci32 *veci32_allocN(u32 n, ...)
{
#ifdef BOUNDS_CHECK
  if(n == 0) {
    boundsErrorAndExit("veci32_allocN", 1, n);
  }
#endif
  Veci32 *vector = veci32_alloc(n);
  va_list args;
  va_start(args, n);
  for(i32 i = 0; i < n; i++) {
    vector->data[i] = va_arg(args, i32);
  }
  va_end(args);
  return vector;
}

void veci32_free(Veci32 *vector)
{
  free(vector->data);
  free(vector);
}


// --------------------------------------------------------------------------
// Operation
// --------------------------------------------------------------------------

bool veci32_indexOf(Veci32 *vector, i32 value, u32 offset, u32 *index)
{
  for(i32 i = offset; i < vector->size; i++) {
    if(*veci32_at(vector, i) == value) {
      *index = i;
      return 1;
    }
  }
  return 0;
}

i32 veci32_max(Veci32 *vector)
{
#ifdef BOUNDS_CHECK
  if(vector->size == 0) {
    errorAndExit("veci32_max: No elements");
  }
#endif
  i32 max = I32_MIN;
  for(i32 i = 0; i < vector->size; i++) {
    max = i32_max(max, *veci32_at(vector, i));
  }
  return max;
}

i32 veci32_min(Veci32 *vector)
{
#ifdef BOUNDS_CHECK
  if(vector->size == 0) {
    errorAndExit("veci32_min: No elements");
  }
#endif
  i32 min = I32_MAX;
  for(i32 i = 0; i < vector->size; i++) {
    min = i32_min(min, *veci32_at(vector, i));
  }
  return min;
}


// --------------------------------------------------------------------------
// Print
// --------------------------------------------------------------------------

void veci32_sprint(char *pstring, Veci32 *vector, u32 width)
{
  i32 viMin = veci32_min(vector);
  u32 maxAbs = i32_max(abs(veci32_max(vector)), abs(viMin));
  u32 numDigits = maxAbs == 0 ? 1 : floor(log10(maxAbs)) + 1;
  u32 padTo = numDigits + (viMin < 0 ? 1 : 0);
  u32 perLine = width / (padTo + 2); // account for ', '
  char format[20]; format[0] = '\0';
  sprintf(format, "%s%u%s", "%", padTo, "i");
  sprintf(pstring, "vi32: len=%u\n", vector->size);
  for(i32 i = 0; i < vector->size; i++) {
    sprintf(pstring + strlen(pstring), format, *veci32_at(vector, i), padTo);
    if(i < vector->size - 1) {
      sprintf(pstring + strlen(pstring), ", ");
      if((i + 1) % perLine == 0) {
        sprintf(pstring + strlen(pstring), "\n");
      }
    }
  }
}

void veci32_print(Veci32 *vector)
{
  i32 viMin = veci32_min(vector);
  u32 maxAbs = i32_max(abs(veci32_max(vector)), abs(viMin));
  u32 numDigits = maxAbs == 0 ? 1 : floor(log10(maxAbs)) + 1;
  u32 width = 80;
  char *pstring = malloc(100 + (numDigits + 3) * vector->size);
  veci32_sprint(pstring, vector, width);
  printf("%s\n", pstring);
  free(pstring);
}
