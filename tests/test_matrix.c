#include "tests.h"
#include "test.h"
#include "test_suite.h"

#include "../include/status_codes.h"
#include "../include/macros.h"
#include "../include/matrix.h"

static int test_matrix_create(void)
{
  int row = 2, col = 2;
  float input[] = {1.0f, 2.0f, 3.0f, 4.0f};
  RunetMatrix *m = runet_matrix_create(row, col, input);

  int test = 
    CHECK_INT(m->cols, ==, row) && 
    CHECK_INT(m->rows, ==, col);

  for (int i = 0; i < row * col; i++) {
    test = test && CHECK_FLOAT(m->data[i], ==, input[i]);
  }
  runet_matrix_free(m);
  return test;
}

static int test_matrix_init(void)
{
  int row = 2, col = 3;
  float input[] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f};
  RunetMatrix *m = runet_matrix_create(2, 2, NULL);

  int test = CHECK_INT(runet_matrix_init(m, row, col, input),
                       ==,
                       SUCCESS_CODE);

  for (int i = 0; i < row * col; i++) {
    test = test && CHECK_FLOAT(m->data[i], ==, input[i]);
  }

  test = test && CHECK_INT(runet_matrix_init(m, 2, 2, NULL),
                           ==,
                           SUCCESS_CODE);

  runet_matrix_free(m);
  return test;
}

static int test_matrix_copy(void)
{
  float input[] = {1.0f, 2.0f, 3.0f, 4.0f};
  RunetMatrix *m = runet_matrix_create(2, 2, input);
  RunetMatrix *copy = runet_matrix_copy(m);

  int test =
    CHECK_PTR(copy, !=, NULL) &&
    CHECK_PTR(copy->data, !=, m->data) &&
    CHECK_INT(copy->cols, ==, 2) &&
    CHECK_INT(copy->rows, ==, 2);

  for (int i = 0; i < 4; i++) {
    test = test && CHECK_FLOAT(copy->data[i], ==, input[i]);
  }

  test = test && CHECK_PTR(runet_matrix_copy(NULL), ==, NULL);

  runet_matrix_free(m);
  runet_matrix_free(copy);
  return test;
}

static int test_matrix_get(void)
{
  int row = 2, col = 2;
  float input[2][2] = {
    {1.0f, 2.0f}, {3.0f, 4.0f}
  };
  RunetMatrix *m = runet_matrix_create(row, col, *input);

  int test = 1;
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      test = test && CHECK_FLOAT(input[i][j],
                                 ==,
                                 runet_matrix_get(m, i, j));
    }
  }

  test = test && (runet_matrix_get(m, 100, 100) == INVALID_MATRIX_INDEX_ACCESS);
  test = test && (runet_matrix_get(m, 0, 0) >= 0);

  runet_matrix_free(m);
  return test;
}

static int test_matrix_set(void)
{
  int row = 2, col = 2;
  float input[2][2] = {
    {1.0f, 2.0f}, {3.0f, 4.0f}
  };
  RunetMatrix *m = runet_matrix_create(row, col, NULL);

  int test = 1;
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      runet_matrix_set(m, i, j, input[i][j]);
      test = test && CHECK_FLOAT(input[i][j],
                                 ==,
                                 m->data[(i * col) + j]);
    }
  }

  test = test && (runet_matrix_set(m, 100, 100, 1.0f) == INVALID_MATRIX_INDEX_ACCESS);
  test = test && (runet_matrix_set(m, 0, 0, 0) >= 0);

  runet_matrix_free(m);
  return test;
}

RunetTestSuite *runet_matrix_test_suite(void)
{
  RunetTest *matrix_tests[] = {
    runet_test_create("runet_matrix_create", test_matrix_create),
    runet_test_create("runet_matrix_init", test_matrix_init),
    runet_test_create("runet_matrix_copy", test_matrix_copy),
    runet_test_create("runet_matrix_get", test_matrix_get),
    runet_test_create("runet_matrix_set", test_matrix_set)
  };

  return runet_test_suite_create(
    "Matrix",
    matrix_tests,
    ARRAY_SIZE(matrix_tests)
  );
}
