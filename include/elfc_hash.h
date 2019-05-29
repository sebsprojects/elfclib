#ifndef ELFC_HASH
#define ELFC_HASH

#include "elfc_common.h"


u64 hash_djb2(char *string);

/*
 * Same as above but processes string in reverse order
 */
u64 hash_djb2Reverse(char *string);

/*
 * Buffer needs to have at least 16 bytes for the u64 in hex plus \0 term
 */
i32 hash_sprintHash(char *buf, u64 hash);
void hash_printHash(u64 hash);

#endif
