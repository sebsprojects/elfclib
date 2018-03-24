#ifndef ELFC_MATH
#define ELFC_MATH

#include <stdint.h>


// --------------------------------------------------------------------------
// Basic math
// --------------------------------------------------------------------------

int32_t i32_max(int32_t a, int32_t b);
int32_t i32_min(int32_t a, int32_t b);

double f64_max(double a, double b);
double f64_min(double a, double b);


// --------------------------------------------------------------------------
// Vector operations
// --------------------------------------------------------------------------

// TODO: returns INT_MIN / INT_MAX if size is 0
struct Vector_i32;
int32_t vi32_max(struct Vector_i32 *vector);
int32_t vi32_min(struct Vector_i32 *vector);

struct Vector_f64;
double vf64_max(struct Vector_f64 *vector);
double vf64_min(struct Vector_f64 *vector);


#endif