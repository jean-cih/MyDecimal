#ifndef ARITHMETIC_H
#define ARITHMETIC_H

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result)
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result)
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result)
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result)

typedef enum s21_arithmetic_result {
    S21_AR_OK = 0,
    S21_AR_BIG = 1,
    S21_AR_SMALL = 2,
    S21_AR_ZERO_DIV = 3,
} s21_ar_result;

#endif
