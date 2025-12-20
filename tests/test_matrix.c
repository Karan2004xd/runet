#include "tests.h"
#include "test.h"
#include "test_suite.h"

#include "../include/error_codes.h"
#include "../include/macros.h"
#include "../include/matrix.h"

static int test_matrix_create(void)
{
  int row = 2, col = 2;
  float numbers[] = {1.0f, 2.0f, 3.0f, 4.0f};
  RunetMatrix *m = runet_matrix_create(row, col, numbers);

  int test = 
    CHECK_INT(m->cols, ==, row) && 
    CHECK_INT(m->rows, ==, col);

  for (int i = 0; i < row * col; i++) {
    test = test && CHECK_FLOAT(m->data[i], ==, numbers[i]);
  }
  runet_matrix_free(m);
  return test;
}

static int test_matrix_get(void)
{
  int row = 2, col = 2;
  float numbers[2][2] = {
    {1.0f, 2.0f}, {3.0f, 4.0f}
  };
  RunetMatrix *m = runet_matrix_create(row, col, *numbers);

  int test = 1;
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      test = test && CHECK_FLOAT(numbers[i][j],
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
  float numbers[2][2] = {
    {1.0f, 2.0f}, {3.0f, 4.0f}
  };
  RunetMatrix *m = runet_matrix_create(row, col, NULL);

  int test = 1;
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      runet_matrix_set(m, i, j, numbers[i][j]);
      test = test && CHECK_FLOAT(numbers[i][j],
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
    runet_test_create("runet_matrix_init", test_matrix_create),
    runet_test_create("runet_matrix_get", test_matrix_get),
    runet_test_create("runet_matrix_set", test_matrix_set)
  };

  return runet_test_suite_create(
    "Matrix",
    matrix_tests,
    ARRAY_SIZE(matrix_tests)
  );
}
