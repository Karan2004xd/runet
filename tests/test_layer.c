#include "tests.h"
#include "test.h"
#include "test_suite.h"

#include "../include/layer.h"
#include "../include/macros.h"
#include "../include/matrix.h"
#include "../include/status_codes.h"

static int test_layer_create(void)
{
  RunetLayer *layer = runet_layer_create_dense(10, 5, RUNET_ACT_RELU);

  int test =
    CHECK_PTR(layer, !=, NULL) &&
    CHECK_INT(layer->type, ==, RUNET_LAYER_DENSE) &&
    CHECK_INT(layer->activation, ==, RUNET_ACT_RELU) &&
    CHECK_PTR(layer->weights, !=, NULL) &&
    CHECK_PTR(layer->bias, !=, NULL) &&
    CHECK_PTR(layer->output, !=, NULL) &&
    CHECK_PTR(layer->forward, !=, NULL);

  runet_layer_free(layer);
  return test;
}

static int test_layer_forward(void)
{
  RunetLayer *layer = runet_layer_create_dense(2, 2, RUNET_ACT_RELU);

  // [1, 0]
  // [0, 1]
  float w_data[] = {1.0f, 0.0f, 0.0f, 1.0f};
  runet_matrix_init(layer->weights, 2, 2, w_data);

  float b_data[] = {0.5f, -0.5f};
  runet_matrix_init(layer->bias, 1, 2, b_data);

  float in_data[] = {1.0f, 1.0f};
  RunetMatrix *input = runet_matrix_create(1, 2, in_data);

  int test = CHECK_INT(runet_layer_forward(layer, input),
                       ==,
                       SUCCESS_CODE);

  test =
    CHECK_FLOAT(layer->output->data[0], ==, 1.5f) &&
    CHECK_FLOAT(layer->output->data[1], ==, 0.5f);

  runet_matrix_free(input);
  runet_layer_free(layer);
  return test;
}

RunetTestSuite *runet_layer_test_suite(void)
{
  RunetTest *layer_tests[] = {
    runet_test_create("runet_layer_create", test_layer_create),
    runet_test_create("runet_layer_forward", test_layer_forward),
  };

  return runet_test_suite_create(
    "Layer",
    layer_tests,
    ARRAY_SIZE(layer_tests)
  );
}
