#ifndef __RUNET_MATRIX_H__
#define __RUNET_MATRIX_H__

struct runet_matrix {
  int rows; /** < The number of rows of matrix */
  int cols; /** < The number of columns of matrix */
  float *data; /** < Array of actual data */
};

typedef struct runet_matrix RunetMatrix;

/**
  * @brief Creates a new 2D Matrix.
  * * This function based on the provided data allocates
  * a new 2D array and copies the provided data into it.
  *
  * @param row The number of row of the matrix.
  * @param col The number of col of the matrix.
  * @param data A pointer to the array of numbers of type float.
  *
  * @return RunetMatrix* A pointer to a new matrix(shape = row x col).
  *
  * @note This function assumes the parameters passed in to be correct,
  * meaning in case of incorrect parameter there can be undefined behaviour.
  */
RunetMatrix *runet_matrix_create(int row, int col, float *data);

/**
  * @brief Frees the memory of the existing matrix struct.
  * * This function destroys or frees the provided matrix struct.
  *
  * @param matrix A pointer to a matrix struct (RunetMatrix).
  */
void runet_matrix_free(RunetMatrix *matrix);

/**
  * @brief Sets the given value to the provided location in matrix.
  * * This function based on the given row and column value, sets the
  * provided value, if the given location is valid.
  *
  * @param matrix A pointer to matrix struct.
  * @param row The row index.
  * @param col The column index.
  * @param value The value to set.
  *
  * @return int If successfull in setting the value, the function
  * returns the index of the value stored (in 1D format) which is
  * always greater then or equal to 0.
  *
  * And if not successfull it returns a negative value.
  * (refer the RUNET_ERROR_CODES for more information).
  */
int runet_matrix_set(RunetMatrix *matrix, int row, int col, float value);

/**
  * @brief Gets the value stored at the provided location in matrix.
  * * This function fetches the value stored in the matrix based on
  * the given row and column value.
  *
  * @param matrix A pointer to matrix struct.
  * @param row The row index.
  * @param col The column index.
  *
  * @return float In case of valid location, function returns the
  * underlying stored value.
  *
  * And if not successfull it returns a negative value.
  * (refer the RUNET_ERROR_CODES for more information).
  */
float runet_matrix_get(const RunetMatrix *matrix, int row, int col);

#endif // __RUNET_MATRIX_H__
