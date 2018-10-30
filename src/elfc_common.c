#include "../include/elfc_common.h"

#include <stdlib.h>
#include <stdio.h>


// ---------------------------------------------------------------------------
// Inlines
// ---------------------------------------------------------------------------

extern u16 u16_max(u16 a, u16 b);
extern u16 u16_min(u16 a, u16 b);

extern i32 i32_max(i32 a, i32 b);
extern i32 i32_min(i32 a, i32 b);

extern f32 f32_max(f32 a, f32 b);
extern f32 f32_min(f32 a, f32 b);

extern u32 get2DIndex(u32 width, u32 w, u32 h);


// ---------------------------------------------------------------------------
// Error Functions
// ---------------------------------------------------------------------------

void errorAndExit(char *message)
{
  fprintf(stderr, "%s", message);
  exit(1);
}

void boundsErrorAndExit(char *message, u32 bound, u32 index)
{
  fprintf(stderr, "Out of bounds error at %s: bound=%u index=%u",
          message, bound, index);
  exit(1);
}
