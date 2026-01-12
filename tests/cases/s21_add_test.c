#include "../s21_main_case.h"

START_TEST(result_is_null_a) {
  s21_decimal value_1 = {0, 0, 0, 0};
  s21_decimal value_2 = {0, 0, 0, 0};

  ck_assert_int_eq(s21_add(value_1, value_2, NULL), 1);
}
END_TEST

START_TEST(both_positive_values_a) {
  s21_decimal value_1 = {10, 10, 10, 0};
  s21_decimal value_2 = {10, 10, 10, 0};
  s21_decimal result;

  ck_assert_int_eq(s21_add(value_1, value_2, &result), ARR_OK);

  ck_assert_int_eq(result.bits[0], 20);
  ck_assert_int_eq(result.bits[1], 20);
  ck_assert_int_eq(result.bits[2], 20);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(both_negative_values_a) {
  s21_decimal value_1 = {100, 100, 100, 0};
  s21_decimal value_2 = {100, 100, 100, 0};
  s21_decimal result;

  s21_set_sign(&value_1, 1);
  s21_set_sign(&value_2, 1);

  ck_assert_int_eq(s21_add(value_1, value_2, &result), ARR_OK);

  ck_assert_int_eq(result.bits[0], 200);
  ck_assert_int_eq(result.bits[1], 200);
  ck_assert_int_eq(result.bits[2], 200);
  ck_assert_int_eq(result.bits[3], 0x80000000);
}
END_TEST

START_TEST(first_positive_value_a) {
  s21_decimal value_1 = {1000, 1000, 1000, 0};
  s21_decimal value_2 = {1000, 1000, 1000, 0};
  s21_decimal result;

  s21_set_sign(&value_2, 1);

  ck_assert_int_eq(s21_add(value_1, value_2, &result), ARR_OK);

  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(first_negative_value_a) {
  s21_decimal value_1 = {10000, 10000, 10000, 0};
  s21_decimal value_2 = {10000, 10000, 10000, 0};
  s21_decimal result;

  s21_set_sign(&value_1, 1);

  ck_assert_int_eq(s21_add(value_1, value_2, &result), ARR_OK);

  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(result_is_too_large_a) {
  s21_decimal value_1 = {UINT_MAX, UINT_MAX, UINT_MAX, 0};
  s21_decimal value_2 = {UINT_MAX, UINT_MAX, UINT_MAX, 0};
  s21_decimal result;

  ck_assert_int_eq(s21_add(value_1, value_2, &result), ARR_TOO_LARGE);
}
END_TEST

START_TEST(result_is_too_small_a) {
  s21_decimal value_1 = {UINT_MAX, UINT_MAX, UINT_MAX, 0};
  s21_decimal value_2 = {UINT_MAX, UINT_MAX, UINT_MAX, 0};
  s21_decimal result;

  s21_set_sign(&value_1, 1);
  s21_set_sign(&value_2, 1);

  ck_assert_int_eq(s21_add(value_1, value_2, &result), ARR_TOO_SMALL);
}
END_TEST

START_TEST(full_result_a) {
  s21_decimal value_1 = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00010000};
  s21_decimal value_2 = {0x00000001, 0x00000000, 0x00000000, 0x00010000};
  s21_decimal result;

  ck_assert_int_eq(s21_add(value_1, value_2, &result), ARR_OK);

  ck_assert_int_eq(s21_get_scale(result), 0);
}
END_TEST

START_TEST(usual_result_a) {
  s21_decimal value_1 = {UINT_MAX, UINT_MAX, 100000, 0x00010000};
  s21_decimal value_2 = {UINT_MAX, UINT_MAX, 500000, 0x00010000};
  s21_decimal result;

  ck_assert_int_eq(s21_add(value_1, value_2, &result), ARR_OK);

  ck_assert_int_eq(result.bits[0], UINT_MAX - 1);
  ck_assert_int_eq(result.bits[1], UINT_MAX);
  ck_assert_int_eq(result.bits[2], 600001);
  ck_assert_int_eq(s21_get_scale(result), 1);
}
END_TEST
