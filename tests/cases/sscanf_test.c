#include "../../s21_string.h"
#include "s21_test_string.h"

START_TEST(simple_i_str_u_test) {
  const char string[] = "50000 red balls 223372036854775807 blue balls";
  const char s21_string[] = "50000 red balls 223372036854775807 blue balls";
  char s[50], s21_s[50], str[10], s21_str[10], str2[10], s21_str2[10];
  wchar_t symb[255];
  int i, s21_i;
  // long long i2 = 0, s21_i2 = 0;       not used
  unsigned long long u2 = 0, s21_u2 = 0;
  int test_result, test_result_s21;
  test_result =
      sscanf(string, "%d %9s %9s %Lu %9s %9ls", &i, s, str, &u2, str2, symb);
  test_result_s21 = s21_sscanf(s21_string, "%d %9s %9s %Lu %9s %9ls", &s21_i,
                               s21_s, s21_str, &s21_u2, s21_str2, symb);
  ck_assert_int_eq(i, s21_i);
  ck_assert_str_eq(s, s21_s);
  ck_assert_str_eq(str, s21_str);
  ck_assert_mem_eq(&u2, &s21_u2, sizeof(unsigned long long));
  ck_assert_str_eq(str2, s21_str2);
  ck_assert_int_eq(test_result, test_result_s21);
}
END_TEST

START_TEST(all_tipes_test) {
  const char src[] =
      "A 123 123 76 0x3AF 54.0032e-3 54.1200045 0.12E3 0.12001 9.97E-3 93.971 "
      "12e12 12404.10023 12E12 13.123 123123 hello 123124 13aF A123F af130000 ";
  // char src[] = "C d   10i 8i 16i   e          e_dot      E      E_dot   f
  // f_dot  g     g_dot       G     G_dot  o      s     u      x    X     p n";
  char c, s21_c;
  int d, s21_d;
  int i10, s21_i10, i8, s21_i8, i16, s21_i16;
  float e, s21_e, e_dot, s21_e_dot;
  float E, s21_E, E_dot, s21_E_dot;
  float f, s21_f, f_dot, s21_f_dot;
  float g, s21_g, g_dot, s21_g_dot;
  float G, s21_G, G_dot, s21_G_dot;
  unsigned int o, s21_o;
  char s[50], s21_s[50];
  unsigned int u, s21_u;
  unsigned int x, s21_x;
  unsigned int X, s21_X;
  void *p, *s21_p;
  int n, s21_n;
  int res_val = sscanf(
      src,
      "%c %d %i %i %i %e %e %E %E %f %f %g %g %G %G %o %20s %u %x %X %p %n", &c,
      &d, &i10, &i8, &i16, &e, &e_dot, &E, &E_dot, &f, &f_dot, &g, &g_dot, &G,
      &G_dot, &o, s, &u, &x, &X, &p, &n);
  int s21_res_val = s21_sscanf(
      src,
      "%c %d %i %i %i %e %e %E %E %f %f %g %g %G %G %o %20s %u %x %X %p %n",
      &s21_c, &s21_d, &s21_i10, &s21_i8, &s21_i16, &s21_e, &s21_e_dot, &s21_E,
      &s21_E_dot, &s21_f, &s21_f_dot, &s21_g, &s21_g_dot, &s21_G, &s21_G_dot,
      &s21_o, s21_s, &s21_u, &s21_x, &s21_X, &s21_p, &s21_n);
  switch (_i) {
    case 1:
      ck_assert_mem_eq(&c, &s21_c, sizeof(char));
      break;
    case 2:
      ck_assert_mem_eq(&d, &s21_d, sizeof(int));
      break;
    case 3:
      ck_assert_int_eq(i10, s21_i10);
      break;
    case 4:
      ck_assert_int_eq(i8, s21_i8);
      break;
    case 5:
      ck_assert_int_eq(i16, s21_i16);
      break;
    case 6:
      ck_assert_float_eq(e, s21_e);
      break;
    case 7:
      ck_assert_float_eq(e_dot, s21_e_dot);
      break;
    case 8:
      ck_assert_float_eq(E, s21_E);
      break;
    case 9:
      ck_assert_float_eq(E_dot, s21_E_dot);
      break;
    case 10:
      ck_assert_float_eq(f, s21_f);
      break;
    case 11:
      ck_assert_float_eq(f_dot, s21_f_dot);
      break;
    case 12:
      ck_assert_float_eq(g, s21_g);
      break;
    case 13:
      ck_assert_float_eq(g_dot, s21_g_dot);
      break;
    case 14:
      ck_assert_float_eq(G, s21_G);
      break;
    case 15:
      ck_assert_float_eq(G_dot, s21_G_dot);
      break;
    case 16:
      ck_assert_mem_eq(&o, &s21_o, sizeof(unsigned int));
      break;
    case 17:
      ck_assert_str_eq(s, s21_s);
      break;
    case 18:
      ck_assert_mem_eq(&u, &s21_u, sizeof(unsigned int));
      break;
    case 19:
      ck_assert_mem_eq(&x, &s21_x, sizeof(unsigned int));
      break;
    case 20:
      ck_assert_mem_eq(&X, &s21_X, sizeof(unsigned int));
      break;
    case 21:
      ck_assert_mem_eq(&p, &s21_p, sizeof(void *));
      break;
    case 22:
      ck_assert_int_eq(n, s21_n);
      break;
    case 23:
      ck_assert_int_eq(res_val, s21_res_val);
      break;
  }
}
END_TEST

START_TEST(number_acc_all_tipes_test) {
  const char src[] =
      "c  +123   -123   76   0x3AF_ 54.0032e-3ae 54.1200045 0.12E3! 0.12001_1 "
      "9.97E-3 93.971   12e12       12404.10023 12E12( (13.123) 123123  hello "
      "123124 13aF A123F af130000 ";
  // char src[] = "C  d     10i   8i   16i    e            e_dot      E E_dot f
  // f_dot    g           g_dot       G      G_dot  o      s     u      x    X
  // p        n";
  char c = 0;

  int d, s21_d;
  int i10, s21_i10, i8, s21_i8, i16, s21_i16;
  float e = 0, s21_e = 0, e_dot = 0, s21_e_dot = 0;
  float E = 0, s21_E = 0, E_dot = 0, s21_E_dot = 0;
  float f = 0, s21_f = 0, f_dot = 0, s21_f_dot = 0;
  float g = 0, s21_g = 0, g_dot = 0, s21_g_dot = 0;
  float G = 0, s21_G = 0, G_dot = 0, s21_G_dot = 0;
  unsigned int o = 0, s21_o = 0;
  char s[50] = " ", s21_s[50] = " ";
  unsigned int u = 0, s21_u = 0;
  unsigned int x = 0, s21_x = 0;
  unsigned int X = 0, s21_X = 0;
  void *p, *s21_p;
  int n = 0, s21_n = 0;
  char s21_c = 0;
  int res_val =
      sscanf(src,
             "%c %5d %5i %4i %6i %12e %4e %7E %9E %4f %8f %10g %12g %6G %8G "
             "%7o %3s %6u %3x %1X %9p %n",
             &c, &d, &i10, &i8, &i16, &e, &e_dot, &E, &E_dot, &f, &f_dot, &g,
             &g_dot, &G, &G_dot, &o, s, &u, &x, &X, &p, &n);
  int s21_res_val = s21_sscanf(
      src,
      "%c %5d %5i %4i %6i %12e %4e %7E %9E %4f %8f %10g %12g %6G %8G %7o %3s "
      "%6u %3x %1X %9p %n",
      &s21_c, &s21_d, &s21_i10, &s21_i8, &s21_i16, &s21_e, &s21_e_dot, &s21_E,
      &s21_E_dot, &s21_f, &s21_f_dot, &s21_g, &s21_g_dot, &s21_G, &s21_G_dot,
      &s21_o, s21_s, &s21_u, &s21_x, &s21_X, &s21_p, &s21_n);
  switch (_i) {
    case 1:
      ck_assert_int_eq(c, s21_c);
      break;
    case 2:
      ck_assert_int_eq(d, s21_d);
      break;
    case 3:
      ck_assert_int_eq(i10, s21_i10);
      break;
    case 4:
      ck_assert_int_eq(i8, s21_i8);
      break;
    case 5:
      ck_assert_int_eq(i16, s21_i16);
      break;
    case 6:
      ck_assert_float_eq(e, s21_e);
      break;
    case 7:
      ck_assert_float_eq(e_dot, s21_e_dot);
      break;
    case 8:
      ck_assert_float_eq(E, s21_E);
      break;
    case 9:
      ck_assert_float_eq(E_dot, s21_E_dot);
      break;
    case 10:
      ck_assert_float_eq(f, s21_f);
      break;
    case 11:
      ck_assert_float_eq(f_dot, s21_f_dot);
      break;
    case 12:
      ck_assert_float_eq(g, s21_g);
      break;
    case 13:
      ck_assert_float_eq(g_dot, s21_g_dot);
      break;
    case 14:
      ck_assert_float_eq(G, s21_G);
      break;
    case 15:
      ck_assert_float_eq(G_dot, s21_G_dot);
      break;
    case 16:
      ck_assert_mem_eq(&o, &s21_o, sizeof(unsigned int));
      break;
    case 17:
      ck_assert_str_eq(s, s21_s);
      break;
    case 18:
      ck_assert_mem_eq(&u, &s21_u, sizeof(unsigned int));
      break;
    case 19:
      ck_assert_mem_eq(&x, &s21_x, sizeof(unsigned int));
      break;
    case 20:
      ck_assert_mem_eq(&X, &s21_X, sizeof(unsigned int));
      break;
    case 21:
      ck_assert_int_eq(n, s21_n);
      break;
    case 22:
      ck_assert_int_eq(res_val, s21_res_val);
      break;
  }
}
END_TEST

START_TEST(supress_all_tipes_test) {
  const char src[] =
      "A 123 123 76 0x3AF 54.0032e-3 54.1200045 0.12E3 0.12001 9.97E-3 93.971 "
      "12e12 12404.10023 12E12 13.123 123123 hello 123124 13aF A123F af130000 ";
  // char src[] = "C d   10i 8i 16i   e          e_dot      E      E_dot   f
  // f_dot  g     g_dot       G     G_dot  o      s     u      x    X     p n";
  char c = 'B', s21_c = 'B';
  int d = 993, s21_d = 993;
  int i10 = 1000, s21_i10 = 1000, i8 = 7, s21_i8 = 7, i16 = 563, s21_i16 = 563;
  float e = 1.03e-3, s21_e = 1.03e-3, e_dot = 13.323, s21_e_dot = 13.323;
  float E = 1.34E4, s21_E = 1.34E4, E_dot = 13213.14, s21_E_dot = 13213.14;
  float f = 444.333, s21_f = 444.333, f_dot = 555.444, s21_f_dot = 555.444;
  float g = 777.555, s21_g = 777.555, g_dot = 666.666, s21_g_dot = 666.666;
  float G = 222.555, s21_G = 222.555, G_dot = 1414.23423,
        s21_G_dot = 1414.23423;
  unsigned int o = 432, s21_o = 432;
  char s[50] = "HELLO_", s21_s[50] = "HELLO_";
  unsigned int u = 111, s21_u = 111;
  unsigned int x = 515, s21_x = 515;
  unsigned int X = 535, s21_X = 535;
  void *p = &u, *s21_p = &u;
  int n = 0, s21_n = 0;
  int res_val = sscanf(src,
                       "%*c %*d %*i %*i %*i %*e %*e %*E %*E %*f %*f %*g %*g "
                       "%*G %*G %*o %*s %*u %*x %*X %*p");
  int s21_res_val = s21_sscanf(src,
                               "%*c %*d %*i %*i %*i %*e %*e %*E %*E %*f %*f "
                               "%*g %*g %*G %*G %*o %*s %*u %*x %*X %*p");
  switch (_i) {
    case 1:
      ck_assert_mem_eq(&c, &s21_c, sizeof(char));
      break;
    case 2:
      ck_assert_mem_eq(&d, &s21_d, sizeof(int));
      break;
    case 3:
      ck_assert_int_eq(i10, s21_i10);
      break;
    case 4:
      ck_assert_int_eq(i8, s21_i8);
      break;
    case 5:
      ck_assert_int_eq(i16, s21_i16);
      break;
    case 6:
      ck_assert_float_eq(e, s21_e);
      break;
    case 7:
      ck_assert_float_eq(e_dot, s21_e_dot);
      break;
    case 8:
      ck_assert_float_eq(E, s21_E);
      break;
    case 9:
      ck_assert_float_eq(E_dot, s21_E_dot);
      break;
    case 10:
      ck_assert_float_eq(f, s21_f);
      break;
    case 11:
      ck_assert_float_eq(f_dot, s21_f_dot);
      break;
    case 12:
      ck_assert_float_eq(g, s21_g);
      break;
    case 13:
      ck_assert_float_eq(g_dot, s21_g_dot);
      break;
    case 14:
      ck_assert_float_eq(G, s21_G);
      break;
    case 15:
      ck_assert_float_eq(G_dot, s21_G_dot);
      break;
    case 16:
      ck_assert_mem_eq(&o, &s21_o, sizeof(unsigned int));
      break;
    case 17:
      ck_assert_str_eq(s, s21_s);
      break;
    case 18:
      ck_assert_mem_eq(&u, &s21_u, sizeof(unsigned int));
      break;
    case 19:
      ck_assert_mem_eq(&x, &s21_x, sizeof(unsigned int));
      break;
    case 20:
      ck_assert_mem_eq(&X, &s21_X, sizeof(unsigned int));
      break;
    case 21:
      ck_assert_mem_eq(&p, &s21_p, sizeof(void *));
      break;
    case 22:
      ck_assert_int_eq(n, s21_n);
      break;
    case 23:
      ck_assert_int_eq(res_val, s21_res_val);
      break;
  }
}
END_TEST

START_TEST(all_short_test) {
  const char short_src[] = "32768 32768 7777 0x7FFE 100000 32768 7ffFE 7FFFE ";
  // char src[] =       "d     10i   8i   16i    o      u      x    X      n";
  short int d, s21_d;
  short int i10, s21_i10, i8, s21_i8, i16, s21_i16;
  unsigned short int o, s21_o;
  unsigned short int u, s21_u;
  unsigned short int x, s21_x;
  unsigned short int X, s21_X;
  int n, s21_n;
  int res_val = sscanf(short_src, "%hd %hi %hi %hi  %ho %hu %hx %hX %n", &d,
                       &i10, &i8, &i16, &o, &u, &x, &X, &n);
  int s21_res_val = s21_sscanf(short_src, "%hd %hi %hi %hi %ho %hu %hx %hX %n",
                               &s21_d, &s21_i10, &s21_i8, &s21_i16, &s21_o,
                               &s21_u, &s21_x, &s21_X, &s21_n);
  switch (_i) {
    case 1:
      ck_assert_int_eq(d, s21_d);
      break;
    case 2:
      ck_assert_int_eq(i10, s21_i10);
      break;
    case 3:
      ck_assert_int_eq(i8, s21_i8);
      break;
    case 4:
      ck_assert_int_eq(i16, s21_i16);
      break;
    case 5:
      ck_assert_int_eq(o, s21_o);
      break;
    case 6:
      ck_assert_int_eq(u, s21_u);
      break;
    case 7:
      ck_assert_int_eq(x, s21_x);
      break;
    case 8:
      ck_assert_int_eq(X, s21_X);
      break;
    case 9:
      ck_assert_int_eq(n, s21_n);
      break;
    case 10:
      ck_assert_int_eq(res_val, s21_res_val);
      break;
  }
}
END_TEST

START_TEST(all_long_test) {
  const char short_src[] =
      "4611686018427387904 4611686018427387904 400000000000000000 "
      "0x4000000000000000 4000000000000000 4611686018427387904 "
      "0x4000000000000000 0x4000000000000000 ";
  // char src[] =       "d                   10i                 8i 16i o u x X
  // n";
  long d, s21_d;
  long i10, s21_i10, i8, s21_i8, i16, s21_i16;
  unsigned long o, s21_o;
  unsigned long u, s21_u;
  unsigned long x, s21_x;
  unsigned long X, s21_X;
  long n = 0, s21_n = 0;
  int res_val = sscanf(short_src, "%ld %li %li %li  %lo %lu %lx %lX %ln", &d,
                       &i10, &i8, &i16, &o, &u, &x, &X, &n);
  int s21_res_val = s21_sscanf(short_src, "%ld %li %li %li %lo %lu %lx %lX %ln",
                               &s21_d, &s21_i10, &s21_i8, &s21_i16, &s21_o,
                               &s21_u, &s21_x, &s21_X, &s21_n);

  switch (_i) {
    case 1:
      ck_assert_int_eq(d, s21_d);
      break;
    case 2:
      ck_assert_int_eq(i10, s21_i10);
      break;
    case 3:
      ck_assert_int_eq(i8, s21_i8);
      break;
    case 4:
      ck_assert_int_eq(i16, s21_i16);
      break;
    case 5:
      ck_assert_int_eq(o, s21_o);
      break;
    case 6:
      ck_assert_int_eq(u, s21_u);
      break;
    case 7:
      ck_assert_int_eq(x, s21_x);
      break;
    case 8:
      ck_assert_int_eq(X, s21_X);
      break;
    case 9:
      ck_assert_int_eq(n, s21_n);
      break;
    case 10:
      ck_assert_int_eq(res_val, s21_res_val);
      break;
  }
}
END_TEST

START_TEST(all_long_long_test) {
  const char src[] =
      "1.7e4000L 1.7e-4000L 9.00019e-4000L -1.6001231315e-4000L "
      "1.600000123e4000L";
  // char src[] =       "e        E         f             g                  G
  // ";
  long double e = 0, s21_e = 0;
  long double E = 0, s21_E = 0;
  long double f = 0, s21_f = 0;
  long double g = 0, s21_g = 0;
  long double G = 0, s21_G = 0;
  int res_val = sscanf(src, "%Le %LE %Lf %Lg %LG", &e, &E, &f, &g, &G);
  int s21_res_val = s21_sscanf(src, "%Le %LE %Lf %Lg %LG", &s21_e, &s21_E,
                               &s21_f, &s21_g, &s21_G);

  switch (_i) {
    case 1:
      // ck_assert_float_eq(e, 12);
      ck_assert_float_eq(e, s21_e);
      break;
    case 2:
      // ck_assert_float_eq(E, 12);
      ck_assert_float_eq(E, s21_E);
      break;
    case 3:
      // ck_assert_float_eq(f, 12);
      ck_assert_float_eq(f, s21_f);
      break;
    case 4:
      // ck_assert_float_eq(g, 12);
      ck_assert_float_eq(g, s21_g);
      break;
    case 5:
      // ck_assert_float_eq(G, 13);
      ck_assert_float_eq(G, s21_G);
      break;
    case 6:
      ck_assert_int_eq(res_val, s21_res_val);
      break;
  }
}
END_TEST

START_TEST(c_test) {
  const char src[20] = "a";
  char c, s21_c;
  int res_val = sscanf(src, "%c", &c);
  int s21_res_val = s21_sscanf(src, "%c", &s21_c);
  ck_assert_mem_eq(&c, &s21_c, sizeof(char));
  ck_assert_int_eq(res_val, s21_res_val);
}
END_TEST

START_TEST(d_test) {
  const char src[20] = "";
  short int hd = 0, s21_hd = 0;
  int res_val = sscanf(src, "%hd", &hd);
  int s21_res_val = s21_sscanf(src, "%hd", &s21_hd);
  ck_assert_int_eq(hd, s21_hd);
  ck_assert_int_eq(res_val, s21_res_val);
}
END_TEST

Suite *suite_sscanf() {
  Suite *s = suite_create("sscanf");
  TCase *tc_average = tcase_create("average");

  tcase_add_test(tc_average, simple_i_str_u_test);
  tcase_add_loop_test(tc_average, all_tipes_test, 1, 23);
  tcase_add_loop_test(tc_average, number_acc_all_tipes_test, 1, 22);
  tcase_add_loop_test(tc_average, supress_all_tipes_test, 1, 23);
  tcase_add_loop_test(tc_average, all_short_test, 1, 10);
  tcase_add_loop_test(tc_average, all_long_test, 1, 10);
  tcase_add_loop_test(tc_average, all_long_long_test, 1, 6);
  tcase_add_test(tc_average, c_test);
  tcase_add_test(tc_average, d_test);
  suite_add_tcase(s, tc_average);

  return s;
}
