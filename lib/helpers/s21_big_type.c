#include "s21_big_type.h"

void big_decimal_set_zero(s21_big_decimal *value) {
  for (int i = 5; i >= 0; i--) {
    value->bits[i] = 0;
  }
  value->scale = 0;
  value->sign = 0;
}

int big_decimal_is_zero(const s21_big_decimal value) {
  for (int i = 5; i >= 0; i--) {
    if (value.bits[i] != 0) {
      return 1;
    }
  }
  return 0;
}

void big_from_decimal(s21_decimal src, s21_big_decimal *dst) {
  big_decimal_set_zero(dst);
  for (int i = 0; i < 3; i++) {
    dst->bits[i] = src.bits[i];
  }

  dst->scale = s21_get_scale(src);
  dst->sign = s21_get_sign(src);
}

int big_decimal_compare(const s21_big_decimal left,
                        const s21_big_decimal right) {
  for (int i = 5; i >= 0; i--) {
    if (left.bits[i] > right.bits[i]) {
      return 1;
    }
    if (left.bits[i] < right.bits[i]) {
      return -1;
    }
  }
  return 0;
}

void big_decimal_sub(s21_big_decimal minuend, const s21_big_decimal subtrahend,
                     s21_big_decimal *result) {
  int borrow = 0;

  for (int i = 0; i < 6; i++) {
    uint64_t diff = (uint64_t)minuend.bits[i] - (uint64_t)subtrahend.bits[i] -
                    (uint64_t)borrow;
    result->bits[i] = (uint32_t)diff;
    borrow = (diff >> 63) & 1u;
  }
}

void big_decimal_shift_left(s21_big_decimal *value, int shift) {
  uint32_t carry_prev = 0;

  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < shift; j++) {
      uint32_t current = value->bits[i];
      uint32_t carry = current >> 31;

      current <<= 1;
      current |= carry_prev;

      value->bits[i] = current;
      carry_prev = carry;
    }
  }
}

int big_decimal_get_bit(const s21_big_decimal value, int bit_index) {
  return (value.bits[bit_index / 32] >> (bit_index % 32)) & 1;
}

void big_decimal_set_bit(s21_big_decimal *value, int bit_index, int bit_value) {
  int word_index = bit_index / 32;
  int bit_position = bit_index % 32;
  if (bit_value) {
    value->bits[word_index] |= (1u << bit_position);
  } else {
    value->bits[word_index] &= ~(1u << bit_position);
  }
}

void big_decimal_divide(const s21_big_decimal dividend,
                        const s21_big_decimal divisor,
                        s21_big_decimal *quotient, s21_big_decimal *remainder) {
  big_decimal_set_zero(quotient);
  big_decimal_set_zero(remainder);

  if (!big_decimal_is_zero(divisor)) {
    return;
  }

  for (int i = 191; i >= 0; i--) {
    big_decimal_shift_left(remainder, 1);
    int bit = big_decimal_get_bit(dividend, i);
    if (bit) {
      remainder->bits[0] |= 1u;
    }

    if (big_decimal_compare(*remainder, divisor) >= 0) {
      big_decimal_sub(*remainder, divisor, remainder);
      big_decimal_set_bit(quotient, i, 1);
    }
  }
}

void big_multiply_mantissa_by_10(s21_big_decimal *value) {
  uint64_t carry = 0;

  for (int i = 0; i < 6; i++) {
    uint64_t product = (uint64_t)value->bits[i] * 10u + carry;
    value->bits[i] = (uint32_t)product;
    carry = product >> 32;
  }
}

void big_divide_mantissa_by_10(s21_big_decimal *value, int *remainder) {
  uint64_t current_remainder = 0;

  for (int i = 5; i >= 0; i--) {
    uint64_t current = (current_remainder << 32) | (uint64_t)value->bits[i];
    value->bits[i] = (uint32_t)(current / 10u);
    current_remainder = current % 10u;
  }

  if (remainder) {
    *remainder = (int)current_remainder;
  }
}

void big_decimal_add(s21_big_decimal *result, const s21_big_decimal *addend) {
  uint64_t carry = 0;

  for (int i = 0; i < 6; i++) {
    uint64_t sum = (uint64_t)result->bits[i] +
                   (uint64_t)(addend ? addend->bits[i] : 0) + carry;
    result->bits[i] = (uint32_t)sum;
    carry = sum >> 32;
  }
}

int big_decimal_get_rounding_decision(int remainder_value,
                                      s21_big_decimal *value) {
  if (remainder_value > 5) {
    return 1;
  } else if (remainder_value < 5) {
    return 0;
  } else {
    int is_mantissa_zero = !big_decimal_is_zero(*value);
    if (is_mantissa_zero) {
      return 0;
    } else {
      int least_significant_bit = value->bits[0] & 1u;
      return (least_significant_bit == 1);
    }
  }
}

void big_decimal_bank_round(s21_big_decimal *value) {
  if (value->scale <= 0) {
    return;
  }

  int remainder = 0;
  big_divide_mantissa_by_10(value, &remainder);

  int should_round_up = big_decimal_get_rounding_decision(remainder, value);

  if (should_round_up) {
    big_decimal_add(value, &(s21_big_decimal){{1, 0, 0, 0, 0, 0}, 0, 0});
  }

  value->scale -= 1;
  if (value->scale < 0) value->scale = 0;
}

int from_big_decimal_to_decimal(s21_big_decimal src, s21_decimal *dst) {
  while ((src.scale > 28 || src.bits[3] != 0 || src.bits[4] != 0 ||
          src.bits[5] != 0) &&
         src.scale > 0) {
    big_decimal_bank_round(&src);
  }

  if (src.bits[3] != 0 || src.bits[4] != 0 || src.bits[5] != 0 ||
      src.scale > 28) {
    return src.sign ? 2 : 1;
  }

  s21_decimal_set_zero(dst);

  for (int i = 0; i < 3; i++) {
    dst->bits[i] = src.bits[i];
  }

  s21_set_scale(dst, src.scale);
  s21_set_sign(dst, src.sign);

  return 0;
}
