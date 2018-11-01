#include "../include/elfc_mapu16.h"

#include <stdlib.h>


// ---------------------------------------------------------------------------
// Inlines
// ---------------------------------------------------------------------------

extern u16 mapu16_mapInd(Mapu16 *map, u32 ind);
extern u16 mapu16_mapEle(Mapu16 *map, u16 ele);


// ---------------------------------------------------------------------------
// Alloc / Free
// ---------------------------------------------------------------------------

Mapu16 *mapu16_alloc(u32 size, bool indexed)
{
#ifdef BOUNDS_CHECK
  if(size == 0) {
    boundsErrorAndExit("mapu16_allow", 1, size);
  }
#endif
  Mapu16 *map = malloc(sizeof(Mapu16));
  map->indexed = indexed;
  map->domain = vecu16_alloc(size);
  map->codomain = vecu16_alloc(size);
  return map;
}

Mapu16 *mapu16_alloc_ref(Vecu16 *domain, Vecu16 *codomain, bool indexed)
{
  Mapu16 *map = malloc(sizeof(Mapu16));
  map->indexed = indexed;
  map->domain = domain;
  map->codomain = codomain;
  return map;
}

void mapu16_free(Mapu16 *map)
{
  vecu16_free(map->codomain);
  vecu16_free(map->domain);
  free(map);
}

void mapu16_free_ref(Mapu16 *map)
{
  free(map);
}


// ---------------------------------------------------------------------------
// Operation
// ---------------------------------------------------------------------------

void mapu16_setDefault(Mapu16 *map)
{
  map->indexed = 1;
  vecu16_setToRange(map->domain, 0, map->domain->size, 0);
  vecu16_setToRange(map->codomain, 0, map->codomain->size, 0);
}

void mapu16_mapEleVec(Mapu16 *map, Vecu16 *from, Vecu16 *to)
{
  for(i32 i = 0; i < from->size; i++) {
    *vecu16_at(to, i) = mapu16_mapEle(map, *vecu16_at(from, i));
  }
}

void mapu16_mapIndVec(Mapu16 *map, Vecu16 *from, Vecu16 *to)
{
  for(i32 i = 0; i < from->size; i++) {
    *vecu16_at(to, i) = mapu16_mapInd(map, *vecu16_at(from, i));
  }
}

void mapu16_toZero(Mapu16 *map)
{
  for(i32 i = 0; i < map->codomain->size; i++) {
    *vecu16_at(map->codomain, i) = 0;
  }
}

void mapu16_toId(Mapu16 *map)
{
  for(u16 i = 0; i < map->domain->size; i++) {
    *vecu16_at(map->codomain, i) = *vecu16_at(map->domain, i);
  }
}

bool mapu16_isId(Mapu16 *map)
{
  for(i32 i = 0; i < map->domain->size; i++) {
    if(*vecu16_at(map->domain, i) != *vecu16_at(map->codomain, i)) {
      return 0;
    }
  }
  return 1;
}

bool mapu16_isValid(Mapu16 *map)
{
  return map->domain->size == map->codomain->size &&
         !vecu16_hasDuplicates(map->domain);
}

bool mapu16_areEqual(Mapu16 *f, Mapu16 *g)
{
  if(f->domain->size != g->domain->size) {
    return 0;
  }
  if(f->indexed && g->indexed) {
    return vecu16_areEqualVectors(f->codomain, g->codomain);
  }
  u32 ind;
  for(i32 i = 0; i < f->domain->size; i++) {
    // Manually check f->domain is subset of g->domain b/c we need ind anyway
    // Assumes that f, g are valid, i.e. one direction subset check suffices
    if(!vecu16_indexOf(g->domain, *vecu16_at(f->domain, i), &ind, 0)) {
      return 0;
    }
    // ind is index of f->domain[i] in g->domain
    if(mapu16_mapInd(f, i) != mapu16_mapInd(g, ind)) { // f(ele) != g(ele)
      return 0;
    }
  }
  return 1;
}

bool mapu16_areComposable(Mapu16 *f, Mapu16 *g)
{
  return vecu16_isSubset(g->codomain, f->domain);
}

bool mapu16_isSurjectiveIn(Mapu16 *map, Vecu16 *set)
{
  return vecu16_isSubset(set, map->codomain);
}

bool mapu16_isInjective(Mapu16 *map)
{
  return !vecu16_hasDuplicates(map->codomain);
}

void mapu16_comp_noalloc(Mapu16 *f, Mapu16 *g, Mapu16 *comp, bool setDomain)
{
  if(setDomain) {
    vecu16_copyInto(comp->domain, g->domain);
  }
  // "map" g->domain to g->codomain by copying
  vecu16_copyInto(comp->codomain, g->codomain);
  // map g->codomain by applying f
  mapu16_mapEleVec(f, comp->codomain, comp->codomain);
}

Mapu16 *mapu16_comp_alloc(Mapu16 *f, Mapu16 *g)
{
  Mapu16 *comp = mapu16_alloc(g->domain->size, g->indexed);
  mapu16_comp_noalloc(f, g, comp, 1);
  return comp;
}

bool mapu16_hasNotfixedPoints(Mapu16 *map)
{
  for(i32 i = 0; i < map->domain->size; i++) {
    if(*vecu16_at(map->domain, i) != mapu16_mapInd(map, i)) {
      return 1;
    }
  }
  return 0;
}

u16 mapu16_getMaximalNotfixedImage(Mapu16 *map)
{
  u16 max = 0;
  u16 x, fx;
  for(i32 i = 0; i < map->domain->size; i++) {
    x = *vecu16_at(map->domain, i);
    fx = mapu16_mapInd(map, i);
    if(x != fx) {
      max = u16_max(fx, max);
    }
  }
  return max;
}
