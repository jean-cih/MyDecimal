#include "../../s21_decimal.h"

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  if (!dst) {
    return CONVERTATION_ERROR;
  }

  if (isnan(src) || isinf(src)) {
    return CONVERTATION_ERROR;
  }

  s21_decimal_set_zero(dst);

  if (src == 0.0f) {
    s21_set_sign(dst, src < 0);
    return CONVERTATION_OK;
  }

  int sign = 0;
  if (src < 0) {
    src *= -1;
    sign = 1;
  }

  int exp = s21_get_float_exp(&src);

  double tmp = (double)src;
  int scale = 0;

  while (scale < 28 && (int)tmp / (int)pow(2, 21) == 0) {
    tmp *= 10;
    scale++;
  }

  if (scale > 28 || !(exp > -94 && exp < 96)) {
    return CONVERTATION_ERROR;
  }

  while (fmod(tmp, 10) == 0 && scale > 0) {
    tmp /= 10;
    scale--;
  }

  tmp = (float)tmp;

  union {
    float fl;
    uint32_t ui;
  } mant;
  mant.fl = tmp;

  exp = s21_get_float_exp(&mant.fl);

  s21_set_bit(dst, exp, 1);

  for (int i = exp - 1, j = 22; j >= 0; i--, j--) {
    if ((mant.ui & (1 << j)) != 0) {
      s21_set_bit(dst, i, 1);
    }
  }

  s21_set_sign(dst, sign);
  s21_set_scale(dst, scale);

  return CONVERTATION_OK;
}
