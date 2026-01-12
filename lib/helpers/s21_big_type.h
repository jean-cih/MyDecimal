#ifndef S21_NEW_TYPE_H
#define S21_NEW_TYPE_H

#include <stdint.h>
#include "../../s21_decimal.h"

typedef struct {
  uint32_t bits[6];
  int scale;
  int sign;
} s21_big_decimal;

void big_decimal_set_zero(s21_big_decimal *value);
int big_decimal_is_zero(const s21_big_decimal value);
void big_from_decimal(s21_decimal src, s21_big_decimal *dst);
int big_decimal_compare(const s21_big_decimal left, const s21_big_decimal right);
void big_decimal_sub(s21_big_decimal minuend, const s21_big_decimal subtrahend, s21_big_decimal *result);
void big_decimal_shift_left(s21_big_decimal *value, int shift);
int big_decimal_get_bit(const s21_big_decimal value, int bit_index);
void big_decimal_set_bit(s21_big_decimal *value, int bit_index, int bit_value);
void big_decimal_divide(const s21_big_decimal dividend, const s21_big_decimal divisor, s21_big_decimal *quotient, s21_big_decimal *remainder);
void big_multiply_mantissa_by_10(s21_big_decimal *value);
void big_divide_mantissa_by_10(s21_big_decimal *value, int *remainder);
void big_decimal_add(s21_big_decimal *result, const s21_big_decimal *addend);
int big_decimal_get_rounding_decision(int remainder_value, s21_big_decimal *value);
void big_decimal_bank_round(s21_big_decimal *value);
int from_big_decimal_to_decimal(s21_big_decimal src, s21_decimal *dst);

#endif
