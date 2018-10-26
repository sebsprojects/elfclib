#include "../include/elfc_mapu16.h"

#include "elfc_math.h"

#include <stdlib.h>


// --------------------------------------------------------------------------
// Alloc / Free
// --------------------------------------------------------------------------

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

Mapu16 *mapu16_alloc_ref(u32 size, bool indexed,
                         Vecu16 *domain, Vecu16 *codomain)
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


// --------------------------------------------------------------------------
// Operation
// --------------------------------------------------------------------------

void mapu16_setDefault(Mapu16 *map)
{
  map->indexed = 1;
  for(i32 i = 0; i < map->domain->size; i++) {
    *vecu16_at(map->domain, i) = i;
    *vecu16_at(map->codomain, i) = i;
  }
}

void mapu16_mapArray(Mapu16 *map, Vecu16 *from, Vecu16 *to)
{
  for(i32 i = 0; i < from->size; i++) {
    *vecu16_at(to, i) = mapu16_mapEle(map, *vecu16_at(from, i));
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

bool mapu16_isValid(Mapu16 *map)
{
  u32 n = map->domain->size;
  if(n != map->codomain->size) {
    return 0;
  }
  for(i32 i = 0; i < n; i++) {
    for(i32 j = 0; j < i; j++) {
      if(*vecu16_at(map->domain, i) == *vecu16_at(map->domain, j)) {
        return 0;
      }
    }
    if(*vecu16_at(map->codomain, i) == 0xffff ||
       *vecu16_at(map->domain, i) == 0xffff) {
      return 0;
    }
  }
  return 1;
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
    if(vecu16_indexOf(g->domain, *vecu16_at(f->domain, i), &ind, 0)) {
      return 0;
    }
    if(mapu16_mapInd(f, i) != mapu16_mapInd(g, ind)) { // f(ele) != g(ele)
      return 0;
    }
  }
  return 1;
}

bool mapu16_areComposable(Mapu16 *f, Mapu16 *g)
{
  u32 ind;
  for(i32 i = 0; i < g->codomain->size; i++) {
    if(!vecu16_indexOf(f->domain, *vecu16_at(g->codomain, i), &ind, 0)) {
      return 0;
    }
  }
  return 1;
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
  for(i32 i = 0; i < g->domain->size; i++) {
    if(setDomain) {
      *vecu16_at(comp->domain, i) = *vecu16_at(g->domain, i);
    }
    *vecu16_at(comp->codomain, i) = mapu16_mapEle(f, mapu16_mapInd(g, i));
  }
}

Mapu16 *mapu16_comp_alloc(Mapu16 *f, Mapu16 *g) {
  Mapu16 *comp = mapu16_alloc(g->domain->size, g->indexed);
  mapu16_comp_noalloc(f, g, comp, 0);
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
#ifdef BOUNDS_CHECK
  if(!mapu16_hasNotfixedPoints(map)) {
    errorAndExit("mapu16_getMaximalNotfixedImage has no not-fixed-points");
  }
#endif
  u16 max = 0;
  u16 ele;
  for(i32 i = 0; i < map->domain->size; i++) {
    ele = *vecu16_at(map->domain, i);
    if(mapu16_mapInd(map, i) != ele) {
      max = u16_max(mapu16_mapInd(map, i), max);
    }
  }
  return max;
}
