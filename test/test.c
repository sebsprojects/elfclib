#include "../include/elfc_common.h"
#include "../include/elfc_vector.h"


int main() {
  Vector_i32 *v = vi32_alloc(4);

  *vi32_at(v, 0) = 2;
  *vi32_at(v, 1) = 4;
  *vi32_at(v, 2) = 6;
  *vi32_at(v, 3) = 8;

  vi32_free(v);
}
