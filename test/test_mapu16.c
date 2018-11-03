#include "../include/elfc_test.h"
#include "../include/elfc_mapu16.h"


bool test_mapu16_setDefault()
{
  bool ok = 1;
  Mapu16* map = mapu16_alloc(4, 0);
  mapu16_setDefault(map);
  ok = ok && map->indexed;
  for(i32 i = 0; i < map->domain->size; i++) {
    ok = ok && *vecu16_at(map->domain, i) == i;
    ok = ok && *vecu16_at(map->codomain, i) == i;
  }
  mapu16_free(map);
  return ok;
}

bool test_mapu16_toZero()
{
  bool ok = 1;
  Mapu16 *map = mapu16_alloc(4, 0);
  mapu16_setDefault(map);
  mapu16_toZero(map);
  for(i32 i = 0; i < map->domain->size; i++) {
    ok = ok && *vecu16_at(map->codomain, i) == 0;
  }
  mapu16_free(map);
  return ok;
}

bool test_mapu16_toId()
{
  bool ok = 1;
  Mapu16 *map = mapu16_alloc(4, 1);
  mapu16_setDefault(map);
  mapu16_toZero(map); // set to zero since setDefault acts like toId here
  // indexed case
  mapu16_toId(map);
  for(i32 i = 0; i < map->domain->size; i++) {
    ok = ok && *vecu16_at(map->domain, i) == *vecu16_at(map->codomain, i);
  }
  // not indexed case
  map->indexed = 0;
  *vecu16_at(map->domain, 0) = 1;
  *vecu16_at(map->domain, 1) = 0;
  mapu16_toId(map);
  for(i32 i = 0; i < map->domain->size; i++) {
    ok = ok && *vecu16_at(map->domain, i) == *vecu16_at(map->codomain, i);
  }
  mapu16_free(map);
  return ok;
}

bool test_mapu16_isId()
{
  bool ok = 1;
  Mapu16 *map = mapu16_alloc(3, 1);
  mapu16_setDefault(map);
  ok = ok && mapu16_isId(map);
  *vecu16_at(map->domain, 0) = 2;
  *vecu16_at(map->domain, 2) = 0;
  map->indexed = 0;
  ok = ok && !mapu16_isId(map); // 2 1 0 -> 0 1 2
  *vecu16_at(map->codomain, 0) = 2;
  *vecu16_at(map->codomain, 2) = 0;
  ok = ok && mapu16_isId(map); // 2 1 0 -> 2 1 0
  mapu16_free(map);
  return ok;
}

bool test_mapu16_mapInd()
{
  bool ok = 1;
  Mapu16 *map = mapu16_alloc(4, 1);
  mapu16_setDefault(map);
  *vecu16_at(map->codomain, 0) = 1;
  *vecu16_at(map->codomain, 1) = 10;
  ok = ok && mapu16_mapInd(map, 0) == 1;
  ok = ok && mapu16_mapInd(map, 1) == 10;
  for(i32 i = 2; i < map->domain->size; i++) {
    ok = ok && mapu16_mapInd(map, i) == i; // map is id
  }
  mapu16_free(map);
  return ok;
}

bool test_mapu16_mapEle()
{
  bool ok = 1;
  Mapu16 *map = mapu16_alloc(4, 1);
  mapu16_setDefault(map);
  for(u16 i = 0; i < map->domain->size; i++) {
    ok = ok && mapu16_mapEle(map, i) == i; // map is id
  }
  // not-indexed case
  map->indexed = 0;
  *vecu16_at(map->domain, 0) = 1;
  *vecu16_at(map->domain, 1) = 0;
  // 1 0 2 3 ->
  // 0 1 2 3
  ok = ok && mapu16_mapEle(map, 0) == 1;
  ok = ok && mapu16_mapEle(map, 1) == 0;
  for(u16 i = 2; i < map->domain->size; i++) {
    ok = ok && mapu16_mapEle(map, i) == i; // map is id
  }
  mapu16_free(map);
  return ok;
}

bool test_mapu16_mapEleVec()
{
  bool ok = 1;
  Mapu16 *map = mapu16_alloc(4, 1);
  mapu16_setDefault(map);
  map->indexed = 0;
  *vecu16_at(map->domain, 0) = 1;
  *vecu16_at(map->domain, 1) = 0;
  // 1 0 2 3 ->
  // 0 1 2 3
  Vecu16 *vec = vecu16_allocN(2, 0, 1);
  mapu16_mapEleVec(map, vec, vec);
  ok = ok && *vecu16_at(vec, 0) == 1;
  ok = ok && *vecu16_at(vec, 1) == 0;
  vecu16_free(vec);
  mapu16_setDefault(map);
  vec = vecu16_allocN(6, 0, 1, 2, 3, 0, 1);
  // test vector bigger than map
  mapu16_mapEleVec(map, vec, vec);
  for(i32 i = 0; i < 6; i++) {
    ok = ok && *vecu16_at(vec, i) == i % 4;
  }
  vecu16_free(vec);
  mapu16_free(map);
  return ok;
}

bool test_mapu16_mapIndVec() {
  bool ok = 1;
  Mapu16 *map = mapu16_alloc(4, 1);
  mapu16_setDefault(map);
  map->indexed = 0;
  *vecu16_at(map->domain, 0) = 1;
  *vecu16_at(map->domain, 1) = 0;
  Vecu16 *vec = vecu16_allocN(2, 0, 1);
  vecu16_setToRange(vec, 0, 2, 0);
  mapu16_mapIndVec(map, vec, vec);
  ok = ok && *vecu16_at(vec, 0) == 0;
  ok = ok && *vecu16_at(vec, 1) == 1;
  vecu16_free(vec);
  mapu16_setDefault(map);
  vec = vecu16_allocN(6, 0, 1, 2, 3, 0, 1);
  // test vector bigger than map
  mapu16_mapIndVec(map, vec, vec);
  for(i32 i = 0; i < 6; i++) {
    ok = ok && *vecu16_at(vec, i) == i % 4;
  }
  vecu16_free(vec);
  mapu16_free(map);
  return ok;
}

bool test_mapu16_isValid()
{
  bool ok = 1;
  Mapu16 *map = mapu16_alloc(4, 1);
  mapu16_setDefault(map);
  ok = ok && mapu16_isValid(map);
  *vecu16_at(map->domain, 1) = 0;
  ok = ok && !mapu16_isValid(map); // domain 0 0 2 3
  mapu16_setDefault(map);
  vecu16_resize(map->codomain, 3);
  ok = ok && !mapu16_isValid(map); // codomain too few elements
  vecu16_resize(map->domain, 3);
  ok = ok && mapu16_isValid(map);
  vecu16_resize(map->domain, 2); // domain has too few elements
  ok = ok && !mapu16_isValid(map);
  mapu16_free(map);
  return ok;
}

// TODO: Only tests simple positive case right now
bool test_mapu16_areEqual()
{
  bool ok = 1;
  Vecu16 *dom1 = vecu16_allocN(4, 0, 1, 2, 3);
  Vecu16 *dom2 = vecu16_allocN(4, 1, 0, 3, 2);
  Vecu16 *cod1 = vecu16_allocN(4, 0, 1, 2, 3);
  Vecu16 *cod2 = vecu16_allocN(4, 1, 0, 3, 2);
  Mapu16 *map1 = mapu16_alloc_ref(dom1, cod1, 1);
  Mapu16 *map2 = mapu16_alloc_ref(dom2, cod2, 0);
  ok = ok && mapu16_areEqual(map1, map2);
  mapu16_setDefault(map2); // set map2 to id and indexed=1
  ok = ok && mapu16_areEqual(map1, map2);
  mapu16_free_ref(map2);
  mapu16_free_ref(map1);
  vecu16_free(cod2);
  vecu16_free(cod1);
  vecu16_free(dom2);
  vecu16_free(dom1);
  return ok;
}

// This test is pretty much covered by vecu16_isSubset. Only one positive case
bool test_mapu16_areComposable()
{
  bool ok = 1;
  Mapu16 *f = mapu16_alloc(4, 1);
  Mapu16 *g = mapu16_alloc(5, 1);
  mapu16_setDefault(f);
  *vecu16_at(f->codomain, 3) = 5; // make gf impossible
  mapu16_setDefault(g);
  *vecu16_at(g->codomain, 4) = 3;
  ok = ok && mapu16_areComposable(f, g);
  ok = ok && !mapu16_areComposable(g, f);
  mapu16_free(f);
  mapu16_free(g);
  return ok;
}

bool test_mapu16_isSurjectiveIn()
{
  bool ok = 1;
  Mapu16 *map = mapu16_alloc(4, 1);
  mapu16_setDefault(map);
  *vecu16_at(map->codomain, 3) = 2; // make surjective only
  Vecu16 *vec = vecu16_allocN(4, 0, 1, 2, 3);
  ok = ok && !mapu16_isSurjectiveIn(map, vec); // 3 is not in codomain of map
  vecu16_resize(vec, 3);
  ok = ok && mapu16_isSurjectiveIn(map, vec);
  vecu16_resize(vec, 2);
  ok = ok && mapu16_isSurjectiveIn(map, vec);
  vecu16_free(vec);
  mapu16_free(map);
  return ok;
}

bool test_mapu16_isInjective()
{
  bool ok = 1;
  Mapu16 *map = mapu16_alloc(4, 1);
  mapu16_setDefault(map);
  ok = ok && mapu16_isInjective(map);
  *vecu16_at(map->codomain, 1) = 0; // codomain 0 0 2 3
  ok = ok && !mapu16_isInjective(map);
  mapu16_free(map);
  return ok;
}

bool test_mapu16_comp()
{
  bool ok = 1;
  // f:         g:
  // 0 1 2 3    1 2 0
  // 1 2 0 0    0 1 2
  //
  // fg:        gf:
  // 1 2 0      0 1 2 3
  // 1 2 0      0 1 2
  Vecu16 *dom1 = vecu16_allocN(4, 0, 1, 2, 3);
  Vecu16 *cod1 = vecu16_allocN(4, 1, 2, 0, 0);
  Vecu16 *dom2 = vecu16_allocN(3, 1, 2, 0);
  Vecu16 *cod2 = vecu16_allocN(3, 0, 1, 2);
  Mapu16 *f = mapu16_alloc_ref(dom1, cod1, 1);
  Mapu16 *g = mapu16_alloc_ref(dom2, cod2, 0);
  ok = ok && mapu16_areComposable(f, g);
  ok = ok && mapu16_areComposable(g, f);
  Mapu16 *fg = mapu16_comp_alloc(f, g);
  Mapu16 *gf = mapu16_comp_alloc(g, f);
  ok = ok && mapu16_isId(fg);
  ok = ok && *vecu16_at(gf->domain, 0) == 0;
  ok = ok && *vecu16_at(gf->domain, 1) == 1;
  ok = ok && *vecu16_at(gf->domain, 2) == 2;
  ok = ok && *vecu16_at(gf->domain, 3) == 3;
  ok = ok && *vecu16_at(gf->codomain, 0) == 0;
  ok = ok && *vecu16_at(gf->codomain, 1) == 1;
  ok = ok && *vecu16_at(gf->codomain, 2) == 2;
  mapu16_free(fg);
  mapu16_free(gf);
  mapu16_free_ref(f);
  mapu16_free_ref(g);
  vecu16_free(dom1);
  vecu16_free(dom2);
  vecu16_free(cod1);
  vecu16_free(cod2);
  return ok;
}

void test_mapu16()
{
  test_printHeader("mapu16");
  test_printMessage(test_mapu16_setDefault(), "mapu16_setDefault");
  test_printMessage(test_mapu16_toZero(), "mapu16_toZero");
  test_printMessage(test_mapu16_toId(), "mapu16_toId");
  test_printMessage(test_mapu16_isId(), "mapu16_isId");
  test_printMessage(test_mapu16_mapInd(), "mapu16_mapInd");
  test_printMessage(test_mapu16_mapEle(), "mapu16_mapEle");
  test_printMessage(test_mapu16_mapIndVec(), "mapu16_mapIndVec");
  test_printMessage(test_mapu16_mapEleVec(), "mapu16_mapEleVec");
  test_printMessage(test_mapu16_isValid(), "mapu16_isValid");
  test_printMessage(test_mapu16_areEqual(), "mapu16_areEqual");
  test_printMessage(test_mapu16_areComposable(), "mapu16_areComposable");
  test_printMessage(test_mapu16_isSurjectiveIn(), "mapu16_isSurjectiveIn");
  test_printMessage(test_mapu16_isInjective(), "mapu16_isInjective");
  test_printMessage(test_mapu16_comp(), "mapu16_comp");
  test_printFooter();
}
