#ifndef ELFC_TEST
#define ELFC_TEST

#include "elfc_common.h"

#include <stdio.h>


// ---------------------------------------------------------------------------
// Checking functions
// ---------------------------------------------------------------------------

struct Vecu16;
bool test_checkVecu16N(struct Vecu16 *vec, u32 n, ...);

// ---------------------------------------------------------------------------
// Inlines
// ---------------------------------------------------------------------------

inline void test_printHeader(char *name)
{
  printf("\nTesting %s ...\n", name);
}

inline void test_printFooter()
{
  printf("\n");
}

inline void test_printMessage(bool ok, char *name)
{
  char *okString = ok ? "Okay" : "Fail";
  printf("  [%s] :: %s\n", okString, name);
}

#endif
