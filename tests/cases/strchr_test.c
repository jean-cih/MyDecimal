#include "../../s21_string.h"
#include "s21_test_string.h"

START_TEST(simple_string) {
  const char *str = {
      "String from English translate on Russian like a нитки but sound like "
      "стринги what means thongs"};
  // char *s21_str = {"String from English translate on Russian like a нитки but
  // sound like стринги what means thongs"}; void *ptr = NULL; size_t size =
  // strlen(str); s21_size_t s21_size = strlen(str);
  for (int i = 0; i < 128; i++) {
    ck_assert_pstr_eq(s21_strchr(str, i), strchr(str, i));
  }
}
END_TEST

START_TEST(over_string) {
  const char *str = {
      "String from English translate on Russian like a нитки but sound like "
      "стринги what means thongs"};
  for (int i = 0; i < 200; i++) {
    ck_assert_pstr_eq(s21_strchr(str, i), strchr(str, i));
  }
}
END_TEST

START_TEST(malloc_string) {
  const char *str = malloc(100 * sizeof(char));
  for (int i = 0; i < 128; i++) {
    ck_assert_pstr_eq(s21_strchr(str, i), strchr(str, i));
  }
}
END_TEST

Suite *suite_strchr() {
  Suite *s = suite_create("strchr_upd");
  TCase *tc_average = tcase_create("average");

  // average tests
  tcase_add_test(tc_average, simple_string);
  tcase_add_test(tc_average, over_string);
  tcase_add_test(tc_average, malloc_string);
  suite_add_tcase(s, tc_average);

  // aditional tests

  return s;
}
