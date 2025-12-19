#include "../include/matrix.h"
#include <stdio.h>

int main() {
  float data[2][2] = {
    {1.0f, 2.0f}, {3.2f, 10.0f}
  };

  RunetMatrix *m = runet_matrix_create(2, 2, *(data));
  printf("Rows: %d, Columns: %d\n", m->rows, m->cols);

  for (int i = 0; i < m->rows; i++) {
    for (int j = 0; j < m->cols; j++) {
      printf("%f ", runet_matrix_get(m, i, j));
    }
    printf("\n");
  }

  runet_matrix_free(m);
  return 0;
}
