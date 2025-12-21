#include "../include/matrix.h"
#include "../include/status_codes.h"
#include "../include/macros.h"

#include <stdlib.h>
#include <string.h>

RunetMatrix *runet_matrix_create(int rows, int cols, float *data)
{
  RunetMatrix *m = malloc(sizeof(RunetMatrix));
  if (m == NULL) return NULL;

  m->rows = rows;
  m->cols = cols;

  m->data = malloc(rows * cols * sizeof(float));
  if (data != NULL) {
    memcpy(m->data, data, rows * cols * sizeof(float));
  }
  return m;
}

void runet_matrix_free(RunetMatrix *m)
{
  if (m->data != NULL) {
    free(m->data);
  }
  free(m);
}

RunetMatrix *runet_matrix_copy(const RunetMatrix *src)
{
  if (!src) {
    return NULL;
  }

  RunetMatrix *dest = runet_matrix_create(src->rows, src->cols, NULL);

  size_t total_bytes = src->rows * src->cols * sizeof(float);
  memcpy(dest->data, src->data, total_bytes);

  return dest;
}

static int runet_get_index(const RunetMatrix *m, int row, int col)
{
  if (row < 0 || col < 0) {
    return -1;
  }

  if (row >= m->rows || col >= m->cols) {
    return -1;
  }

  return ARRAY_INDEX(row, col, m->cols);
}

int runet_matrix_set(RunetMatrix *m, int row, int col, float val)
{
  int index;

  if ((index = runet_get_index(m, row, col)) != -1) {
    m->data[index] = val;
    return index;
  }
  return INVALID_MATRIX_INDEX_ACCESS;
}

float runet_matrix_get(const RunetMatrix *m, int row, int col)
{
  int index;

  if ((index = runet_get_index(m, row, col)) != -1) {
    return m->data[index];
  }
  return INVALID_MATRIX_INDEX_ACCESS;
}
