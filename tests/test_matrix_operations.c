#include "test_suite.h"
#include "test.h"
#include "tests.h"
#include "../include/status_codes.h"
#include "../include/macros.h"
#include "../include/matrix.h"
#include "../include/matrix_operations.h"

#include <math.h>

static int test_matrix_mul(void)
{
  float input[] = {1.0f, 2.0f, 3.0f, 4.0f};
  float mul_res[] = {7.0f, 10.0f, 15.0f, 22.0f};

  RunetMatrix *m1 = runet_matrix_create(2, 2, input);
  RunetMatrix *m2 = runet_matrix_create(2, 2, input);
  RunetMatrix *temp = runet_matrix_create(2, 2, NULL);

  int test = CHECK_INT(runet_matrix_mul(temp, m1, m2), ==, SUCCESS_CODE);
  for (int i = 0; i < 4; i++) {
    test = test && CHECK_FLOAT(temp->data[i], ==, mul_res[i]);
  }

  test = test && CHECK_INT(runet_matrix_mul(NULL, m1, m2), ==, NULL_PARAMETER);
  test = test && CHECK_INT(runet_matrix_mul(temp, NULL, m2), ==, NULL_PARAMETER);
  test = test && CHECK_INT(runet_matrix_mul(temp, m1, NULL), ==, NULL_PARAMETER);

  RunetMatrix *invalid_dim_m = runet_matrix_create(3, 2, NULL);
  test = test && CHECK_INT(runet_matrix_mul(temp, m1, invalid_dim_m),
                           ==,
                           INCOMPATIBLE_MATRIX_SHAPES);

  runet_matrix_free(m1);
  runet_matrix_free(m2);
  runet_matrix_free(temp);
  runet_matrix_free(invalid_dim_m);
  return test;
}

static int test_matrix_add(void)
{
  float input[] = {1.0f, 2.0f, 3.0f, 4.0f};
  float add_res[] = {2.0f, 4.0f, 6.0f, 8.0f};

  RunetMatrix *m1 = runet_matrix_create(2, 2, input);
  RunetMatrix *m2 = runet_matrix_create(2, 2, input);
  RunetMatrix *temp = runet_matrix_create(2, 2, NULL);

  int test = CHECK_INT(runet_matrix_add(temp, m1, m2), ==, SUCCESS_CODE);
  for (int i = 0; i < 4; i++) {
    test = test && CHECK_FLOAT(temp->data[i], ==, add_res[i]);
  }

  test = test && CHECK_INT(runet_matrix_add(NULL, m1, m2), ==, NULL_PARAMETER);
  test = test && CHECK_INT(runet_matrix_add(temp, NULL, m2), ==, NULL_PARAMETER);
  test = test && CHECK_INT(runet_matrix_add(temp, m1, NULL), ==, NULL_PARAMETER);

  RunetMatrix *invalid_dim_m = runet_matrix_create(3, 2, NULL);
  test = test && CHECK_INT(runet_matrix_add(temp, m1, invalid_dim_m),
                           ==,
                           INCOMPATIBLE_MATRIX_SHAPES);

  runet_matrix_free(m1);
  runet_matrix_free(m2);
  runet_matrix_free(temp);
  runet_matrix_free(invalid_dim_m);
  return test;
}

static int test_matrix_max(void)
{
  float res;
  float input[] = {1.0f, 2.0f, 3.0f, 4.0f};

  RunetMatrix *m = runet_matrix_create(2, 2, input);

  int test =
    CHECK_INT(runet_matrix_max(m, &res), ==, SUCCESS_CODE) &&
    CHECK_FLOAT(res, ==, 4.0f) &&
    CHECK_INT(runet_matrix_max(NULL, &res), ==, NULL_PARAMETER) &&
    CHECK_INT(runet_matrix_max(m, NULL), ==, NULL_PARAMETER);

  runet_matrix_free(m);
  return test;
}

static int test_matrix_min(void)
{
  float res;
  float input[] = {1.0f, 2.0f, 3.0f, 4.0f};

  RunetMatrix *m = runet_matrix_create(2, 2, input);

  int test =
    CHECK_INT(runet_matrix_min(m, &res), ==, SUCCESS_CODE) &&
    CHECK_FLOAT(res, ==, 1.0f) &&
    CHECK_INT(runet_matrix_min(NULL, &res), ==, NULL_PARAMETER) &&
    CHECK_INT(runet_matrix_min(m, NULL), ==, NULL_PARAMETER);

  runet_matrix_free(m);
  return test;
}

static int test_matrix_fill(void)
{
  RunetMatrix *m = runet_matrix_create(2, 2, NULL);
  float val = 2.5;

  int test =
    CHECK_INT(runet_matrix_fill(m, val), ==, SUCCESS_CODE) &&
    CHECK_INT(runet_matrix_fill(NULL, val), ==, NULL_PARAMETER);

  for (int i = 0; i < 4; i++) {
    test = test && CHECK_FLOAT(val, ==, m->data[i]);
  }
  runet_matrix_free(m);
  return test;
}

static int test_matrix_add_bias(void)
{
  float m_data[] = {1.0f, 2.0f, 3.0f, 4.0f};
  float b_data[] = {10.0f, 20.0f};
  float expected[] = {11.0f, 22.0f, 13.0f, 24.0f};

  RunetMatrix *m = runet_matrix_create(2, 2, m_data);
  RunetMatrix *b = runet_matrix_create(1, 2, b_data);

  int test = CHECK_INT(runet_matrix_add_bias(m, b), ==, SUCCESS_CODE);

  for (int i = 0; i < 4; i++) {
    test = test && CHECK_FLOAT(m->data[i], ==, expected[i]);
  }

  test = test && CHECK_INT(runet_matrix_add_bias(NULL, b), ==, NULL_PARAMETER);
  test = test && CHECK_INT(runet_matrix_add_bias(m, NULL), ==, NULL_PARAMETER);

  runet_matrix_free(m);
  runet_matrix_free(b);
  return test;
}

static int test_apply_relu(void)
{
  float input[] = {-10.f, 5.0f, 0.0f, -0.0001f};
  float expected[] = {0.0f, 5.0f, 0.0f, 0.0f};

  RunetMatrix *src = runet_matrix_create(2, 2, input);
  RunetMatrix *dest = runet_matrix_create(2, 2, NULL);

  int test = CHECK_INT(runet_apply_relu(dest, src), ==, SUCCESS_CODE);

  for (int i = 0; i < 4; i++) {
    test = test && CHECK_FLOAT(dest->data[i], ==, expected[i]);
  }

  test = test && CHECK_INT(runet_apply_relu(NULL, src), ==, NULL_PARAMETER);
  test = test && CHECK_INT(runet_apply_relu(dest, NULL), ==, NULL_PARAMETER);

  runet_matrix_free(src);
  runet_matrix_free(dest);
  return test;
}

static int test_apply_softmax(void)
{
  float input[] = {0.0f, 1.0f, 2.0f};
  RunetMatrix *src = runet_matrix_create(1, 3, input);
  RunetMatrix *dest = runet_matrix_create(1, 3, NULL);

  int test = CHECK_INT(runet_apply_softmax(dest, src), ==, SUCCESS_CODE);

  float sum = 0.0f;
  for (int i = 0; i < 3; i++) {
    test = test && CHECK_FLOAT(dest->data[i], >, 0.0f);
    sum += dest->data[i];
  }

  // small epsilon used for float precision
  test = test && CHECK_FLOAT(fabsf(sum - 1.0f), <, 1e-6);

  runet_matrix_free(src);
  runet_matrix_free(dest);
  return test;
}

RunetTestSuite *runet_matrix_ops_test_suite(void)
{
  RunetTest *tests[] = {
    runet_test_create("runet_matrix_mul", test_matrix_mul),
    runet_test_create("runet_matrix_add", test_matrix_add),
    runet_test_create("runet_matrix_max", test_matrix_max),
    runet_test_create("runet_matrix_min", test_matrix_min),
    runet_test_create("runet_matrix_fill", test_matrix_fill),
    runet_test_create("runet_matrix_add_bias", test_matrix_add_bias),
    runet_test_create("runet_apply_relu", test_apply_relu),
    runet_test_create("runet_apply_softmax", test_apply_softmax),
  };

  return runet_test_suite_create(
    "Matrix Operation",
    tests,
    ARRAY_SIZE(tests)
  );
}
