#include "../s21_main_case.h"

START_TEST(result_is_null_r) {
  s21_decimal value = {0, 0, 0, 0};

  ck_assert_int_eq(s21_round(value, NULL), CALCULATION_ERROR);
}
END_TEST

START_TEST(incorrect_value_r) {
  s21_decimal value = {12345, 0, 0, 12345};
  s21_decimal result;

  ck_assert_int_eq(s21_round(value, &result), CALCULATION_ERROR);
}
END_TEST

START_TEST(int_value_r) {
  s21_decimal value = {12345, 0, 0, 0};
  s21_decimal result;

  ck_assert_int_eq(s21_round(value, &result), OTH_OK);
  ck_assert_int_eq(result.bits[0], 12345);
}
END_TEST

START_TEST(negative_value_r) {
  s21_decimal value = {67890, 0, 0, 0x80020000};
  s21_decimal result;

  ck_assert_int_eq(s21_round(value, &result), OTH_OK);
  ck_assert_int_eq(result.bits[0], 679);
  ck_assert_int_eq(s21_get_sign(result), 1);
}
END_TEST

START_TEST(value_r) {
  s21_decimal value = {12345, 0, 0, 0x00020000};
  s21_decimal result;

  ck_assert_int_eq(s21_round(value, &result), OTH_OK);
  ck_assert_int_eq(result.bits[0], 123);
}
END_TEST

START_TEST(not_even_value_r) {
  s21_decimal value = {111111, 1111, 0, 0x00020000};
  s21_decimal result;

  ck_assert_int_eq(s21_round(value, &result), OTH_OK);
}
END_TEST
