#include "../../s21_string.h"
#include "s21_test_string.h"

START_TEST(eq_string) {
  char str[200] =
      "String from English translate on Russian like a нитки but sound like "
      "стринги what means thongs";
  char str1[200] =
      "String from English translate on Russian like a нитки but sound like "
      "стринги what means thongs";
  const char *delim =
      "String from English translate on Russian like a нитки but sound like "
      "стринги what means thongs";
  char *ptr;
  char *ptr1;
  ptr = s21_strtok(str, delim);
  ptr1 = strtok(str1, delim);
  if (ptr && ptr1) ck_assert_str_eq(ptr, ptr1);
  while (ptr || ptr1) {
    ptr = s21_strtok(S21_NULL, delim);
    ptr1 = strtok(S21_NULL, delim);
    ck_assert_str_eq(ptr, ptr1);
  }
}
END_TEST

START_TEST(punctuation_string) {
  char str[200] =
      "String. from English, translate on Russian like/ a нитки but, sound "
      "like стринги what means. thongs";
  char str1[200] =
      "String. from English, translate on Russian like/ a нитки but, sound "
      "like стринги what means. thongs";
  const char *delim = ".,/";
  char *ptr;
  char *ptr1;
  ptr = s21_strtok(str, delim);
  ptr1 = strtok(str1, delim);
  ck_assert_str_eq(ptr, ptr1);
  while (ptr || ptr1) {
    ptr = s21_strtok(S21_NULL, delim);
    ptr1 = strtok(S21_NULL, delim);
    if (ptr && ptr1) ck_assert_str_eq(ptr, ptr1);
  }
}
END_TEST

START_TEST(empty_string) {
  char str[200] = "";
  char str1[200] = "";
  const char *delim = "/.,";
  char *ptr;
  char *ptr1;
  ptr = s21_strtok(str, delim);
  ptr1 = strtok(str1, delim);
  if (ptr && ptr1) ck_assert_str_eq(ptr, ptr1);
  while (ptr || ptr1) {
    ptr = s21_strtok(S21_NULL, delim);
    ptr1 = strtok(S21_NULL, delim);
    if (ptr && ptr1) ck_assert_str_eq(ptr, ptr1);
  }
}
END_TEST

START_TEST(empty_delim) {
  char str[200] =
      "String. from English, translate on Russian like/ a нитки but, sound "
      "like стринги what means. thongs";
  char str1[200] =
      "String. from English, translate on Russian like/ a нитки but, sound "
      "like стринги what means. thongs";
  const char *delim = "";
  char *ptr;
  char *ptr1;
  ptr = s21_strtok(str, delim);
  ptr1 = strtok(str1, delim);
  if (ptr && ptr1) ck_assert_str_eq(ptr, ptr1);
  while (ptr || ptr1) {
    ptr = s21_strtok(S21_NULL, delim);
    ptr1 = strtok(S21_NULL, delim);
    if (ptr && ptr1) ck_assert_str_eq(ptr, ptr1);
  }
}
END_TEST

START_TEST(only_delim) {
  char str[200] = " ,.//., ";
  char str1[200] = " ,.//., ";
  const char *delim = " ,./";
  char *ptr;
  char *ptr1;
  ptr = s21_strtok(str, delim);
  ptr1 = strtok(str1, delim);
  if (ptr && ptr1) ck_assert_str_eq(ptr, ptr1);
  while (ptr || ptr1) {
    ptr = s21_strtok(S21_NULL, delim);
    ptr1 = strtok(S21_NULL, delim);
    if (ptr && ptr1) ck_assert_str_eq(ptr, ptr1);
  }
}
END_TEST

START_TEST(double_delim) {
  char str[200] =
      "String  from  English  translate  on  Russian  like  a  нитки  but  "
      "sound  like  стринги  what  means  thongs";
  char str1[200] =
      "String from English translate on Russian like a нитки but sound like "
      "стринги what means thongs";
  const char *delim = " ";
  char *ptr;
  char *ptr1;
  ptr = s21_strtok(str, delim);
  ptr1 = strtok(str1, delim);
  ck_assert_str_eq(ptr, ptr1);
  while (ptr || ptr1) {
    ptr = s21_strtok(S21_NULL, delim);
    ptr1 = strtok(S21_NULL, delim);
    if (ptr && ptr1) ck_assert_str_eq(ptr, ptr1);
  }
}
END_TEST

START_TEST(above_delims) {
  char str[200] = " String ";
  char str1[200] = " String ";
  const char *delim = " ";
  char *ptr;
  char *ptr1;
  ptr = s21_strtok(str, delim);
  ptr1 = strtok(str1, delim);
  ck_assert_str_eq(ptr, ptr1);
  while (ptr != NULL || ptr1 != NULL) {
    ptr = s21_strtok(S21_NULL, delim);
    ptr1 = strtok(S21_NULL, delim);
    if (ptr && ptr1) ck_assert_str_eq(ptr, ptr1);
  }
}
END_TEST

Suite *suite_strtok() {
  Suite *s = suite_create("strtok_upd");
  TCase *tc_average = tcase_create("average");

  // average tests
  tcase_add_test(tc_average, eq_string);
  tcase_add_test(tc_average, punctuation_string);
  tcase_add_test(tc_average, empty_string);
  tcase_add_test(tc_average, empty_delim);
  tcase_add_test(tc_average, only_delim);
  tcase_add_test(tc_average, double_delim);
  tcase_add_test(tc_average, above_delims);
  suite_add_tcase(s, tc_average);

  // aditional tests

  return s;
}
