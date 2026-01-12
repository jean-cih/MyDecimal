#include "../s21_main_case.h"

START_TEST(result_is_null_fd) {
  float value = 12.0f;

  ck_assert_int_eq(s21_from_float_to_decimal(value, NULL), 1);
}
END_TEST

START_TEST(positive_value_fd) {
  float value = 12345.023f;
  s21_decimal result;

  ck_assert_int_eq(s21_from_float_to_decimal(value, &result), CONVERTATION_OK);
  ck_assert_int_eq(result.bits[0], 12345023);
  ck_assert_int_eq(s21_get_scale(result), 3);
}
END_TEST

START_TEST(negative_value_fd) {
  float value = -12345.023f;
  s21_decimal result;

  ck_assert_int_eq(s21_from_float_to_decimal(value, &result), CONVERTATION_OK);
  ck_assert_int_eq(result.bits[0], 12345023);
  ck_assert_int_eq(s21_get_scale(result), 3);
  ck_assert_int_eq(s21_get_sign(result), 1);
}
END_TEST

START_TEST(zero_value_fd) {
  float value = 0.0f;
  s21_decimal result;

  ck_assert_int_eq(s21_from_float_to_decimal(value, &result), CONVERTATION_OK);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(s21_get_scale(result), 0);
}
END_TEST

START_TEST(max_value_fd) {
  float value = FLT_MAX;
  s21_decimal result;

  ck_assert_int_eq(s21_from_float_to_decimal(value, &result),
                   CONVERTATION_ERROR);
}
END_TEST

START_TEST(min_value_fd) {
  float value = FLT_MIN;
  s21_decimal result;

  ck_assert_int_eq(s21_from_float_to_decimal(value, &result),
                   CONVERTATION_ERROR);
}
END_TEST
