#include "../include/elfc_print.h"
#include "../include/elfc_math.h"
#include "../include/elfc_vecu16.h"
#include "../include/elfc_veci32.h"
#include "../include/elfc_vecf32.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>


// --------------------------------------------------------------------------
// Vector printing
// --------------------------------------------------------------------------

void veci32_sprint(char *pstring, Veci32 *vector, u32 width) {
  i32 viMin = veci32_min(vector);
  u32 maxAbs = i32_max(abs(veci32_max(vector)), abs(viMin));
  u32 numDigits = maxAbs == 0 ? 1 : floor(log10(maxAbs)) + 1;
  u32 padTo = numDigits + (viMin < 0 ? 1 : 0);
  u32 perLine = width / (padTo + 2); // account for ', '
  char format[20]; format[0] = '\0';
  sprintf(format, "%s%u%s", "%", padTo, "i");
  sprintf(pstring, "vi32: len=%u\n", vector->size);
  i32 i;
  for(i = 0; i < vector->size; i++) {
    sprintf(pstring + strlen(pstring), format, *veci32_at(vector, i), padTo);
    if(i < vector->size - 1) {
      sprintf(pstring + strlen(pstring), ", ");
      if((i + 1) % perLine == 0) {
        sprintf(pstring + strlen(pstring), "\n");
      }
    }
  }
}

void veci32_print(Veci32 *vector) {
  i32 viMin = veci32_min(vector);
  u32 maxAbs = i32_max(abs(veci32_max(vector)), abs(viMin));
  u32 numDigits = maxAbs == 0 ? 1 : floor(log10(maxAbs)) + 1;
  u32 width = 80;
  char *pstring = malloc(100 + (numDigits + 3) * vector->size);
  veci32_sprint(pstring, vector, width);
  printf("%s\n", pstring);
  free(pstring);
}

// ---------------------------------------------------------------------------

void vecu16_sprint(char *pstring, Vecu16 *vector, u32 width) {
  u16 viMin = vecu16_min(vector);
  u16 maxAbs = u16_max(abs(vecu16_max(vector)), abs(viMin));
  u32 numDigits = maxAbs == 0 ? 1 : floor(log10(maxAbs)) + 1;
  u32 padTo = numDigits + (viMin < 0 ? 1 : 0);
  u32 perLine = width / (padTo + 2); // account for ', '
  char format[20]; format[0] = '\0';
  sprintf(format, "%s%u%s", "%", padTo, "i");
  sprintf(pstring, "vu16: len=%u\n", vector->size);
  i32 i;
  for(i = 0; i < vector->size; i++) {
    sprintf(pstring + strlen(pstring), format, *vecu16_at(vector, i), padTo);
    if(i < vector->size - 1) {
      sprintf(pstring + strlen(pstring), ", ");
      if((i + 1) % perLine == 0) {
        sprintf(pstring + strlen(pstring), "\n");
      }
    }
  }
}

void vecu16_print(Vecu16 *vector) {
  u16 viMin = vecu16_min(vector);
  u16 maxAbs = i32_max(abs(vecu16_max(vector)), abs(viMin));
  u32 numDigits = maxAbs == 0 ? 1 : floor(log10(maxAbs)) + 1;
  u32 width = 80;
  char *pstring = malloc(100 + (numDigits + 3) * vector->size);
  vecu16_sprint(pstring, vector, width);
  printf("%s\n", pstring);
  free(pstring);
}

// ---------------------------------------------------------------------------


void vecf32_sprint(char *pstring, Vecf32 *vector, u32 width, u32 numDecimal) {
  float viMin = vecf32_min(vector);
  u32 maxAbs = i32_max(abs(floor(vecf32_max(vector))), abs(floor(viMin)));
  u32 numDigits = maxAbs == 0 ? 1 : floor(log10(maxAbs)) + 1;
  u32 padTo = numDigits + numDecimal + (viMin < 0 ? 1 : 0);
  u32 perLine = width / (padTo + 2); // account for ', '
  char format[20]; format[0] = '\0';
  sprintf(format, "%s%u%s", "%", padTo, ".3f");
  sprintf(pstring, "f32: len=%u\n", vector->size);
  i32 i;
  for(i = 0; i < vector->size; i++) {
    sprintf(pstring + strlen(pstring), format, *vecf32_at(vector, i), padTo);
    if(i < vector->size - 1) {
      sprintf(pstring + strlen(pstring), ", ");
      if((i + 1) % perLine == 0) {
        sprintf(pstring + strlen(pstring), "\n");
      }
    }
  }
}

void vecf32_print(Vecf32 *vector) {
  i32 viMin = vecf32_min(vector);
  u32 maxAbs = i32_max(abs(vecf32_max(vector)), abs(viMin));
  u32 numDigits = maxAbs == 0 ? 1 : floor(log10(maxAbs)) + 1;
  u32 width = 80;
  u32 numDecimal = 3;
  char *pstring = malloc(100 + (numDigits + numDecimal + 4) * vector->size);
  vecf32_sprint(pstring, vector, width, numDecimal);
  printf("%s\n", pstring);
  free(pstring);
}

