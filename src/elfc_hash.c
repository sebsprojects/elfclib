#include "../include/elfc_hash.h"

#include <stdio.h>


// Taken from http://www.cse.yorku.ca/~oz/hash.html
u64 hash_djb2(char *string)
{
  u64 hash = 5381;
  char c;
  while((c = *string++)) {
    hash = ((hash << 5) + hash) + c;
  }
  return hash;
}

void sprintHash(u64 hash, char *buf)
{
  // pad to 16 characters, print u64 in lowercase hex
  sprintf(buf, "%016lx", hash);
}

void printHash(u64 hash)
{
  printf("%016lx", hash);
}
