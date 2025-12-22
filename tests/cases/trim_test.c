#include "../../s21_string.h"
#include "s21_test_string.h"

START_TEST(simple_string) {
  const char *str = {
      "acdrhj1234567890String from English translate on Russian like a нитки "
      "but sound like стринги what means thongsdhjrca9807465321"};
  char *str_check = {
      "String from English translate on Russian like a нитки but sound like "
      "стринги what means thongs"};
  void *ptr = NULL;
  ptr = s21_trim(str, "acdrhj1234567890");
  ck_assert_str_eq(ptr, str_check);
  free(ptr);
}
END_TEST

START_TEST(space_in_space) {
  const char *str = {"   "};
  char *str_check = {""};
  void *ptr = NULL;
  ptr = s21_trim(str, " ");
  ck_assert_str_eq(ptr, str_check);
  free(ptr);
}
END_TEST

START_TEST(space) {
  const char *str = {"  "};
  char *str_check = {""};
  void *ptr = NULL;
  ptr = s21_trim(str, " ");
  ck_assert_str_eq(ptr, str_check);
  free(ptr);
}
END_TEST

/*
START_TEST(null){
  char *str = NULL;
  char *str_check = NULL;
  void *ptr = NULL;
  ptr = s21_trim(str, " ");
  ck_assert_str_eq(ptr, str_check);
  free(ptr);
}
END_TEST
*/

Suite *suite_trim() {
  Suite *s = suite_create("trim_upd");
  TCase *tc_average = tcase_create("average");

  // average tests
  tcase_add_test(tc_average, simple_string);
  tcase_add_test(tc_average, space_in_space);
  tcase_add_test(tc_average, space);
  // tcase_add_test(tc_average, null);
  suite_add_tcase(s, tc_average);

  // aditional tests

  return s;
}
