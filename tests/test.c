#include "test.h"
#include <string.h>
#include <stdlib.h>

RunetTest *runet_test_create(const char *name, test_func func)
{
  RunetTest *test = malloc(sizeof(RunetTest));

  test->name = strdup(name);
  test->func = func;

  return test;
}

void runet_test_free(RunetTest *test)
{
  if (test == NULL) {
    return ;
  }

  if (test->name != NULL) {
    free((void *) test->name);
  }

  free(test);
}
