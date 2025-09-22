#include <cstddef>
#include <cstdlib>
#include <iostream>
#include "errors.h"
using namespace std;

int input_sizes(size_t *n, size_t *m)
{
    int n_int, m_int;
    cout << "Input N: ";
    cin >> n_int;
    if (n_int <= 0)
        return ERROR_INPUT_DATA;

    cout << "Input M: ";
    cin >> m_int;
    if (m_int <= 0)
        return ERROR_INPUT_DATA;

    *n = n_int;
    *m = m_int;

    return OK;
}


int input_matrix(double **arr, size_t n, size_t m)
{
    int elem;
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
        {
            cin >> elem;
            arr[i][j] = elem;
        }
    }
    return OK;
}


void print_matrix(double **arr, size_t n, size_t m)
{
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
        {
            cout << arr[i][j] << "  ";
        }
        cout << endl;
    }
}
