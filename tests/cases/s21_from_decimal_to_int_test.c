#include "../s21_main_case.h"

START_TEST(result_is_null_di) {
  s21_decimal value = {10, 10, 10, 0};

  ck_assert_int_eq(s21_from_decimal_to_int(value, NULL), 1);
}
END_TEST

START_TEST(positive_value_di) {
  s21_decimal value = {36, 0, 0, 0};
  int result;

  ck_assert_int_eq(s21_from_decimal_to_int(value, &result), CONVERTATION_OK);
  ck_assert_int_eq(result, 36);
}
END_TEST

START_TEST(negative_value_di) {
  s21_decimal value = {36, 0, 0, 0x80000000};
  int result;

  ck_assert_int_eq(s21_from_decimal_to_int(value, &result), CONVERTATION_OK);
  ck_assert_int_eq(result, -36);
}
END_TEST

START_TEST(zero_value_di) {
  s21_decimal value = {0, 0, 0, 0};
  int result;

  ck_assert_int_eq(s21_from_decimal_to_int(value, &result), CONVERTATION_OK);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(value_di) {
  s21_decimal value = {12345, 0, 0, 0x80020000};
  int result;

  ck_assert_int_eq(s21_from_decimal_to_int(value, &result), CONVERTATION_OK);
  ck_assert_int_eq(result, -123);
}
END_TEST

START_TEST(value_is_too_large_di) {
  s21_decimal value = {12345, 10, 10, 0x00020000};
  int result;

  ck_assert_int_eq(s21_from_decimal_to_int(value, &result), CONVERTATION_ERROR);
}
END_TEST

START_TEST(value_is_too_small_di) {
  s21_decimal value = {12345, 10, 10, 0x80020000};
  int result;

  ck_assert_int_eq(s21_from_decimal_to_int(value, &result), CONVERTATION_ERROR);
}
END_TEST

START_TEST(incorrect_value_di) {
  s21_decimal value = {12345, 0, 0, 12345};
  int result;

  ck_assert_int_eq(s21_from_decimal_to_int(value, &result), CALCULATION_ERROR);
}
END_TEST
