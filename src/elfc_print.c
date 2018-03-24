#include "../include/elfc_print.h"
#include "../include/elfc_vector.h"
#include "../include/elfc_math.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>


// --------------------------------------------------------------------------
// Vector printing
// --------------------------------------------------------------------------

void vi32_sprint(char *pstring, struct Vector_i32 *vector, uint32_t width) {
  int32_t viMin = vi32_min(vector);
  uint32_t maxAbs = i32_max(abs(vi32_max(vector)), abs(viMin));
  uint32_t numDigits = maxAbs == 0 ? 1 : floor(log10(maxAbs)) + 1;
  uint32_t padTo = numDigits + (viMin < 0 ? 1 : 0);
  uint32_t perLine = width / (padTo + 2); // account for ', '
  char format[20]; format[0] = '\0';
  sprintf(format, "%s%u%s", "%", padTo, "i");
  sprintf(pstring, "vi32: len=%u\n", vector->size);
  uint32_t i;
  for(i = 0; i < vector->size; i++) {
    sprintf(pstring + strlen(pstring), format, *vi32_at(vector, i), padTo);
    if(i < vector->size - 1) {
      sprintf(pstring + strlen(pstring), ", ");
      if((i + 1) % perLine == 0) {
        sprintf(pstring + strlen(pstring), "\n");
      }
    }
  }
}

void vi32_print(struct Vector_i32 *vector) {
  int32_t viMin = vi32_min(vector);
  uint32_t maxAbs = i32_max(abs(vi32_max(vector)), abs(viMin));
  uint32_t numDigits = maxAbs == 0 ? 1 : floor(log10(maxAbs)) + 1;
  uint32_t width = 80;
  char *pstring = malloc(100 + (numDigits + 3) * vector->size);
  vi32_sprint(pstring, vector, width);
  printf("%s\n", pstring);
  free(pstring);
}


// --------------------------------------------------------------------------


void f64_sprint(char *pstring, struct Vector_f64 *vector, uint32_t width) {
  double viMin = vf64_min(vector);
  uint32_t maxAbs = i32_max(abs(floor(vf64_max(vector))), abs(floor(viMin)));
  uint32_t numDigits = maxAbs == 0 ? 1 : floor(log10(maxAbs)) + 1;
  uint32_t padTo = numDigits + 3 + (viMin < 0 ? 1 : 0); // account for '.xx'
  uint32_t perLine = width / (padTo + 2); // account for ', '
  char format[20]; format[0] = '\0';
  sprintf(format, "%s%u%s", "%", padTo, ".2f");
  sprintf(pstring, "f64: len=%u\n", vector->size);
  uint32_t i;
  for(i = 0; i < vector->size; i++) {
    sprintf(pstring + strlen(pstring), format, *vf64_at(vector, i), padTo);
    if(i < vector->size - 1) {
      sprintf(pstring + strlen(pstring), ", ");
      if((i + 1) % perLine == 0) {
        sprintf(pstring + strlen(pstring), "\n");
      }
    }
  }
}

void vf64_print(struct Vector_f64 *vector) {
  int32_t viMin = vf64_min(vector);
  uint32_t maxAbs = i32_max(abs(vf64_max(vector)), abs(viMin));
  uint32_t numDigits = maxAbs == 0 ? 1 : floor(log10(maxAbs)) + 1;
  uint32_t width = 80;
  char *pstring = malloc(100 + (numDigits + 6) * vector->size);
  f64_sprint(pstring, vector, width);
  printf("%s\n", pstring);
  free(pstring);
}
