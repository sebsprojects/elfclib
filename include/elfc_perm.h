#ifndef ELFC_PERM
#define ELFC_PERM

#include "elfc_common.h"
#include "elfc_vecu16.h"


// ---------------------------------------------------------------------------
// Binomial Structures to represent combinations of u16
//
// With binom_shift one can systematically test all (unordered) k-subsets of
// an integer interval [min..max)
// ---------------------------------------------------------------------------

/*
 * Equivalent to binom_init(vec, 0, k, 0)
 */
void binom_initDefault(Vecu16 *vec, i32 k);

/*
 * Fills the vector with 0xffff and sets the range [offset, offset + k)
 * to the standard range with rangeOffset min
 */
void binom_init(Vecu16 *vec, i32 min, i32 k, i32 offset);

/*
 * Equivalent to binom_shift(vec, max, 0, <first entry with 0xffff>)
 * Caution: This needs to determine k every time, i.e. call
 * indexOf(..., 0xffff, ...)
 */
bool binom_shiftDefault(Vecu16 *vec, i32 n);

/*
 * Shifts up a binomial combination by one towards the next biggest numerical
 * values. I.e. n=4, k=3 with starting vector ( 0 1 2 0xffff ... )
 *   ( 0 1 2 0xffff ... ) ->
 *   ( 0 1 3 0xffff ... ) ->
 *   ( 0 1 4 0xffff ... ) ->
 *   ( 0 2 3 0xffff ... ) ->
 *   ( 0 2 4 0xffff ... ) ->
 *   ( 0 3 4 0xffff ... ) ->
 *   ( 1 2 3 0xffff ... ) ->
 *   ...
 * No minimal value parameter is needed since we only shift up
 *
 * Input:
 *   vec    - array of the form a[offset] < a[offset+1] < ... < a[offset+n-1]
 *   n      - the highest value to attain
 *   k      - k-subset
 *   offset - offset into vec
 * Return:
 *   Return 1 if a shift was possible and done, 0 otherwise
 */
bool binom_shift(Vecu16 *vec, i32 n, i32 k, i32 offset);

/*
 * Returns the k of ("n over k"), i.e. the number of the first non 0xffff 
 * elements in vec.
 */
u32 binom_getKIndex(Vecu16 *vec);


// ---------------------------------------------------------------------------
// Permutations
//
// In contrast to the binomal structure this merely permutates a range of
// integer within the vec. The array as a set is left invariant, only the
// positioning of the elements changes.
// The value 0xffff is reserved and may not be used
// ---------------------------------------------------------------------------

/*
 * Fills the whole vec with id = (0 1 2 3 ... array->size - 1)
 */
void perm_init(Vecu16 *vec);

/*
 * Shifts the vec by one step towards the "numerical" maximum value if
 * you take the elements of the vec as digits of a number
 * For Example:
 *   ( 0 1 2 3 ) ->
 *   ( 0 1 3 2 ) ->
 *   ( 0 2 1 3 ) ->
 *   ( 0 2 3 1 ) ->
 *   ( 1 0 2 3 ) ->
 *   ( 1 0 3 2 ) ->
 *   ...
 * Equivalent to perm_shift(vec, 0, vec->size)
 */
bool perm_shiftDefault(Vecu16 *vec);

/*
 * Shifts the permutation within [from, to) as described in default version
 */
bool perm_shift(Vecu16 *vec, i32 from, i32 to);

#endif
