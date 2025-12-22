#include "../../s21_string.h"
#include "s21_test_string.h"

START_TEST(simple_string) {
  const char *str = {
      "String from English translate on Russian like a нитки but sound like "
      "стринги what means thongs"};
  // char *s21_str = {"String from English translate on Russian like a нитки but
  // sound like стринги what means thongs"}; void *ptr = NULL; size_t size =
  // strlen(str);
  ck_assert_int_eq(s21_strlen(str), strlen(str));
  // s21_size_t s21_size = strlen(str);
  // for(int i = 0; i < 128; i++){
  // ck_assert_pstr_eq(s21_memchr(str, i, size), memchr(str, i, size));
  //}
}
END_TEST

START_TEST(empty_string) {
  const char *str = {""};
  ck_assert_int_eq(s21_strlen(str), strlen(str));
}
END_TEST

START_TEST(null_contained_string) {
  const char *str = {"\0"};
  ck_assert_int_eq(s21_strlen(str), strlen(str));
}
END_TEST

START_TEST(double_null_terminated_string) {
  const char *str = {"\0HELLO WORLD\0"};
  ck_assert_int_eq(s21_strlen(str), strlen(str));
}
END_TEST

Suite *suite_strlen() {
  Suite *s = suite_create("strlen_upd");
  TCase *tc_average = tcase_create("average");
  TCase *tc_aditional = tcase_create("aditional");

  // average tests
  tcase_add_test(tc_average, simple_string);
  suite_add_tcase(s, tc_average);

  // aditional tests
  tcase_add_test(tc_aditional, empty_string);
  tcase_add_test(tc_aditional, null_contained_string);
  tcase_add_test(tc_aditional, double_null_terminated_string);
  suite_add_tcase(s, tc_aditional);
  return s;
}
