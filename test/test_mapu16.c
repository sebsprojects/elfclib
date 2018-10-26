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

bool test_mapArray()
{
  bool ok = 1;
  // TODO
  return ok;
}

void test_mapu16()
{
  printTestHeader("mapu16");
  printTestMessage(test_setDefault(), "mapu16_setDefault");
  printTestMessage(test_toZero(), "mapu16_toZero");
  printTestMessage(test_toId(), "mapu16_toId");
  printTestMessage(test_mapEle(), "mapu16_mapEle");
  printTestMessage(test_mapInd(), "mapu16_mapInd");
  printTestMessage(test_mapArray(), "mapu16_mapArray");
  printTestFooter();
}
