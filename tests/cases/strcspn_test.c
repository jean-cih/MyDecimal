#include "../../s21_string.h"
#include "s21_test_string.h"

START_TEST(simple_string) {
  const char *str = {
      "String from English translate on Russian like a нитки but sound like "
      "стринги what means thongs"};
  char *str_pat = calloc(128, sizeof(char));
  // char *s21_str = {"String from English translate on Russian like a нитки but
  // sound like стринги what means thongs"}; void *ptr = NULL; size_t size =
  // strlen(str); s21_size_t s21_size = strlen(str);
  for (int i = 0; i < 128; i++) {
    *str_pat = i;
    ck_assert_int_eq(s21_strcspn(str, str_pat), strcspn(str, str_pat));
    str_pat++;
  }
  // free(str_pat);
}
END_TEST

START_TEST(non_contain_string) {
  const char *str = {"asdfg"};
  const char *str_pat = {"zxc"};
  ck_assert_int_eq(s21_strcspn(str, str_pat), strcspn(str, str_pat));
}
END_TEST

START_TEST(eq_string) {
  const char *str = {"asdfg"};
  const char *str_pat = {"asdfg"};
  ck_assert_int_eq(s21_strcspn(str, str_pat), strcspn(str, str_pat));
}
END_TEST

START_TEST(reverse_string) {
  const char *str = {"asdfg"};
  const char *str_pat = {"gfdsa"};
  ck_assert_int_eq(s21_strcspn(str, str_pat), strcspn(str, str_pat));
}
END_TEST

START_TEST(empty_string) {
  const char *str = {""};
  const char *str_pat = {"zxc"};
  ck_assert_int_eq(s21_strcspn(str, str_pat), strcspn(str, str_pat));
}
END_TEST

START_TEST(empty_pat) {
  const char *str = {"asdfg"};
  const char *str_pat = {""};
  ck_assert_int_eq(s21_strcspn(str, str_pat), strcspn(str, str_pat));
}
END_TEST

START_TEST(empty_all) {
  const char *str = {""};
  const char *str_pat = {""};
  ck_assert_int_eq(s21_strcspn(str, str_pat), strcspn(str, str_pat));
}
END_TEST

Suite *suite_strcspn() {
  Suite *s = suite_create("strcspn_upd");
  TCase *tc_average = tcase_create("average");

  // average tests
  tcase_add_test(tc_average, simple_string);
  tcase_add_test(tc_average, non_contain_string);
  tcase_add_test(tc_average, eq_string);
  tcase_add_test(tc_average, reverse_string);
  tcase_add_test(tc_average, empty_string);
  tcase_add_test(tc_average, empty_pat);
  tcase_add_test(tc_average, empty_all);
  suite_add_tcase(s, tc_average);

  // aditional tests

  return s;
}
