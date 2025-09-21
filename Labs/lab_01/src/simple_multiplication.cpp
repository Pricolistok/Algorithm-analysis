#include "../inc/errors.h"
#include <cstddef>



int simple_multiplication(size_t  n, size_t m, size_t t,
                             double **matrix_A, double **matrix_B, double **result_matrix)
{
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < t; j++)
        {
            for (size_t k = 0; k < m; k++)
            {
                result_matrix[i][j] += matrix_A[i][k] * matrix_B[k][j];
            }
        }
    }
    return OK;
}