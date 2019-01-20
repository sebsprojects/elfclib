#include "test_vecu16.c"
#include "test_mapu16.c"
#include "test_hash.c"
#include "test_perm.c"
#include "test_math.c"


int main()
{
  test_vecu16();
  test_mapu16();
  test_hash();
  test_perm();
  test_math();
  return 0;
}
