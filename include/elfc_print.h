#ifndef ELFC_PRINT
#define ELFC_PRINT

#include <stdint.h>


// --------------------------------------------------------------------------
// Vector printing
// --------------------------------------------------------------------------

struct Vector_i32;
void vi32_sprint(char *pstring, struct Vector_i32 *vector, uint32_t width);
void vi32_print(struct Vector_i32 *vector);

struct Vector_f64;
void vf64_sprint(char *pstring, struct Vector_f64 *vector, uint32_t width);
void vf64_print(struct Vector_f64 *vector);

#endif
