#include "../s21_string.h"
int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  int res = 0;
  unsigned char *s1 = (unsigned char *)str1;
  unsigned char *s2 = (unsigned char *)str2;
  for (s21_size_t i = 0; i < n && !res; i++) {
    if (*s1 != *s2) {
      res = *s1 - *s2;
    }
    s1++;
    s2++;
  }
  return res;
}
