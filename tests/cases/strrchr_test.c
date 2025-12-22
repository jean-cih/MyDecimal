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
    ck_assert_pstr_eq(s21_strrchr(str, i), strrchr(str, i));
  }
}
END_TEST

START_TEST(empty_dinamic_string) {
  const char *str = malloc(150 * sizeof(char));
  for (int i = 0; i < 128; i++) {
    ck_assert_pstr_eq(s21_strrchr(str, i), strrchr(str, i));
  }
}
END_TEST

Suite *suite_strrchr() {
  Suite *s = suite_create("strrchr_upd");
  TCase *tc_average = tcase_create("average");

  // average tests
  tcase_add_test(tc_average, simple_string);
  tcase_add_test(tc_average, empty_dinamic_string);
  suite_add_tcase(s, tc_average);

  // aditional tests

  return s;
}
