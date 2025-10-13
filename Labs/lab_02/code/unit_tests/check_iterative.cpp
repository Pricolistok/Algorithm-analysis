#include "errors.h"
#include "funcs.h"
#include <check.h>

START_TEST(test_iterative_empty_sequence) {
  std::vector<int> sequence = {};
  std::vector<int> expected = {};
  std::vector<int> result;

  iterative_algorithm_to_array(sequence, result);
  ck_assert_uint_eq(result.size(), expected.size());
}
END_TEST

START_TEST(test_iterative_single_element) {
  std::vector<int> sequence = {42};
  std::vector<int> expected = {42};
  std::vector<int> result;

  iterative_algorithm_to_array(sequence, result);
  ck_assert_uint_eq(result.size(), expected.size());
  ck_assert_int_eq(result[0], expected[0]);
}
END_TEST

START_TEST(test_iterative_two_elements) {
  std::vector<int> sequence = {10, 20};
  std::vector<int> expected = {10};
  std::vector<int> result;

  iterative_algorithm_to_array(sequence, result);
  ck_assert_uint_eq(result.size(), expected.size());
  ck_assert_int_eq(result[0], expected[0]);
}
END_TEST

START_TEST(test_iterative_three_elements) {
  std::vector<int> sequence = {1, 2, 3};
  std::vector<int> expected = {1, 3};
  std::vector<int> result;

  iterative_algorithm_to_array(sequence, result);
  ck_assert_uint_eq(result.size(), expected.size());
  ck_assert_int_eq(result[0], expected[0]);
  ck_assert_int_eq(result[1], expected[1]);
}
END_TEST

START_TEST(test_iterative_five_elements) {
  std::vector<int> sequence = {1, 2, 3, 4, 5};
  std::vector<int> expected = {1, 3, 5};
  std::vector<int> result;

  iterative_algorithm_to_array(sequence, result);
  ck_assert_uint_eq(result.size(), expected.size());

  for (size_t i = 0; i < expected.size(); i++) {
    ck_assert_int_eq(result[i], expected[i]);
  }
}
END_TEST

START_TEST(test_iterative_ten_elements) {
  std::vector<int> sequence = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::vector<int> expected = {1, 3, 5, 7, 9};
  std::vector<int> result;

  iterative_algorithm_to_array(sequence, result);
  ck_assert_uint_eq(result.size(), expected.size());

  for (size_t i = 0; i < expected.size(); i++) {
    ck_assert_int_eq(result[i], expected[i]);
  }
}
END_TEST

START_TEST(test_iterative_with_negatives) {
  std::vector<int> sequence = {-1, -2, -3, -4, -5};
  std::vector<int> expected = {-1, -3, -5};
  std::vector<int> result;

  iterative_algorithm_to_array(sequence, result);
  ck_assert_uint_eq(result.size(), expected.size());

  for (size_t i = 0; i < expected.size(); i++) {
    ck_assert_int_eq(result[i], expected[i]);
  }
}
END_TEST

START_TEST(test_iterative_mixed_numbers) {
  std::vector<int> sequence = {100, -50, 25, -10, 0, 77};
  std::vector<int> expected = {100, 25, 0};
  std::vector<int> result;

  iterative_algorithm_to_array(sequence, result);
  ck_assert_uint_eq(result.size(), expected.size());

  for (size_t i = 0; i < expected.size(); i++) {
    ck_assert_int_eq(result[i], expected[i]);
  }
}
END_TEST

Suite *iterative_suite(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("iterative algorithm");
  tc = tcase_create("iterative tests");

  tcase_add_test(tc, test_iterative_empty_sequence);
  tcase_add_test(tc, test_iterative_single_element);
  tcase_add_test(tc, test_iterative_two_elements);
  tcase_add_test(tc, test_iterative_three_elements);
  tcase_add_test(tc, test_iterative_five_elements);
  tcase_add_test(tc, test_iterative_ten_elements);
  tcase_add_test(tc, test_iterative_with_negatives);
  tcase_add_test(tc, test_iterative_mixed_numbers);

  suite_add_tcase(s, tc);
  return s;
}