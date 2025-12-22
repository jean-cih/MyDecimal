#include "../s21_string.h"

void *s21_trim(const char *src, const char *trim_chars) {
  char *ptr = S21_NULL;

  if (src == S21_NULL) {
    return S21_NULL;
  }

  s21_size_t len_src = s21_strlen(src);

  const char *default_trim = " \t\n\r\f\v";
  const char *trim_set = trim_chars;

  if (trim_chars == S21_NULL || *trim_chars == '\0') {
    trim_set = default_trim;
  }

  if (len_src > 0) {
    const char *start_pos = src;
    const char *end_pos = src + len_src;

    while (*start_pos != '\0' && s21_strchr(trim_set, *start_pos)) {
      start_pos++;
    }

    while (end_pos > start_pos && s21_strchr(trim_set, *(end_pos - 1))) {
      end_pos--;
    }

    s21_size_t new_len = end_pos - start_pos;
    ptr = (char *)calloc(new_len + 1, sizeof(char));

    if (ptr != S21_NULL) {
      s21_strncpy(ptr, start_pos, new_len);
      ptr[new_len] = '\0';
    }
  } else {
    ptr = (char *)calloc(1, sizeof(char));
    if (ptr != S21_NULL) {
      ptr[0] = '\0';
    }
  }

  return ptr;
}