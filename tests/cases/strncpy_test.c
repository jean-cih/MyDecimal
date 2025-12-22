#include "../../s21_string.h"
#include "s21_test_string.h"

START_TEST(eq_string) {
  const char *str = {
      "String from English translate on Russian like a нитки but sound like "
      "стринги what means thongs"};
  char copy[120];
  // char *str1 = {"String from English translate on Russian like a нитки but
  // sound like стринги what means thongs"}; void *ptr = NULL;
  size_t size = strlen(str);
  // s21_size_t s21_size = strlen(str);
  for (size_t i = 0; i < size; i++) {
    ck_assert_pstr_eq(s21_strncpy(copy, str, i), strncpy(copy, str, i));
  }
}
END_TEST

START_TEST(all_char_static_string) {
  char str[128];
  for (int i = 0; i < 128; i++) {
    str[i] = i;
  }
  char copy[120];
  size_t size = strlen(str);
  for (size_t i = 0; i < size; i++) {
    ck_assert_pstr_eq(s21_strncpy(copy, str, i), strncpy(copy, str, i));
  }
}
END_TEST

START_TEST(all_char_dinamic_string) {
  char *str = malloc(128 * sizeof(char));
  for (int i = 0; i < 128; i++) {
    str[i] = i;
  }
  char copy[120];
  size_t size = strlen(str);
  for (size_t i = 0; i < size; i++) {
    ck_assert_pstr_eq(s21_strncpy(copy, str, i), strncpy(copy, str, i));
  }
}
END_TEST

START_TEST(all_char_static_overlen_string) {
  char str[128];
  for (int i = 0; i < 128; i++) {
    str[i] = i;
  }
  char copy[120];
  for (int i = 0; i < 200; i++) {
    ck_assert_pstr_eq(s21_strncpy(copy, str, i), strncpy(copy, str, i));
  }
}
END_TEST

Suite *suite_strncpy() {
  Suite *s = suite_create("strncpy_upd");
  TCase *tc_average = tcase_create("average");

  // average tests
  tcase_add_test(tc_average, eq_string);
  tcase_add_test(tc_average, all_char_static_string);
  tcase_add_test(tc_average, all_char_dinamic_string);
  tcase_add_test(tc_average, all_char_static_overlen_string);
  suite_add_tcase(s, tc_average);

  // aditional tests

  return s;
}
