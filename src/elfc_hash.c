#include "../include/elfc_hash.h"

#include <stdio.h>
#include <string.h>


// Taken from http://www.cse.yorku.ca/~oz/hash.html
u64 hash_djb2(char *string)
{
  u64 hash = 5381;
  char c = 0;
  while((c = *string++)) {
    hash = ((hash << 5) + hash) + c;
  }
  return hash;
}

u64 hash_djb2Reverse(char *string)
{
  u64 hash = 5381;
  char c = 0;
  u32 len = strlen(string);
  for(i32 i = len - 1; i >= 0; i--) {
    c = string[i];
    hash = ((hash << 5) + hash) + c;
  }
  return hash;
}

i32 hash_sprintHash(char *buf, u64 hash)
{
  // pad to 16 characters, print u64 in lowercase hex
  return sprintf(buf, "%016lx", hash);
}

void hash_printHash(u64 hash)
{
  printf("%016lx", hash);
}
