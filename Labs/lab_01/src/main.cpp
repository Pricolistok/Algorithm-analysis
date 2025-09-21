#include <iostream>
#include "../inc/vinograd_algorithm.h"
#include "../inc/simple_multiplication.h"
#include "../inc/funcs.h"


using namespace std;

int main()
{
    size_t n = 3, m = 4;
    double **matrix_a = add_memory_matrix(n, m);
    free_memory_matrix(matrix_a, n);
}
