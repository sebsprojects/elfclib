#include "test.h"

#include "../include/elfc_common.h"
#include "../include/elfc_vecu16.h"
#include "../include/elfc_print.h"

bool test_fill() {
  Vecu16 *vec = vecu16_alloc(5);
  vecu16_fill(vec, 42);
  bool ok = 1;
  i32 i; for(i = 0; i < vec->size; i++) {
    ok = ok && *vecu16_at(vec, i) == 42;
  }
  //vecu16_print(vec);
  vecu16_free(vec);
  return ok;
}

bool test_setToRange() {
  Vecu16 *vec = vecu16_allocN(7, 0, 0, 0, 0, 0, 0, 0);
  vecu16_setToRange(vec, 2, 5, 2);
  bool ok = 1;
  ok = ok && *vecu16_at(vec, 0) == 0;
  ok = ok && *vecu16_at(vec, 1) == 0;
  ok = ok && *vecu16_at(vec, 5) == 0;
  ok = ok && *vecu16_at(vec, 6) == 0;
  i32 i; for(i = 2; i < 5; i++) {
    ok = ok && *vecu16_at(vec, i) == i;
  }
  //vecu16_print(vec);
  vecu16_free(vec);
  return ok;
}

bool test_resize() {
  Vecu16 *vec = vecu16_alloc(10);
  vecu16_fill(vec, 0);
  bool ok = 1;
  ok = ok && vec->size == 10;
  vecu16_resize(vec, 4);
  ok = ok && vec->size == 4;
  vecu16_resize(vec, 10);
  ok = ok && vec->size == 10;
  vecu16_free(vec);
  return ok;
}

bool test_copy() {
  Vecu16 *vec = vecu16_allocN(4, 1, 2, 3, 4);
  vecu16_resize(vec, 2);
  Vecu16 *copy = vecu16_copy(vec);
  bool ok = 1;
  ok = ok && copy->size == 2;
  ok = ok && copy->allocSize == 4;
  i32 i; for(i = 0; i < vec->allocSize; i++) {
    ok = ok && vec->data[i] == copy->data[i];
  }
  vecu16_free(copy);
  vecu16_free(vec);
  return ok;
}

bool test_copyInto() {
  Vecu16 *vec = vecu16_allocN(4, 1, 2, 3, 4);
  Vecu16 *copy = vecu16_allocN(4, 0, 0, 0, 0);
  vecu16_resize(vec, 3);
  vecu16_copyInto(copy, vec);
  bool ok = 1;
  i32 i; for(i = 0; i < vec->size; i++) {
    ok = ok && *vecu16_at(vec, i) == *vecu16_at(copy, i);
  }
  ok = ok && *vecu16_at(copy, 3) == 0;
  vecu16_free(copy);
  vecu16_free(vec);
  return ok;
}

bool test_sort() {
  Vecu16 *vec = vecu16_allocN(6, 6, 5, 3, 2, 4, 1);
  vecu16_sort(vec, 2, 4);
  bool ok = 1;
  ok = ok && *vecu16_at(vec, 0) == 6;
  ok = ok && *vecu16_at(vec, 1) == 5;
  ok = ok && *vecu16_at(vec, 2) == 2;
  ok = ok && *vecu16_at(vec, 3) == 3;
  ok = ok && *vecu16_at(vec, 4) == 4;
  ok = ok && *vecu16_at(vec, 5) == 1;
  vecu16_free(vec);
  return ok;
}

bool test_areEqualVectors() {
  Vecu16 *vec = vecu16_allocN(5, 1, 2, 3, 4, 5);
  Vecu16 *copy = vecu16_copy(vec);
  bool ok = 1;
  // test basic case
  ok = ok && vecu16_areEqualVectors(vec, copy);
  // test that only up to size matters
  *vecu16_at(copy, 4) = 0;
  vecu16_resize(vec, 4);
  vecu16_resize(copy, 4);
  ok = ok && vecu16_areEqualVectors(vec, copy);
  // test order matters
  *vecu16_at(copy, 0) = 1;
  *vecu16_at(copy, 1) = 0;
  ok = ok && !vecu16_areEqualVectors(vec, copy);
  vecu16_free(copy);
  vecu16_free(vec);
  return ok;
}

bool test_haveEqualContent() {
  Vecu16 *a = vecu16_allocN(4, 1, 2, 3, 1);
  Vecu16 *b = vecu16_allocN(4, 2, 3, 1, 1);
  Vecu16 *c = vecu16_allocN(4, 2, 1, 2, 3);
  bool ok = 1;
  ok = ok && vecu16_haveEqualContent(a, b);
  ok = ok && !vecu16_haveEqualContent(a, c);
  vecu16_free(c);
  vecu16_free(b);
  vecu16_free(a);
  return ok;
}

bool test_hasDuplicates() {
  Vecu16 *a = vecu16_allocN(5, 1, 2, 3, 3, 4);
  Vecu16 *b = vecu16_allocN(5, 1, 2, 3, 4, 5);
  bool ok = 1;
  ok = ok && vecu16_hasDuplicates(a);
  ok = ok && !vecu16_hasDuplicates(b);
  vecu16_free(b);
  vecu16_free(a);
  return ok;
}

void test_vecu16() {
  printTestHeader("vecu16");
  printTestMessage(test_fill(), "vecu16_fill");
  printTestMessage(test_setToRange(), "vecu16_setToRange");
  printTestMessage(test_resize(), "vecu16_resize");
  printTestMessage(test_copy(), "vecu16_copy");
  printTestMessage(test_copyInto(), "vecu16_copyInto");
  printTestMessage(test_sort(), "vecu16_copySort");
  printTestMessage(test_areEqualVectors(), "vecu16_areEqualVectors");
  printTestMessage(test_haveEqualContent(), "vecu16_haveEqualContent");
  printTestMessage(test_hasDuplicates(), "vecu16_hasDuplicates");
  printTestFooter();
}
