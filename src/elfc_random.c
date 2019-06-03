#include "../include/elfc_random.h"

#include <stdlib.h>


void rand_setSeed(u32 seed)
{
  srand(seed);
}

u32 rand_getU32InRange(u32 lower, u32 upper)
{
  return rand() % (upper - lower + 1) + lower;
}
