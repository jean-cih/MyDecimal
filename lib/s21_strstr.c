#include "../s21_string.h"

char *s21_strstr(const char *haystack, const char *needle) {
  char *ptr1 = (char *)haystack;
  char *ptr2 = (char *)needle;
  char *res = S21_NULL;
  int len = 0;
  while (*ptr1 != '\0') {
    if (*ptr2 == '\0') {
      res = ptr1 - len;
      break;
    }
    if (*ptr1 == *ptr2) {
      ptr2++;
      len++;
    } else {
      len = 0;
      ptr2 = (char *)needle;
    }
    ptr1++;
  }
  if (*ptr1 == '\0' && *ptr2 == '\0') {
    res = ptr1 - len;
  }
  return res;
}
