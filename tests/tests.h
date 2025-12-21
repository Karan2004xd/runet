#ifndef __RUNET_TESTS_H__
#define __RUNET_TESTS_H__

typedef struct runet_test_suite RunetTestSuite;

// Contains test suites of different modules.

RunetTestSuite *runet_matrix_test_suite(void);
RunetTestSuite *runet_matrix_ops_test_suite(void);
RunetTestSuite *runet_layer_test_suite(void);
RunetTestSuite *runet_network_test_suite(void);

#endif // __RUNET_TESTS_H__
