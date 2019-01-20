#include "../include/elfc_math.h"

#include <math.h>


u32 math_factorial(u32 n)
{
#ifdef BOUNDS_CHECK
  if(n > 12) {
    boundsErrorAndExit("math_factorial", 12, n);
  }
#endif
  if(n == 0) {
    return 1;
  } else {
    return n * math_factorial(n - 1);
  }
}

Vecu16 *math_getPrimeFactors_alloc(u32 n)
{
#ifdef BOUNDS_CHECK
  if(n <= 1) {
    boundsErrorAndExit("math_getPrimeFactors", 2, n);
  }
#endif
  i32 sqrtn = floor(sqrt(n));
  Vecu16 *vec = vecu16_alloc(n / sqrtn);
  i32 c = 0;
  for(i32 i = 2; i <= sqrtn; i++) {
    while(n % i == 0) {
      *vecu16_at(vec, c) = i;
      c++;
      n = n / i;
    }
  }
  if(n > 2) {
    *vecu16_at(vec, c) = n; // in case n is prime
    c++;
  }
  vecu16_resize(vec, c);
  return vec;
}

Vecu16 *math_getFactors_alloc(u32 n)
{
  Vecu16 *vec = vecu16_alloc(n / 2 + 1);
  if(n == 0) {
    *vecu16_at(vec, 0) = 0;
    return vec; // n / 2 + 1 = 1, so no resize req
  }
  i32 c = 0;
  for(i32 i = 1; i <= n; i++) {
    if(n % i == 0) {
      *vecu16_at(vec, c) = i;
      c++;
    }
  }
  vecu16_resize(vec, c);
  return vec;
}
