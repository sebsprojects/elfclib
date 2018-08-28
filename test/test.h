#ifndef ELFC_TEST
#define ELFC_TEST

#include "../include/elfc_common.h"

#include <stdio.h>

inline void printTestHeader(char *name) {
  printf("Testing %s ...\n", name);
}

inline void printTestFooter() {
  printf("\n");
}

inline void printTestMessage(bool ok, char *name) {
  char *okString = ok ? "Okay" : "Fail";
  printf("  [%s] :: %s\n", okString, name);
}

#endif
