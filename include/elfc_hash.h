#ifndef ELFC_HASH
#define ELFC_HASH

#include "elfc_common.h"


u64 hash_djb2(char *string);

/*
 * Buffer needs to have at least 16 bytes for the u64 in hex plus \0 term
 */
void sprintHash(u64 hash, char *buf);
void printHash(u64 hash);

#endif
