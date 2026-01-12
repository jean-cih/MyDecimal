#include "s21_operate.h"

int s21_shift_left_mantissa(s21_decimal *value, int shift) {
  int overflow = 0;
  for (int i = 0; i < shift; i++) {
    uint32_t carry = 0;

    for (int j = 0; j < 3; j++) {
      uint32_t next_carry = (value->bits[j] >> 31) & 1;
      value->bits[j] = (value->bits[j] << 1) | carry;
      carry = next_carry;
    }

    if (carry) {
      overflow = 1;
    }
  }

  return overflow;
}

void s21_decimal_set_zero(s21_decimal *value) {
  value->bits[3] = value->bits[2] = value->bits[1] = value->bits[0] = 0;
}

int s21_multiply_by_10_mantissa(s21_decimal *value) {
  uint64_t carry = 0;
  for (int i = 0; i < 3; i++) {
    uint64_t product = (uint64_t)value->bits[i] * 10 + carry;
    value->bits[i] = (uint32_t)product;
    carry = product >> 32;
  }

  return (carry != 0);
}

int s21_divide_by_10_mantissa_round(s21_decimal *value) {
  uint8_t original_scale = s21_get_scale(*value);

  s21_decimal backup = *value;

  uint32_t remainder = 0;
  s21_divide_by_10_mantissa_with_remainder(value, &remainder);

  if (remainder > 5) {
    if (s21_mantissa_add_one(value)) {
      *value = backup;
      return 1;
    }
  } else if (remainder == 5) {
    if (!s21_is_even(*value)) {
      if (s21_mantissa_add_one(value)) {
        *value = backup;
        return 1;
      }
    }
  }

  if (original_scale > 0) {
    s21_set_scale(value, original_scale - 1);
  }

  return 0;
}

void s21_divide_by_10_mantissa_with_remainder(s21_decimal *value,
                                              uint32_t *remainder) {
  uint64_t carry = 0;

  for (int i = 2; i >= 0; i--) {
    uint64_t dividend = ((uint64_t)carry << 32) | value->bits[i];
    value->bits[i] = (uint32_t)(dividend / 10);
    carry = dividend % 10;
  }

  *remainder = (uint32_t)carry;
}

void s21_divide_by_10_mantissa_truncate(s21_decimal *value) {
  uint64_t carry = 0;

  for (int i = 2; i >= 0; i--) {
    uint64_t dividend = ((uint64_t)carry << 32) | value->bits[i];
    value->bits[i] = (uint32_t)(dividend / 10);
    carry = dividend % 10;
  }
}

int s21_mantissa_add_one(s21_decimal *value) {
  s21_decimal one = {{1, 0, 0, 0}};
  uint64_t carry = 0;

  for (int i = 0; i < 3; i++) {
    uint64_t sum = (uint64_t)value->bits[i] + one.bits[i] + carry;
    value->bits[i] = (uint32_t)sum;
    carry = sum >> 32;
  }

  return (carry != 0);
}

int s21_is_even(s21_decimal value) { return (value.bits[0] & 1) == 0; }

void s21_normalize(s21_decimal *value_1, s21_decimal *value_2) {
  uint8_t scale_1 = s21_get_scale(*value_1);
  uint8_t scale_2 = s21_get_scale(*value_2);

  if (scale_1 == scale_2) {
    return;
  }

  while (scale_1 < scale_2 && scale_1 < 28) {
    s21_decimal backup = *value_1;
    if (s21_multiply_by_10_mantissa(value_1)) {
      *value_1 = backup;
      break;
    }

    scale_1++;
  }

  while (scale_1 > scale_2 && scale_2 < 28) {
    s21_decimal backup = *value_2;
    if (s21_multiply_by_10_mantissa(value_2)) {
      *value_2 = backup;
      break;
    }

    scale_2++;
  }

  while (scale_1 < scale_2 && scale_2 > 0) {
    s21_divide_by_10_mantissa_round(value_2);
    scale_2--;
  }

  while (scale_1 > scale_2 && scale_1 > 0) {
    s21_divide_by_10_mantissa_round(value_1);
    scale_1--;
  }

  s21_set_scale(value_1, scale_1);
  s21_set_scale(value_2, scale_2);
}

int s21_sub_bits(s21_decimal value_1, s21_decimal value_2,
                 s21_decimal *result) {
  int64_t borrow = 0;

  for (int i = 0; i < 3; i++) {
    int64_t diff = (int64_t)value_1.bits[i] - (int64_t)value_2.bits[i] - borrow;

    if (diff < 0) {
      diff += (1LL << 32);
      borrow = 1;
    } else {
      borrow = 0;
    }
    result->bits[i] = (uint32_t)diff;
  }

  return borrow;
}

int s21_compare_bits(s21_decimal value_1, s21_decimal value_2) {
  int status = 0;
  for (int i = 2; i >= 0; i--) {
    uint32_t v_1 = value_1.bits[i];
    uint32_t v_2 = value_2.bits[i];

    if (v_1 > v_2) {
      status = 1;
      break;
    } else if (v_1 < v_2) {
      status = -1;
      break;
    }
  }
  return status;
}

int s21_add_bits(s21_decimal value_1, s21_decimal value_2,
                 s21_decimal *result) {
  uint64_t carry = 0;

  for (int i = 0; i < 3; i++) {
    uint64_t sum =
        (uint64_t)value_1.bits[i] + (uint64_t)value_2.bits[i] + carry;
    result->bits[i] = (uint32_t)sum;
    carry = sum >> 32;
  }

  return carry != 0;
}

void s21_decimal_round(s21_decimal *value, int current_scale) {
  if (!value || current_scale <= 0) {
    return;
  }

  uint32_t remainder;
  s21_decimal backup = *value;

  s21_divide_by_10_mantissa_with_remainder(value, &remainder);

  int should_round_up = 0;

  if (remainder > 5) {
    should_round_up = 1;
  } else if (remainder == 5) {
    if (value->bits[0] & 1) {
      should_round_up = 1;
    }
  }

  if (should_round_up) {
    if (s21_mantissa_add_one(value)) {
      *value = backup;
      return;
    }
  }

  s21_set_scale(value, current_scale - 1);
}

void s21_set_bit(s21_decimal *value, int bit_index, int bit_value) {
  if (!value || bit_index < 0 || bit_index > 95) {
    return;
  }

  int word_index = bit_index / 32;
  int bit_in_word = bit_index % 32;

  if (bit_value) {
    value->bits[word_index] |= (1u << bit_in_word);
  } else {
    value->bits[word_index] &= ~(1u << bit_in_word);
  }
}

int s21_get_bits(s21_decimal value, int bit_index) {
  if (bit_index < 0 || bit_index > 95) {
    return 0;
  }

  return ((value.bits[bit_index / 32] >> (bit_index % 32)) & 1);
}
