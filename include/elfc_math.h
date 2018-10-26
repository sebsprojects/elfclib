#ifndef ELFC_MATH
#define ELFC_MATH

#include "elfc_common.h"


// --------------------------------------------------------------------------
// Basic math
// --------------------------------------------------------------------------


inline u16 u16_max(u16 a, u16 b) {
  return a < b ? b : a;
}

inline u16 u16_min(u16 a, u16 b) {
  return a < b ? a : b;
}

inline i32 i32_max(i32 a, i32 b) {
  return a < b ? b : a;
}

inline i32 i32_min(i32 a, i32 b) {
  return a < b ? a : b;
}

inline f32 f32_max(f32 a, f32 b) {
  return a < b ? b : a;
}

inline f32 f32_min(f32 a, f32 b) {
  return a < b ? a : b;
}


#endif
