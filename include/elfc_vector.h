#ifndef ELFC_SVECTOR
#define ELFC_SVECTOR

#include "elfc_common.h"


// --------------------------------------------------------------------------
// Types
// --------------------------------------------------------------------------

struct Vector_i32 {
  uint32_t allocSize;
  uint32_t size;
  int32_t *data;
};
typedef struct Vector_i32 Vector_i32;

struct Vector_f64 {
  uint32_t allocSize;
  uint32_t size;
  double *data;
};
typedef struct Vector_f64 Vector_f64;

struct Vector_ptr {
  uint32_t allocSize;
  uint32_t size;
  void **data;
};
typedef struct Vector_ptr Vector_ptr;


// --------------------------------------------------------------------------
// Alloc / Free
// --------------------------------------------------------------------------

Vector_i32 *vi32_alloc(uint32_t size);
Vector_i32 *vi32_allocN(uint32_t n, ...);
void vi32_free(Vector_i32 *vector);

// --

Vector_f64 *vf64_alloc(uint32_t size);
Vector_f64 *vf64_allocN(uint32_t n, ...);
void vf64_free(Vector_f64 *vector);


// --------------------------------------------------------------------------
// Access
// --------------------------------------------------------------------------

int32_t *vi32_at(Vector_i32 *vector, uint32_t index);
bool vi32_indexOf(Vector_i32 *vector, int32_t value, uint32_t offset,
                  uint32_t *index);

//void *vi32_push(Vector_i32 *vector, int32_t value);
//int32_t vi32_pop(Vector_i32 *vector, uint32_t index);
//void vi32_insert(Vector_i32 *vector, uint32_t index, int32_t value);
//int32_t vi32_delete(Vector_i32 *vector, uint32_t index);

// --

double *vf64_at(Vector_f64 *vector, uint32_t index);

#endif
