#include "../include/elfc_common.h"

#include <stdlib.h>
#include <stdio.h>


void errorAndExit(char *message) {
  fprintf(stderr, "%s", message);
  exit(1);
}

void boundsErrorAndExit(char *message, u32 bound, u32 index) {
  fprintf(stderr, "Out of bounds error at %s: bound=%u index=%u",
          message, bound, index);
  exit(1);
}
