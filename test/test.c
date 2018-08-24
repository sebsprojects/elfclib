#include "../include/elfc_common.h"
#include "../include/elfc_veci32.h"
#include "../include/elfc_vecf32.h"
#include "../include/elfc_vecptr.h"
#include "../include/elfc_print.h"

#include <stdio.h>
#include <string.h>


struct Coord {
  i32 x;
  i32 y;
};
typedef struct Coord Coord;

void printCoord(Coord *coord) {
  printf("Coord: %i %i\n", coord->x, coord->y);
}

int main() {
  Veci32 *vec = veci32_allocN(4, 0, 1, -200, 3);
  *veci32_at(vec, 0) = 1000;
  veci32_print(vec);
  veci32_free(vec);

  Vecf32 *fvec = vecf32_allocN(4.0f, 0.01f, -0.003f, 0.0f, -0.4f);
  vecf32_print(fvec);
  vecf32_free(fvec);

  Vecptr *pvec = vecptr_alloc(3);
  Coord c1 = { 1, 2 };
  Coord c2 = { 10, 20 };
  Coord c3 = { 100, 200 };
  *vecptr_at(pvec, 0) = &c1;
  *vecptr_at(pvec, 1) = &c2;
  *vecptr_at(pvec, 2) = &c3;
  printCoord(*vecptr_at(pvec, 1));
  vecptr_free(pvec);
}
