#include "../include/elfc_math.h"
#include "../include/elfc_vecu16.h"
#include "../include/elfc_veci32.h"
#include "../include/elfc_vecf32.h"


// --------------------------------------------------------------------------
// Basic math
// --------------------------------------------------------------------------

u16 u16_max(u16 a, u16 b) {
  return a < b ? b : a;
}

u16 u16_min(u16 a, u16 b) {
  return a < b ? a : b;
}

i32 i32_max(i32 a, i32 b) {
  return a < b ? b : a;
}

i32 i32_min(i32 a, i32 b) {
  return a < b ? a : b;
}

f32 f32_max(f32 a, f32 b) {
  return a < b ? b : a;
}

f32 f32_min(f32 a, f32 b) {
  return a < b ? a : b;
}
