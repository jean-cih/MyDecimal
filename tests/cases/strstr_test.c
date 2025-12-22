#include "../../s21_string.h"
#include "s21_test_string.h"

START_TEST(simple_string) {
  char *str = {
      "String from English translate on Russian like a нитки but sound like "
      "стринги what means thongs"};
  const char *str1 = {
      "String from English translate on Russian like a нитки but sound like "
      "стринги what means thongs"};
  // void *ptr = NULL;
  // size_t size = strlen(str);
  // s21_size_t s21_size = strlen(str);
  // for(int i = 0; i < 128; i++){
  ck_assert_pstr_eq(s21_strstr(str, str1), strstr(str, str1));
  //}
}
END_TEST

START_TEST(simple_string_1) {
  char *str = {
      "String from English translate on Russian like a нитки but sound like "
      "стринги what means thongs"};
  const char *str1 = "Russian";
  // void *ptr = NULL;
  // size_t size = strlen(str);
  // s21_size_t s21_size = strlen(str);
  // for(int i = 0; i < 128; i++){
  ck_assert_pstr_eq(s21_strstr(str, str1), strstr(str, str1));
  //}
}
END_TEST

START_TEST(empty_string) {
  char *str = "";
  const char *str1 = {
      "String from English translate on Russian like a нитки but sound like "
      "стринги what means thongs"};
  ck_assert_pstr_eq(s21_strstr(str, str1), strstr(str, str1));
}
END_TEST

START_TEST(empty_pattern) {
  char *str = {
      "String from English translate on Russian like a нитки but sound like "
      "стринги what means thongs"};
  const char *str1 = "";
  ck_assert_pstr_eq(s21_strstr(str, str1), strstr(str, str1));
}
END_TEST

START_TEST(empty_all) {
  char *str = "";
  const char *str1 = "";
  ck_assert_pstr_eq(s21_strstr(str, str1), strstr(str, str1));
}
END_TEST

Suite *suite_strstr() {
  Suite *s = suite_create("strstr_upd");
  TCase *tc_average = tcase_create("average");

  // average tests
  tcase_add_test(tc_average, simple_string);
  tcase_add_test(tc_average, simple_string_1);
  tcase_add_test(tc_average, empty_string);
  tcase_add_test(tc_average, empty_pattern);
  tcase_add_test(tc_average, empty_all);
  suite_add_tcase(s, tc_average);

  // aditional tests

  return s;
}
