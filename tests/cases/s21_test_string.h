#ifndef S21_TEST_STRING_H
#define S21_TEST_STRING_H

#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <check.h>

Suite *suite_build();
Suite *suite_memchr();
Suite *suite_memcmp();
Suite *suite_memcpy();
Suite *suite_memset();
Suite *suite_strlen();
Suite *suite_strncat();
Suite *suite_strchr();
Suite *suite_strncmp();
Suite *suite_strncpy();
Suite *suite_strrchr();
Suite *suite_strcspn();
Suite *suite_strstr();
Suite *suite_strpbrk();
Suite *suite_strtok();
Suite *suite_to_upper();
Suite *suite_to_lower();
Suite *suite_insert();
Suite *suite_trim();
Suite *suite_sprintf();
Suite *suite_sscanf();
Suite *suite_strerror();
Suite *suite_maker(int i);

#endif
