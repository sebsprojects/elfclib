#ifndef ELFC_MATH
#define ELFC_MATH

#include "elfc_common.h"
#include "elfc_vecu16.h"


u32 math_factorial(u32 n);

/*
 * Returns the prime factors of a natural number > 1. 1 is not a valid input.
 */
Vecu16 *math_getPrimeFactors_alloc(u32 n);

/*
 * Returns all factors of a natural number >= 0.
 * n = 0 results in the vector ( 0 )
 * n = 12 results in the vector ( 1 2 3 6 12 )
 */
Vecu16 *math_getFactors_alloc(u32 n);

#endif
