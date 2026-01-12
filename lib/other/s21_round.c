#include "../../s21_decimal.h"

int s21_round(s21_decimal value, s21_decimal *result) {
  if (!result) {
    return CALCULATION_ERROR;
  }

  s21_decimal_set_zero(result);

  if (!s21_is_correct_decimal(value)) {
    return CALCULATION_ERROR;
  }

  uint8_t scale = s21_get_scale(value);
  *result = value;

  if (!scale) {
    return OTH_OK;
  }

  for (int i = 0; i < scale; i++) {
    if (s21_divide_by_10_mantissa_round(result)) {
      return CALCULATION_ERROR;
    }
  }

  return OTH_OK;
}
