#ifndef __RUNET_TEST_H__
#define __RUNET_TEST_H__

typedef int (*test_func)(void);

struct runet_test {
  const char *name; /**< The name of the test */
  test_func func;   /**< The function pointer to be executed */
};

typedef struct runet_test RunetTest;

/**
  * @brief Creates a new test.
  * * This function allocates memory for a test and copies the provided
  * name of the test and the test function to execute.
  *
  * @param name A string literal specifying the name of the test
  * (the string gets copied).
  *
  * @param func A function pointer which takes in no parameter and
  * returns a integer value (indicating true or false).
  *
  * @return RunetTest* A pointer to the new test, or NULL on failure
  */
RunetTest *runet_test_create(const char *name, test_func func);

/**
  * @brief Frees the memory of the existing test struct.
  * * This function deallocates the memory for a test struct by freeing away
  * all the allocated memory and destroying the object.
  *
  * @param test A pointer to a test object to be destroyed or freed.
  */
void runet_test_free(RunetTest *test);

#endif // __RUNET_TEST_H__
