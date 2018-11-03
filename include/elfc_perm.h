#ifndef ELFC_PERM
#define ELFC_PERM

#include "elfc_common.h"
#include "elfc_vecu16.h"


// ---------------------------------------------------------------------------
// Binomial Structures to represent combinations of u16
//
// With binom_shift one can systematically test all (unordered) n-subsets of
// an integer interval [min..max)
// ---------------------------------------------------------------------------

/*
  Fills the vec with 0xffff and fills to id = (0 1 2 3 ... n - 1 0xffff ...)
  before (excluding) index n
 */
void binom_init(Vecu16 *vec, u16 n);

/*
 * Shifts the vec by one step if possible according to the following scheme:
 *   1. [ a b ... x [x + >= 2] ... ]      -> [ 0 1 ... [x + 1] [x + >= 2] ... ]
 *   2. [ a b ... x [x + 1] 0xffff ... ]  -> [ 0 1 ... x [x + 2 < max] ...]
 *   3. [ 0 1 ... [max - 2] [max - 1] 0xffff ...]   -> no action
 * For example n = 3, max = 5
 *   ( 0 1 2 0xffff ...) -> (case 2)
 *   ( 0 1 3 0xffff ...) ->
 *   ( 0 2 3 0xffff ...) ->
 *   ( 1 2 3 0xffff ...) -> (case 2)
 *   ( 0 1 4 0xffff ...) ->
 *   ( 0 2 4 0xffff ...) ->
 *   ( 1 2 4 0xffff ...) ->
 *   ( 0 3 4 0xffff ...) ->
 *   ( 1 3 4 0xffff ...) ->
 *   ( 2 3 4 0xffff ...) -> (case 3)
 * Input:
 *   vec - array of the form a[0] < a[1] < ... < a[n-1], 0xffff, 0xffff, ...
 *   max   - 1 + maximal element to occur in vec (ie. array[<n] < max)
 *   n     - size of subset to "permute". Must be leq max - min
 * Return:
 *   1  -  if shift was possible (case 1, 2)
 *   0  -  if shift was impossible (case 3)
 */
bool binom_shiftDefault(Vecu16 *vec, u16 max);

/*
 * More general version of the scheme above
 * Input:
 *   vec  - array of the form a[offset] < a[offset+1] < ... < a[offset+n-1]
 *   min    - minimal element to occur the vec
 *   max    - see above
 *   offset - offset into the vec. Entries < offset are left invariant
 *   n      - size of subset to "permute". Must be leq max - min
 * Return:
 *    Same as the default version
 */
bool binom_shift(Vecu16 *vec, u16 min, u16 max, u16 offset, u16 n);

/*
 * Returns the current k of ("n over k"), i.e. the number of non 0xffff elements
 * in vec.
 */
u32 binom_getKIndex(Vecu16 *vec);


// ---------------------------------------------------------------------------
// Permutations
//
// In contrast to the binomal structure this merely permutates a range of
// integer within the vec. The array as a set is left invariant, only the
// positioning of the elements changes.
// The value 0xffff is reserved and may not be used as part of a 0xffff-sized
// permutation
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
bool perm_shift(Vecu16 *vec, u16 from, u16 to);

#endif
