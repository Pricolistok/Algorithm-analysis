#include <cstddef>
#include "errors.h"

int check_matrix(size_t n_1, size_t m_1, size_t n_2, size_t m_2, double **matrix_1, double **matrix_2)
{
    if (n_1 != n_2 || m_1 != m_2)
        return ERROR;
    for (size_t i = 0; i < n_1; i++)
    {
        for (size_t j = 0; j < m_1; j++) {
            if (matrix_1[i][j] - matrix_2[i][j] > 1e-6)
                return ERROR;
        }
    }
    return OK;
}
