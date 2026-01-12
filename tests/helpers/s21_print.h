#ifndef S21_PRINT_H
#define S21_PRINT_H

#include <stdint.h>
#include <stdio.h>
#include "../../s21_decimal.h"

void s21_print_32_bits(uint32_t value);
void s21_print_mantissa(s21_decimal value);

#endif
