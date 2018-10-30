#include "../include/elfc_vecf32.h"

#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <math.h>


// ---------------------------------------------------------------------------
// Inlines
// ---------------------------------------------------------------------------

extern f32 *vecf32_at(Vecf32 *vector, u32 index);


// ---------------------------------------------------------------------------
// Alloc / Free
// ---------------------------------------------------------------------------

Vecf32 *vecf32_alloc(u32 size)
{
#ifdef BOUNDS_CHECK
  if(size == 0) {
    boundsErrorAndExit("vecf32_alloc", 1, size);
  }
#endif
  Vecf32 *vector = malloc(sizeof(Vecf32));
  vector->allocSize = size;
  vector->size = size;
  vector->data = malloc(size * sizeof(f32));
  return vector;
}

Vecf32 *vecf32_allocN(u32 n, ...)
{
#ifdef BOUNDS_CHECK
  if(n == 0) {
    boundsErrorAndExit("vecf32_allocN", 1, n);
  }
#endif
  Vecf32 *vector = vecf32_alloc(n);
  va_list args;
  va_start(args, n);
  for(i32 i = 0; i < n; i++) {
    vector->data[i] = (float) va_arg(args, double);
  }
  va_end(args);
  return vector;
}

void vecf32_free(Vecf32 *vector)
{
  free(vector->data);
  free(vector);
}


// ---------------------------------------------------------------------------
// Operation
// ---------------------------------------------------------------------------

f32 vecf32_max(Vecf32 *vector)
{
#ifdef BOUNDS_CHECK
  if(vector->size == 0) {
    errorAndExit("vecf32_max: No elements");
  }
#endif
  f32 max = F32_MIN;
  for(i32 i = 0; i < vector->size; i++) {
    max = f32_max(max, *vecf32_at(vector, i));
  }
  return max;
}

f32 vecf32_min(Vecf32 *vector)
{
#ifdef BOUNDS_CHECK
  if(vector->size == 0) {
    errorAndExit("vecf32_min: No elements");
  }
#endif
  f32 min = F32_MAX;
  for(i32 i = 0; i < vector->size; i++) {
    min = f32_min(min, *vecf32_at(vector, i));
  }
  return min;
}


// ---------------------------------------------------------------------------
// Print
// ---------------------------------------------------------------------------

void vecf32_sprint(char *pstring, Vecf32 *vector, u32 width, u32 numDecimal)
{
  i32 absViMin = (i32) fabs(vecf32_min(vector));
  i32 absViMax = (i32) fabs(vecf32_max(vector));
  i32 maxAbs = i32_max(absViMin, absViMax);
  u32 numDigits = maxAbs == 0 ? 1 : floor(log10(maxAbs)) + 1;
  u32 padTo = numDigits + numDecimal + (vecf32_min(vector) < 0 ? 1 : 0);
  u32 perLine = width / (padTo + 2); // account for ', '
  char format[20]; format[0] = '\0';
  sprintf(format, "%s%u%s", "%", padTo, ".3f");
  sprintf(pstring, "f32: len=%u\n", vector->size);
  for(i32 i = 0; i < vector->size; i++) {
    sprintf(pstring + strlen(pstring), format, *vecf32_at(vector, i), padTo);
    if(i < vector->size - 1) {
      sprintf(pstring + strlen(pstring), ", ");
      if((i + 1) % perLine == 0) {
        sprintf(pstring + strlen(pstring), "\n");
      }
    }
  }
}

void vecf32_print(Vecf32 *vector)
{
  i32 absViMin = (i32) fabs(vecf32_min(vector));
  i32 absViMax = (i32) fabs(vecf32_max(vector));
  i32 maxAbs = i32_max(absViMin, absViMax);
  u32 numDigits = maxAbs == 0 ? 1 : floor(log10(maxAbs)) + 1;
  u32 width = 80;
  u32 numDecimal = 3;
  char *pstring = malloc(100 + (numDigits + numDecimal + 4) * vector->size);
  vecf32_sprint(pstring, vector, width, numDecimal);
  printf("%s\n", pstring);
  free(pstring);
}
