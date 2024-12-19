#include <assert.h>
#include <cdefer.h>

void
basic_test(int* val)
{
  DEFER(*val = 1;);
}

void
ascend_test(int* val)
{
  DEFER(*val = 1;);
  DEFER(*val = 2;);
}

int
main()
{
  int val = 0;
  basic_test(&val);
  assert(val == 1);

  val = 0;
  ascend_test(&val);
  assert(val == 1);
}
