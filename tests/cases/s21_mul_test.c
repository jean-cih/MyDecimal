#include "../s21_main_case.h"

START_TEST(result_is_null_m) {
  s21_decimal value_1 = {0, 0, 0, 0};
  s21_decimal value_2 = {0, 0, 0, 0};

  ck_assert_int_eq(s21_mul(value_1, value_2, NULL), 1);
}
END_TEST

START_TEST(both_positive_values_m) {
  s21_decimal value_1 = {3, 0, 0, 0};
  s21_decimal value_2 = {4, 0, 0, 0};
  s21_decimal result;

  ck_assert_int_eq(s21_mul(value_1, value_2, &result), ARR_OK);

  ck_assert_int_eq(result.bits[0], 12);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(both_negative_values_m) {
  s21_decimal value_1 = {15, 0, 0, 0x00010000};
  s21_decimal value_2 = {20, 0, 0, 0x00010000};
  s21_decimal result;

  s21_set_sign(&value_1, 1);
  s21_set_sign(&value_2, 1);

  ck_assert_int_eq(s21_mul(value_1, value_2, &result), ARR_OK);

  ck_assert_int_eq(result.bits[0], 300);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0x00020000);
}
END_TEST

START_TEST(first_positive_value_m) {
  s21_decimal value_1 = {23, 12, 0, 0};
  s21_decimal value_2 = {34, 12, 0, 0};
  s21_decimal result;

  s21_set_sign(&value_2, 1);

  ck_assert_int_eq(s21_mul(value_1, value_2, &result), ARR_OK);

  ck_assert_int_eq(result.bits[0], 782);
  ck_assert_int_eq(result.bits[1], 684);
  ck_assert_int_eq(result.bits[2], 144);
  ck_assert_int_eq(result.bits[3], 0x80000000);
}
END_TEST

START_TEST(first_negative_value_m) {
  s21_decimal value_1 = {23, 12, 0, 0};
  s21_decimal value_2 = {34, 12, 0, 0};
  s21_decimal result;

  s21_set_sign(&value_1, 1);

  ck_assert_int_eq(s21_mul(value_1, value_2, &result), ARR_OK);

  ck_assert_int_eq(result.bits[0], 782);
  ck_assert_int_eq(result.bits[1], 684);
  ck_assert_int_eq(result.bits[2], 144);
  ck_assert_int_eq(result.bits[3], 0x80000000);
}
END_TEST

START_TEST(result_is_too_large_m) {
  s21_decimal value_1 = {UINT_MAX, UINT_MAX, UINT_MAX, 0};
  s21_decimal value_2 = {UINT_MAX, UINT_MAX, UINT_MAX, 0};
  s21_decimal result;

  ck_assert_int_eq(s21_mul(value_1, value_2, &result), ARR_TOO_LARGE);
}
END_TEST

START_TEST(result_is_too_small_m) {
  s21_decimal value_1 = {UINT_MAX, UINT_MAX, UINT_MAX, 0};
  s21_decimal value_2 = {UINT_MAX, UINT_MAX, UINT_MAX, 0};
  s21_decimal result;

  s21_set_sign(&value_1, 1);

  ck_assert_int_eq(s21_mul(value_1, value_2, &result), ARR_TOO_SMALL);
}
END_TEST
