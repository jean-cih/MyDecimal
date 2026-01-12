#include "s21_parsers.h"

int s21_get_sign(s21_decimal value) { return value.bits[3] >> 31; }

void s21_set_sign(s21_decimal *value, int sign) {
  if (sign) {
    value->bits[3] |= 0x80000000;
  } else {
    value->bits[3] &= 0x7FFFFFFF;
  }
}

int s21_get_scale(s21_decimal value) { return (value.bits[3] >> 16) & 0xFF; }

void s21_set_scale(s21_decimal *value, uint8_t scale) {
  if (scale > 28) {
    return;
  }

  int sign = s21_get_sign(*value);
  value->bits[3] = 0;
  value->bits[3] &= ~(0xFF << 16);
  value->bits[3] |= scale << 16;

  s21_set_sign(value, sign);
}

int s21_get_float_exp(const float *f) {
  union {
    float fl;
    uint32_t ui;
  } bits;
  bits.fl = *f;

  int exp = ((bits.ui >> 23) & 0xFF) - 127;
  return exp;
}
