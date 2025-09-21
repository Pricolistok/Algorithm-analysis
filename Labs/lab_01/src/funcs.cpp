#include <cstddef>
#include <cstdlib>


void free_memory_matrix(double **arr, size_t n)
{
    for (size_t i = 0; i < n; i++)
        free(arr[i]);
    free(arr);
}


double **add_memory_matrix(size_t n, size_t m)
{
    double **arr = (double**)malloc(n * sizeof(double*));
    if (!arr)
        return NULL;

    for (size_t i = 0; i < n; i++)
    {
        arr[i] = (double*)malloc(m * sizeof(double ));
        if (!arr[i])
        {
            free_memory_matrix(arr, i);
            return NULL;
        }
    }
    return arr;
}