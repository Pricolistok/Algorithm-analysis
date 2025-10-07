#include "vinograd_update.h"
#include "errors.h"
#include <cstddef>
#include <cstdlib>

int vinograd_algorithm_update(size_t n, size_t m, size_t t, double **matrix_A,
                              double **matrix_B, double **result_matrix) {

  if (n != t)
    return ERROR;
  size_t idx1;
  size_t idx2;

  size_t half_m = m / 2;
  size_t last = m - 1;
  double sum;

  double *tmp_a = (double *)calloc(n, sizeof(double));
  if (!tmp_a)
    return ERROR_ADD_MEM;

  double *tmp_b = (double *)calloc(t, sizeof(double));
  if (!tmp_b) {
    free(tmp_a);
    return ERROR_ADD_MEM;
  }

  for (size_t i = 0; i < n; i++) {
    sum = 0.0;
    for (size_t k = 0; k < half_m; k++) {
      idx1 = 2 * k;
      idx2 = idx1 + 1;
      sum += matrix_A[i][idx1] * matrix_A[i][idx2];
    }
    tmp_a[i] = sum;
  }

  for (size_t j = 0; j < t; j++) {
    sum = 0.0;
    for (size_t k = 0; k < half_m; k++) {
      idx1 = 2 * k;
      idx2 = idx1 + 1;
      sum += matrix_B[idx1][j] * matrix_B[idx2][j];
    }
    tmp_b[j] = sum;
  }

  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < t; j++) {
      double res = -tmp_a[i] - tmp_b[j];

      for (size_t k = 0; k < half_m; k++) {
        idx1 = 2 * k;
        idx2 = idx1 + 1;

        res += (matrix_A[i][idx1] + matrix_B[idx2][j]) *
               (matrix_A[i][idx2] + matrix_B[idx1][j]);
      }

      result_matrix[i][j] = res;
    }
  }

  if (m % 2 != 0) {
    for (size_t i = 0; i < n; i++) {
      for (size_t j = 0; j < t; j++) {
        result_matrix[i][j] += matrix_A[i][last] * matrix_B[last][j];
      }
    }
  }

  free(tmp_a);
  free(tmp_b);
  return OK;
}
