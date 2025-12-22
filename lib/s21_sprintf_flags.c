#include "../s21_string.h"

int parser_flags(const char **flag_form) {
  int flag_s = 0;
  while (1) {
    switch (*(*flag_form)) {
      case '+':
        flag_s |= 1;
        break;
      case '-':
        flag_s |= 1 << 1;
        break;
      case '#':
        flag_s |= 1 << 2;
        break;
      case '0':
        flag_s |= 1 << 3;
        break;
      case ' ':
        flag_s |= 1 << 4;
        break;
      default:
        return flag_s;
    }
    (*flag_form)++;
  }
}

void flags_char(char **buffer, form params) {
  char *width_buff = (char *)calloc(MAX_BUFFER_SIZE, sizeof(char));
  for (int i = 1; i < params.width; i++) {
    width_buff[i - 1] = ' ';
  }

  if (params.flags & (1 << 1)) {
    char *temp = s21_insert(*buffer, width_buff, 1);
    free(*buffer);
    *buffer = temp;
  } else if (params.flags & (1)) {
    char *temp = s21_insert(*buffer, width_buff, 0);
    free(*buffer);
    *buffer = temp;
  }
  (*buffer)[s21_strlen(*buffer)] = '\0';

  free(width_buff);
}

void flags_str(char **buffer, form params) {
  int width = !params.accurasy ? params.width - (int)s21_strlen(*buffer)
                               : params.width - params.accurasy;

  char *width_buff = (char *)calloc(MAX_BUFFER_SIZE, sizeof(char));
  for (int i = 0; i < width; i++) {
    if (params.flags & (1 << 1)) {
      width_buff[i] = ' ';
    }
  }

  int k = params.star_width - s21_strlen(*buffer);
  for (int i = 0; i < k; i++) {
    width_buff[i] = ' ';
  }

  char *temp = s21_insert(*buffer, width_buff, 0);
  free(*buffer);
  *buffer = temp;

  free(width_buff);
}

void flags_ptr(char **buffer, form params) {
  char *width_buff = (char *)calloc(MAX_BUFFER_SIZE, sizeof(char));
  for (int i = 0; i < params.width - 14; i++) {
    width_buff[i] = ' ';
  }

  for (int i = 0; i < params.star_width - 14; i++) {
    width_buff[i] = ' ';
  }

  if (params.flags & (1 << 1)) {  //-
    char *temp = s21_insert(*buffer, width_buff, s21_strlen(*buffer));
    free(*buffer);
    *buffer = temp;
  } else {
    char *temp = s21_insert(*buffer, width_buff, 0);
    free(*buffer);
    *buffer = temp;
  }

  free(width_buff);
}

void flags(int size, char **buffer, form params, char specifier) {
  char *width_buff = (char *)calloc(MAX_BUFFER_SIZE, sizeof(char));
  for (int k = 0; k < params.width - size; k++) {
    if (params.flags & (1 << 1) || params.flags & (1) || params.width != 0) {
      width_buff[k] = ' ';
    } else if (params.flags & (1 << 3)) {
      width_buff[k] = '0';
    }
  }

  for (int i = 0; i < params.star_width - size; i++) {
    width_buff[i] = ' ';
  }

  for (int i = 0; i < params.point_width - size; i++) {
    width_buff[i] = '0';
  }

  if (params.flags & (1 << 1)) {  //-

    char *temp = s21_insert(*buffer, width_buff, size);
    free(*buffer);
    *buffer = temp;
  } else if (params.flags & (1) || params.flags & (1 << 3)) {  //+ или 0
    char *temp = s21_insert(*buffer, width_buff, 0);
    free(*buffer);
    *buffer = temp;
  } else if (params.flags & (1 << 4) &&
             s21_strchr("dfeEgG", specifier)) {  //' '
    char *temp = s21_insert(*buffer, " ", 0);
    free(*buffer);
    *buffer = temp;
  } else {
    char *temp = s21_insert(*buffer, width_buff, 0);
    free(*buffer);
    *buffer = temp;
  }

  free(width_buff);
}
