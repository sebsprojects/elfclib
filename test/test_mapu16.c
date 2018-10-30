#include "test.h"

#include "../include/elfc_mapu16.h"


bool test_setDefault()
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

bool test_toZero()
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

bool test_toId()
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
  // not-indexed case
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

bool test_mapInd()
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

bool test_mapEle()
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

bool test_mapEleVec()
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

bool test_mapIndVec() {
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

bool test_isValid()
{
  bool ok = 1;
  return ok;
}

bool test_areEqual()
{
  bool ok = 1;
  return ok;
}

bool test_areComposable()
{
  bool ok = 1;
  return ok;
}

bool test_isSurjectiveIn()
{
  bool ok = 1;
  return ok;
}

bool test_isInjective()
{
  bool ok = 1;
  return ok;
}

bool test_comp()
{
  bool ok = 1;
  return ok;
}

void test_mapu16()
{
  printTestHeader("mapu16");
  printTestMessage(test_setDefault(), "mapu16_setDefault");
  printTestMessage(test_toZero(), "mapu16_toZero");
  printTestMessage(test_toId(), "mapu16_toId");
  printTestMessage(test_mapInd(), "mapu16_mapInd");
  printTestMessage(test_mapEle(), "mapu16_mapEle");
  printTestMessage(test_mapIndVec(), "mapu16_mapIndVec");
  printTestMessage(test_mapEleVec(), "mapu16_mapEleVec");
  printTestMessage(test_isValid(), "mapu16_isValid");
  printTestMessage(test_areEqual(), "mapu16_areEqual");
  printTestMessage(test_areComposable(), "mapu16_areComposable");
  printTestMessage(test_isSurjectiveIn(), "mapu16_isSurjectiveIn");
  printTestMessage(test_isInjective(), "mapu16_isInjective");
  printTestMessage(test_comp(), "mapu16_comp");
  printTestFooter();
}
