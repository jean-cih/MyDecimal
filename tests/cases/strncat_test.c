#include "../../s21_string.h"
#include "s21_test_string.h"

START_TEST(simple_string) {
  const char *str = {"String from English translate on Russian "};
  const char *str1 = {"like a нитки but sound like стринги what means thongs"};
  char dest[220] = {0};
  char dest_s21[220] = {0};
  ck_assert_str_eq(s21_strncat(dest_s21, str, strlen(str)),
                   strncat(dest, str, strlen(str)));
  ck_assert_str_eq(s21_strncat(dest_s21, str1, strlen(str1)),
                   strncat(dest, str1, strlen(str1)));
}
END_TEST

START_TEST(all_char_string) {
  char *str = malloc(128 * sizeof(char));
  for (int i = 0; i < 128; i++) {
    str[i] = i;
  }
  const char *str1 = {"like a нитки but sound like стринги what means thongs"};
  char dest[200] = {0};
  char dest_s21[200] = {0};
  ck_assert_str_eq(s21_strncat(dest_s21, str, strlen(str)),
                   strncat(dest, str, strlen(str)));
  ck_assert_str_eq(s21_strncat(dest_s21, str1, strlen(str1)),
                   strncat(dest, str1, strlen(str1)));
}
END_TEST

Suite *suite_strncat() {
  Suite *s = suite_create("strncat_upd");
  TCase *tc_average = tcase_create("average");

  // average tests
  tcase_add_test(tc_average, simple_string);
  tcase_add_test(tc_average, all_char_string);
  suite_add_tcase(s, tc_average);

  // aditional tests

  return s;
}
