#include "../s21_string.h"
///*
void *s21_to_upper(const char *str) {
  char *ptr = S21_NULL;
  if (str) {
    int len = s21_strlen(str);
    ptr = calloc(len + 1, sizeof(char));
    for (int i = 0; i < len; i++) {
      if (str[i] >= 97 && str[i] <= 122) {
        ptr[i] = str[i] - 32;
      } else
        ptr[i] = str[i];
    }
  }
  return ptr;
}
