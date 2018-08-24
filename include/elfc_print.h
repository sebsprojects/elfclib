#ifndef ELFC_PRINT
#define ELFC_PRINT

#include "elfc_common.h"


// --------------------------------------------------------------------------
// Vector printing
// --------------------------------------------------------------------------

struct Vecu16;
void vecu16_sprint(char *pstring, struct Vecu16 *vector, u32 width);
void vecu16_print(struct Vecu16 *vector);

struct Veci32;
void veci32_sprint(char *pstring, struct Veci32 *vector, u32 width);
void veci32_print(struct Veci32 *vector);

struct Vecf32;
void vecf32_sprint(char *pstring, struct Vecf32 *vector, u32 width,
                   u32 numDecimal);
void vecf32_print(struct Vecf32 *vector);


#endif
