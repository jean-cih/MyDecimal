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
    ck_assert_int_eq(s21_strncmp(str, str1, i), strncmp(str, str1, i));
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
    ck_assert_int_eq(s21_strncmp(str, str1, i), strncmp(str, str1, i));
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
  // void *ptr = NULL;
  size_t size = strlen(str);
  // s21_size_t s21_size = strlen(str);
  for (int i = 0; i < (int)size; i++) {
    ck_assert_int_eq(s21_strncmp(str, str1, i), strncmp(str, str1, i));
  }
}
END_TEST

START_TEST(unsigned_compare_string) {
  char *str = malloc(129 * sizeof(char));
  const char *str1 = malloc(129 * sizeof(char));
  for (int i = 0; i < 64; i++) {
    str[i] = i;
    str[128 - i] = 128 - i;
  }
  size_t size = strlen(str);
  for (int i = 0; i < (int)size; i++) {
    ck_assert_int_eq(s21_strncmp(str, str1, i), strncmp(str, str1, i));
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
    ck_assert_int_eq(s21_strncmp(str, str1, i), strncmp(str, str1, i));
  }
}
END_TEST

START_TEST(non_eq_string) {
  const void *str = {
      "String from ENGLISH translate on Russian like a нитки but sound like "
      "стринги what means thongs"};
  const void *str1 = {
      "String from English translate on Russian like a нитки but sound like "
      "стринги what means thongs"};
  size_t size = strlen(str);
  for (int i = 0; i < (int)size; i++) {
    ck_assert_int_eq(s21_strncmp(str, str1, i), strncmp(str, str1, i));
  }
}
END_TEST

START_TEST(exit_from_string) {
  char *str = malloc(129 * sizeof(char));
  const char *str1 = malloc(129 * sizeof(char));
  for (int i = 0; i < 64; i++) {
    str[i] = i;
    str[128 - i] = 128 - i;
  }
  for (int i = 0; i < 200; i++) {
    ck_assert_int_eq(s21_strncmp(str, str1, i), strncmp(str, str1, i));
  }
}
END_TEST

Suite *suite_strncmp() {
  Suite *s = suite_create("strncmp_upd");
  TCase *tc_average = tcase_create("average");
  TCase *tc_aditional = tcase_create("aditional");

  // average tests
  tcase_add_test(tc_average, eq_string);
  tcase_add_test(tc_average, lt_string);
  tcase_add_test(tc_average, gt_string);
  tcase_add_test(tc_average, eq_void);
  tcase_add_test(tc_average, non_eq_string);
  suite_add_tcase(s, tc_average);

  // aditional tests
  tcase_add_test(tc_aditional, unsigned_compare_string);
  tcase_add_test(tc_aditional, exit_from_string);
  suite_add_tcase(s, tc_aditional);

  return s;
}
