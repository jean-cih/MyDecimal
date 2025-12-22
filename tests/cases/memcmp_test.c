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
  size_t size = strlen(str);
  // s21_size_t s21_size = strlen(str);
  for (int i = 0; i < (int)size; i++) {
    ck_assert_int_eq(s21_memcmp(str, str1, i), memcmp(str, str1, i));
  }
}
END_TEST

START_TEST(lt_string) {
  const char *str = {
      "String from English translate on Russian like a нитки but sound like "
      "стринги what means thongs"};
  const char *str1 = {
      "String from English translate on Russian like a нитки but sound like "
      "стринги what means"};
  size_t size = strlen(str);
  for (int i = 0; i < (int)size; i++) {
    ck_assert_int_eq(s21_memcmp(str, str1, i), memcmp(str, str1, i));
  }
}
END_TEST

START_TEST(gt_string) {
  const char *str = {
      "String from English translate on Russian like a нитки but sound like "
      "стринги what means"};
  const char *str1 = {
      "String from English translate on Russian like a нитки but sound like "
      "стринги what means thongs"};
  size_t size = strlen(str);
  for (int i = 0; i < (int)size; i++) {
    ck_assert_int_eq(s21_memcmp(str, str1, i), memcmp(str, str1, i));
  }
}
END_TEST

START_TEST(eq_void) {
  const void *str = {
      "String from English translate on Russian like a нитки but sound like "
      "стринги what means thongs"};
  const void *str1 = {
      "String from English translate on Russian like a нитки but sound like "
      "стринги what means thongs"};
  size_t size = strlen(str);
  for (int i = 0; i < (int)size; i++) {
    ck_assert_int_eq(s21_memcmp(str, str1, i), memcmp(str, str1, i));
  }
}
END_TEST

START_TEST(non_eq_string) {
  const char *str = {
      "String from Engaafasfsh translate on Russian like a нитки but sound "
      "like стринги what means thongs"};
  const char *str1 = {
      "String from English translate on Russian like a нитки but sound like "
      "стринги what means thongs"};
  // size_t size = strlen(str);
  if (_i) {
    // for(int i = 0; i < (int)size; i++){
    ck_assert_int_eq(s21_memcmp(str, str1, _i), memcmp(str, str1, _i));
    // ck_assert_int_eq(i, i+1);
  }
}
END_TEST

START_TEST(exit_from_string) {
  const char *str = {
      "String from English translate on Russian like a нитки but sound like "
      "стринги what means thongs"};
  const char *str1 = {
      "String from English translate on Russian like a нитки but sound like "
      "стринги what means thongs"};
  for (int i = 100; i < 200; i++) {
    ck_assert_int_eq(s21_memcmp(str, str1, i), memcmp(str, str1, i));
  }
}
END_TEST

Suite *suite_memcmp() {
  Suite *s = suite_create("memcmp_upd");
  TCase *tc_average = tcase_create("average");
  TCase *tc_aditional = tcase_create("aditional");

  // average tests
  tcase_add_test(tc_average, eq_string);
  tcase_add_test(tc_average, lt_string);
  tcase_add_test(tc_average, gt_string);
  tcase_add_loop_test(tc_average, non_eq_string, 0, 100);
  suite_add_tcase(s, tc_average);

  // aditional tests
  tcase_add_test(tc_aditional, eq_void);
  tcase_add_test(tc_aditional, exit_from_string);
  suite_add_tcase(s, tc_aditional);

  return s;
}
