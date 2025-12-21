#include "../include/matrix.h"
#include "../include/matrix_operations.h"
#include "../include/status_codes.h"
#include "../include/macros.h"

#include <float.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>

static int validate_matrix_ptrs(int count, ...)
{
  va_list args;
  va_start(args, count);

  for (int i = 0; i < count; i++) {
    RunetMatrix *m = va_arg(args, RunetMatrix *);
    if (m == NULL) {
      va_end(args);
      return NULL_PARAMETER;
    }
  }
  va_end(args);
  return SUCCESS_CODE;
}

static float max_wrapper_f(float a, float b)
{
  return MAX(a, b);
}

static float min_wrapper_f(float a, float b)
{
  return MIN(a, b);
}

static int filter_value(const RunetMatrix *matrix,
                        float initial_value,
                        float *value,
                        float (*filter)(float a, float b))
{
  if (validate_matrix_ptrs(1, matrix) == NULL_PARAMETER) {
    return NULL_PARAMETER;
  }

  if (!value) {
    return NULL_PARAMETER;
  }

  int size = matrix->rows * matrix->cols;
  if (size <= 0) {
    return NULL_PARAMETER;
  }

  float max_val = initial_value;
  for (int i = 0; i < size; i++) {
    max_val = filter(matrix->data[i], max_val);
  }

  *value = max_val;
  return SUCCESS_CODE;
}

int runet_matrix_mul(RunetMatrix *dest,
                     const RunetMatrix *src_a,
                     const RunetMatrix *src_b)
{
  if (validate_matrix_ptrs(3, dest, src_a, src_b) == NULL_PARAMETER) {
    return NULL_PARAMETER;
  }

  if (src_a->cols != src_b->rows) {
    return INCOMPATIBLE_MATRIX_SHAPES;
  }

  if (dest->rows != src_a->rows || dest->cols != src_b->cols) {
    return INCOMPATIBLE_MATRIX_SHAPES;
  }

  for (int i = 0; i < src_a->rows; i++) {
    for (int j = 0; j < src_b->cols; j++) {
      float sum = 0.0f;

      for (int k = 0; k < src_a->cols; k++) {
        int a_idx = ARRAY_INDEX(i, k, src_a->cols);
        int b_idx = ARRAY_INDEX(k, j, src_b->cols);

        sum += src_a->data[a_idx] * src_b->data[b_idx];
      }
      dest->data[ARRAY_INDEX(i, j, dest->cols)] = sum;
    }
  }
  return SUCCESS_CODE;
}

int runet_matrix_add(RunetMatrix *dest,
                     const RunetMatrix *src_a,
                     const RunetMatrix *src_b)
{
  if (validate_matrix_ptrs(3, dest, src_a, src_b) == NULL_PARAMETER) {
    return NULL_PARAMETER;
  }

  if (src_a->rows != src_b->rows) {
    return INCOMPATIBLE_MATRIX_SHAPES;
  }

  if (src_a->cols != src_b->cols) {
    return INCOMPATIBLE_MATRIX_SHAPES;
  }

  if (dest->rows != src_a->rows || dest->cols != src_a->cols) {
    return INCOMPATIBLE_MATRIX_SHAPES;
  }

  for (int i = 0; i < src_a->rows; i++) {
    for (int j = 0; j < src_a->cols; j++) {
      int a_idx = ARRAY_INDEX(i, j, src_a->cols);
      int b_idx = ARRAY_INDEX(i, j, src_b->cols);
      int dest_idx = ARRAY_INDEX(i, j, dest->cols);

      dest->data[dest_idx] = src_a->data[a_idx] + src_b->data[b_idx];
    }
  }
  return SUCCESS_CODE;
}

int runet_matrix_max(const RunetMatrix *matrix,
                     float *value)
{
  return filter_value(matrix, -FLT_MAX, value, max_wrapper_f);
}

int runet_matrix_min(const RunetMatrix *matrix, float *value)
{
  return filter_value(matrix, FLT_MAX, value, min_wrapper_f);
}

int runet_matrix_fill(RunetMatrix *matrix, float value)
{
  if (validate_matrix_ptrs(1, matrix) == NULL_PARAMETER) {
    return NULL_PARAMETER;
  }

  for (int i = 0; i < matrix->rows * matrix->cols; i++) {
    matrix->data[i] = value;
  }
  return SUCCESS_CODE;
}

int runet_matrix_add_bias(RunetMatrix *matrix, const RunetMatrix *bias)
{
  if (validate_matrix_ptrs(2, matrix, bias) == NULL_PARAMETER) {
    return NULL_PARAMETER;
  }

  int bias_len = bias->rows * bias->cols;
  if (bias_len != matrix->cols) {
    return INCOMPATIBLE_MATRIX_SHAPES;
  }

  for (int i = 0; i < matrix->rows; i++) {
    for (int j = 0; j < matrix->cols; j++) {
      matrix->data[ARRAY_INDEX(i, j, matrix->cols)] += bias->data[j];
    }
  }

  return SUCCESS_CODE;
}

int runet_apply_relu(RunetMatrix *dest, const RunetMatrix *src)
{
  if (validate_matrix_ptrs(2, dest, src) == NULL_PARAMETER) {
    return NULL_PARAMETER;
  }

  for (int i = 0; i < src->cols * src->rows; i++) {
    dest->data[i] = MAX(0, src->data[i]);
  }
  return SUCCESS_CODE;
}

int runet_apply_softmax(RunetMatrix *dest, const RunetMatrix *src)
{
  if (validate_matrix_ptrs(2, dest, src) == NULL_PARAMETER) {
    return NULL_PARAMETER;
  }

  float max_val = -FLT_MAX;
  int size = src->cols * src->rows;

  for (int i = 0; i < size; i++) {
    max_val = MAX(max_val, src->data[i]);
  }

  float sum = 0.0f;
  for (int i = 0; i < size; i++) {
    dest->data[i] = expf(src->data[i] - max_val);
    sum += dest->data[i];
  }

  for (int i = 0; i < size; i++) {
    dest->data[i] /= sum;
  }

  return SUCCESS_CODE;
}
