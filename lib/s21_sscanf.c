#include "../s21_string.h"
// Функция sscanf() используется для считывания отформатированного ввода из
// строки. функция sscanf() считывает ввод из строки и сохраняет его в другой
// строке. Возвращаемое значение В случае успешного выполнения функция
// возвращает количество успешно прочитанных значений. В случае сбоя ввода до
// успешного считывания каких-либо данных возвращается значение EOF.
// проверим

int s21_sscanf(const char *str, const char *format, ...) {
  int result = 0;
  va_list arguments;
  form params = {0};
  va_start(arguments, format);
  int count_for_n = 0, count_char = 0;
  while (*format && count_char != -1) {
    count_char = 0;
    if (*format == '%' && *(format + 1) != '%') {
      format++;
      params.width = 0;
      if (iss_digit(*format)) params.width = convert_str_to_int_sc(&format);
      params.length = parser_length_sc(*format);
      if (params.length != no_length) format++;
      if (s21_strchr("cs", *format)) {
        count_char = scanf_cs(str, arguments, params, format, &result);
      } else if (s21_strchr("di", *format)) {
        count_char = scanf_di(str, arguments, params, &result);
      } else if (s21_strchr("ouxXp", *format)) {
        count_char = scanf_unsig(str, arguments, params, format, &result);
      } else if (s21_strchr("eEgGf", *format)) {
        count_char = scanf_float(str, arguments, params, &result);
      } else if (s21_strchr("n", *format)) {
        *va_arg(arguments, int *) = count_for_n;
      }
      if (count_char > 0) str = str + count_char;
      count_for_n += count_char;
      format++;
    } else if (*format == ' ') {
      format++;
      if (*str == ' ') {
        str++;
        count_for_n++;
      }
    } else {
      if (*format != '%' && *format != *str) break;
      format++;
      str++;
      count_for_n++;
    }
  }
  va_end(arguments);
  if (result == 0) result = -1;
  return result;
}

Length parser_length_sc(char len) {
  Length length = no_length;
  switch (len) {
    case 'h':
      length = short_int;
      break;
    case 'l':
      length = long_int;
      break;
    case 'L':
      length = long_double;
      break;
  }
  return length;
}

int iss_digit(char symb) { return symb >= '0' && symb <= '9' ? 1 : 0; }

int is_space(char symb) {
  return (symb == ' ' || symb == '\n' || symb == '\t' || symb == '\0') ? 1 : 0;
}

int convert_str_to_int_sc(const char **format) {
  int digit = *(*format)++ - '0';
  while (iss_digit(*(*format))) {
    digit *= 10;
    digit += *(*format)++ - '0';
  }

  return digit;
}

long long my_atoi(const char **str, int *count, int width) {
  long long result = 0;
  int sign = 1;
  int max = 0;
  int len;
  (width > 0) ? (len = width) : (len = -1);

  if (*(*str) == '-') {
    sign = -1;
    *str = *str + 1;
    *count += 1;
  } else if (*(*str) == '+') {
    sign = 1;
    *str = *str + 1;
    *count += 1;
  }

  while (iss_digit(*(*str)) && len != 0) {
    if ((sign == -1) && (result != 0)) {
      result = -1 * result;
      sign = 1;
    }
    if (result < 0 && max == 0) {
      if (result < ((-9223372036854775807 + (*(*str) - '0')) / 10)) {
        result = -9223372036854775807;
        max = 1;
      } else {
        result = result * 10 - (*(*str) - '0');
      }
    } else if (max == 0) {
      if (result > ((9223372036854775807 - (*(*str) - '0')) / 10)) {
        result = 9223372036854775807;
        max = 1;
      } else
        result = result * 10 + (*(*str) - '0');
    }
    *str = *str + 1;
    *count += 1;
    len--;
  }
  return result;
}

unsigned long long my_atoi_base(const char **str, unsigned base, int *count,
                                int width) {
  unsigned long long result = 0;
  int bbase = (int)base;
  int len;
  (width > 0) ? (len = width) : (len = -1);
  while (len != 0 &&
         ((**str >= '0' && **str <= ('0' + bbase - 1)) ||
          (base > 10 && ((**str >= 'A' && **str <= ('A' + bbase - 10)) ||
                         (**str >= 'a' && **str <= ('a' + bbase - 10)))))) {
    char base_char;
    (**str >= 'a')
        ? (base_char = 'a' - 10)
        : ((**str >= 'A') ? (base_char = 'A' - 10) : (base_char = '0'));
    if (result > ((MAXUNSIG - (*(*str) - base_char)) / base)) {
      result = MAXUNSIG;
    } else
      result = result * base + (*(*str) - base_char);
    *str = *str + 1;
    *count += 1;
    len--;
  }
  return result;
}

int scanf_cs(const char *str, va_list arguments, form params,
             const char *format, int *result) {
  int count_char = 0;
  int count_probel = 0;

  if (*format == 'c') {
    if (str[0]) {
      char *c_new = va_arg(arguments, char *);
      count_char++;
      *c_new = *str++;
      *result = *result + 1;
    }
  } else {
    while (is_space(*str)) {
      str++;
      count_probel++;
    }

    if ((params.length == long_int) && (*format == 's')) {
      wchar_t *s_new = va_arg(arguments, wchar_t *);
      while ((*str != '\0' && *str != ' ' && *str != '\n') &&
             (params.width == 0 || count_char < params.width)) {
        *s_new++ = *str++;
        count_char++;
      }
      *s_new = '\0';
      *result = *result + 1;
    } else {
      char *s_new = va_arg(arguments, char *);
      while ((*str != '\0' && *str != ' ' && *str != '\n') &&
             (params.width == 0 || count_char < params.width)) {
        *s_new++ = *str++;
        count_char++;
      }
      *s_new = '\0';
      *result = *result + 1;
    }
  }
  if (count_char == 0)
    count_char = -1;
  else
    count_char = count_char + count_probel;
  return count_char;
}

int scanf_di(const char *str, va_list arguments, form params, int *result) {
  int count_char = 0, old_count = 0, bad = 0;
  int base = 10;
  long long data = 0;

  while (is_space(*str)) {
    str++;
    count_char++;
  }
  if (str[0] == '0' && str[1] == 'x') {
    str = str + 2;
    count_char = count_char + 2;
    base = 16;
  }

  old_count = count_char;
  if (base == 16) {
    data = my_atoi_base(&str, base, &count_char, params.width);
  } else
    data = my_atoi(&str, &count_char, params.width);
  if (count_char == old_count) bad = 1;

  if (!bad) {
    if (params.length == short_int) {
      short int *d = va_arg(arguments, short int *);
      *d = (short)data;
    } else if (params.length == long_double) {
      long long *d = va_arg(arguments, long long *);
      *d = data;
    } else if (params.length == long_int) {
      long *d = va_arg(arguments, long *);
      *d = (long)data;
    } else {
      int *d = va_arg(arguments, int *);
      *d = (int)data;
    }
    *result = *result + 1;
  } else {
    va_arg(arguments, void *);
  }

  return count_char;
}

int scanf_unsig(const char *str, va_list arguments, form params,
                const char *format, int *result) {
  int count_char = 0;
  int base = 10;
  unsigned long long data = 0;
  int read_something = 0;

  while (is_space(*str)) {
    str++;
    count_char++;
  }

  switch (*format) {
    case 'o':
      base = 8;
      break;
    case 'x':
    case 'X':
    case 'p':
      base = 16;
      if (str[0] == '0' && str[1] == 'x') {
        str = str + 2;
        count_char = count_char + 2;
      }
      break;
    default:
      base = 10;
      break;
  }

  if ((base == 10 && (iss_digit(*str))) ||
      (base == 8 && (*str >= '0' && *str <= '7')) ||
      (base == 16 &&
       ((*str >= '0' && *str <= '9') || (*str >= 'A' && *str <= 'F') ||
        (*str >= 'a' && *str <= 'f')))) {
    data = my_atoi_base(&str, base, &count_char, params.width);
    read_something = 1;
  }

  if (read_something) {
    if (*format == 'p') {
      unsigned long int *p_void = va_arg(arguments, void *);
      *p_void = (unsigned long)data;
    } else if (params.length == short_int) {
      short unsigned *d = va_arg(arguments, short unsigned *);
      *d = (short)data;
    } else if (params.length == long_double) {
      unsigned long long *d = va_arg(arguments, unsigned long long *);
      *d = data;
    } else if (params.length == long_int) {
      long unsigned *d = va_arg(arguments, unsigned long *);
      *d = (long unsigned)data;
    } else {
      unsigned *d = va_arg(arguments, unsigned *);
      *d = (unsigned)data;
    }
    *result = *result + 1;
  } else {
    va_arg(arguments, void *);
    return -1;
  }

  return count_char;
}

int scanf_float(const char *str, va_list arguments, form params, int *result) {
  int count_char = 0;
  int count_probel = 0;

  int bad = 0;
  long double data = 0.0;

  while (is_space(*str)) {
    str++;
    count_probel++;
  }

  if (iss_digit(*str) || *str == '+' || *str == '-' || *str == '.') {
    char znak = ' ';
    if (*str == '+' || *str == '-') {
      znak = *str;
      str++;
      count_char++;
    }

    if ((s21_strncmp(str, "nan", 3) == 0) ||
        (s21_strncmp(str, "inf", 3) == 0) ||
        (s21_strncmp(str, "NAN", 3) == 0) ||
        (s21_strncmp(str, "INF", 3) == 0)) {
      if (params.length == long_double) {
        long double *d = va_arg(arguments, long double *);
        if (s21_strncmp(str, "nan", 3) == 0 ||
            s21_strncmp(str, "NAN", 3) == 0) {
          *d = NAN;
        } else {
          *d = (znak == '-') ? -INFINITY : INFINITY;
        }
      } else {
        float *d = va_arg(arguments, float *);
        if (s21_strncmp(str, "nan", 3) == 0 ||
            s21_strncmp(str, "NAN", 3) == 0) {
          *d = NAN;
        } else {
          *d = (znak == '-') ? -INFINITY : INFINITY;
        }
      }
      *result = *result + 1;
      return count_char + 3;
    }

    data = (long double)my_atoi(&str, &count_char, params.width);

    if (count_char == 0) bad = 1;

    if (!bad && *str == '.') {
      str++;
      int frac_digits = 0;
      long double data2 =
          (long double)my_atoi(&str, &frac_digits, params.width);
      count_char += frac_digits + 1;
      while (frac_digits > 0) {
        data2 = data2 / 10.0;
        frac_digits--;
      }
      data += data2;
    }

    if (!bad && (*str == 'e' || *str == 'E')) {
      str++;
      count_char++;
      char exp_sign = '+';
      if (*str == '+' || *str == '-') {
        exp_sign = *str;
        str++;
        count_char++;
      }
      int exp_digits = 0;
      long long exponent = my_atoi(&str, &exp_digits, params.width);
      count_char += exp_digits;

      long double multiplier = 1.0;
      for (long long i = 0; i < exponent; i++) {
        multiplier *= (exp_sign == '-') ? 0.1 : 10.0;
      }
      data *= multiplier;
    }

    if (znak == '-') data = -data;
  } else {
    bad = 1;
  }

  if (!bad) {
    if (params.length == long_double) {
      long double *d = va_arg(arguments, long double *);
      *d = (long double)data;
    } else {
      float *d = va_arg(arguments, float *);
      *d = (float)data;
    }
    *result = *result + 1;
    return count_char + count_probel;
  } else {
    va_arg(arguments, void *);
    return -1;
  }
}
