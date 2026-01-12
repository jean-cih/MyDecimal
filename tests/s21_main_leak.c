#include "../s21_decimal.h"

int main(void) {
  s21_decimal value_1 = {{10, 10, 10, 0}};
  s21_decimal value_2 = {{10, 10, 10, 0}};

  s21_decimal result1;
  s21_add(value_1, value_2, &result1);

  s21_decimal result2;
  s21_set_sign(&value_2, 1);
  s21_div(value_1, value_2, &result2);

  s21_decimal result3;
  s21_sub(value_1, value_2, &result3);

  s21_decimal result4;
  s21_div(value_1, value_2, &result4);

  s21_is_less(value_1, value_2);
  s21_is_less_or_equal(value_1, value_2);
  s21_is_greater(value_1, value_2);
  s21_is_greater_or_equal(value_1, value_2);
  s21_is_equal(value_1, value_2);
  s21_is_not_equal(value_1, value_2);

  int value1 = 36;
  s21_decimal result5;
  s21_from_int_to_decimal(value1, &result5);

  float value2 = 12345.023f;
  s21_decimal result6;
  s21_from_float_to_decimal(value2, &result6);

  s21_decimal value3 = {{36, 0, 0, 0x80000000}};
  int result7;
  s21_from_decimal_to_int(value3, &result7);

  s21_decimal value4 = {{12345, 0, 0, 0x80020000}};
  float result8;
  s21_from_decimal_to_float(value4, &result8);

  return 0;
}
