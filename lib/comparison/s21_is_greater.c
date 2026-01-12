#include "../../s21_decimal.h"

int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
  if (s21_decimal_is_zero(value_1) && s21_decimal_is_zero(value_2)) {
    return FALSE;
  }

  uint8_t sign_1 = s21_get_sign(value_1);
  uint8_t sign_2 = s21_get_sign(value_2);

  int status = TRUE;
  if (sign_1 != sign_2) {
    status = sign_1 == 0;
  } else {
    s21_normalize(&value_1, &value_2);

    int cmp = s21_compare_bits(value_1, value_2);
    if (cmp == 0) {
      status = FALSE;
    } else {
      if (sign_1 == 0) {
        status = cmp > 0;
      } else {
        status = cmp < 0;
      }
    }
  }

  return status;
}
