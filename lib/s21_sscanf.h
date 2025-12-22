#ifndef S21_SSCANF_H
#define S21_SSCANF_H

//#define s21_NULL (void *)0
//#define MAXUNSIG 18446744073709551615ull
//typedef unsigned long s21_size_t;

#define MAXUNSIG 18446744073709551615ull
//#define MAXUNSIG 9223372036854775807ull
//#define MAXSHORT 140737488355328 
#define MAXLONG  9223372036854775807l

//typedef struct formatting {
//  int width;
//  Length length;
//  char sign;
//} form;


// for sscanf
int s21_sscanf(const char *str, const char *format, ...);
Length parser_length_sc(char len);
int iss_digit(char symb);
int is_space(char symb);
int convert_str_to_int_sc(const char **format);
long long my_atoi(const char **str, int *count, int width);
unsigned long long my_atoi_base(const char **str, unsigned base, int *count,
                                int width);
int scanf_cs(const char *str, va_list arguments, form params,
             const char *format, int *result);
int scanf_di(const char *str, va_list arguments, form params, int *result);
int scanf_unsig(const char *str, va_list arguments, form params,
                const char *format, int *result);
int scanf_float(const char *str, va_list arguments, form params,
                int *result);


#endif

