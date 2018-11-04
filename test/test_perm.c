#include "../include/elfc_test.h"
#include "../include/elfc_common.h"
#include "../include/elfc_perm.h"


bool test_perm_init() {
  bool ok = 1;
  Vecu16 *vec = vecu16_alloc(4);
  perm_init(vec);
  for(i32 i = 0; i < vec->size; i++) {
    ok = ok && *vecu16_at(vec, i) == i;
  }
  vecu16_free(vec);
  return ok;
}

// tests the usual shifting cases
bool test_perm_shift_basic() {
  bool ok = 1;
  Vecu16 *vec = vecu16_alloc(4);
  perm_init(vec); // 0 1 2 3
  perm_shiftDefault(vec);
  ok = ok && test_checkVecu16N(vec, 4, 0, 1, 3, 2);
  ok = ok && perm_shiftDefault(vec);
  ok = ok && test_checkVecu16N(vec, 4, 0, 2, 1, 3);
  ok = ok &&perm_shiftDefault(vec);
  ok = ok && test_checkVecu16N(vec, 4, 0, 2, 3, 1);
  ok = ok && perm_shift(vec, 0, 2); // shift!
  ok = ok && test_checkVecu16N(vec, 4, 2, 0, 3, 1);
  ok = ok && perm_shiftDefault(vec);
  ok = ok && test_checkVecu16N(vec, 4, 2, 1, 0, 3);
  ok = ok && perm_shiftDefault(vec);
  ok = ok && test_checkVecu16N(vec, 4, 2, 1, 3, 0);
  ok = ok && perm_shiftDefault(vec);
  ok = ok && test_checkVecu16N(vec, 4, 2, 3, 0, 1);
  ok = ok && perm_shift(vec, 0, 2); // shift!
  ok = ok && test_checkVecu16N(vec, 4, 3, 2, 0, 1);
  ok = ok && !perm_shift(vec, 0, 2);
  ok = ok && !perm_shift(vec, 1, 3);
  ok = ok && perm_shiftDefault(vec);
  ok = ok && test_checkVecu16N(vec, 4, 3, 2, 1, 0);
  ok = ok && !perm_shiftDefault(vec);
  vecu16_free(vec);
  return ok;
}


// tests the edge case of shifting a single element permutation
bool test_perm_shift_single() {
  bool ok = 1;
  Vecu16 *vec = vecu16_alloc(1);
  perm_init(vec);
  ok = ok && *vecu16_at(vec, 0) == 0;
  ok = ok && !perm_shiftDefault(vec);
  ok = ok && *vecu16_at(vec, 0) == 0;
  vecu16_free(vec);
  return ok;
}

bool test_binom_shift_basic()
{
  bool ok = 1;
  Vecu16 *vec = vecu16_alloc(5);
  binom_init(vec, 1, 3, 1); // 0xfffff 1 2 3 0xffff
  ok = ok && test_checkVecu16N(vec, 5, 0xffff, 1, 2, 3, 0xffff);
  ok = ok && binom_shift(vec, 5, 3, 1);
  ok = ok && test_checkVecu16N(vec, 5, 0xffff, 1, 2, 4, 0xffff);
  ok = ok && binom_shift(vec, 5, 3, 1);
  ok = ok && test_checkVecu16N(vec, 5, 0xffff, 1, 2, 5, 0xffff);
  ok = ok && binom_shift(vec, 5, 3, 1);
  ok = ok && test_checkVecu16N(vec, 5, 0xffff, 1, 3, 4, 0xffff);
  ok = ok && binom_shift(vec, 5, 3, 1);
  ok = ok && test_checkVecu16N(vec, 5, 0xffff, 1, 3, 5, 0xffff);
  ok = ok && binom_shift(vec, 5, 3, 1);
  ok = ok && test_checkVecu16N(vec, 5, 0xffff, 1, 4, 5, 0xffff);
  ok = ok && binom_shift(vec, 5, 3, 1);
  ok = ok && test_checkVecu16N(vec, 5, 0xffff, 2, 3, 4, 0xffff);
  ok = ok && binom_shift(vec, 5, 3, 1);
  ok = ok && test_checkVecu16N(vec, 5, 0xffff, 2, 3, 5, 0xffff);
  ok = ok && binom_shift(vec, 5, 3, 1);
  ok = ok && test_checkVecu16N(vec, 5, 0xffff, 2, 4, 5, 0xffff);
  ok = ok && binom_shift(vec, 5, 3, 1);
  ok = ok && test_checkVecu16N(vec, 5, 0xffff, 3, 4, 5, 0xffff);
  ok = ok && !binom_shift(vec, 5, 3, 1);
  ok = ok && test_checkVecu16N(vec, 5, 0xffff, 3, 4, 5, 0xffff);
  vecu16_free(vec);
  return ok;
}

// tests edge case with a single element to shift
bool test_binom_shift_single()
{
  bool ok = 1;
  Vecu16 *vec = vecu16_alloc(1);
  binom_init(vec, 0, 1, 0);
  ok = ok && *vecu16_at(vec, 0) == 0;
  ok = ok && binom_shift(vec, 2, 1, 0);
  ok = ok && *vecu16_at(vec, 0) == 1;
  ok = ok && binom_shift(vec, 2, 1, 0);
  ok = ok && *vecu16_at(vec, 0) == 2;
  ok = ok && !binom_shift(vec, 2, 1, 0);
  ok = ok && *vecu16_at(vec, 0) == 2;
  vecu16_free(vec);
  vec = vecu16_alloc(3);
  binom_init(vec, 1, 1, 1);
  ok = ok && test_checkVecu16N(vec, 3, 0xffff, 1, 0xffff);
  ok = ok && binom_shift(vec, 2, 1, 1);
  ok = ok && test_checkVecu16N(vec, 3, 0xffff, 2, 0xffff);
  ok = ok && !binom_shift(vec, 2, 1, 1);
  ok = ok && test_checkVecu16N(vec, 3, 0xffff, 2, 0xffff);
  vecu16_free(vec);
  return ok;
}

void test_perm()
{
  test_printHeader("perm");
  test_printMessage(test_perm_init(), "perm_init");
  test_printMessage(test_perm_shift_basic(), "perm_shift (basic)");
  test_printMessage(test_perm_shift_single(), "perm_shift (single)");
  test_printMessage(test_binom_shift_basic(), "binom_shift (basic)");
  test_printMessage(test_binom_shift_single(), "binom_shift (single)");
  test_printFooter();
}
