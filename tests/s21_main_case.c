#include "s21_main_case.h"

#include <check.h>
#include <stdlib.h>
#include <unistd.h>

#include "cases/s21_add_test.c"
#include "cases/s21_div_test.c"
#include "cases/s21_floor_test.c"
#include "cases/s21_from_decimal_to_float_test.c"
#include "cases/s21_from_decimal_to_int_test.c"
#include "cases/s21_from_float_to_decimal_test.c"
#include "cases/s21_from_int_to_decimal_test.c"
#include "cases/s21_is_equal_test.c"
#include "cases/s21_is_greater_or_equal_test.c"
#include "cases/s21_is_greater_test.c"
#include "cases/s21_is_less_or_equal_test.c"
#include "cases/s21_is_less_test.c"
#include "cases/s21_is_not_equal_test.c"
#include "cases/s21_mul_test.c"
#include "cases/s21_negate_test.c"
#include "cases/s21_round_test.c"
#include "cases/s21_sub_test.c"
#include "cases/s21_truncate_test.c"

Suite *suite(void) {
  Suite *s;
  TCase *arr_add, *arr_sub, *arr_mul, *arr_div, *com_l, *com_le, *com_g,
      *com_ge, *com_e, *com_ne, *con_id, *con_fd, *con_di, *con_df, *oth_f,
      *oth_r, *oth_t, *oth_n;

  s = suite_create("s21_decimal");

  int t = 100000;

  printf("\n === Unit-Test ===\n\n");

  // Tests for arithmetics
  printf("\n == Running tests for arithmetics module ==\n");
  usleep(t);

  printf("Test: Add\n");
  arr_add = tcase_create("s21_addition");
  tcase_add_test(arr_add, result_is_null_a);
  tcase_add_test(arr_add, both_positive_values_a);
  tcase_add_test(arr_add, both_negative_values_a);
  tcase_add_test(arr_add, first_positive_value_a);
  tcase_add_test(arr_add, first_negative_value_a);
  tcase_add_test(arr_add, result_is_too_large_a);
  tcase_add_test(arr_add, result_is_too_small_a);
  tcase_add_test(arr_add, full_result_a);
  tcase_add_test(arr_add, usual_result_a);
  suite_add_tcase(s, arr_add);
  usleep(t);

  printf("Test: Sub\n");
  arr_sub = tcase_create("s21_subtraction");
  tcase_add_test(arr_sub, result_is_null_s);
  tcase_add_test(arr_sub, both_positive_values_s);
  tcase_add_test(arr_sub, both_negative_values_s);
  tcase_add_test(arr_sub, first_positive_value_s);
  tcase_add_test(arr_sub, first_negative_value_s);
  tcase_add_test(arr_sub, result_is_too_large_s);
  tcase_add_test(arr_sub, result_is_too_small_s);
  tcase_add_test(arr_sub, first_is_greater);
  tcase_add_test(arr_sub, second_is_greater);
  suite_add_tcase(s, arr_sub);
  usleep(t);

  printf("Test: Mul\n");
  arr_mul = tcase_create("s21_multiplication");
  tcase_add_test(arr_mul, result_is_null_m);
  tcase_add_test(arr_mul, both_positive_values_m);
  tcase_add_test(arr_mul, both_negative_values_m);
  tcase_add_test(arr_mul, first_positive_value_m);
  tcase_add_test(arr_mul, first_negative_value_m);
  tcase_add_test(arr_mul, result_is_too_large_m);
  tcase_add_test(arr_mul, result_is_too_small_m);
  suite_add_tcase(s, arr_mul);
  usleep(t);

  printf("Test: Div\n");
  arr_div = tcase_create("s21_division");
  tcase_add_test(arr_div, result_is_null_d);
  tcase_add_test(arr_div, both_positive_values_d);
  tcase_add_test(arr_div, both_negative_values_d);
  tcase_add_test(arr_div, first_positive_value_d);
  tcase_add_test(arr_div, first_negative_value_d);
  tcase_add_test(arr_div, result_is_too_large_d);
  tcase_add_test(arr_div, result_is_too_small_d);
  tcase_add_test(arr_div, division_by_zero_d);
  suite_add_tcase(s, arr_div);
  usleep(t);

  // Tests for comparisons
  printf("\n == Running tests for comparisons module ==\n");
  usleep(t);

  printf("Test: Is_Less\n");
  com_l = tcase_create("s21_is_less");
  tcase_add_test(com_l, both_equal_zero_l);
  tcase_add_test(com_l, different_signs_one_l);
  tcase_add_test(com_l, different_signs_two_l);
  tcase_add_test(com_l, different_values_one_l);
  tcase_add_test(com_l, different_values_two_l);
  tcase_add_test(com_l, equal_values_l);
  suite_add_tcase(s, com_l);
  usleep(t);

  printf("Test: Is_Less_Or_Equal\n");
  com_le = tcase_create("s21_is_less_or_equal");
  tcase_add_test(com_l, both_equal_zero_le);
  tcase_add_test(com_l, different_signs_one_le);
  tcase_add_test(com_l, different_signs_two_le);
  tcase_add_test(com_l, different_values_one_le);
  tcase_add_test(com_l, different_values_two_le);
  tcase_add_test(com_l, equal_values_l);
  suite_add_tcase(s, com_le);
  usleep(t);

  printf("Test: Is_Greater\n");
  com_g = tcase_create("s21_is_greater");
  tcase_add_test(com_g, both_equal_zero_g);
  tcase_add_test(com_g, different_signs_one_g);
  tcase_add_test(com_g, different_signs_two_g);
  tcase_add_test(com_g, different_values_one_g);
  tcase_add_test(com_g, different_values_two_g);
  tcase_add_test(com_g, equal_values_g);
  suite_add_tcase(s, com_g);
  usleep(t);

  printf("Test: Is_Greater_Or_Equal\n");
  com_ge = tcase_create("s21_is_greater_or_equal");
  tcase_add_test(com_g, both_equal_zero_ge);
  tcase_add_test(com_g, different_signs_one_ge);
  tcase_add_test(com_g, different_signs_two_ge);
  tcase_add_test(com_g, different_values_one_ge);
  tcase_add_test(com_g, different_values_two_ge);
  tcase_add_test(com_g, equal_values_ge);
  suite_add_tcase(s, com_ge);
  usleep(t);

  printf("Test: Is_Equal\n");
  com_e = tcase_create("s21_is_equal");
  tcase_add_test(com_e, both_equal_zero_e);
  tcase_add_test(com_e, different_signs_e);
  tcase_add_test(com_e, different_values_e);
  tcase_add_test(com_e, equal_values_e);
  tcase_add_test(com_e, usual_values_e);
  suite_add_tcase(s, com_e);
  usleep(t);

  printf("Test: Is_Not_Equal\n");
  com_ne = tcase_create("s21_is_not_equal");
  tcase_add_test(com_ne, both_equal_zero_ne);
  tcase_add_test(com_ne, different_signs_ne);
  tcase_add_test(com_ne, different_values_ne);
  tcase_add_test(com_ne, equal_values_ne);
  suite_add_tcase(s, com_ne);
  usleep(t);

  // Tests for converters
  printf("\n == Running tests for converters module ==\n");
  usleep(t);

  printf("Test: From_Int_To_Decimal\n");
  con_id = tcase_create("s21_from_int_to_decimal");
  tcase_add_test(con_id, result_is_null_id);
  tcase_add_test(con_id, positive_value_id);
  tcase_add_test(con_id, negative_value_id);
  tcase_add_test(con_id, zero_value_id);
  tcase_add_test(con_id, max_value_id);
  tcase_add_test(con_id, min_value_id);
  suite_add_tcase(s, con_id);
  usleep(t);

  printf("Test: From_Float_To_Decimal\n");
  con_fd = tcase_create("s21_from_float_to_decimal");
  tcase_add_test(con_fd, result_is_null_fd);
  tcase_add_test(con_fd, positive_value_fd);
  tcase_add_test(con_fd, negative_value_fd);
  tcase_add_test(con_fd, zero_value_fd);
  tcase_add_test(con_fd, max_value_fd);
  tcase_add_test(con_fd, min_value_fd);
  suite_add_tcase(s, con_fd);
  usleep(t);

  printf("Test: From_Decimal_To_int\n");
  con_di = tcase_create("s21_from_decimal_to_int");
  tcase_add_test(con_di, result_is_null_di);
  tcase_add_test(con_di, positive_value_di);
  tcase_add_test(con_di, negative_value_di);
  tcase_add_test(con_di, zero_value_di);
  tcase_add_test(con_di, value_di);
  tcase_add_test(con_di, value_is_too_large_di);
  tcase_add_test(con_di, value_is_too_small_di);
  tcase_add_test(con_di, incorrect_value_di);
  suite_add_tcase(s, con_di);
  usleep(t);

  printf("Test: From_Decimal_To_Float\n");
  con_df = tcase_create("s21_from_decimal_to_float");
  tcase_add_test(con_df, result_is_null_df);
  tcase_add_test(con_df, positive_value_df);
  tcase_add_test(con_df, negative_value_df);
  tcase_add_test(con_df, zero_value_df);
  tcase_add_test(con_df, value_df);
  suite_add_tcase(s, con_df);
  usleep(t);

  // Tests for other
  printf("\n == Running tests for other module ==\n");
  usleep(t);

  printf("Test: Floor\n");
  oth_f = tcase_create("s21_floor");
  tcase_add_test(oth_f, result_is_null_f);
  tcase_add_test(oth_f, incorrect_value_f);
  tcase_add_test(oth_f, int_value_f);
  tcase_add_test(oth_f, negative_value_f);
  tcase_add_test(oth_f, value_f);
  suite_add_tcase(s, oth_f);
  usleep(t);

  printf("Test: Round\n");
  oth_r = tcase_create("s21_round");
  tcase_add_test(oth_r, result_is_null_r);
  tcase_add_test(oth_r, incorrect_value_r);
  tcase_add_test(oth_r, int_value_r);
  tcase_add_test(oth_r, negative_value_r);
  tcase_add_test(oth_r, value_r);
  tcase_add_test(oth_r, not_even_value_r);
  suite_add_tcase(s, oth_r);
  usleep(t);

  printf("Test: Truncate\n");
  oth_t = tcase_create("s21_truncate");
  tcase_add_test(oth_t, result_is_null_t);
  tcase_add_test(oth_t, incorrect_value_t);
  tcase_add_test(oth_t, int_value_t);
  tcase_add_test(oth_t, negative_value_t);
  tcase_add_test(oth_t, value_t);
  suite_add_tcase(s, oth_t);
  usleep(t);

  printf("Test: Negate\n");
  oth_n = tcase_create("s21_negate");
  tcase_add_test(oth_n, result_is_null_n);
  tcase_add_test(oth_n, positive_value_n);
  tcase_add_test(oth_n, negative_value_n);
  suite_add_tcase(s, oth_n);
  usleep(t);

  return s;
}

int main(void) {
  int number_failed;
  Suite *s = suite();
  SRunner *sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
