#include <cstddef>
#include <cstdlib>
#include "vinograd_algorithm.h"
#include "errors.h"


int vinograd_algorithm(size_t n, size_t m, size_t t,
                       double **matrix_A, double **matrix_B, double **result_matrix)
{
    if (n != t)
        return ERROR;
    double *tmp_a = (double*)calloc(n, sizeof(double));
    if (!tmp_a)
        return ERROR_ADD_MEM;

    double *tmp_b = (double*)calloc(t, sizeof(double));
    if (!tmp_b)
    {
        free(tmp_a);
        return ERROR_ADD_MEM;
    }

    for (size_t i = 0; i < n; i++)
    {
        for (size_t k = 0; k < m / 2; k++)
        {
            tmp_a[i] += matrix_A[i][2 * k] * matrix_A[i][2 * k + 1];
        }
    }

    for (size_t j = 0; j < t; j++)
    {
        for (size_t k = 0; k < m / 2; k++)
        {
            tmp_b[j] += matrix_B[2 * k][j] * matrix_B[2 * k + 1][j];
        }
    }


    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < t; j++)
        {
            result_matrix[i][j] = -tmp_a[i] - tmp_b[j];

            for (size_t k = 0; k < m / 2; k++)
            {
                result_matrix[i][j] += (matrix_A[i][2 * k] + matrix_B[2 * k + 1][j]) *
                                       (matrix_A[i][2 * k + 1] + matrix_B[2 * k][j]);
            }
        }
    }

    if (m % 2 != 0)
    {
        size_t last = m - 1;
        for (size_t i = 0; i < n; i++)
        {
            for (size_t j = 0; j < t; j++)
            {
                result_matrix[i][j] += matrix_A[i][last] * matrix_B[last][j];
            }
        }
    }

    free(tmp_a);
    free(tmp_b);
    return OK;
}