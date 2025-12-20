#ifndef __MATRIX_OPERATIONS_H__
#define __MATRIX_OPERATIONS_H__

typedef struct runet_matrix RunetMatrix;

int runet_matrix_mul(RunetMatrix *dest,
                     const RunetMatrix *src_a,
                     const RunetMatrix *src_b);

int runet_matrix_add(RunetMatrix *dest,
                     const RunetMatrix *src_a,
                     const RunetMatrix *src_b);

int runet_matrix_argmax(const RunetMatrix *matrix);

#endif // __MATRIX_OPERATIONS_H__
