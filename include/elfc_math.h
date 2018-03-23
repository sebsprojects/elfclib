#ifndef ELFC_MATH
#define ELFC_MATH

#include <stdint.h>


// --------------------------------------------------------------------------
// Basic math
// --------------------------------------------------------------------------

int32_t i32_max(int32_t a, int32_t b);
int32_t i32_min(int32_t a, int32_t b);


// --------------------------------------------------------------------------
// Vector operations
// --------------------------------------------------------------------------

struct Vector_i32;

// TODO: returns INT_MIN / INT_MAX if size is 0
int32_t vi32_max(struct Vector_i32 *vector);
int32_t vi32_min(struct Vector_i32 *vector);


#endif
