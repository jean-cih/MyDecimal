#include "../s21_main_case.h"

START_TEST(result_is_null_d) {
  s21_decimal value_1 = {0, 0, 0, 0};
  s21_decimal value_2 = {0, 0, 0, 0};

  ck_assert_int_eq(s21_div(value_1, value_2, NULL), 1);
}
END_TEST

START_TEST(both_positive_values_d) {
  s21_decimal value_1 = {10, 10, 10, 0};
  s21_decimal value_2 = {1, 2, 0, 0};
  s21_decimal result;

  ck_assert_int_eq(s21_div(value_1, value_2, &result), ARR_OK);
}
END_TEST

START_TEST(both_negative_values_d) {
  s21_decimal value_1 = {100, 100, 100, 0};
  s21_decimal value_2 = {10, 34, 23, 0};
  s21_decimal result;

  s21_set_sign(&value_1, 1);
  s21_set_sign(&value_2, 1);

  ck_assert_int_eq(s21_div(value_1, value_2, &result), ARR_OK);
}
END_TEST

START_TEST(first_positive_value_d) {
  s21_decimal value_1 = {1000, 1000, 1000, 0};
  s21_decimal value_2 = {112, 112312, 11, 0};
  s21_decimal result;

  s21_set_sign(&value_2, 1);

  ck_assert_int_eq(s21_div(value_1, value_2, &result), ARR_OK);
}
END_TEST

START_TEST(first_negative_value_d) {
  s21_decimal value_1 = {10000, 10000, 10000, 0};
  s21_decimal value_2 = {100123, 30, 2, 0};
  s21_decimal result;

  s21_set_sign(&value_1, 1);

  ck_assert_int_eq(s21_div(value_1, value_2, &result), ARR_OK);
}
END_TEST

START_TEST(result_is_too_large_d) {
  s21_decimal value_1 = {UINT_MAX, UINT_MAX, UINT_MAX, 0};
  s21_decimal value_2 = {1, 0, 0, 0x1C0000};
  s21_decimal result;

  ck_assert_int_eq(s21_div(value_1, value_2, &result), ARR_TOO_LARGE);
}
END_TEST

START_TEST(result_is_too_small_d) {
  s21_decimal value_1 = {UINT_MAX, UINT_MAX, UINT_MAX, 0};
  s21_decimal value_2 = {1, 0, 0, 0x1C0000};
  s21_decimal result;

  s21_set_sign(&value_1, 1);

  ck_assert_int_eq(s21_div(value_1, value_2, &result), ARR_TOO_SMALL);
}
END_TEST

START_TEST(division_by_zero_d) {
  s21_decimal value_1 = {10000, 10000, 10000, 0};
  s21_decimal value_2 = {0, 0, 0, 0};
  s21_decimal result;

  ck_assert_int_eq(s21_div(value_1, value_2, &result), ARR_DIVISION_BY_ZERO);
}
END_TEST
