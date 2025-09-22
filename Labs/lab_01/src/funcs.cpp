#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <x86intrin.h>
#include <cstdint>
#include <fstream>
#include <chrono>
#include "../inc/input_output.h"
#include "../inc/funcs.h"
#include "../inc/simple_multiplication.h"
#include "../inc/vinograd_algorithm.h"
#include "../inc/errors.h"

using namespace std;


inline void compiler_barrier() {
    asm volatile ("" : : : "memory");
}


inline uint64_t read_tsc() {
    compiler_barrier();
    uint64_t tsc = __rdtsc();
    compiler_barrier();
    return tsc;
}

void free_memory_matrix(double **arr, size_t n)
{
    for (size_t i = 0; i < n; i++)
        free(arr[i]);
    free(arr);
}


double **add_memory_matrix(size_t n, size_t m)
{
    double **arr = (double**)calloc(n, sizeof(double*));
    if (!arr)
        return NULL;

    for (size_t i = 0; i < n; i++)
    {
        arr[i] = (double*)calloc(m, sizeof(double ));
        if (!arr[i])
        {
            free_memory_matrix(arr, i);
            return NULL;
        }
    }
    return arr;
}

double* add_memory_to_array(size_t n)
{
    double *arr = (double*)malloc(n * sizeof(double));
    if (!arr)
        return NULL;
    return arr;
}



void input_data_to_matrix(double **matrix, double *data, size_t n, size_t m)
{
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
        {
            matrix[i][j] = data[m * i + j];
        }
    }
}


void generate_data_array(double *arr, size_t n)
{
    for (size_t i = 0; i < n; i++)
        arr[i] = i;
}

int add_memory_for_matrices(double ***matrix_a, double ***matrix_b, double ***matrix_result,
                            size_t n_a, size_t m_a, size_t n_b, size_t m_b)
{
    *matrix_a = add_memory_matrix(n_a, m_a);
    if (!*matrix_a)
    {
        cout << "Error add memory!" << endl;
        return ERROR_ADD_MEM;
    }
    *matrix_b = add_memory_matrix(n_b, m_b);
    if (!*matrix_b)
    {
        cout << "Error add memory!" << endl;
        free_memory_matrix(*matrix_a, n_a);
        return ERROR_ADD_MEM;
    }
    *matrix_result = add_memory_matrix(n_a, m_b);
    if (!*matrix_result)
    {
        cout << "Error add memory!" << endl;
        free_memory_matrix(*matrix_a, n_a);
        free_memory_matrix(*matrix_b, n_b);
        return ERROR_ADD_MEM;
    }
    return OK;
}

int check_sizes(size_t n_a, size_t m_b)
{
    if (n_a != m_b)
    {
        cout << "Invalid input!" << endl;
        return ERROR_INPUT_DATA;
    }
    return OK;
}


int multiply_two_matrix()
{
    int rc;
    size_t n_a, m_a, n_b, m_b;
    double **matrix_a, **matrix_b, **matrix_result;

    cout << "Sizes matrix A:" << endl;
    input_sizes(&n_a, &m_a);
    cout << "Sizes matrix B:" << endl;
    input_sizes(&n_b, &m_b);

    rc = check_sizes(n_a, m_b);
    if (rc != OK)
        return rc;
    rc = add_memory_for_matrices(&matrix_a, &matrix_b, &matrix_result, n_a, m_a, n_b, m_b);
    if (rc != OK)
        return rc;

    cout << "Input elements matrix A:" << endl;
    input_matrix(matrix_a, n_a, m_a);
    cout << "Input elements matrix B:" << endl;
    input_matrix(matrix_b, n_b, m_b);

    cout << "Simple:" << endl;
    simple_multiplication(n_a, m_a, m_b, matrix_a, matrix_b, matrix_result);
    print_matrix(matrix_result, n_a, m_b);

    cout << endl << "Vinograd:" << endl;
    vinograd_algorithm(n_a, m_a, m_b, matrix_a, matrix_b, matrix_result);
    print_matrix(matrix_result, n_a, m_b);

    free_memory_matrix(matrix_a, n_a);
    free_memory_matrix(matrix_b, n_b);
    free_memory_matrix(matrix_result, n_a);

    return OK;
}


void write_result_to_file(const std::string &filename,
                          size_t size,
                          unsigned long long avg_simple,
                          unsigned long long avg_vinograd)
{
    std::ofstream file(filename, std::ios::app);
    if (!file.is_open())
    {
        cout << "Error: cannot open file " << endl;
        return;
    }
    file << size << " " << avg_simple << " " << avg_vinograd << "\n";
    file.close();
}

int time_tests()
{
    int rc;
    double **matrix_a, **matrix_b, **matrix_result, *data;
    unsigned long long start, end, total_simple, total_vinograd;
    const int measurements = 100;
    const string out_file = "results.txt";

    cout << "Matrix Size | Simple (ns) | Vinograd (ns)" << endl;
    cout << "-----------------------------------------" << endl;

    for (size_t i = 1; i < 50; i++)
    {

        rc = add_memory_for_matrices(&matrix_a, &matrix_b, &matrix_result, i, i, i, i);
        if (rc != OK)
        {
            cerr << "Error: Failed to allocate memory for " << i << "x" << i << " matrices" << endl;
            return rc;
        }

        data = add_memory_to_array(i * i);
        if (!data)
        {
            free_memory_matrix(matrix_a, i);
            free_memory_matrix(matrix_b, i);
            free_memory_matrix(matrix_result, i);
            cerr << "Error: Failed to allocate data array for size " << i << "x" << i << endl;
            return ERROR_ADD_MEM;
        }

        generate_data_array(data, i * i);
        input_data_to_matrix(matrix_a, data, i, i);
        input_data_to_matrix(matrix_b, data, i, i);

        for (int j = 0; j < measurements; j++)
        {
            start = __rdtsc();
            simple_multiplication(i, i, i, matrix_a, matrix_b, matrix_result);
            end = __rdtsc();
            total_simple += end - start;

            start = __rdtsc();
            vinograd_algorithm(i, i, i, matrix_a, matrix_b, matrix_result);
            end = __rdtsc();
            total_vinograd += end - start;
        }

        auto avg_simple = total_simple / measurements;
        auto avg_vinograd = total_vinograd / measurements;

        cout << i << "x" << i << " | "
             << avg_simple << " | "
             << avg_vinograd << endl;

        write_result_to_file(out_file, i, avg_simple, avg_vinograd);

        free_memory_matrix(matrix_a, i);
        free_memory_matrix(matrix_b, i);
        free_memory_matrix(matrix_result, i);
        free(data);
    }

    cout << "-----------------------------------------" << endl;
    cout << "Time tests completed successfully" << endl;
    return OK;
}

//1 2 3
//4 5 6
//7 8 9
//1 2 3
//4 5 6
//7 8 9
