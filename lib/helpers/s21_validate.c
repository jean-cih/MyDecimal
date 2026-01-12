#include "s21_validate.h"

int s21_is_correct_decimal(s21_decimal value) {
  int result = 0;

  uint16_t empty_1 = value.bits[3] & 0xFFFF;
  uint8_t power = s21_get_scale(value);
  uint8_t empty_2 = (value.bits[3] >> 24) & 0x7F;

  if (empty_1 == 0 && empty_2 == 0 && power <= 28) {
    result = 1;
  }

  return result;
}

int s21_decimal_is_zero(s21_decimal value) {
  return !(value.bits[0] | value.bits[1] | value.bits[2]);
}
