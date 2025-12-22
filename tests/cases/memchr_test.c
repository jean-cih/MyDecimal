#include "../../s21_string.h"
#include "s21_test_string.h"

START_TEST(simple_string) {
  char *str = {
      "String from English translate on Russian like a нитки but sound like "
      "стринги what means thongs"};
  // char *s21_str = {"String from English translate on Russian like a нитки but
  // sound like стринги what means thongs"}; void *ptr = NULL;
  size_t size = strlen(str);
  // s21_size_t s21_size = strlen(str);
  // for(int i = 0; i < 128; i++){
  ck_assert_pstr_eq(s21_memchr(str, _i, size), memchr(str, _i, size));
  //}
}
END_TEST

START_TEST(all_chars_static) {
  char string[128];
  for (int i = 0; i < 128; i++) {
    string[i] = i;
  }
  for (int i = 0; i < 128; i++) {
    ck_assert_pstr_eq(s21_memchr(string, i, 128), memchr(string, i, 128));
  }
}
END_TEST

START_TEST(all_chars_dinamic) {
  char *string = malloc(129 * sizeof(char));
  for (int i = 0; i < 128; i++) {
    string[i] = i;
  }
  for (int i = 0; i < 128; i++) {
    ck_assert_pstr_eq(s21_memchr(string, i, 128), memchr(string, i, 128));
  }
  // free(string);
}
END_TEST

START_TEST(empty_string_static) {
  char string[1] = {0};
  for (int i = 0; i < 128; i++) {
    ck_assert_pstr_eq(s21_memchr(string, i, 1), memchr(string, i, 1));
  }
}
END_TEST

START_TEST(empty_string_dinamic) {
  char *string = malloc(sizeof(char));
  for (int i = 0; i < 128; i++) {
    ck_assert_pstr_eq(s21_memchr(string, i, 1), memchr(string, i, 1));
  }
  // free(string);
}
END_TEST

START_TEST(null_size_string) {
  char *string = malloc(5 * sizeof(char));
  for (int i = 0; i < 128; i++) {
    ck_assert_pstr_eq(s21_memchr(string, i, 0), memchr(string, i, 0));
  }
  // free(string);
}
END_TEST

START_TEST(find_numbers) {
  int *num = malloc(22 * sizeof(int));
  for (int i = 0; i < 11; i++) {
    num[i] = i;
  }
  for (int i = 0; i < 11; i++) {
    ck_assert_pstr_eq(s21_memchr(num, i, 20), memchr(num, i, 20));
  }
  // Поиск отрицательного числа выдает сегмент
}
END_TEST

Suite *suite_memchr() {
  Suite *s = suite_create("memchr_upd");
  TCase *tc_average = tcase_create("average");
  TCase *tc_aditional = tcase_create("aditional");

  // average tests
  tcase_add_loop_test(tc_average, simple_string, 0, 128);
  tcase_add_test(tc_average, all_chars_static);
  tcase_add_test(tc_average, all_chars_dinamic);
  suite_add_tcase(s, tc_average);

  // aditional tests
  tcase_add_test(tc_aditional, empty_string_static);
  tcase_add_test(tc_aditional, empty_string_dinamic);
  tcase_add_test(tc_aditional, null_size_string);
  tcase_add_test(tc_aditional, find_numbers);
  suite_add_tcase(s, tc_aditional);

  return s;
}
