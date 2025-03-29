#ifndef CONVERTORS_H
#define CONVERTORS_H

int s21_from_int_to_decimal(int src, s21_decimal *dst)
int s21_from_float_to_decimal(float src, s21_decimal *dst)
int s21_from_decimal_to_int(s21_decimal src, int *dst)
int s21_from_decimal_to_float(s21_decimal src, float *dst)

typedef enum s21_conversion_result {
    S21_CONV_OK = 0,
    S21_CONV_ERROR = 1
} s21_conv_result;

#endif
