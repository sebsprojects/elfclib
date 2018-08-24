#ifndef ELFC_MATH
#define ELFC_MATH

#include "elfc_common.h"


// --------------------------------------------------------------------------
// Basic math
// --------------------------------------------------------------------------

u16 u16_max(u16 a, u16 b);
u16 u16_min(u16 a, u16 b);

i32 i32_max(i32 a, i32 b);
i32 i32_min(i32 a, i32 b);

f32 f32_max(f32 a, f32 b);
f32 f32_min(f32 a, f32 b);


// --------------------------------------------------------------------------
// Vector operations
// --------------------------------------------------------------------------

// TODO: returns INT_MIN / INT_MAX if size is 0
struct Vecu16;
u16 vecu16_max(struct Vecu16 *vector);
u16 vecu16_min(struct Vecu16 *vector);

struct Veci32;
i32 veci32_max(struct Veci32 *vector);
i32 veci32_min(struct Veci32 *vector);

struct Vecf32;
f32 vecf32_max(struct Vecf32 *vector);
f32 vecf32_min(struct Vecf32 *vector);


#endif
