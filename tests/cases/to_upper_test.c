#include "../../s21_string.h"
#include "s21_test_string.h"

START_TEST(simple_string) {
  const char *str = {
      "String from English translate on Russian like a нитки but sound like "
      "стринги what means thongs"};
  char *str1 = {
      "STRING FROM ENGLISH TRANSLATE ON RUSSIAN LIKE A нитки BUT SOUND LIKE "
      "стринги WHAT MEANS THONGS"};
  for (int i = 0; i < 128; i++) {
    ck_assert_str_eq(s21_to_upper(str), str1);
  }
}
END_TEST

START_TEST(empty_string) {
  const char *str = "";
  char *str1 = "";
  for (int i = 0; i < 128; i++) {
    ck_assert_str_eq(s21_to_upper(str), str1);
  }
}
END_TEST

/*
START_TEST(null_string){
  char *str = NULL;
  char *str1 = NULL;
  for(int i = 0; i < 128; i++){
    ck_assert_str_eq(s21_to_upper(str), str1);
  }
}
END_TEST
*/

START_TEST(no_changes) {
  const char *str = "NULL";
  char *str1 = "NULL";
  for (int i = 0; i < 128; i++) {
    ck_assert_str_eq(s21_to_upper(str), str1);
  }
}
END_TEST

Suite *suite_to_upper() {
  Suite *s = suite_create("to_upper_upd");
  TCase *tc_average = tcase_create("average");

  // average tests
  tcase_add_test(tc_average, simple_string);
  tcase_add_test(tc_average, empty_string);
  // tcase_add_test(tc_average, null_string);
  tcase_add_test(tc_average, no_changes);
  suite_add_tcase(s, tc_average);

  // aditional tests

  return s;
}
