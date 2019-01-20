#include "../include/elfc_test.h"
#include "../include/elfc_math.h"


bool test_math_factorial()
{
  bool ok = 1;

  return 0;
}

bool test_math_getPrimeFactors()
{
  bool ok = 1;

  return 0;
}

bool test_math_getFactors()
{
  bool ok = 1;

  return 0;
}

void test_math()
{
  test_printHeader("math");
  test_printMessage(test_math_factorial(), "math_factorial");
  test_printMessage(test_math_getPrimeFactors(), "math_getPrimeFactors");
  test_printMessage(test_math_getFactors(), "math_getFactors");
  test_printFooter();
}
