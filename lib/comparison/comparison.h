#ifndef COMPARISON_H
#define COMPARISON_H

int s21_is_less(s21_decimal, s21_decimal)
int s21_is_less_or_equal(s21_decimal, s21_decimal)
int s21_is_greater(s21_decimal, s21_decimal)
int s21_is_greater_or_equal(s21_decimal, s21_decimal)
int s21_is_equal(s21_decimal, s21_decimal)
int s21_is_not_equal(s21_decimal, s21_decimal)

typedef enum s21_comparison_result {
    S21_COMP_FALSE = 0,
    S21_COMP_TRUE = 1,
} s21_comp_result;

#endif
