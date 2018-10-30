#ifndef ELFC_COMMON
#define ELFC_COMMON

#include <stdint.h>

// ---------------------------------------------------------------------------
// Constants and typedefs
// ---------------------------------------------------------------------------

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


// ---------------------------------------------------------------------------
// Error functions
// ---------------------------------------------------------------------------

void errorAndExit(char *message);
void boundsErrorAndExit(char *message, u32 bound, u32 index);


// ---------------------------------------------------------------------------
// Utility functions
// ---------------------------------------------------------------------------

inline u16 u16_max(u16 a, u16 b)
{
  return a < b ? b : a;
}

inline u16 u16_min(u16 a, u16 b)
{
  return a < b ? a : b;
}

inline i32 i32_max(i32 a, i32 b)
{
  return a < b ? b : a;
}

inline i32 i32_min(i32 a, i32 b)
{
  return a < b ? a : b;
}

inline f32 f32_max(f32 a, f32 b)
{
  return a < b ? b : a;
}

inline f32 f32_min(f32 a, f32 b)
{
  return a < b ? a : b;
}

inline u32 get2DIndex(u32 width, u32 w, u32 h)
{
  return width * h + w;
}


#endif
