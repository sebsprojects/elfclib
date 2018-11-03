#include "../include/elfc_test.h"
#include "../include/elfc_hash.h"

#include <stdio.h>


bool test_hash_djb2()
{
  bool ok = 1;
  char *string1 = "123456789213456789123456789123456789";
  char *string2 = "223456789213456789123456789123456789";
  char *string3 = "123456789213456789123456789123456788";
  u64 hash1 = hash_djb2(string1);
  u64 hash2 = hash_djb2(string2);
  u64 hash3 = hash_djb2(string3);
  //printf("  hash1: "); printHash(hash1); printf("\n");
  //printf("  hash2: "); printHash(hash2); printf("\n");
  //printf("  hash3: "); printHash(hash3); printf("\n");
  ok = ok && hash1 != hash2;
  ok = ok && hash1 != hash3;
  ok = ok && hash2 != hash3;
  return ok;
}

void test_hash()
{
  test_printHeader("hash");
  test_printMessage(test_hash_djb2(), "hash_djb2");
  test_printFooter();
}
