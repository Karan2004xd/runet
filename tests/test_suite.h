#ifndef __TEST_SUITE_H__
#define __TEST_SUITE_H__

typedef struct runet_test RunetTest;

struct runet_test_suite {
  const char *name;   /**< The name of the test suite */
  RunetTest **tests;  /**< A pointer to an array of pointers of test struct */
  int size;           /**< The total number of tests in the suite */
};

typedef struct runet_test_suite RunetTestSuite;

/**
  * @brief Creates a new test suite.
  * * This function allocates memory for a new test suite and copies the
  * array of test pointers as well as the name of the test suite.
  *
  * @param name The display name of the test suite (string is copied).
  * @param tests Pointer to an array of pointer of tests (RunetTest struct).
  * @param size The number of tests in the array
  *
  * @return RunetTestSuite* A pointer to the new suite, or NULL on failure.
  *
  * @note This function assumes the parameters passed in to be correct,
  * meaning in case of incorrect parameter there can be undefined behaviour.
  */
RunetTestSuite *runet_test_suite_create(const char *name, RunetTest **tests, int size);

/**
  * @brief Frees the memory of the existing test suite struct.
  * * This function deallocates the memory for a test suite (RunetTestSuite) struct 
  * by freeing away all the allocated memory and destroying the object.
  *
  * @param suite A pointer to a test suite object to be destroying or freed.
  */
void runet_test_suite_free(RunetTestSuite *suite);

/**
  * @brief Executes the test for a single suite
  * * This functions executes the tests of the single suite
  * specified (if any), and prints out the result.
  *
  * @param suite A const pointer to a test suite object
  */
void runet_run_test_suite(const RunetTestSuite *suite);

/**
  * @brief Executes the test for an array suites
  * * This functions executes the tests of the array of suites
  * specified (if any), and prints out the results for each suites.
  *
  * @param suites A pointer to pointer of test suites.
  * @param size The number of test suites provided.
  *
  * @note This function assumes the parameters passed in to be correct,
  * meaning in case of incorrect parameter there can be undefined behaviour.
  */
void runet_run_test_suites(RunetTestSuite **suites, int size);

#endif // __TEST_SUITE_H__
