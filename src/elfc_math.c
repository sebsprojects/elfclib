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


// --------------------------------------------------------------------------
// Vector operations
// --------------------------------------------------------------------------

u16 vecu16_max(Vecu16 *vector) {
  i32 i;
  u16 max = U16_MIN;
  for(i = 0; i < vector->size; i++) {
    max = u16_max(max, *vecu16_at(vector, i));
  }
  return max;
}

u16 vecu16_min(Vecu16 *vector) {
  i32 i;
  u16 min = U16_MAX;
  for(i = 0; i < vector->size; i++) {
    min = u16_min(min, *vecu16_at(vector, i));
  }
  return min;
}

i32 veci32_max(Veci32 *vector) {
  i32 i;
  i32 max = I32_MIN;
  for(i = 0; i < vector->size; i++) {
    max = i32_max(max, *veci32_at(vector, i));
  }
  return max;
}

i32 veci32_min(Veci32 *vector) {
  i32 i;
  i32 min = I32_MAX;
  for(i = 0; i < vector->size; i++) {
    min = i32_min(min, *veci32_at(vector, i));
  }
  return min;
}

f32 vecf32_max(Vecf32 *vector) {
  i32 i;
  f32 max = F32_MIN;
  for(i = 0; i < vector->size; i++) {
    max = f32_max(max, *vecf32_at(vector, i));
  }
  return max;
}

f32 vecf32_min(Vecf32 *vector) {
  i32 i;
  f32 min = F32_MAX;
  for(i = 0; i < vector->size; i++) {
    min = f32_min(min, *vecf32_at(vector, i));
  }
  return min;
}
