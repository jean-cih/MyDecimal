#include "../../s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  if (!result) {
    return CALCULATION_ERROR;
  }

  s21_decimal_set_zero(result);

  uint8_t sign = s21_get_sign(value);

  *result = value;
  s21_set_sign(result, !sign);

  return OTH_OK;
}
