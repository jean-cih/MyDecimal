#include "../../s21_string.h"
#include "s21_test_string.h"

START_TEST(eq_string) {
  char str[40] = " ";
  for (size_t i = 0; i < 128; i++) {
    ck_assert_pstr_eq(s21_memset(str, i, 35), memset(str, i, 35));
  }
}
END_TEST

START_TEST(num_test) {
  int num[] = {1, 4, 2, 6, 9, 11, 123, 124234, 34534};
  for (size_t i = 0; i < 128; i++) {
    ck_assert_pstr_eq(s21_memset(num, i, 9), memset(num, i, 9 * sizeof(int)));
  }
}
END_TEST

START_TEST(rewrite_string) {
  char str[200] = {
      "String from English translate on Russian like a нитки but sound like "
      "стринги what means thongs"};
  for (size_t i = 0; i < 128; i++) {
    ck_assert_pstr_eq(s21_memset(str, i, 105 * sizeof(char)),
                      memset(str, i, 105 * sizeof(char)));
  }
}
END_TEST

START_TEST(malloc_empty) {
  char *str = malloc(128 * sizeof(char));
  for (size_t i = 0; i < 128; i++) {
    ck_assert_pstr_eq(s21_memset(str, i, 106 * sizeof(char)),
                      memset(str, i, 106 * sizeof(char)));
  }
}
END_TEST

Suite *suite_memset() {
  Suite *s = suite_create("memset_upd");
  TCase *tc_average = tcase_create("average");
  TCase *tc_aditional = tcase_create("aditional");

  // average tests
  tcase_add_test(tc_average, eq_string);
  tcase_add_test(tc_average, rewrite_string);
  suite_add_tcase(s, tc_average);

  // aditional tests
  tcase_add_test(tc_aditional, num_test);
  tcase_add_test(tc_aditional, malloc_empty);
  suite_add_tcase(s, tc_aditional);

  return s;
}
