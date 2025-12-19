#ifndef __RUNET_MATRIX_H__
#define __RUNET_MATRIX_H__

typedef struct runet_matrix {
  int rows;
  int cols;
  float *data;
} RunetMatrix;

RunetMatrix *runet_matrix_create(int, int, float *);
void runet_matrix_free(RunetMatrix *);

void runet_matrix_set(RunetMatrix *, int, int, float);
float runet_matrix_get(const RunetMatrix *, int, int);

#endif // __RUNET_MATRIX_H__
