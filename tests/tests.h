#ifndef __RUNET_TESTS_H__
#define __RUNET_TESTS_H__

typedef struct runet_test_suite RunetTestSuite;

/**
  * @brief Creates a test suite for matrix module
  * * This function compiles down all the tests to run,
  * into a test suite for the matrix module.
  *
  * @return RunetTestSuite* A pointer to a new test suite.
  */
RunetTestSuite *runet_matrix_test_suite(void);

/**
  * @brief Creates a test suite for matrix operation module
  * * This function compiles down all the tests to run,
  * into a test suite for the matrix operation module.
  *
  * @return RunetTestSuite* A pointer to a new test suite.
  */
RunetTestSuite *runet_matrix_ops_test_suite(void);

RunetTestSuite *runet_layer_test_suite(void);

RunetTestSuite *runet_network_test_suite(void);

#endif // __RUNET_TESTS_H__
