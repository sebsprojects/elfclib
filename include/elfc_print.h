#ifndef ELFC_PRINT
#define ELFC_PRINT

#include <stdint.h>


// --------------------------------------------------------------------------
// String and Printing
// --------------------------------------------------------------------------

static void padString(char *string, uint32_t pad);


// --------------------------------------------------------------------------
// Vector printing
// --------------------------------------------------------------------------

struct Vector_i32;
void vi32_print(struct Vector_i32 *vector);


#endif
