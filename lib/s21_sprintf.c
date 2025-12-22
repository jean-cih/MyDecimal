#include "../s21_string.h"

int s21_sprintf(char *str, const char *format, ...) {
  char *str_copy = (char *)calloc(MAX_BUFFER_SIZE, sizeof(char));

  form params = {0};
  va_list args;
  va_start(args, format);

  parser_specifiers(&args, format, str_copy, &params);
  s21_strcpy(str, str_copy);

  va_end(args);
  free(str_copy);

  return s21_strlen(str);
}

void parser_specifiers(va_list *args, const char *format, char *str,
                       form *params) {
  int i = 0;
  while (*format) {
    if (*format == '%' && *(format + 1) != '%') {
      format++;
      if (*format == 'n') {
        parser_n(args, *params, str);
      }

      params->star_width = 0;
      params->point_width = 0;
      if (*format == '*') {
        params->star_width = va_arg(*args, int);
        format++;
      }

      if (*format == '.') {
        params->accurasy =
            is_digit(*++format) ? convert_str_to_int(&format) : 0;
        if (*format == '*') {
          params->point_width = va_arg(*args, int);
          format++;
        }
      } else {
        params->accurasy = -1;
      }

      params->flags = parser_flags(&format);
      params->width = is_digit(*format) ? convert_str_to_int(&format) : 0;

      params->length = parser_length(*format);
      if (params->length != no_length) {
        format++;
      }

      needed_specifier(args, format, str, params, &i);
    } else {
      str[i++] = *format;

      if (*format == '%') {
        format++;
      }
    }

    format++;
  }
}

void needed_specifier(va_list *args, const char *format, char *str,
                      form *params, int *i) {
  if (s21_strchr("cdiufsxXopgGeE", *format)) {
    if (params->accurasy == -1) {
      params->accurasy = default_accurasy(*format);
    }

    char *buffer = (char *)calloc(MAX_BUFFER_SIZE, sizeof(char));
    pull_string(args, *params, *format, &buffer);
    add_string(str, buffer, i);

    free(buffer);
  }
}

Length parser_length(char len) {
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

int default_accurasy(char symb) {
  int accurasy;
  if (s21_strchr("eEfgG", symb)) {
    accurasy = 6;
  } else if (symb == 's') {
    accurasy = 0;
  } else {
    accurasy = 1;
  }

  return accurasy;
}

void pull_string(va_list *input, form params, char specifier, char **buffer) {
  int sign = 0;
  switch (specifier) {
    case 'c':
      parser_c(input, buffer, params);
      break;
    case 'd':
    case 'i':
      parser_d(input, buffer, params, &sign);
      break;
    case 'u':
      parser_u(input, buffer, params, &sign);
      break;
    case 'f':
      parser_f(input, buffer, params, &sign);
      break;
    case 's':
      parser_s(input, buffer, params);
      break;
    case 'x':
    case 'X':
      convert_int_to_hex(*input, buffer, params, specifier);
      break;
    case 'o':
      convert_int_to_oct(*input, buffer, params);
      break;
    case 'p':
      convert_ptr_to_str(*input, buffer, params);
      break;
    case 'g':
    case 'G':
      parser_g(input, buffer, params, specifier, &sign);
      break;
    case 'e':
    case 'E':
      parser_e(input, buffer, params, specifier, &sign);
      break;
  }
}
void parser_c(const va_list *input, char **buffer, form params) {
  if (params.length == long_int) {
    long_char_to_str(*input, buffer, params);
  } else {
    char_to_str(*input, buffer, params);
  }
}

void parser_d(const va_list *input, char **buffer, form params, int *sign) {
  if (params.length == short_int) {
    *sign = convert_short_int_to_str(*input, buffer, params);
  } else if (params.length == long_int) {
    *sign = convert_long_int_to_str(*input, buffer, params);
  } else {
    *sign = convert_int_to_str(*input, buffer, params);
  }
}

void parser_u(const va_list *input, char **buffer, form params, int *sign) {
  if (params.length == short_int) {
    *sign = convert_unsign_short_int_to_str(*input, buffer, params);
  } else if (params.length == long_int) {
    *sign = convert_unsign_long_int_to_str(*input, buffer, params);
  } else {
    *sign = convert_unsign_int_to_str(*input, buffer, params);
  }
}

void parser_f(va_list *input, char **buffer, form params, int *sign) {
  if (params.length == long_double) {
    *sign = convert_long_double_to_str(input, buffer, params);
  } else {
    *sign = convert_double_to_str(input, buffer, params);
  }
}
void parser_s(const va_list *input, char **buffer, form params) {
  if (params.length == long_int) {
    long_str_to_str(buffer, *input, params);
  } else {
    str_to_str(buffer, *input, params);
  }
}
void parser_g(va_list *input, char **buffer, form params, char specifier,
              int *sign) {
  if (params.length == long_double) {
    *sign = convert_long_double_to_g(input, buffer, params, specifier);
  } else {
    *sign = convert_double_to_g(input, buffer, params, specifier);
  }
}

void parser_e(va_list *input, char **buffer, form params, char specifier,
              int *sign) {
  if (params.length == long_double) {
    *sign = convert_long_double_to_e(input, buffer, params, specifier);
  } else {
    *sign = convert_double_to_e(input, buffer, params, specifier);
  }
}

void parser_n(const va_list *input, form params, const char *buffer) {
  if (params.length == short_int) {
    short *n = va_arg(*input, short *);
    *n = s21_strlen(buffer);
  } else if (params.length == long_int) {
    long int *n = va_arg(*input, long int *);
    *n = s21_strlen(buffer);
  } else {
    int *n = va_arg(*input, int *);
    *n = s21_strlen(buffer);
  }
}

void insert_sign(char **buffer, form params, int sign) {
  const char *insert_str =
      (sign != 0) ? "-" : ((params.flags & (1)) ? "+" : S21_NULL);

  if (insert_str != S21_NULL) {
    char *temp = s21_insert(*buffer, insert_str, 0);
    free(*buffer);
    *buffer = temp;
  }
}

void char_to_str(const va_list input, char **buffer, form params) {
  char c = va_arg(input, int);

  (*buffer)[0] = c;

  work_with_char(buffer, params);
}

void long_char_to_str(const va_list input, char **buffer, form params) {
  wint_t c = va_arg(input, wint_t);

  (*buffer)[0] = c;

  work_with_char(buffer, params);
}

void work_with_char(char **buffer, form params) {
  int count = 1;
  char *old_ptr = *buffer;
  while (params.width - count > 0) {
    *buffer = s21_insert(*buffer, " ", 0);

    free(old_ptr);
    old_ptr = *buffer;
    count++;
  }

  flags_char(buffer, params);
}

void str_to_str(char **buffer, const va_list input, form params) {
  const char *str = va_arg(input, char *);
  s21_strcpy(*buffer, str);

  work_with_str(buffer, params);
}

void long_str_to_str(char **buffer, const va_list input, form params) {
  const wchar_t *str = va_arg(input, wchar_t *);

  int i = 0;
  while (str[i] != '\0') {
    i++;
  }

  for (int j = 0; j < i; j++) {
    (*buffer)[j] = str[j];
  }

  work_with_str(buffer, params);
}

void work_with_str(char **buffer, form params) {
  int count = s21_strlen(*buffer);
  char *old_ptr = *buffer;
  while (params.width - count > 0) {
    *buffer = s21_insert(*buffer, " ", 0);

    free(old_ptr);
    old_ptr = *buffer;
    count++;
  }

  if (params.accurasy) {
    (*buffer)[params.accurasy] = '\0';
  }
  if (params.point_width) {
    (*buffer)[params.point_width] = '\0';
  }

  flags_str(buffer, params);
}

int convert_str_to_int(const char **format) {
  int digit = *(*format)++ - '0';
  while (is_digit(*(*format))) {
    digit *= 10;
    digit += *(*format)++ - '0';
  }

  return digit;
}

int is_digit(char symb) { return symb >= '0' && symb <= '9' ? 1 : 0; }

void add_string(char *str, const char *buffer, int *index) {
  s21_strcpy(str + *index, buffer);
  *index += s21_strlen(buffer);
}

void convert_ptr_to_str(va_list input, char **buffer, form params) {
  unsigned long int n = (unsigned long int)va_arg(input, void *);

  int j = 0;
  while (n) {
    int digit = (n % 16);
    if (digit < 10) {
      (*buffer)[j++] = digit + '0';
    } else {
      (*buffer)[j++] = digit - 10 + 'a';
    }

    n /= 16;
  }
  (*buffer)[j++] = 'x';
  (*buffer)[j++] = '0';

  reverse_str(*buffer, j);

  (*buffer)[j] = '\0';

  flags_ptr(buffer, params);
}

void convert_int_to_oct(va_list input, char **buffer, form params) {
  unsigned long long n = va_arg(input, unsigned long long);

  int j = 0, size = 0, count = 0;
  while (n) {
    (*buffer)[j++] = n % 8 + '0';
    n /= 8;
    size++;
    count++;
  }

  while (params.accurasy - count > 0) {
    (*buffer)[j++] = '0';
    count++;
  }

  reverse_str(*buffer, j);

  (*buffer)[j] = '\0';

  if (params.flags & (1 << 2)) {
    char *temp = s21_insert(*buffer, "0", 0);
    free(*buffer);
    *buffer = temp;
  }

  flags(size, buffer, params, 'o');
}

void convert_int_to_hex(va_list input, char **buffer, form params,
                        char specifier) {
  unsigned long long n = va_arg(input, unsigned long long);

  int j = 0;
  int size = 0;
  int count = 0;
  while (n) {
    int digit = (n % 16);
    if (digit < 10) {
      (*buffer)[j++] = digit + '0';
    } else {
      if (specifier == 'X') {
        (*buffer)[j++] = digit - 10 + 'A';
      } else {
        (*buffer)[j++] = digit - 10 + 'a';
      }
    }

    n /= 16;
    size++;
    count++;
  }

  while (params.accurasy - count > 0) {
    (*buffer)[j++] = '0';
    count++;
  }
  reverse_str(*buffer, j);

  (*buffer)[j] = '\0';

  if (params.flags & (1 << 2)) {
    if (specifier == 'x') {
      char *temp = s21_insert(*buffer, "0x", 0);
      free(*buffer);
      *buffer = temp;
    } else if (specifier == 'X') {
      char *temp = s21_insert(*buffer, "0X", 0);
      free(*buffer);
      *buffer = temp;
    }
  }

  flags(size, buffer, params, 'x');
}

int convert_double_to_g(va_list *input, char **buffer, form params,
                        char specifier) {
  double n = va_arg(*input, double);

  return divide_double(n, buffer, params, specifier);
}

int convert_long_double_to_g(va_list *input, char **buffer, form params,
                             char specifier) {
  long double n = va_arg(*input, long double);

  return divide_double(n, buffer, params, specifier);
}

int divide_double(long double n, char **buffer, form params, char specifier) {
  int sign = 0;
  int width = params.accurasy ? params.accurasy : params.point_width;
  if (fabsl(n) < pow(10, -4) || fabsl(n) >= pow(10, width)) {
    sign = convert_double_to_e_add(n, buffer, params, specifier, 2);
  } else {
    sign = convert_double_to_str_add(n, buffer, params, specifier);
  }
  return sign;
}

int convert_double_to_e(va_list *input, char **buffer, form params,
                        char specifier) {
  double n = va_arg(*input, double);

  return convert_double_to_e_add(n, buffer, params, specifier, 0);
}

int convert_long_double_to_e(va_list *input, char **buffer, form params,
                             char specifier) {
  long double n = va_arg(*input, long double);

  return convert_double_to_e_add(n, buffer, params, specifier, 1);
}

int convert_double_to_e_add(long double n, char **buffer, form params,
                            char specifier, int key) {
  int sign = 0;
  if (n < 0) {
    n *= -1;
    sign = 1;
  }

  int sign_pow = 0;
  if (n < 1) {
    sign_pow = 1;
  }

  int prime = 0;
  int width = work_with_double_e(n, &prime, buffer, params, key);

  int shift = 0;
  if (specifier == 'g' || specifier == 'G') {
    (*buffer)[width] = '\0';
    shift = 1;
  }

  char *buffer_prime =
      fill_buffer_e(buffer, width, shift, specifier, prime, sign_pow);

  char *temp = s21_insert(*buffer, buffer_prime, s21_strlen(*buffer));
  free(*buffer);
  *buffer = temp;

  free(buffer_prime);

  insert_sign(buffer, params, sign);

  flags(s21_strlen(*buffer), buffer, params, specifier);

  return sign;
}

char *fill_buffer_e(char **buffer, int width, int shift, char specifier,
                    int prime, int sign_pow) {
  char *temp1 = s21_insert(*buffer, ".", 1);
  free(*buffer);
  *buffer = temp1;

  char *temp2 = s21_insert(*buffer, "e+", 2 + width - shift);
  free(*buffer);
  *buffer = temp2;

  if (specifier == 'E' || specifier == 'G') {
    (*buffer)[2 + width - shift] = 'E';
  }

  if (sign_pow) {
    (*buffer)[3 + width - shift] = '-';
  }

  char *buffer_prime = (char *)calloc(MAX_BUFFER_SIZE, sizeof(char));
  int t = 0;
  while (prime % 10 != 0) {
    buffer_prime[t++] = (prime % 10) + '0';
    prime /= 10;
  }
  if (t == 1) {
    buffer_prime[t++] = '0';
  }
  reverse_str(buffer_prime, t);

  return buffer_prime;
}

int work_with_double_e(long double n, int *prime, char **buffer, form params,
                       int key) {
  int width = params.accurasy ? params.accurasy : params.point_width;

  whole_part_e(n, buffer, prime, width, key);

  return width;
}

void whole_part_e(long double n, char **buffer, int *prime, int width,
                  int key) {
  if ((long int)n - n) {
    while ((long int)n == 0) {
      (*prime)++;
      n *= 10;
    }
  }

  while ((long int)n / 10 != 0) {
    (*prime)++;
    n /= 10;
  }

  int i = 0;
  int end = key == 2 ? width - 1 : width;
  for (; i < end; i++) {
    (*buffer)[i] = (long int)n % 10 + '0';
    n *= 10;
  }

  (*buffer)[i] = (int)(fmodl(roundl(n), 10)) % 10 + '0';
}

void whole_part_f(long double n, char **buffer, int *i, int *prime) {
  long long whole_part = (long long)n;
  if (whole_part == 0) {
    (*buffer)[(*i)++] = '0';
  } else {
    while (whole_part > 0) {
      (*buffer)[(*i)++] = whole_part % 10 + '0';
      whole_part /= 10;
      (*prime)++;
    }
  }
}

int convert_double_to_str(va_list *input, char **buffer, form params) {
  double n = va_arg(*input, double);

  return convert_double_to_str_add(n, buffer, params, 'f');
}

int convert_long_double_to_str(va_list *input, char **buffer, form params) {
  long double n = va_arg(*input, long double);

  return convert_double_to_str_add(n, buffer, params, 'f');
}

int convert_double_to_str_add(long double n, char **buffer, form params,
                              char specifier) {
  int sign = 0;
  if (n < 0) {
    n *= -1;
    sign = 1;
  }

  int prime = 0;
  int width = work_with_double(n, &prime, buffer, specifier, params);

  if (specifier != 'g' && specifier != 'G') {
    prime = 0;
  } else {
    (*buffer)[width + 1] = '\0';
  }

  insert_sign(buffer, params, sign);

  flags(s21_strlen(*buffer), buffer, params, specifier);

  return sign;
}

int work_with_double(long double n, int *prime, char **buffer, char specifier,
                     form params) {
  int i = 0;
  whole_part_f(n, buffer, &i, prime);

  reverse_str(*buffer, i);

  long double n_fract = n - (long long)n;
  int width = params.accurasy ? params.accurasy : params.point_width;
  if ((width == *prime && specifier != 'f') ||
      (width == 0 && specifier == 'f')) {
    i--;
    (*buffer)[i] = (*buffer)[i] - '0' + (int)roundl(n_fract) + '0';
    i++;
    (*buffer)[i++] = '\0';
  } else {
    (*buffer)[i++] = '.';
  }
  if (width < 0) {
    width = 6;
  }
  if (width > 14 && (specifier == 'g' || specifier == 'G') &&
      params.length != long_double) {
    width = 14;
    if (specifier == 'G') {
      width = 17;
    }
  }

  int digit;
  for (int j = 0; j < width; j++) {
    n_fract *= 10;
    if ((j == width - *prime - 1 && (specifier == 'g' || specifier == 'G')) ||
        (j == width - 1 && specifier == 'f')) {
      digit = (int)(roundl(n_fract));
    } else {
      digit = (int)n_fract;
    }
    (*buffer)[i++] = (digit % 10) + '0';
    n_fract -= digit;
  }

  return width;
}

int convert_int_to_str(const va_list input, char **buffer, form params) {
  int n = va_arg(input, int);

  return work_with_int(n, buffer, params);
}

int convert_short_int_to_str(const va_list input, char **buffer, form params) {
  short n = (short)va_arg(input, int);

  return work_with_int(n, buffer, params);
}

int convert_long_int_to_str(const va_list input, char **buffer, form params) {
  long int n = va_arg(input, long int);

  return work_with_int(n, buffer, params);
}

int work_with_int(long int n, char **buffer, form params) {
  int sign = 0;
  if (n < 0) {
    n *= -1;
    sign = 1;
  }

  int j = 0, count = 0, size = 0;
  while (n) {
    (*buffer)[j++] = (n % 10) + '0';
    n /= 10;
    count++;
    size++;
  }

  while (params.accurasy - count > 0) {
    (*buffer)[j++] = '0';
    count++;
  }
  reverse_str(*buffer, j);

  (*buffer)[j] = '\0';

  insert_sign(buffer, params, sign);

  flags(size, buffer, params, 'd');

  return sign;
}

int convert_unsign_int_to_str(const va_list input, char **buffer, form params) {
  unsigned int n = va_arg(input, unsigned int);

  return work_with_int(n, buffer, params);
}

int convert_unsign_short_int_to_str(const va_list input, char **buffer,
                                    form params) {
  unsigned short n = (unsigned short)va_arg(input, unsigned int);

  return work_with_int(n, buffer, params);
}

int convert_unsign_long_int_to_str(const va_list input, char **buffer,
                                   form params) {
  unsigned long int n = va_arg(input, unsigned long int);

  return work_with_int(n, buffer, params);
}

void reverse_str(char *buffer, int j) {
  for (int i = 0; i < j / 2; i++) {
    char temp = buffer[i];
    buffer[i] = buffer[j - i - 1];
    buffer[j - i - 1] = temp;
  }
}
