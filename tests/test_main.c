#include "test.h"
#include "test_suite.h"
#include "../include/macros.h"

int check_two_nums(void)
{
  return 10 >= 0;
}

int check_three_nums(void)
{
  return 10 >= 0 && 10 > 10;
}

int main() {
  RunetTest *tests[] = {
    runet_test_create("demo_test_1", check_two_nums),
    runet_test_create("demo_test_2", check_three_nums)
  };

  RunetTest *tests1[] = {
    runet_test_create("demo_test_1", check_two_nums),
    runet_test_create("demo_test_2", check_three_nums)
  };

  int size = ARRAY_SIZE(tests);
  RunetTestSuite *suites[] = {
    runet_test_suite_create("Demo Suite 1", tests, size),
    runet_test_suite_create("Demo Suite 2", tests1, size)
  };

  runet_run_test_suites(suites, 2);
  for (int i = 0; i < 2; i++) {
    runet_test_suite_free(suites[i]);
  }
  return 0;
}
