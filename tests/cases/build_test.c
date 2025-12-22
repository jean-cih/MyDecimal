#include "../../s21_string.h"
#include "s21_test_string.h"

START_TEST(build) { ck_assert_int_eq(1, 1); }
END_TEST

Suite *suite_build() {
  Suite *s = suite_create("build");
  TCase *tc_average = tcase_create("average");

  // average tests
  tcase_add_test(tc_average, build);
  suite_add_tcase(s, tc_average);

  // aditional tests

  return s;
}
