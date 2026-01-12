#ifndef S21_PARSERS_H
#define S21_PARSERS_H

#include "../../s21_decimal.h"

int s21_get_sign(s21_decimal value);
void s21_set_sign(s21_decimal *value, int sign);
int s21_get_scale(s21_decimal value);
void s21_set_scale(s21_decimal *value, uint8_t scale);
int s21_get_float_exp(const float *f);

#endif
