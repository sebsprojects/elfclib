#ifndef ELFC_TEST
#define ELFC_TEST

#include "elfc_common.h"

#include <stdio.h>

// ---------------------------------------------------------------------------
// Inlines
// ---------------------------------------------------------------------------

inline void printTestHeader(char *name)
{
  printf("\nTesting %s ...\n", name);
}

inline void printTestFooter()
{
  printf("\n");
}

inline void printTestMessage(bool ok, char *name)
{
  char *okString = ok ? "Okay" : "Fail";
  printf("  [%s] :: %s\n", okString, name);
}

#endif
