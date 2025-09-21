#include "../inc/errors.h"
#include <cstddef>
#include <cstdlib>



int vinograd_algorithm(size_t  n, size_t m, size_t t,
                        double **matrix_A, double **matrix_B, double **result_matrix)
{
    double *tmp_a = (double*)malloc(n * sizeof(double));
    if (!tmp_a)
        return ERROR_ADD_MEM;
    double *tmp_b = (double*)malloc(m * sizeof(double));
    if (!tmp_b)
    {
        free(tmp_a);
        return ERROR_ADD_MEM;
    }

    for (size_t i = 0; i < n; i++)
    {
        for (size_t k = 0; k < m / 2; k++)
        {
            tmp_a[i] = tmp_a[i] + matrix_A[i][2 * k] * matrix_A[i][2 * k + 1];
        }
    }
    for (size_t i = 0; i < t; i++)
    {
        for (size_t k = 0; k < m / 2; i++)
        {
            tmp_b[i] = tmp_b[i] + matrix_B[2 * k][i] * matrix_B[i][2 * k + 1];
        }
    }
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < t; j++)
        {
            for (size_t k = 0; k < m / 2; k++)
            {
                result_matrix[i][j] = result_matrix[i][j] + (matrix_A[i][2 * k] * matrix_B[2 * k + 1][j])
                        + (matrix_A[i][2 * k + 1] * matrix_B[2 * k][j]);
            }
        }
    }
    if (t % 2 == 0)
    {
        for (size_t i = 0; i < n; i++)
        {
            for (size_t j = 0; j < t; j++)
            {
                result_matrix[i][j] = result_matrix[i][j] + matrix_A[i][t - 1] * matrix_B[t - 1][j];
            }
        }

    }
    free(tmp_a);
    free(tmp_b);
    return OK;
}