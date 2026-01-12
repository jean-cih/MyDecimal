#include "../s21_main_case.h"

START_TEST(result_is_null_n) {
  s21_decimal value = {0, 0, 0, 0};

  ck_assert_int_eq(s21_negate(value, NULL), CALCULATION_ERROR);
}
END_TEST

START_TEST(positive_value_n) {
  s21_decimal value = {12345, 0, 0, 0};
  s21_decimal result;

  ck_assert_int_eq(s21_negate(value, &result), OTH_OK);
  ck_assert_int_eq(s21_get_sign(result), 1);
}
END_TEST

START_TEST(negative_value_n) {
  s21_decimal value = {67890, 0, 0, 0x80020000};
  s21_decimal result;

  ck_assert_int_eq(s21_negate(value, &result), OTH_OK);
  ck_assert_int_eq(s21_get_sign(result), 0);
}
END_TEST
