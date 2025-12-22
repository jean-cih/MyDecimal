#include "../s21_string.h"

char *s21_strrchr(const char *str, int c) {
  unsigned char *ptr = (unsigned char *)str + s21_strlen(str);
  for (s21_size_t sz = s21_strlen(str); sz > 0; sz--) {
    if (*ptr == c) {
      break;
    } else
      ptr--;
  }
  return *ptr == c ? (char *)ptr : S21_NULL;
}
