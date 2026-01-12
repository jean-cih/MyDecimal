#include "../../s21_decimal.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  if (!dst) {
    return CONVERTATION_ERROR;
  }

  *dst = 0.0f;

  if (s21_decimal_is_zero(src)) {
    return CONVERTATION_OK;
  }

  int scale = s21_get_scale(src);
  int sign = s21_get_sign(src);

  double value = 0.0;

  value += (double)src.bits[2] * 18446744073709551616.0;
  value += (double)src.bits[1] * 4294967296.0;
  value += (double)src.bits[0];

  for (int i = 0; i < scale; ++i) {
    value /= 10.0;
  }

  if (sign) {
    value = -value;
  }

  *dst = (float)value;
  return CONVERTATION_OK;
}
