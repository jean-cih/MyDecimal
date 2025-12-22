#include "../s21_string.h"

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  unsigned char *ptr1 = (unsigned char *)dest;
  unsigned char *ptr2 = (unsigned char *)src;
  while (n-- > 0) {
    *ptr1 = *ptr2;
    ptr1++;
    ptr2++;
  }
  return dest;
}
