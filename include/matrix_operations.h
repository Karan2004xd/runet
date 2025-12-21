#ifndef __MATRIX_OPERATIONS_H__
#define __MATRIX_OPERATIONS_H__

typedef struct runet_matrix RunetMatrix;

/**
  * @brief Multiplies two matrices.
  * * This function calculates the dot product of two matrices
  * and stores the result inside the provided array.
  *
  * @param dest A destination pointer where the result is to be stored
  * @param src_a A const pointer of Matrix A.
  * @param src_b A const pointer of Matrix B.
  *
  * @return int A status code specifying operation success or failure.
  * (refer to RUNET_STATUS_CODE for more information)
  */
int runet_matrix_mul(RunetMatrix *dest,
                     const RunetMatrix *src_a,
                     const RunetMatrix *src_b);

/**
  * @brief Adds two matrices.
  * * This function calculates the sum of two matrices and 
  * stores the result inside the provided array.
  *
  * @param dest A destination pointer where the result is to be stored.
  * @param src_a A const pointer of Matrix A.
  * @param src_b A const pointer of Matrix B.
  *
  * @return int A status code specifying operation success or failure.
  * (refer to RUNET_STATUS_CODE for more information)
  */
int runet_matrix_add(RunetMatrix *dest,
                     const RunetMatrix *src_a,
                     const RunetMatrix *src_b);

/**
  * @brief Finds the maximum value in the matrix
  * * This function finds the largest value in the matrix
  * and stores it inside the provided pointer.
  *
  * @param matrix A const pointer to Matrix to find the number from.
  * @param val A pointer to the container where the result will be stored.
  *
  * @return int A status code specifying operation success or failure.
  * (refer to RUNET_STATUS_CODE for more information)
  */
int runet_matrix_max(const RunetMatrix *matrix, float *val);

/**
  * @brief Finds the minimum value in the matrix
  * * This function finds the largest value in the matrix
  * and stores it inside the provided pointer.
  *
  * @param matrix A const pointer to Matrix to find the number from.
  * @param val A pointer to the container where the result will be stored.
  *
  * @return int A status code specifying operation success or failure.
  * (refer to RUNET_STATUS_CODE for more information)
  */
int runet_matrix_min(const RunetMatrix *matrix, float *val);

/**
  * @brief Fills the matrix with the provided value.
  * * This function sets each of the element of the matrix
  * to the provided value.
  *
  * @param matrix A pointer to the Matrix (where the changes will be made).
  * @param value The value to set.
  *
  * @return int A status code specifying operation success or failure.
  * (refer to RUNET_STATUS_CODE for more information)
  */
int runet_matrix_fill(RunetMatrix *matrix, float value);

/**
  * @brief Adds bias to the matrix (Addition)
  * * This function adds the provided bias to the provided matrix.
  *
  * @param matrix A pointer to the original Matrix.
  * @param bias A pointer to the bias Matrix.
  *
  * @return int A status code specifying operation success or failure.
  * (refer to RUNET_STATUS_CODE for more information)
  *
  * @note The function expects the bias matrix shape to be (1 x N).
  */
int runet_matrix_add_bias(RunetMatrix *matrix, const RunetMatrix *bias);

/**
  * @brief Applys the activation function ReLU to the matrix.
  * * This function applies the activation function ReLU on the
  * provided destination matrix from the source matrix.
  *
  * @param dest A pointer to the destination matrix
  * (where the result will be stored)
  * @param src A pointer to the source matrix.
  *
  * @return int A status code specifying operation success or failure.
  * (refer to RUNET_STATUS_CODE for more information)
  */
int runet_apply_relu(RunetMatrix *dest, const RunetMatrix *src);

/**
  * @brief Applys the activation function Softmax to the matrix.
  * * This function applies the activation function Softmax on the
  * provided destination matrix from the source matrix.
  *
  * @param dest A pointer to the destination matrix
  * (where the result will be stored)
  * @param src A pointer to the source matrix.
  *
  * @return int A status code specifying operation success or failure.
  * (refer to RUNET_STATUS_CODE for more information)
  */
int runet_apply_softmax(RunetMatrix *dest, const RunetMatrix *src);

#endif // __MATRIX_OPERATIONS_H__
