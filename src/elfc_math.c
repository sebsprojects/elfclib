#include "../include/elfc_math.h"
#include "../include/elfc_vector.h"


// --------------------------------------------------------------------------
// Basic math
// --------------------------------------------------------------------------

int32_t i32_max(int32_t a, int32_t b) {
  return a < b ? b : a;
}

int32_t i32_min(int32_t a, int32_t b) {
  return a < b ? a : b;
}


// --------------------------------------------------------------------------
// Vector operations
// --------------------------------------------------------------------------

int32_t vi32_max(Vector_i32 *vector) {
  uint32_t i;
  uint32_t max = INT32_MIN;
  for(i = 0; i < vector->size; i++) {
    max = i32_max(max, *vi32_at(vector, i));
  }
  return max;
}

int32_t vi32_min(Vector_i32 *vector) {
  uint32_t i;
  uint32_t min = INT32_MAX;
  for(i = 0; i < vector->size; i++) {
    min = i32_min(min, *vi32_at(vector, i));
  }
  return min;
}
