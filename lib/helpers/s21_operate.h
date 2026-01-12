#ifndef S21_OPERATE_H
#define S21_OPERATE_H

#include <stdint.h>
#include "../../s21_decimal.h"

int s21_shift_left_mantissa(s21_decimal *value, int shift);
void s21_decimal_set_zero(s21_decimal *value);
int s21_multiple_by_10_mantissa(s21_decimal *value);
int s21_divide_by_10_mantissa_round(s21_decimal *value);
void s21_divide_by_10_mantissa_with_remainder(s21_decimal *value, uint32_t *remainder);
void s21_divide_by_10_mantissa_truncate(s21_decimal *value);
int s21_mantissa_add_one(s21_decimal *value);
int s21_is_even(s21_decimal value);
void s21_normalize(s21_decimal *value_1, s21_decimal *value_2);
int s21_get_bits(s21_decimal value, int bit_index);
int s21_sub_bits(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_compare_bits(s21_decimal value_1, s21_decimal value_2);
int s21_add_bits(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
void s21_decimal_round(s21_decimal *value, int current_scale);
void s21_set_bit(s21_decimal *value, int bit_index, int bit_value);

#endif
