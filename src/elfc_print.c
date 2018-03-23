#include "../include/elfc_print.h"
#include "../include/elfc_vector.h"

#include <stdio.h>


// --------------------------------------------------------------------------
// String and Printing
// --------------------------------------------------------------------------

void padString(char *string, uint32_t pad) {
  uint32_t i;
  for(i = 0; i < pad; i++) {
    sprintf(string + strlen(string), " ");
  }
}


// --------------------------------------------------------------------------
// Vector printing
// --------------------------------------------------------------------------

void vi32_print(Vector_i32 *vector) {

}
