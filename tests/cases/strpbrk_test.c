#include "../../s21_string.h"
#include "s21_test_string.h"

START_TEST(eq_string) {
  const char *str = {
      "String from English translate on Russian like a нитки but sound like "
      "стринги what means thongs"};
  const char *str1 = {
      "String from English translate on Russian like a нитки but sound like "
      "стринги what means thongs"};
  // void *ptr = NULL;
  // size_t size = strlen(str);
  // s21_size_t s21_size = strlen(str);
  for (int i = 0; i < 1; i++) {
    ck_assert_pstr_eq(s21_strpbrk(str, str1), strpbrk(str, str1));
  }
}
END_TEST

START_TEST(simple_string) {
  const char *str = {
      "String from English translate on Russian like a нитки but sound like "
      "стринги what means thongs"};
  const char *str1 = "trans";
  ck_assert_pstr_eq(s21_strpbrk(str, str1), strpbrk(str, str1));
}
END_TEST

START_TEST(empty_string) {
  const char *str = "";
  const char *str1 = {
      "String from English translate on Russian like a нитки but sound like "
      "стринги what means thongs"};
  ck_assert_pstr_eq(s21_strpbrk(str, str1), strpbrk(str, str1));
}
END_TEST

START_TEST(empty_second_string) {
  const char *str =
      "String from English translate on Russian like a нитки but sound like "
      "стринги what means thongs";
  const char *str1 = "";
  ck_assert_pstr_eq(s21_strpbrk(str, str1), strpbrk(str, str1));
}
END_TEST

START_TEST(empty_all_string) {
  const char *str = "";
  const char *str1 = "";
  ck_assert_pstr_eq(s21_strpbrk(str, str1), strpbrk(str, str1));
}
END_TEST

START_TEST(no_match_string) {
  const char *str =
      "String from English translate on Russian like a нитки but sound like "
      "стринги what means thongs";
  const char *str1 = "12345678";
  ck_assert_pstr_eq(s21_strpbrk(str, str1), strpbrk(str, str1));
}
END_TEST

Suite *suite_strpbrk() {
  Suite *s = suite_create("strpbrk_upd");
  TCase *tc_average = tcase_create("average");

  // average tests
  tcase_add_test(tc_average, eq_string);
  tcase_add_test(tc_average, simple_string);
  tcase_add_test(tc_average, empty_string);
  tcase_add_test(tc_average, empty_second_string);
  tcase_add_test(tc_average, empty_all_string);
  tcase_add_test(tc_average, no_match_string);
  suite_add_tcase(s, tc_average);

  // aditional tests

  return s;
}
