#include "tests.h"
#include "test_suite.h"
#include "../include/macros.h"

int main() {
  RunetTestSuite *suites[] = {
    runet_matrix_test_suite(),
    runet_matrix_ops_test_suite(),
  };

  int size = ARRAY_SIZE(suites);
  runet_run_test_suites(suites, size);

  for (int i = 0; i < size; i++) {
    runet_test_suite_free(suites[i]);
  }
  return 0;
}
