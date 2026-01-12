#include "s21_print.h"

void s21_print_mantissa(s21_decimal value) {
  for (int i = 2; i >= 0; i--) {
    s21_print_32_bits(value.bits[i]);
  }
}

void s21_print_32_bits(uint32_t value) {
  for (int i = 31; i >= 0; i--) {
    uint8_t bit = (value >> i) & 1;
    printf("%i", bit);
  }
}
