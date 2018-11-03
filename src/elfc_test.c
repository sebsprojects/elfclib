#include "../include/elfc_test.h"
#include "../include/elfc_vecu16.h"

#include <stdarg.h>


// ---------------------------------------------------------------------------
// Checking functions
// ---------------------------------------------------------------------------

bool test_checkVecu16N(Vecu16 *vec, u32 n, ...)
{
  bool ok = 1;
  va_list args;
  va_start(args, n);
  for(i32 i = 0; i < n; i++) {
    ok = ok && *vecu16_at(vec, i) == va_arg(args, i32);
  }
  va_end(args);
  return ok;
}


// ---------------------------------------------------------------------------
// Inlines
// ---------------------------------------------------------------------------

extern void test_printHeader(char *name);
extern void test_printFooter();
extern void test_printMessage(bool ok, char *name);
