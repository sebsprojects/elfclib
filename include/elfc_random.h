#ifndef ELFC_RANDOM
#define ELFC_RANDOM

#include "elfc_common.h"


void rand_setSeed(u32 seed);

/*
 * Return a (bad) pseudo-random number in [lower, upper]
 */
u32 rand_getU32InRange(u32 lower, u32 upper);

#endif
