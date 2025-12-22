#include "../s21_string.h"

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  char *ptr = dest;
  while (*ptr) ptr++;
  while (n-- > 0) {
    *ptr = *src;
    ptr++;
    src++;
  }
  *ptr = '\0';

  return dest;
}
