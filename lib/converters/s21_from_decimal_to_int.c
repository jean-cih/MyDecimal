#include "../../s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  if (!dst) {
    return CONVERTATION_ERROR;
  }

  s21_decimal truncated;
  if (s21_truncate(src, &truncated)) {
    return CONVERTATION_ERROR;
  }

  if (truncated.bits[1] | truncated.bits[2]) {
    return CONVERTATION_ERROR;
  }

  uint8_t sign = s21_get_sign(truncated);
  if (sign) {
    if (truncated.bits[0] > (uint32_t)INT_MAX + 1) {
      return CONVERTATION_ERROR;
    }
    if (truncated.bits[0] == (uint32_t)INT_MAX + 1) {
      *dst = INT_MIN;
    } else {
      *dst = -(int)truncated.bits[0];
    }
  } else {
    if (truncated.bits[0] > (uint32_t)INT_MAX) {
      return CONVERTATION_ERROR;
    }
    *dst = (int)truncated.bits[0];
  }

  return CONVERTATION_OK;
}
