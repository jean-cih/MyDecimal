#include "../../s21_string.h"
#include "s21_test_string.h"

START_TEST(start_string) {
  char *str = {
      "String from English translate on Russian like a нитки but sound like "
      "стринги what means thongs"};
  const char *str_copy = {
      " from English translate on Russian like a нитки but sound like стринги "
      "what means thongs"};
  const char str_past[120] = "String";

  ck_assert_pstr_eq(s21_insert(str_past, str_copy, strlen(str_past)), str);
}
END_TEST

START_TEST(end_string) {
  char *str = {
      "String from English translate on Russian like a нитки but sound like "
      "стринги what means thongs"};
  const char *str_copy = {" thongs"};
  const char str_past[120] =
      "String from English translate on Russian like a нитки but sound like "
      "стринги what means";
  ck_assert_pstr_eq(s21_insert(str_past, str_copy, strlen(str_past)), str);
}
END_TEST

START_TEST(empty_string) {
  char *str = NULL;
  const char *str_copy = NULL;
  const char str_past[100] = "HELLO";
  ck_assert_pstr_eq(s21_insert(str_past, str_copy, strlen(str_past)), str);
}
END_TEST

START_TEST(empty_past) {
  char *str = NULL;
  const char *str_copy = "HELLO";
  const char str_past[] = "";
  ck_assert_pstr_eq(s21_insert(str_past, str_copy, 6), str);
}
END_TEST

Suite *suite_insert() {
  Suite *s = suite_create("insert_upd");
  TCase *tc_average = tcase_create("average");
  TCase *tc_aditional = tcase_create("aditional");

  // average tests
  tcase_add_test(tc_average, start_string);
  tcase_add_test(tc_average, end_string);
  suite_add_tcase(s, tc_average);

  // aditional tests
  tcase_add_test(tc_average, empty_string);
  tcase_add_test(tc_average, empty_past);
  suite_add_tcase(s, tc_aditional);

  return s;
}
