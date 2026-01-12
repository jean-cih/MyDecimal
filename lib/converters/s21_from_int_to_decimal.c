#include "../../s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  if (!dst) {
    return CONVERTATION_ERROR;
  }

  s21_decimal_set_zero(dst);

  if (!src) {
    return CONVERTATION_OK;
  }

  if (src == INT_MIN) {
    dst->bits[0] = 0x80000000;
    s21_set_sign(dst, 1);
    return CONVERTATION_OK;
  }

  if (src < 0) {
    s21_set_sign(dst, 1);
    src = -src;
  }

  dst->bits[0] = src;

  return CONVERTATION_OK;
}
