#include <stdlib.h>
#include <iostream>
#include <check.h>
#include "errors.h"
#include "funcs.h"
#include "funcs_for_units.h"
#include "vinograd_algorithm.h"
#include "input_output.h"

using namespace std;

START_TEST(test_vinograd_algorithm_multiplication_with_simple_matrix)
{
    int rc;
    double data_a[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
    double data_b[] = { 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
    double data_check[] = {60, 50, 40, 180, 154, 128, 300, 258, 216};
    size_t n_a = 3, m_a = 4, n_b = 4, m_b = 3;
    double **matrix_a, **matrix_b;
    double **matrix_result;
    double **matrix_check = nullptr;

    rc = add_memory_for_matrices(&matrix_a, &matrix_b, &matrix_result, n_a, m_a, n_b, m_b);
    ck_assert_int_eq(rc, OK);
    matrix_check = add_memory_matrix(n_a, m_b);
    ck_assert_ptr_nonnull(matrix_check);

    input_data_to_matrix(matrix_a, data_a, n_a, m_a);
    input_data_to_matrix(matrix_b, data_b, n_b, m_b);
    input_data_to_matrix(matrix_check, data_check, n_a, m_b);

    rc = vinograd_algorithm(n_a, m_a, m_b, matrix_a, matrix_b, matrix_result);
    ck_assert_int_eq(rc, OK);

    rc = check_matrix(n_a, m_b, n_a, m_b, matrix_result, matrix_check);
    ck_assert_int_eq(rc, OK);

    free_memory_matrix(matrix_a, n_a);
    free_memory_matrix(matrix_b, n_b);
    free_memory_matrix(matrix_result, n_a);
    free_memory_matrix(matrix_check, n_a);
}
END_TEST

START_TEST(test_vinograd_algorithm_multiplication_with_simple_matrix_with_negatives)
{
    int rc;
    double data_a[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9};
    double data_b[] = {9, 8, 7, 6, 5, 4, 3, 2, 1 };
    double data_check[] = {30, 24, 18, 84, 69, 54, 138, 114, 90};
    size_t n_a = 3, m_a = 3, n_b = 3, m_b = 3;
    double **matrix_a, **matrix_b;
    double **matrix_result;
    double **matrix_check = nullptr;

    rc = add_memory_for_matrices(&matrix_a, &matrix_b, &matrix_result, n_a, m_a, n_b, m_b);
    ck_assert_int_eq(rc, OK);
    matrix_check = add_memory_matrix(n_a, m_b);
    ck_assert_ptr_nonnull(matrix_check);

    input_data_to_matrix(matrix_a, data_a, n_a, m_a);
    input_data_to_matrix(matrix_b, data_b, n_b, m_b);
    input_data_to_matrix(matrix_check, data_check, n_a, m_b);

    rc = vinograd_algorithm(n_a, m_a, m_b, matrix_a, matrix_b, matrix_result);
    ck_assert_int_eq(rc, OK);

    rc = check_matrix(n_a, m_b, n_a, m_b, matrix_result, matrix_check);
    ck_assert_int_eq(rc, OK);

    free_memory_matrix(matrix_a, n_a);
    free_memory_matrix(matrix_b, n_b);
    free_memory_matrix(matrix_result, n_a);
    free_memory_matrix(matrix_check, n_a);
}
END_TEST

START_TEST(test_vinograd_algorithm_multiplication_with_simple_matrix_with_all_negatives)
{
    int rc;
    double data_a[] = { -1, -2, -3, -4, -5, -6, -7, -8, -9, -10, -11, -12 };
    double data_b[] = { -12, -11, -10, -9, -8, -7, -6, -5, -4, -3, -2, -1 };
    double data_check[] = {60, 50, 40, 180, 154, 128, 300, 258, 216};
    size_t n_a = 3, m_a = 4, n_b = 4, m_b = 3;
    double **matrix_a, **matrix_b;
    double **matrix_result;
    double **matrix_check = nullptr;

    rc = add_memory_for_matrices(&matrix_a, &matrix_b, &matrix_result, n_a, m_a, n_b, m_b);
    ck_assert_int_eq(rc, OK);
    matrix_check = add_memory_matrix(n_a, m_b);
    ck_assert_ptr_nonnull(matrix_check);

    input_data_to_matrix(matrix_a, data_a, n_a, m_a);
    input_data_to_matrix(matrix_b, data_b, n_b, m_b);
    input_data_to_matrix(matrix_check, data_check, n_a, m_b);

    rc = vinograd_algorithm(n_a, m_a, m_b, matrix_a, matrix_b, matrix_result);
    ck_assert_int_eq(rc, OK);

    rc = check_matrix(n_a, m_b, n_a, m_b, matrix_result, matrix_check);
    ck_assert_int_eq(rc, OK);

    free_memory_matrix(matrix_a, n_a);
    free_memory_matrix(matrix_b, n_b);
    free_memory_matrix(matrix_result, n_a);
    free_memory_matrix(matrix_check, n_a);
}
END_TEST


START_TEST(test_vinograd_algorithm_multiplication_with_sq_matrix)
{
    int rc;
    double data_a[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    double data_b[] = { 9, 8, 7, 6, 5, 4, 3, 2, 1 };
    double data_check[] = {30, 24, 18, 84, 69, 54, 138, 114, 90};
    size_t n_a = 3, m_a = 3, n_b = 3, m_b = 3;
    double **matrix_a, **matrix_b;
    double **matrix_result;
    double **matrix_check = nullptr;

    rc = add_memory_for_matrices(&matrix_a, &matrix_b, &matrix_result, n_a, m_a, n_b, m_b);
    ck_assert_int_eq(rc, OK);
    matrix_check = add_memory_matrix(n_a, m_b);
    ck_assert_ptr_nonnull(matrix_check);

    input_data_to_matrix(matrix_a, data_a, n_a, m_a);
    input_data_to_matrix(matrix_b, data_b, n_b, m_b);
    input_data_to_matrix(matrix_check, data_check, n_a, m_b);

    rc = vinograd_algorithm(n_a, m_a, m_b, matrix_a, matrix_b, matrix_result);
    ck_assert_int_eq(rc, OK);

    rc = check_matrix(n_a, m_b, n_a, m_b, matrix_result, matrix_check);
    ck_assert_int_eq(rc, OK);

    free_memory_matrix(matrix_a, n_a);
    free_memory_matrix(matrix_b, n_b);
    free_memory_matrix(matrix_result, n_a);
    free_memory_matrix(matrix_check, n_a);
}
END_TEST


START_TEST(test_vinograd_algorithm_multiplication_with_zero_matrix)
{
    int rc;
    double data_a[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    double data_b[] = { 9, 8, 7, 6, 5, 4, 3, 2, 1 };
    double data_check[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    size_t n_a = 3, m_a = 3, n_b = 3, m_b = 3;
    double **matrix_a, **matrix_b;
    double **matrix_result;
    double **matrix_check = nullptr;

    rc = add_memory_for_matrices(&matrix_a, &matrix_b, &matrix_result, n_a, m_a, n_b, m_b);
    ck_assert_int_eq(rc, OK);
    matrix_check = add_memory_matrix(n_a, m_b);
    ck_assert_ptr_nonnull(matrix_check);

    input_data_to_matrix(matrix_a, data_a, n_a, m_a);
    input_data_to_matrix(matrix_b, data_b, n_b, m_b);
    input_data_to_matrix(matrix_check, data_check, n_a, m_b);

    rc = vinograd_algorithm(n_a, m_a, m_b, matrix_a, matrix_b, matrix_result);
    ck_assert_int_eq(rc, OK);

    rc = check_matrix(n_a, m_b, n_a, m_b, matrix_result, matrix_check);
    ck_assert_int_eq(rc, OK);

    free_memory_matrix(matrix_a, n_a);
    free_memory_matrix(matrix_b, n_b);
    free_memory_matrix(matrix_result, n_a);
    free_memory_matrix(matrix_check, n_a);
}
END_TEST

START_TEST(test_vinograd_algorithm_multiplication_with_identity_matrix)
{
    int rc;
    double data_a[] = { 1, 0, 0, 0, 1, 0, 0, 0, 1};
    double data_b[] = { 9, 8, 7, 6, 5, 4, 3, 2, 1 };
    double data_check[] = { 9, 8, 7, 6, 5, 4, 3, 2, 1 };
    size_t n_a = 3, m_a = 3, n_b = 3, m_b = 3;
    double **matrix_a, **matrix_b;
    double **matrix_result;
    double **matrix_check = nullptr;

    rc = add_memory_for_matrices(&matrix_a, &matrix_b, &matrix_result, n_a, m_a, n_b, m_b);
    ck_assert_int_eq(rc, OK);
    matrix_check = add_memory_matrix(n_a, m_b);
    ck_assert_ptr_nonnull(matrix_check);

    input_data_to_matrix(matrix_a, data_a, n_a, m_a);
    input_data_to_matrix(matrix_b, data_b, n_b, m_b);
    input_data_to_matrix(matrix_check, data_check, n_a, m_b);

    rc = vinograd_algorithm(n_a, m_a, m_b, matrix_a, matrix_b, matrix_result);
    ck_assert_int_eq(rc, OK);

    rc = check_matrix(n_a, m_b, n_a, m_b, matrix_result, matrix_check);
    ck_assert_int_eq(rc, OK);

    free_memory_matrix(matrix_a, n_a);
    free_memory_matrix(matrix_b, n_b);
    free_memory_matrix(matrix_result, n_a);
    free_memory_matrix(matrix_check, n_a);
}
END_TEST


Suite* vinograd(void)
{
    Suite *s;
    TCase *tc;

    s = suite_create("vinograd algorithm multiplication matrix");

    tc = tcase_create("test");

    tcase_add_test(tc, test_vinograd_algorithm_multiplication_with_simple_matrix);
    tcase_add_test(tc, test_vinograd_algorithm_multiplication_with_simple_matrix_with_negatives);
    tcase_add_test(tc, test_vinograd_algorithm_multiplication_with_simple_matrix_with_all_negatives);
    tcase_add_test(tc, test_vinograd_algorithm_multiplication_with_sq_matrix);
    tcase_add_test(tc, test_vinograd_algorithm_multiplication_with_zero_matrix);
    tcase_add_test(tc, test_vinograd_algorithm_multiplication_with_identity_matrix);

    suite_add_tcase(s, tc);

    return s;
}
