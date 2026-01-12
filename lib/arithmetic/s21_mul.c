#include "../../s21_decimal.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (!result) {
    return 1;
  }

  s21_decimal_set_zero(result);
  if (s21_decimal_is_zero(value_1) || s21_decimal_is_zero(value_2)) {
    return ARR_OK;
  }

  int flag = 0;
  int sign_result = s21_get_sign(value_1) != s21_get_sign(value_2);
  int scale1 = s21_get_scale(value_1);
  int scale2 = s21_get_scale(value_2);
  int result_scale = scale1 + scale2;

  s21_set_sign(&value_1, 0);
  s21_set_sign(&value_2, 0);

  s21_decimal temp = value_1;
  s21_decimal accumulator = {0};

  for (int i = 0; i < 96; i++) {
    if (s21_get_bits(value_2, i)) {
      flag = s21_add(accumulator, temp, &accumulator);
      if (flag) {
        break;
      }
    }
    s21_shift_left_mantissa(&temp, 1);
    if (s21_decimal_is_zero(temp)) {
      break;
    }
  }

  int status = ARR_OK;
  if (flag) {
    s21_decimal_set_zero(result);
    status = sign_result ? ARR_TOO_SMALL : ARR_TOO_LARGE;
  } else {
    *result = accumulator;
    s21_set_scale(result, result_scale);
    s21_set_sign(result, sign_result);

    if (result_scale > 28) {
      status = sign_result ? ARR_TOO_SMALL : ARR_TOO_LARGE;
    }
  }
  return status;
}