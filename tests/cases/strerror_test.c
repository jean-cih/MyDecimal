#include "../../s21_string.h"
#include "s21_test_string.h"

START_TEST(eq_string) { ck_assert_str_eq(strerror(_i), s21_strerror(_i)); }
END_TEST

Suite *suite_strerror() {
  Suite *s = suite_create("strerror");
  TCase *tc_average = tcase_create("average");

  // average tests
  tcase_add_loop_test(tc_average, eq_string, 0, 135);
  suite_add_tcase(s, tc_average);
  // aditional tests

  return s;
}
