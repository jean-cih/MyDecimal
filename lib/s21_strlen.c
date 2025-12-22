#include "../s21_string.h"

s21_size_t s21_strlen(const char *str) {
  const char *ptr = str;
  while (*ptr) ptr++;
  return ptr - str;
}
