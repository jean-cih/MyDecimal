#include "../../s21_decimal.h"

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (!result) {
    return 1;
  }

  if (s21_decimal_is_zero(value_2)) {
    return ARR_DIVISION_BY_ZERO;
  }

  s21_decimal_set_zero(result);
  if (s21_decimal_is_zero(value_1)) {
    return ARR_OK;
  }

  int result_sign = s21_get_sign(value_1) != s21_get_sign(value_2);

  s21_set_sign(&value_1, 0);
  s21_set_sign(&value_2, 0);

  s21_big_decimal big_value_1;
  s21_big_decimal big_value_2;
  big_from_decimal(value_1, &big_value_1);
  big_from_decimal(value_2, &big_value_2);

  s21_big_decimal quotient;
  s21_big_decimal remainder;
  big_decimal_set_zero(&quotient);
  big_decimal_set_zero(&remainder);

  big_decimal_divide(big_value_1, big_value_2, &quotient, &remainder);

  int fractional_scale = 0;
  const int max_fractional_scale = 28;

  while (big_decimal_is_zero(remainder) &&
         fractional_scale < max_fractional_scale) {
    big_multiply_mantissa_by_10(&remainder);

    s21_big_decimal current_digit;
    s21_big_decimal new_remainder;
    big_decimal_set_zero(&current_digit);
    big_decimal_set_zero(&new_remainder);

    big_decimal_divide(remainder, big_value_2, &current_digit, &new_remainder);
    remainder = new_remainder;

    big_multiply_mantissa_by_10(&quotient);
    big_decimal_add(&quotient, &current_digit);

    fractional_scale++;
  }

  if (big_decimal_is_zero(remainder)) {
    s21_big_decimal multiplied_remainder;
    s21_big_decimal rounding_digit;
    s21_big_decimal rounding_remainder;

    multiplied_remainder = remainder;
    big_multiply_mantissa_by_10(&multiplied_remainder);

    big_decimal_set_zero(&rounding_digit);
    big_decimal_set_zero(&rounding_remainder);
    big_decimal_divide(multiplied_remainder, big_value_2, &rounding_digit,
                       &rounding_remainder);

    int digit = (int)rounding_digit.bits[0];
    int should_round_up = big_decimal_get_rounding_decision(digit, &quotient);

    if (should_round_up) {
      big_decimal_add(&quotient, &(s21_big_decimal){{1, 0, 0, 0, 0, 0}, 0, 0});
    }
  }

  s21_big_decimal result_big = quotient;
  result_big.sign = result_sign;
  result_big.scale =
      fractional_scale - (s21_get_scale(value_2) - s21_get_scale(value_1));

  if (result_big.scale < 0) {
    int scale_adjustment = -result_big.scale;
    for (int i = 0; i < scale_adjustment; i++) {
      big_multiply_mantissa_by_10(&result_big);
    }
    result_big.scale = 0;
  }

  return from_big_decimal_to_decimal(result_big, result);
}
