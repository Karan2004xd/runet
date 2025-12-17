#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>

void set_matrix(int r, int c, float val, float M[r][c]) {
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      M[i][j] = val;
    }
  }
}

void apply_relu(int r, int c, float M[r][c], float C[r][c]) {
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      C[i][j] = M[i][j] > 0 ? M[i][j] : 0;
    }
  }
}

void apply_softmax(int size, const float M[size], float C[size]) {
  float max_val = -FLT_MAX;
  for (int i = 0; i < size; i++) {
    if (M[i] > max_val) max_val = M[i];
  }

  float sum = 0.0f;
  for (int i = 0; i < size; i++) {
    C[i] = expf(M[i] - max_val);
    sum += C[i];
  }

  for (int i = 0; i < size; i++) {
    C[i] /= sum;
  }
}

void multiply_matrices(int r1, int c1, const float A[r1][c1],
                       int r2, int c2, const float B[r2][c2],
                       float C[r1][c2], int reset) {

  if (c1 != r2) {
    fprintf(stderr, "Invalid dot product format (%dx%d).(%dx%d)\n", r1, c1, r2, c2);
    return;
  }

  if (reset) {
    set_matrix(r1, c2, 0, C);
  }

  for (int i = 0; i < r1; i++) {
    for (int j = 0; j < c2; j++) {
      for (int k = 0; k < c1; k++) {
        C[i][j] += A[i][k] * B[k][j];
      }
    }
  }
}

void add_matrices(int r, int c, const float A[r][c],
                  const float B[r][c], float C[r][c],
                  int reset) {
  if (reset) {
    set_matrix(r, c, 0, C);
  }

  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      C[i][j] = A[i][j] + B[i][j];
    }
  }
}

void print_matrix(int r, int c, const float M[r][c]) {
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      printf("%.2f ", M[i][j]);
    }
    printf("\n");
  }
}

void flatten(int r, int c, const float M[r][c], float C[]) {
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      C[i * c + j] = M[i][j];
    }
  }
}

int argmax(int c, const float M[c]) {
  int max_index = 0;
  float max_val = -FLT_MAX;

  for (int i = 0; i < c; i++) {
    if (M[i] > max_val) {
      max_val = M[i];
      max_index = i;
    }
  }
  return max_index;
}

int main() {
  float weights[2][2] = {
    {1, -1}, {0.5, 2}
  };

  float bias[2][1] = {
    {0.1}, {-0.2}
  };

  float input[2][1] = {
    {2}, {1}
  };

  float mul_result[2][1], add_result[2][1], after_relu[2][1];

  multiply_matrices(2, 2, weights, 2, 1, input, mul_result, 1);
  print_matrix(2, 1, mul_result);

  printf("\n");
  add_matrices(2, 1, mul_result, bias, add_result, 1);
  print_matrix(2, 1, add_result);
  
  printf("\n");
  apply_relu(2, 1, add_result, after_relu);
  print_matrix(2, 1, after_relu);


  float weights_2[2][2] = {
    {1.2, -0.7}, {-0.3, 0.9}
  };

  float bias_2[2][1] = {
    {0.05}, {-0.1}
  };
  float logits[2][1], after_softmax[2];

  printf("\n");
  multiply_matrices(2, 2, weights_2, 2, 1, after_relu, mul_result, 1);
  print_matrix(2, 1, mul_result);

  printf("\n");
  add_matrices(2, 1, mul_result, bias_2, logits, 1);
  print_matrix(2, 1, logits);

  float flattened_res[2];
  flatten(2, 1, logits, flattened_res);

  apply_softmax(2, flattened_res, after_softmax);
  printf("\n%d = Result index\n", argmax(2, after_softmax));
  return 0;
}
