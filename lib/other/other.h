#ifndef OTHER_H
#define OTHER_H

int s21_floor(s21_decimal value, s21_decimal *result)
int s21_round(s21_decimal value, s21_decimal *result)
int s21_truncate(s21_decimal value, s21_decimal *result)
int s21_negate(s21_decimal value, s21_decimal *result)

typedef enum s21_other_result {
    S21_OTHER_OK = 0,
    S21_OTHER_ERROR = 1
} s21_other_result;

#endif
