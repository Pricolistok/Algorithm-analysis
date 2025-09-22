#ifndef LAB_01_FUNCS_H
#define LAB_01_FUNCS_H


double **add_memory_matrix(size_t n, size_t m);
void free_memory_matrix(double **arr, size_t n);
void input_data_to_matrix(double **matrix, double *data, size_t n, size_t m);
void print_matrix(double **arr, size_t n, size_t m);
double* add_memory_to_array(size_t n);
void generate_data_array(double *arr, size_t n);
int multiply_two_matrix();
int add_memory_for_matrices(double ***matrix_a, double ***matrix_b, double ***matrix_result,
                            size_t n_a, size_t m_a, size_t n_b, size_t m_b);
int time_tests();

#endif
