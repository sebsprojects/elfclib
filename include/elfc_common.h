#ifndef ELFC_COMMON
#define ELFC_COMMON

#include <stdint.h>

#define U16_MIN 0
#define U16_MAX 65535

#define I32_MIN -2147483648
#define I32_MAX 2147483647

#define F32_MIN -1E-37
#define F32_MAX 1E+37

typedef int32_t bool;

typedef int16_t i16;
typedef int32_t i32;

typedef uint16_t u16;
typedef uint32_t u32;

typedef float f32;
typedef double f64;


void errorAndExit(char *message);
void boundsErrorAndExit(char *message, u32 bound, u32 index);

inline u32 get2DIndex(u32 width, u32 w, u32 h) {
  return width * h + w;
}


#endif
