#ifndef S21_SPRINTF_H
#define S21_SPRINTF_H

#define MAX_BUFFER_SIZE 1024

typedef enum Length { short_int, long_int, long_double, no_length } Length;

typedef struct formatting {
    int width;
    int star_width;
    int point_width;
    Length length;
    int flags;
    int accurasy;
    char sign;
} form;

void convert_int_to_hex(va_list input, char **buffer, form params, char specifier);
void convert_int_to_oct(va_list input, char **buffer, form params);

int convert_double_to_e(va_list *input, char **buffer, form params, char specifier);
int convert_long_double_to_e(va_list *input, char **buffer, form params, char specifier);
int convert_double_to_e_add(long double n, char **buffer, form params, char specifier, int key);

int convert_int_to_str(const va_list input, char **buffer, form params);
int convert_long_int_to_str(const va_list input, char **buffer, form params);
int convert_short_int_to_str(const va_list input, char **buffer, form params);
int work_with_int(long int n, char **buffer, form params);

int convert_double_to_str(va_list *input, char **buffer, form params);
int convert_long_double_to_str(va_list *input, char **buffer, form params);
int convert_double_to_str_add(long double n, char **buffer, form params, char specifier);

void convert_ptr_to_str(va_list input, char **buffer, form params);
int convert_double_to_g(va_list *input, char **buffer, form params, char specifier);
int convert_long_double_to_g(va_list *input, char **buffer, form params, char specifier);

void str_to_str(char **buffer, const va_list input, form params);
void long_str_to_str(char **buffer, const va_list input, form params);
void work_with_str(char** buffer, form params);

int convert_unsign_int_to_str(const va_list input, char **buffer, form params);
int convert_unsign_short_int_to_str(const va_list input, char **buffer, form params);
int convert_unsign_long_int_to_str(const va_list input, char **buffer, form params);

int convert_str_to_int(const char **format);
void reverse_str(char *buffer, int j);
void add_string(char *str, const char *buffer, int *result);

int parser_flags(const char **flag_form);
Length parser_length(char len);
int is_digit(char symb);
int default_accurasy(char symb);
void pull_string(va_list *input, form params, char specifier, char **buffer);

void char_to_str(const va_list input, char **buffer, form params);
void long_char_to_str(const va_list input, char **buffer, form params);
void work_with_char(char **buffer, form params);


void flags(int size, char **buffer, form params, char specifier);
void flags_char(char **buffer, form params);
void flags_str(char **buffer, form params);
void flags_ptr(char **buffer, form params);

void parser_specifiers(va_list *args, const char *format, char *str, form *params);

void insert_sign(char **buffer, form params, int sign);
void parser_n(const va_list *input, form params, const char *buffer);
void parser_e(va_list *input, char **buffer, form params, char specifier, int *sign);
void parser_g(va_list *input, char **buffer, form params, char specifier, int *sign);
void parser_s(const va_list *input, char **buffer, form params);
void parser_f(va_list *input, char **buffer, form params, int *sign);
void parser_u(const va_list *input, char **buffer, form params, int *sign);
void parser_d(const va_list *input, char **buffer, form params, int *sign);
void parser_c(const va_list *input, char **buffer, form params);

int work_with_double(long double n, int *prime, char **buffer, char specifier, form params);
int work_with_double_e(long double n, int *prime, char **buffer, form params, int key);
void whole_part_e(long double n, char **buffer, int *prime, int width, int key);
void whole_part_f(long double n, char **buffer, int *i, int *prime);
int divide_double(long double n, char **buffer, form params, char specifier);
void needed_specifier(va_list *args, const char *format, char *str, form *params, int *i);
char  *fill_buffer_e(char **buffer, int width, int shift, char specifier, int prime, int sign_pow);

#endif
