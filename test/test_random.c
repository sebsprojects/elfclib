#include "../include/elfc_test.h"
#include "../include/elfc_random.h"

#include <stdio.h>

bool test_rand_getU32InRange()
{
  bool ok = 1;
  rand_setSeed(41);
  for(i32 i = 0; i < 20; i++) {
    u32 rand = rand_getU32InRange(0, 9);
    //printf("%u ", rand);
  }
  //printf("\n");
  return ok;
}

void test_random()
{
  test_printHeader("random");
  test_printMessage(test_rand_getU32InRange(), "rand_getU32InRange");
  test_printFooter();
}
