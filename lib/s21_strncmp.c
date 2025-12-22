#include "../s21_string.h"

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  return s21_memcmp((char *)str1, (char *)str2, n);
}
