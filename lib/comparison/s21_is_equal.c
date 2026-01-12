#include "../../s21_decimal.h"

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  if (s21_decimal_is_zero(value_1) && s21_decimal_is_zero(value_2)) {
    return TRUE;
  }

  uint8_t sign_1 = s21_get_sign(value_1);
  uint8_t sign_2 = s21_get_sign(value_2);

  int status = TRUE;
  if (sign_1 != sign_2) {
    status = FALSE;
  } else {
    s21_normalize(&value_1, &value_2);

    for (int i = 2; i >= 0; i--) {
      if (value_1.bits[i] != value_2.bits[i]) {
        status = FALSE;
        break;
      }
    }
  }
  return status;
}
