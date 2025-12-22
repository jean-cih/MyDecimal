#include "../../s21_string.h"
#include "s21_test_string.h"

START_TEST(eq_string) {
  const char *str = {
      "String from English translate on Russian like a нитки but sound like "
      "стринги what means thongs"};
  size_t size = strlen(str);
  for (size_t i = 0; i < size; i++) {
    char copy[320] = {0};
    char s21_copy[320] = {0};
    ck_assert_pstr_eq(s21_memcpy(s21_copy, str, i), memcpy(copy, str, i));
  }
}
END_TEST

START_TEST(into_string) {
  const char *str = {
      "String from English translate on Russian like a нитки but sound like "
      "стринги what means thongs"};
  size_t size = strlen(str);
  for (size_t i = 0; i < size; i++) {
    char copy[320] = "str";
    char s21_copy[320] = "str";
    ck_assert_pstr_eq(s21_memcpy(s21_copy, str, i), memcpy(copy, str, i));
  }
}
END_TEST

START_TEST(over_len_string) {
  const char *str = {
      "String from English translate on Russian like a нитки but sound like "
      "стринги what means thongs"};
  // size_t size = strlen(str);
  for (size_t i = 0; i < 200; i++) {
    char copy[321] = "str";
    char s21_copy[321] = "str";
    ck_assert_pstr_eq(s21_memcpy(s21_copy, str, i), memcpy(copy, str, i));
  }
}
END_TEST

Suite *suite_memcpy() {
  Suite *s = suite_create("memcpy_upd");
  TCase *tc_average = tcase_create("average");

  // average tests
  tcase_add_test(tc_average, eq_string);
  tcase_add_test(tc_average, into_string);
  tcase_add_test(tc_average, over_len_string);
  suite_add_tcase(s, tc_average);

  // aditional tests

  return s;
}
