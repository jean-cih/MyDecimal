#include "../s21_main_case.h"

START_TEST(both_equal_zero_e) {
  s21_decimal value_1 = {0, 0, 0, 0};
  s21_decimal value_2 = {0, 0, 0, 0};

  ck_assert_int_eq(s21_is_equal(value_1, value_2), TRUE);
}
END_TEST

START_TEST(different_signs_e) {
  s21_decimal value_1 = {10, 10, 10, 0};
  s21_decimal value_2 = {10, 10, 10, 0};

  s21_set_sign(&value_1, 1);

  ck_assert_int_eq(s21_is_equal(value_1, value_2), FALSE);
}
END_TEST

START_TEST(different_values_e) {
  s21_decimal value_1 = {20, 20, 20, 0};
  s21_decimal value_2 = {11, 10, 10, 0};

  ck_assert_int_eq(s21_is_equal(value_1, value_2), FALSE);
}
END_TEST

START_TEST(equal_values_e) {
  s21_decimal value_1 = {20, 20, 20, 0};
  s21_decimal value_2 = {20, 20, 20, 0};

  ck_assert_int_eq(s21_is_equal(value_1, value_2), TRUE);
}
END_TEST

START_TEST(usual_values_e) {
  s21_decimal value_1 = {20, 20, 218282, 0x00020000};
  s21_decimal value_2 = {20, 20, 20122, 0x00050000};

  ck_assert_int_eq(s21_is_equal(value_1, value_2), FALSE);
}
END_TEST
