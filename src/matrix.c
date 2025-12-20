#include "../include/matrix.h"
#include "../include/error_codes.h"

#include <stdio.h>
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

static int runet_get_index(const RunetMatrix *m, int row, int col)
{
  if (row < 0 || col < 0) {
    return -1;
  }

  if (row >= m->rows || col >= m->cols) {
    return -1;
  }

  return (row * m->cols) + col;
}

int runet_matrix_set(RunetMatrix *m, int row, int col, float val)
{
  int index;

  if ((index = runet_get_index(m, row, col)) != -1) {
    m->data[index] = val;
    return index;
  }

  fprintf(stderr,
          "Trying to access an invalid index for a matrix (%dx%d)\n",
          m->rows, m->cols);

  return INVALID_MATRIX_INDEX_ACCESS;
}

float runet_matrix_get(const RunetMatrix *m, int row, int col)
{
  int index;

  if ((index = runet_get_index(m, row, col)) != -1) {
    return m->data[index];
  }

  fprintf(stderr,
          "Trying to access an invalid index for a matrix (%dx%d)\n",
          m->rows, m->cols);

  return INVALID_MATRIX_INDEX_ACCESS;
}
