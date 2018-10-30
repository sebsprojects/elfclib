#ifndef ELFC_MAPU16
#define ELFC_MAPU16

#include "elfc_common.h"
#include "elfc_vecu16.h"


// --------------------------------------------------------------------------
// Types
// --------------------------------------------------------------------------

struct Mapu16 {
  bool indexed;
  Vecu16 *domain;
  Vecu16 *codomain;
};
typedef struct Mapu16 Mapu16;


// --------------------------------------------------------------------------
// Alloc / Free
// --------------------------------------------------------------------------

/*
 * Note that the domain and codomain are uninitialized and accessing them
 * is undefined behavior. Call mapu16_setDefault to have a valid starting
 * point.
 */
Mapu16 *mapu16_alloc(u32 size, bool indexed);

Mapu16 *mapu16_alloc_ref(u32 size, bool indexed,
                         Vecu16 *domain, Vecu16 *codomain);

void mapu16_free(Mapu16 *map);
void mapu16_free_ref(Mapu16 *map);


// --------------------------------------------------------------------------
// MapU
// --------------------------------------------------------------------------

/*
 * Sets domain and codomain to [0..map->domain->size)
 */
void mapu16_setDefault(Mapu16 *map);

void mapu16_mapEleVec(Mapu16 *map, Vecu16 *from, Vecu16 *to);
void mapu16_mapIndVec(Mapu16 *map, Vecu16 *from, Vecu16 *to);

void mapu16_toZero(Mapu16 *map);
void mapu16_toId(Mapu16 *map);

bool mapu16_isValid(Mapu16 *map);

bool mapu16_areEqual(Mapu16 *f, Mapu16 *g);

/*
 * Checks if f(g(x)) is well defined.
 * For maps to be composable it is required that g->codomain is subset of
 * f->domain
 */
bool mapu16_areComposable(Mapu16 *f, Mapu16 *g);

bool mapu16_isSurjectiveIn(Mapu16 *map, Vecu16 *set);
bool mapu16_isInjective(Mapu16 *map);

/*
  g->domain->size must be equal to comp->domain->size to get a valid map
  If setDomain == 0, then comp->domain will be left untouched
*/
void mapu16_comp_noalloc(Mapu16 *f, Mapu16 *g, Mapu16 *comp, bool setDomain);
Mapu16 *mapu16_comp_alloc(Mapu16 *f, Mapu16 *g);

/*
 * A notfixed point is a point with x != f(x)
 */
bool mapu16_hasNotfixedPoints(Mapu16 *map);

/*
 * If there are no notfixed points (i.e. map is id) then this returns 0 which
 * is a wrong result. Always call hasNotfixedPoint beforehand to make sure.
 */
u16 mapu16_getMaximalNotfixedImage(Mapu16 *map);


// --------------------------------------------------------------------------
// Printing
// --------------------------------------------------------------------------

/*
  For doc see sarray.h. The formatting looks like this:

  <   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,
  < 123,  44,   5,   0, 123,  34,  42,  44, 432,   1,   0,

     12,  13,  14,  15                                     >
      0, 132,  42,  43                                     >

  Note that the padding should be the maximum of pad for the domain / codomain
  range to have it nicely aligned.
*/

/*
void mapu16_sprintLine(Mapu16 *map, char *pstring, u32 indFrom,
                       u32 indTo, u32 indent, u32 digitPad);

void mapu16_sprintToNum(Mapu16 *map, char *pstring, u32 elePerLine, u32 indent);
void mapu16_sprintToWidth(Mapu16 *map, char *pstring, u32 width, u32 indent);
void mapu16_sprintDefault(Mapu16 *map, char *pstring);

void mapu16_printToNum(Mapu16 *map, u32 elePerLine,u32 indent);
void mapu16_printToWidth(Mapu16 *map, u32 width, u32 indent);
void mapu16_printDefault(Mapu16 *map);
*/

// --------------------------------------------------------------------------
// Inline Functions
// --------------------------------------------------------------------------

/*
  Maps from index to element
 */
inline u16 mapu16_mapInd(Mapu16 *map, u32 ind) {
#ifdef BOUNDS_CHECK
  if(index >= map->codomain->size) {
    boundsErrorAndExit("mapu16_mapEle", map->codomain.>size, index);
  }
#endif
  return *vecu16_at(map->codomain, ind);
}

inline u16 mapu16_mapEle(Mapu16 *map, u16 ele) {
  u32 index = -1;
  if(map->indexed) {
    index = ele;
  } else {
    vecu16_indexOf(map->domain, ele, &index, 0);
  }
  return mapu16_mapInd(map, index);
}

#endif
