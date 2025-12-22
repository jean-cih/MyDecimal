#include "../s21_string.h"

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  char *ptr = S21_NULL;
  if (src != S21_NULL && str != S21_NULL) {
    s21_size_t len_src = s21_strlen(src);
    s21_size_t len_str = s21_strlen(str);
    if (len_src >= start_index && src != S21_NULL) {
      ptr = (char *)calloc(len_str + len_src + 1, sizeof(char));
      s21_memcpy(ptr, src, start_index);
      s21_memcpy(ptr + start_index, str, len_str);
      s21_memcpy(ptr + start_index + len_str, src + start_index,
                 len_src - start_index);
    }
  }
  return ptr;
}
