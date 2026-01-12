#include "../../s21_decimal.h"

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (!result) {
    return 1;
  }

  s21_decimal_set_zero(result);

  uint8_t sign_1 = s21_get_sign(value_1);
  uint8_t sign_2 = s21_get_sign(value_2);

  int status = ARR_OK;
  if (sign_1 != sign_2) {
    if (sign_1) {
      s21_set_sign(&value_1, 0);
      status = s21_add(value_1, value_2, result);
      if (status == ARR_OK) {
        s21_set_sign(result, 1);
      } else if (status == ARR_TOO_LARGE) {
        status = ARR_TOO_SMALL;
      }
    } else {
      s21_set_sign(&value_2, 0);
      status = s21_add(value_1, value_2, result);
    }
  } else {
    s21_normalize(&value_1, &value_2);
    int scale = s21_get_scale(value_1);

    s21_set_sign(&value_1, 0);
    s21_set_sign(&value_2, 0);

    int cmp = s21_compare_bits(value_1, value_2);

    if (cmp > 0) {
      s21_sub_bits(value_1, value_2, result);
      s21_set_sign(result, 0);
    } else if (cmp < 0) {
      s21_sub_bits(value_2, value_1, result);
      s21_set_sign(result, 1);
    }

    s21_set_scale(result, scale);
  }
  return status;
}
