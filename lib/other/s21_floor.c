#include "../../s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  if (!result) {
    return CALCULATION_ERROR;
  }

  s21_decimal_set_zero(result);

  if (!s21_is_correct_decimal(value)) {
    return CALCULATION_ERROR;
  }

  s21_decimal truncated_value;
  int truncate_status = s21_truncate(value, &truncated_value);
  if (truncate_status != OTH_OK) {
    return truncate_status;
  }

  uint8_t sign = s21_get_sign(value);
  if (sign == 1 && s21_is_not_equal(value, truncated_value) == 1) {
    s21_decimal one = {{1, 0, 0, 0}};
    int add_status = s21_sub(truncated_value, one, result);
    if (add_status != OTH_OK) {
      return CALCULATION_ERROR;
    }
  } else {
    *result = truncated_value;
  }

  return OTH_OK;
}
