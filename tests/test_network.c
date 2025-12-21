#include "tests.h"
#include "test.h"
#include "test_suite.h"

#include "../include/macros.h"
#include "../include/network.h"
#include "../include/layer.h"
#include "../include/status_codes.h"
#include "../include/matrix.h"
#include "../include/matrix_operations.h"

static int test_network_create(void)
{
  RunetNetwork *net = runet_network_create(5);

  int test =
    CHECK_PTR(net, !=, NULL) &&
    CHECK_INT(net->curr_size, ==, 0) &&
    CHECK_INT(net->capacity, ==, 5);

  runet_network_free(net);
  return test;
}

static int test_network_add(void)
{
  RunetNetwork *net = runet_network_create(2);
  RunetLayer *layer1 = runet_layer_create_dense(2, 64, RUNET_ACT_NONE);
  RunetLayer *layer2 = runet_layer_create_dense(32, 10, RUNET_ACT_NONE);

  int test =
    CHECK_INT(runet_network_add(net, layer1), ==, SUCCESS_CODE) &&
    CHECK_INT(runet_network_add(net, layer2), ==, SHAPE_MISMATCH) &&
    CHECK_INT(runet_network_add(NULL, layer2), ==, NULL_PARAMETER) &&
    CHECK_INT(runet_network_add(net, NULL), ==, NULL_PARAMETER);

  runet_layer_free(layer2);
  runet_network_free(net);
  return test;
}

static int test_network_predict(void)
{
  RunetNetwork *net = runet_network_create(2);

  RunetLayer *l1 = runet_layer_create_dense(2, 3, RUNET_ACT_RELU);
  RunetLayer *l2 = runet_layer_create_dense(3, 2, RUNET_ACT_NONE);

  float w1[] = {
    1.0f, 0.0f, 0.0f, 
    0.0f, 1.0f, 0.0f
  }; // [2x3]
  runet_matrix_init(l1->weights, 2, 3, w1);
  runet_matrix_fill(l1->bias, 0.0f);

  float w2[] = {
    1.0f, 0.0f,
    0.0f, 1.0f,
    0.0f, 0.0f
  }; // [3x2]
  runet_matrix_init(l2->weights, 3, 2, w2);
  runet_matrix_fill(l2->bias, 0.0f);

  runet_network_add(net, l1);
  runet_network_add(net, l2);

  float in_data[] = {1.0f, 2.0f};
  RunetMatrix *input = runet_matrix_create(1, 2, in_data);
  RunetMatrix *output = NULL;

  runet_network_predict(net, input, &output);

  int test = 
    CHECK_PTR(output, !=, NULL) &&
    CHECK_INT(output->rows, ==, 1) &&
    CHECK_INT(output->cols, ==, 2) &&
    CHECK_FLOAT(output->data[0], ==, 1.0f) &&
    CHECK_FLOAT(output->data[1], ==, 2.0f);

  runet_matrix_free(input);
  runet_network_free(net); // Should free layers too!
  return test;
}

RunetTestSuite *runet_network_test_suite(void)
{
  RunetTest *network_tests[] = {
    runet_test_create("runet_network_create", test_network_create),
    runet_test_create("runet_network_add", test_network_add),
    runet_test_create("runet_network_predict", test_network_predict),
  };

  return runet_test_suite_create(
    "Network",
    network_tests,
    ARRAY_SIZE(network_tests)
  );
}
