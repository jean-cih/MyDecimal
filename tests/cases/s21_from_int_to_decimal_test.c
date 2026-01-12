#include "../s21_main_case.h"

START_TEST(result_is_null_id) {
  int value = 36;

  ck_assert_int_eq(s21_from_int_to_decimal(value, NULL), 1);
}
END_TEST

START_TEST(positive_value_id) {
  int value = 36;
  s21_decimal result;

  ck_assert_int_eq(s21_from_int_to_decimal(value, &result), CONVERTATION_OK);
  ck_assert_int_eq(result.bits[0], 36);
}
END_TEST

START_TEST(negative_value_id) {
  int value = -240;
  s21_decimal result;

  ck_assert_int_eq(s21_from_int_to_decimal(value, &result), CONVERTATION_OK);
  ck_assert_int_eq(result.bits[0], 240);
  ck_assert_int_eq(s21_get_sign(result), 1);
}
END_TEST

START_TEST(zero_value_id) {
  int value = 0;
  s21_decimal result;

  ck_assert_int_eq(s21_from_int_to_decimal(value, &result), CONVERTATION_OK);
  ck_assert_int_eq(result.bits[0], 0);
}
END_TEST

START_TEST(max_value_id) {
  int value = INT_MAX;
  s21_decimal result;

  ck_assert_int_eq(s21_from_int_to_decimal(value, &result), CONVERTATION_OK);
  ck_assert_int_eq(result.bits[0], INT_MAX);
}
END_TEST

START_TEST(min_value_id) {
  int value = INT_MIN;
  s21_decimal result;

  ck_assert_int_eq(s21_from_int_to_decimal(value, &result), CONVERTATION_OK);
  ck_assert_int_eq(result.bits[0], (uint32_t)INT_MAX + 1);
  ck_assert_int_eq(s21_get_sign(result), 1);
}
END_TEST
