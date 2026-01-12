#include "../../s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (!result) {
    return 1;
  }
  s21_decimal_set_zero(result);

  int sign_1 = s21_get_sign(value_1);
  int sign_2 = s21_get_sign(value_2);

  int status = ARR_OK;
  if (sign_1 != sign_2) {
    if (sign_1) {
      s21_set_sign(&value_1, 0);
      status = s21_sub(value_2, value_1, result);
    } else {
      s21_set_sign(&value_2, 0);
      status = s21_sub(value_1, value_2, result);
    }
  } else {
    s21_normalize(&value_1, &value_2);
    int scale = s21_get_scale(value_1);

    s21_decimal sum;
    s21_decimal_set_zero(&sum);

    int overflow = s21_add_bits(value_1, value_2, &sum);

    if (overflow) {
      if (scale == 0) {
        status = sign_1 ? ARR_TOO_SMALL : ARR_TOO_LARGE;
      } else {
        s21_decimal_round(&sum, scale);
        scale = s21_get_scale(sum);
      }
    }

    s21_set_sign(&sum, sign_1);
    s21_set_scale(&sum, scale);

    *result = sum;
  }
  return status;
}