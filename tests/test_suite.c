#include "test.h"
#include "test_suite.h"
#include "../include/macros.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

RunetTestSuite *runet_test_suite_create(const char *name, RunetTest **tests, int size)
{
  RunetTestSuite *suite = malloc(sizeof(RunetTestSuite));
  int test_size = size * sizeof(RunetTest *);

  suite->name = strdup(name);
  suite->tests = malloc(test_size);
  suite->size = size;

  if (tests != NULL) {
    memcpy(suite->tests, tests, test_size);
  }

  return suite;
}

void runet_test_suite_free(RunetTestSuite *suite)
{
  if (suite == NULL) {
    return ;
  }

  if (suite->name != NULL) {
    free((void *) suite->name);
  }

  for (int i = 0; i < suite->size; i++) {
    runet_test_free(suite->tests[i]);
  }
  free(suite->tests);
  free(suite);
}

static void runet_show_failed_tests(const RunetTestSuite *suite,
                                   int failed_tests[],
                                   int failed_count)
{
  if (failed_count == -1) {
    return ;
  }

  int i;
  printf("\nFailed Tests...\n");
  for (i = 0; i <= failed_count; i++) {
    printf("\t%d. %s\n", i + 1, suite->tests[failed_tests[i]]->name);
  }
  printf("\nTotal Fails: %d\n", i);
}

static void runet_run_test_suite_base(const RunetTestSuite *suite) {
  if (suite == NULL) {
    return ;
  }

  int failed_tests[suite->size];
  int pos = -1;

  printf("\n==== %s Test Suite ====\n", suite->name);
  for (int i = 0; i < suite->size; i++) {
    const RunetTest *test = suite->tests[i];

    if (test->func()) {
      printf("[%sPASS%s] ", ANSI_COLOR_GREEN, ANSI_COLOR_RESET);

    } else {
      printf("[%sFAIL%s] ", ANSI_COLOR_RED, ANSI_COLOR_RESET);
      failed_tests[++pos] = i; // add the failed tests from left to right
    }

    printf("%s\n", test->name);
  }
  runet_show_failed_tests(suite, failed_tests, pos);
}

void runet_run_test_suite(const RunetTestSuite *suite)
{
  runet_run_test_suite_base(suite);
}

void runet_run_test_suites(RunetTestSuite **suites, int size)
{
  if (suites == NULL) {
    return ;
  }

  for (int i = 0; i < size; i++) {
    runet_run_test_suite_base(suites[i]);
  }
}
