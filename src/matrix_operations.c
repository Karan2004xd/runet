#include "../include/matrix.h"
#include "../include/matrix_operations.h"
#include "../include/error_codes.h"
#include <float.h>
#include <string.h>

int runet_matrix_mul(RunetMatrix *dest,
                     const RunetMatrix *src_a,
                     const RunetMatrix *src_b)
{
  if (src_a->cols != src_b->rows) {
    return INCOMPATIBLE_MATRIX_SHAPES;
  }

  for (int i = 0; i < src_a->rows; i++) {
    for (int j = 0; j < src_b->cols; j++) {
      for (int k = 0; k < src_a->cols; k++) {
        float a = runet_matrix_get(src_a, i, k);
        float b = runet_matrix_get(src_a, k, j);
        float c = runet_matrix_get(dest, i, j);

        runet_matrix_set(dest, i, j, (a * b) + c);
      }
    }
  }
  return SUCCESS_CODE;
}

int runet_matrix_add(RunetMatrix *dest,
                     const RunetMatrix *src_a,
                     const RunetMatrix *src_b)
{
  if (src_a->rows != src_b->rows) {
    return INCOMPATIBLE_MATRIX_SHAPES;
  }

  if (src_a->cols != src_b->cols) {
    return INCOMPATIBLE_MATRIX_SHAPES;
  }

  for (int i = 0; i < src_a->rows; i++) {
    for (int j = 0; j < src_a->cols; j++) {
      float a = runet_matrix_get(src_a, i, j);
      float b = runet_matrix_get(src_b, i, j);

      runet_matrix_set(dest, i, j, a + b);
    }
  }
  return SUCCESS_CODE;
}

int runet_matrix_argmax(const RunetMatrix *matrix)
{
  int size = matrix->rows * matrix->cols;
  if (matrix == NULL || size <= 0) {
    return EMPTY_MATRIX;
  }

  int max_index = 0;
  float max_val = FLT_MIN;
}
