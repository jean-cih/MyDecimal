#include "../s21_string.h"

char *s21_strpbrk(const char *str1, const char *str2) {
  char *ptr1 = (char *)str1;
  char *ptr2 = (char *)str2;
  char *exit = S21_NULL;
  if (str1 && str2 && *str2 != '\0') {
    while (*ptr1 != '\0') {
      while (*ptr1 != *ptr2) {
        ptr2++;
        if (*ptr2 == '\0') {
          ptr2 = (char *)str2;
          break;
        }
      }
      if (*ptr1 == *ptr2) {
        exit = ptr1;
        break;
      } else
        ptr1++;
    }
  }
  return exit;
}
