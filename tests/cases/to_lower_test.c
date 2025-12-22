#include "../../s21_string.h"
#include "s21_test_string.h"

START_TEST(simple_string) {
  const char *str = {
      "STRING FROM ENGLISH TRANSLATE ON RUSSIAN LIKE A нитки BUT SOUND LIKE "
      "стринги WHAT MEANS THONGS"};
  char *str1 = {
      "string from english translate on russian like a нитки but sound like "
      "стринги what means thongs"};
  ck_assert_str_eq(s21_to_lower(str), str1);
}
END_TEST

START_TEST(empty_string) {
  const char *str = "";
  char *str1 = "";
  ck_assert_str_eq(s21_to_lower(str), str1);
}
END_TEST

START_TEST(no_changes) {
  const char *str = "null";
  char *str1 = "null";
  ck_assert_str_eq(s21_to_lower(str), str1);
}
END_TEST

Suite *suite_to_lower() {
  Suite *s = suite_create("to_lower_upd");
  TCase *tc_average = tcase_create("average");

  // average tests
  tcase_add_test(tc_average, simple_string);
  tcase_add_test(tc_average, empty_string);
  // tcase_add_test(tc_average, null_string);
  tcase_add_test(tc_average, no_changes);
  suite_add_tcase(s, tc_average);

  // aditional tests

  return s;
}
