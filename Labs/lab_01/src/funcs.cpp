#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <x86intrin.h>
#include <cstdint>
#include <iomanip>
#include <fstream>
#include "input_output.h"
#include "funcs.h"
#include "simple_multiplication.h"
#include "vinograd_algorithm.h"
#include "vinograd_update.h"
#include "errors.h"

using namespace std;


inline uint64_t read_tsc() {
    uint64_t tsc = __rdtsc();
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
    rc = simple_multiplication(n_a, m_a, m_b, matrix_a, matrix_b, matrix_result);
    if (rc != OK)
    {
        free_memory_matrix(matrix_a, n_a);
        free_memory_matrix(matrix_b, n_b);
        free_memory_matrix(matrix_result, n_a);
        cout << "Error multiply!" << endl;
        return rc;
    }
    print_matrix(matrix_result, n_a, m_b);

    cout << endl << "Vinograd:" << endl;
    rc = vinograd_algorithm(n_a, m_a, m_b, matrix_a, matrix_b, matrix_result);
    if (rc != OK)
    {
        free_memory_matrix(matrix_a, n_a);
        free_memory_matrix(matrix_b, n_b);
        free_memory_matrix(matrix_result, n_a);
        cout << "Error multiply!" << endl;
        return rc;
    }
    print_matrix(matrix_result, n_a, m_b);

    cout << endl << "Vinograd Update:" << endl;
    rc = vinograd_algorithm_update(n_a, m_a, m_b, matrix_a, matrix_b, matrix_result);
    if (rc != OK)
    {
        free_memory_matrix(matrix_a, n_a);
        free_memory_matrix(matrix_b, n_b);
        free_memory_matrix(matrix_result, n_a);
        cout << "Error multiply!" << endl;
        return rc;
    }
    print_matrix(matrix_result, n_a, m_b);

    free_memory_matrix(matrix_a, n_a);
    free_memory_matrix(matrix_b, n_b);
    free_memory_matrix(matrix_result, n_a);

    return OK;
}


void write_result_to_file(const string &filename,
                          size_t size,
                          unsigned long long avg_simple,
                          unsigned long long avg_vinograd,
                          unsigned long long avg_vinograd_update)
{
    ofstream file(filename, ios::app);
    if (!file.is_open())
    {
        cout << "Error: cannot open file " << endl;
        return;
    }

    file << size << " "
         << avg_simple << " "
         << avg_vinograd << " "
         << avg_vinograd_update << "\n";
    file.close();
}


int time_tests(size_t cnt_times, size_t measurements, bool verbose)
{
    int rc;
    double **matrix_a, **matrix_b, **matrix_result, *data;
    unsigned long long start, end, total_simple, total_vinograd, total_vinograd_update;
    const string out_file = "results.txt";

    remove(out_file.c_str());
    if (!verbose)
    {
        cout << left
             << setw(12) << "Matrix Size" << "|"
             << setw(15) << "Simple (cycles)" << "|"
             << setw(17) << "Vinograd (cycles)" << "|"
             << setw(22) << "Vinograd update (cycles)" << endl;

        cout << string(12, '-') << "+"
             << string(15, '-') << "+"
             << string(17, '-') << "+"
             << string(22, '-') << endl;
    }

    for (size_t i = 1; i < cnt_times; i += 10)
    {
        rc = add_memory_for_matrices(&matrix_a, &matrix_b, &matrix_result, i, i, i, i);
        if (rc != OK)
        {
            if (!verbose)
                cout << "Error: Failed to allocate memory for " << i << "x" << i << " matrices" << endl;
            return rc;
        }

        data = add_memory_to_array(i * i);
        if (!data)
        {
            free_memory_matrix(matrix_a, i);
            free_memory_matrix(matrix_b, i);
            free_memory_matrix(matrix_result, i);
            if (!verbose)
                cout << "Error: Failed to allocate data array for size " << i << "x" << i << endl;
            return ERROR_ADD_MEM;
        }

        generate_data_array(data, i * i);
        input_data_to_matrix(matrix_a, data, i, i);
        input_data_to_matrix(matrix_b, data, i, i);

        total_simple = total_vinograd = total_vinograd_update = 0;

        for (size_t j = 0; j < measurements; j++)
        {
            start = __rdtsc();
            rc = simple_multiplication(i, i, i, matrix_a, matrix_b, matrix_result);
            if (rc != OK)
            {
                free_memory_matrix(matrix_a, i);
                free_memory_matrix(matrix_b, i);
                free_memory_matrix(matrix_result, i);
                if (!verbose)
                    cout << "Error multiply!" << endl;
                return ERROR;
            }
            end = __rdtsc();
            total_simple += end - start;

            start = __rdtsc();
            rc = vinograd_algorithm(i, i, i, matrix_a, matrix_b, matrix_result);
            if (rc != OK)
            {
                free_memory_matrix(matrix_a, i);
                free_memory_matrix(matrix_b, i);
                free_memory_matrix(matrix_result, i);
                if (!verbose)
                    cout << "Error multiply!" << endl;
                return ERROR;
            }
            end = __rdtsc();
            total_vinograd += end - start;

            start = __rdtsc();
            rc = vinograd_algorithm_update(i, i, i, matrix_a, matrix_b, matrix_result);
            if (rc != OK)
            {
                free_memory_matrix(matrix_a, i);
                free_memory_matrix(matrix_b, i);
                free_memory_matrix(matrix_result, i);
                if (!verbose)
                    cout << "Error multiply!" << endl;
                return ERROR;
            }
            end = __rdtsc();
            total_vinograd_update += end - start;
        }

        auto avg_simple = total_simple / measurements;
        auto avg_vinograd = total_vinograd / measurements;
        auto avg_vinograd_update = total_vinograd_update / measurements;

        if (!verbose)
        {
            cout << left
                 << setw(12) << (to_string(i) + "x" + to_string(i)) << "|"
                 << setw(15) << avg_simple << "|"
                 << setw(17) << avg_vinograd << "|"
                 << setw(22) << avg_vinograd_update << endl;
        }

        write_result_to_file(out_file, i, avg_simple, avg_vinograd, avg_vinograd_update);

        free_memory_matrix(matrix_a, i);
        free_memory_matrix(matrix_b, i);
        free_memory_matrix(matrix_result, i);
        free(data);
    }

    if (!verbose)
    {
        cout << string(12, '-') << "+"
             << string(15, '-') << "+"
             << string(17, '-') << "+"
             << string(22, '-') << endl;

        cout << "Time tests completed successfully" << endl;
    }
    return OK;
}
