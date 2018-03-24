#include "../include/elfc_common.h"
#include "../include/elfc_vector.h"
#include "../include/elfc_print.h"

#include <stdio.h>
#include <string.h>

int main() {
  Vector_i32 *vec = vi32_allocN(4, 0, 1, -200, 3);
  vi32_print(vec);
  vi32_free(vec);

  Vector_f64 *fvec = vf64_allocN(4, 0.01, -0.003, 0.0, -0.4);
  vf64_print(fvec);
  vf64_free(fvec);
}
