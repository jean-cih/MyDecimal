#include "../s21_main_case.h"

START_TEST(result_is_null_df) {
  s21_decimal value = {10, 10, 10, 0};

  ck_assert_int_eq(s21_from_decimal_to_float(value, NULL), 1);
}
END_TEST

START_TEST(positive_value_df) {
  s21_decimal value = {1234567, 0, 0, 0};
  float result;

  ck_assert_int_eq(s21_from_decimal_to_float(value, &result), CONVERTATION_OK);
  ck_assert_float_eq(result, 1234567.0f);
}
END_TEST

START_TEST(negative_value_df) {
  s21_decimal value = {1234567, 0, 0, 0x80000000};
  float result;

  ck_assert_int_eq(s21_from_decimal_to_float(value, &result), CONVERTATION_OK);
  ck_assert_float_eq(result, -1234567.0f);
}
END_TEST

START_TEST(zero_value_df) {
  s21_decimal value = {0, 0, 0, 0};
  float result;

  ck_assert_int_eq(s21_from_decimal_to_float(value, &result), CONVERTATION_OK);
  ck_assert_float_eq(result, 0);
}
END_TEST

START_TEST(value_df) {
  s21_decimal value = {12345, 0, 0, 0x80020000};
  float result;

  ck_assert_int_eq(s21_from_decimal_to_float(value, &result), CONVERTATION_OK);
  ck_assert_float_eq(result, -123.45f);
}
END_TEST
