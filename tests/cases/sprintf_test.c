#include "../../s21_string.h"
#include "s21_test_string.h"

START_TEST(all_tipes_test) {
  char string[1000] = {0};
  char s21_string[1000] = {0};
  char c = 'A';
  int d = 123;
  int i = 123;
  float e = 12364.131;
  float E = 12315.123;
  float f = 12123.134;
  float g = 12313.13123;
  float G = 1214.1241;
  unsigned int o = 12124;
  char s[50] = "STRINGmatch,./bus thuth";
  unsigned int u = 131231;
  unsigned int x = 123123;
  unsigned int X = 13123123;
  void *p = &x;
  int n = 0, s21_n;
  int res_val = sprintf(string, "%c %d %i %e %E %f %g %G %o %s %u %x %X %p %n",
                        c, d, i, e, E, f, g, G, o, s, u, x, X, p, &n);
  int s21_res_val =
      s21_sprintf(s21_string, "%c %d %i %e %E %f %g %G %o %s %u %x %X %p %n", c,
                  d, i, e, E, f, g, G, o, s, u, x, X, p, &s21_n);

  switch (_i) {
    case 1:
      ck_assert_str_eq(string, s21_string);
      break;
    case 2:
      ck_assert_int_eq(n, s21_n);
      break;
    case 3:
      ck_assert_int_eq(res_val, s21_res_val);
      break;
  }
}
END_TEST

START_TEST(c_test) {
  char c = 'A';
  wint_t C = 'B';
  int n = 0, s21_n;
  char string[1000] = {0};
  char s21_string[1000] = {0};
  int res_val = sprintf(string, " %c %-c %3c %lc %n", c, c, c, C, &n);
  int s21_res_val =
      s21_sprintf(s21_string, " %c %-c %3c %lc %n", c, c, c, C, &s21_n);
  switch (_i) {
    case 1:
      ck_assert_str_eq(string, s21_string);
      break;
    case 2:
      ck_assert_int_eq(n, s21_n);
      break;
    case 3:
      ck_assert_int_eq(res_val, s21_res_val);
      break;
  }
}
END_TEST

START_TEST(d_test) {
  int d = 32768;
  short int hd = 345;
  long ld = 461168601842738;
  int n = 0, s21_n;
  char string[1000] = {0};
  char s21_string[1000] = {0};
  int res_val =
      sprintf(string, "%d %-d %+d % d %0d %7d %*d %.4d %.*d %hd %ld %n", d, d,
              d, d, d, d, 4, d, d, 6, d, hd, ld, &n);
  int s21_res_val =
      s21_sprintf(s21_string, "%d %-d %+d % d %0d %7d %*d %.4d %.*d %hd %ld %n",
                  d, d, d, d, d, d, 4, d, d, 6, d, hd, ld, &s21_n);
  switch (_i) {
    case 1:
      ck_assert_str_eq(string, s21_string);
      break;
    case 2:
      ck_assert_int_eq(n, s21_n);
      break;
    case 3:
      ck_assert_int_eq(res_val, s21_res_val);
      break;
  }
}
END_TEST

START_TEST(i_test) {
  short int hi = 12;
  int i = 1243;
  long int li = 461168601842738;
  int n = 0, s21_n = 0;
  char string[1000];
  char s21_string[1000] = {0};
  int res_val =
      sprintf(string, "%i %-i %+i % i %0i %7i %*i %.5i %.*i %hi %li %n", i, i,
              i, i, i, i, 4, i, i, 6, i, hi, li, &n);
  int s21_res_val =
      s21_sprintf(s21_string, "%i %-i %+i % i %0i %7i %*i %.5i %.*i %hi %li %n",
                  i, i, i, i, i, i, 4, i, i, 6, i, hi, li, &s21_n);
  switch (_i) {
    case 1:
      ck_assert_str_eq(string, s21_string);
      break;
    case 2:
      ck_assert_int_eq(n, s21_n);
      break;
    case 3:
      ck_assert_int_eq(res_val, s21_res_val);
      break;
  }
}
END_TEST

START_TEST(e_test) {
  float e = 125.116e3;
  long double Le =
      12649374198483589732809482394328497230.82937498327489237432479823748923L;
  int n = 0, s21_n;
  char string[1000] = {0};
  char s21_string[1000] = {0};
  int res_val =
      sprintf(string, "%e %-e %+e % e %#e %0e %7e %*e %.12e %.*e %.14Le %n", e,
              e, e, e, e, e, e, 4, e, e, 4, e, Le, &n);
  int s21_res_val = s21_sprintf(
      s21_string, "%e %-e %+e % e %#e %0e %7e %*e %.12e %.*e %.14Le %n", e, e,
      e, e, e, e, e, 4, e, e, 4, e, Le, &s21_n);
  switch (_i) {
    case 1:
      ck_assert_str_eq(string, s21_string);
      break;
    case 2:
      ck_assert_int_eq(n, s21_n);
      break;
    case 3:
      ck_assert_int_eq(res_val, s21_res_val);
      break;
  }
}
END_TEST

START_TEST(E_test) {
  float E = 12313.123;
  long double LE =
      12649374198483589732809482394328497230.82937498327489237432479823748923L;
  int n = 0, s21_n;
  char string[1000] = {0};
  char s21_string[1000] = {0};
  int res_val =
      sprintf(string, "%E %-E %+E % E %#E %0E %10E %*E %.12E %.*E %.14Le %n", E,
              E, E, E, E, E, E, 4, E, E, 5, E, LE, &n);
  int s21_res_val = s21_sprintf(
      s21_string, "%E %-E %+E % E %#E %0E %10E %*E %.12E %.*E %.14Le %n", E, E,
      E, E, E, E, E, 4, E, E, 5, E, LE, &s21_n);
  switch (_i) {
    case 1:
      ck_assert_str_eq(string, s21_string);
      break;
    case 2:
      ck_assert_int_eq(n, s21_n);
      break;
    case 3:
      ck_assert_int_eq(res_val, s21_res_val);
      break;
  }
}
END_TEST

START_TEST(f_test) {
  float f = 1251.534645;
  int n = 0, s21_n;
  char string[1000] = {0};
  char s21_string[1000] = {0};
  int res_val = sprintf(string, "%f %-f %+f % f %#f %0f %10f %*f %.12f %.*f %n",
                        f, f, f, f, f, f, f, 4, f, f, 5, f, &n);
  int s21_res_val =
      s21_sprintf(s21_string, "%f %-f %+f % f %#f %0f %10f %*f %.12f %.*f %n",
                  f, f, f, f, f, f, f, 4, f, f, 5, f, &s21_n);
  switch (_i) {
    case 1:
      ck_assert_str_eq(string, s21_string);
      break;
    case 2:
      ck_assert_int_eq(n, s21_n);
      break;
    case 3:
      ck_assert_int_eq(res_val, s21_res_val);
      break;
  }
}
END_TEST

START_TEST(g_test) {
  float g = 12313.13123;
  long double Lg =
      12649374198483589732809482394328497230.82937498327489237432479823748923L;
  int n = 204, s21_n;
  char string[1000] = {0};
  char s21_string[1000] = {0};
  int res_val =
      sprintf(string, "%g %-g %+g % g %#g %0g %10g %*g %.12g %.*g %.14Lg %n", g,
              g, g, g, g, g, g, 4, g, g, 5, g, Lg, &n);
  int s21_res_val = s21_sprintf(
      s21_string, "%g %-g %+g % g %#g %0g %10g %*g %.12g %.*g %.14Lg %n", g, g,
      g, g, g, g, g, 4, g, g, 5, g, Lg, &s21_n);
  switch (_i) {
    case 1:
      ck_assert_str_eq(string, s21_string);
      break;
    case 2:
      ck_assert_int_eq(n, s21_n);
      break;
    case 3:
      ck_assert_int_eq(res_val, s21_res_val);
      break;
  }
}
END_TEST

START_TEST(G_test) {
  float G = 1214.1241;
  long double LG =
      12649374198483589732809482394328497230.82937498327489237432479823748923L;
  int n = 0, s21_n;
  char string[1000] = {0};
  char s21_string[1000] = {0};
  int res_val =
      sprintf(string, "%G %-G %+G % G %#G %0G %10G %*G %.12G %.*G %.14LG %n", G,
              G, G, G, G, G, G, 4, G, G, 5, G, LG, &n);
  int s21_res_val = s21_sprintf(
      s21_string, "%G %-G %+G % G %#G %0G %10G %*G %.12G %.*G %.14LG %n", G, G,
      G, G, G, G, G, 4, G, G, 5, G, LG, &s21_n);
  switch (_i) {
    case 1:
      ck_assert_str_eq(string, s21_string);
      break;
    case 2:
      ck_assert_int_eq(n, s21_n);
      break;
    case 3:
      ck_assert_int_eq(res_val, s21_res_val);
      break;
  }
}
END_TEST

START_TEST(o_test) {
  unsigned int o = 12124;
  unsigned long int lo = 461168601842738;
  unsigned short int ho = 65532;
  int n = 0, s21_n;
  char string[1000] = {0};
  char s21_string[1000] = {0};
  int res_val = sprintf(string, "%o %-o %o %0o %7o %*o %.4o %.*o %ho %lo %n", o,
                        o, o, o, o, 4, o, o, 6, o, ho, lo, &n);
  int s21_res_val =
      s21_sprintf(s21_string, "%o %-o %o %0o %7o %*o %.4o %.*o %ho %lo %n", o,
                  o, o, o, o, 4, o, o, 6, o, ho, lo, &s21_n);
  switch (_i) {
    case 1:
      ck_assert_str_eq(string, s21_string);
      break;
    case 2:
      ck_assert_int_eq(n, s21_n);
      break;
    case 3:
      ck_assert_int_eq(res_val, s21_res_val);
      break;
  }
}
END_TEST

START_TEST(s_test) {
  char s[50] = "STRINGmatch,./bus thuth- ";
  wchar_t S[50] = L"HELLO THIS MORtal world";
  int n = 0, s21_n;
  char string[1000] = {0};
  char s21_string[1000] = {0};
  int res_val = sprintf(string, "%s %-s %23s %*s %.21s %.*s %ls %n", s, s, s, 4,
                        s, s, 5, s, S, &n);
  int s21_res_val = s21_sprintf(s21_string, "%s %-s %23s %*s %.21s %.*s %ls %n",
                                s, s, s, 4, s, s, 5, s, S, &s21_n);
  switch (_i) {
    case 1:
      ck_assert_str_eq(string, s21_string);
      break;
    case 2:
      ck_assert_int_eq(n, s21_n);
      break;
    case 3:
      ck_assert_int_eq(res_val, s21_res_val);
      break;
  }
}
END_TEST

START_TEST(u_test) {
  unsigned int u = 131231;
  unsigned long int lu = 4.61168601842738;
  unsigned short int hu = 65532;
  int n = 0, s21_n;
  char string[1000] = {0};
  char s21_string[1000] = {0};
  int res_val = sprintf(string, "%u %-u %u %0u %7u %*u %.4u %.*u %hu %lu %n", u,
                        u, u, u, u, 4, u, u, 6, u, hu, lu, &n);
  int s21_res_val =
      s21_sprintf(s21_string, "%u %-u %u %0u %7u %*u %.4u %.*u %hu %lu %n", u,
                  u, u, u, u, 4, u, u, 6, u, hu, lu, &s21_n);
  switch (_i) {
    case 1:
      ck_assert_str_eq(string, s21_string);
      break;
    case 2:
      ck_assert_int_eq(n, s21_n);
      break;
    case 3:
      ck_assert_int_eq(res_val, s21_res_val);
      break;
  }
}
END_TEST

START_TEST(x_test) {
  unsigned int x = 12312;
  unsigned long int lx = 4.61168601842738;
  unsigned short int hx = 65532;
  int n = 0, s21_n;
  char string[1000] = {0};
  char s21_string[1000] = {0};
  int res_val = sprintf(string, "%x %-x %x %0x %7x %*x %.4x %.*x %hx %lx %n", x,
                        x, x, x, x, 4, x, x, 6, x, hx, lx, &n);
  int s21_res_val =
      s21_sprintf(s21_string, "%x %-x %x %0x %7x %*x %.4x %.*x %hx %lx %n", x,
                  x, x, x, x, 4, x, x, 6, x, hx, lx, &s21_n);
  switch (_i) {
    case 1:
      ck_assert_str_eq(string, s21_string);
      break;
    case 2:
      ck_assert_int_eq(n, s21_n);
      break;
    case 3:
      ck_assert_int_eq(res_val, s21_res_val);
      break;
  }
}
END_TEST

START_TEST(X_test) {
  unsigned int X = 13123123;
  unsigned long int lX = 46116860184273;
  unsigned short int hX = 65532;
  int n = 0, s21_n;
  char string[1000] = {0};
  char s21_string[1000] = {0};
  int res_val = sprintf(string, "%X %-X %X %0X %7X %*X %.4X %.*X %hX %lX %n", X,
                        X, X, X, X, 4, X, X, 6, X, hX, lX, &n);
  int s21_res_val =
      s21_sprintf(s21_string, "%X %-X %X %0X %7X %*X %.4X %.*X %hX %lX %n", X,
                  X, X, X, X, 4, X, X, 6, X, hX, lX, &s21_n);

  switch (_i) {
    case 1:
      ck_assert_str_eq(string, s21_string);
      break;
    case 2:
      ck_assert_int_eq(n, s21_n);
      break;
    case 3:
      ck_assert_int_eq(res_val, s21_res_val);
      break;
  }
}
END_TEST

START_TEST(p_test) {
  unsigned int x = 13123123;
  void *p = &x;
  int n = 0, s21_n;
  char string[1000] = {0};
  char s21_string[1000] = {0};
  int res_val = sprintf(string, "%p %-p %3p %*p %n", p, p, p, 23, p, &n);
  int s21_res_val =
      s21_sprintf(s21_string, "%p %-p %3p %*p %n", p, p, p, 23, p, &s21_n);
  switch (_i) {
    case 1:
      ck_assert_str_eq(string, s21_string);
      break;
    case 2:
      ck_assert_int_eq(n, s21_n);
      break;
    case 3:
      ck_assert_int_eq(res_val, s21_res_val);
      break;
  }
}
END_TEST

START_TEST(long_double_e) {
  long double Le =
      4611686018427387904461.46116860184273879044611686018427387904L;
  int n = 0, s21_n;
  char string[1000] = "";
  char s21_string[1000] = "";
  int res_val = sprintf(string, "%Le %.7Le %.14Le %.13Le %.*Le %n", Le, Le, Le,
                        Le, 5, Le, &n);
  int s21_res_val = s21_sprintf(s21_string, "%Le %.7Le %.14Le %.13Le %.*Le %n",
                                Le, Le, Le, Le, 5, Le, &s21_n);
  switch (_i) {
    case 1:
      ck_assert_str_eq(string, s21_string);
      break;
    case 2:
      ck_assert_int_eq(n, s21_n);
      break;
    case 3:
      ck_assert_int_eq(res_val, s21_res_val);
      break;
  }
}
END_TEST

START_TEST(long_double_E) {
  long double LE =
      4611686018427387904461.4611686018427387904461168601842738790446116860184273879044611686018427387904L;
  int n = 0, s21_n;
  char string[1000] = "";
  char s21_string[1000] = "";
  int res_val = sprintf(string, "%LE %.7LE %.14LE %.13LE %.*LE %n", LE, LE, LE,
                        LE, 5, LE, &n);
  int s21_res_val = s21_sprintf(s21_string, "%LE %.7LE %.14LE %.13LE %.*LE %n",
                                LE, LE, LE, LE, 5, LE, &s21_n);
  switch (_i) {
    case 1:
      ck_assert_str_eq(string, s21_string);
      break;
    case 2:
      ck_assert_int_eq(n, s21_n);
      break;
    case 3:
      ck_assert_int_eq(res_val, s21_res_val);
      break;
  }
}
END_TEST

START_TEST(long_double_f) {
  long double Lf =
      4611686018424559491.4611686018427387904461168601842738790446116860184273879044611686018427387904L;
  int n = 0, s21_n;
  char string[1000] = "";
  char s21_string[1000] = "";
  int res_val = sprintf(string, "%Lf %.7Lf %.14Lf %.13Lf %.*Lf %n", Lf, Lf, Lf,
                        Lf, 5, Lf, &n);
  int s21_res_val = s21_sprintf(s21_string, "%Lf %.7Lf %.14Lf %.13Lf %.*Lf %n",
                                Lf, Lf, Lf, Lf, 5, Lf, &s21_n);
  switch (_i) {
    case 1:
      ck_assert_str_eq(string, s21_string);

      break;
    case 2:
      ck_assert_int_eq(n, s21_n);
      break;
    case 3:
      ck_assert_int_eq(res_val, s21_res_val);
      break;
  }
}
END_TEST

START_TEST(long_double_g) {
  long double Lg =
      4611686018424559491.4611686018427387904461168601842738790446116860184273879044611686018427387904L;
  int n = 0, s21_n;
  char string[1000] = "";
  char s21_string[1000] = "";
  int res_val = sprintf(string, "%Lg %.7Lg %.14Lg %.13Lg %.*Lg %n", Lg, Lg, Lg,
                        Lg, 5, Lg, &n);
  int s21_res_val = s21_sprintf(s21_string, "%Lg %.7Lg %.14Lg %.13Lg %.*Lg %n",
                                Lg, Lg, Lg, Lg, 5, Lg, &s21_n);
  switch (_i) {
    case 1:
      ck_assert_str_eq(string, s21_string);
      break;
    case 2:
      ck_assert_int_eq(n, s21_n);
      break;
    case 3:
      ck_assert_int_eq(res_val, s21_res_val);
      break;
  }
}
END_TEST

START_TEST(long_double_G) {
  long double LG =
      4611686018424559491.4611686018427387904461168601842738790446116860184273879044611686018427387904L;
  int n = 0, s21_n;
  char string[1000] = "";
  char s21_string[1000] = "";
  int res_val = sprintf(string, "%LG %.7LG %.14LG %.13LG %.*LG %n", LG, LG, LG,
                        LG, 5, LG, &n);
  int s21_res_val = s21_sprintf(s21_string, "%LG %.7LG %.14LG %.13LG %.*LG %n",
                                LG, LG, LG, LG, 5, LG, &s21_n);
  switch (_i) {
    case 1:
      ck_assert_str_eq(string, s21_string);
      break;
    case 2:
      ck_assert_int_eq(n, s21_n);
      break;
    case 3:
      ck_assert_int_eq(res_val, s21_res_val);
      break;
  }
}
END_TEST

START_TEST(da_test) {
  char string[1000] = "";
  char s21_string[1000] = "";
  sprintf(string, "da");
  s21_sprintf(s21_string, "da");

  ck_assert_str_eq(string, s21_string);
}
END_TEST

Suite *suite_sprintf() {
  Suite *s = suite_create("sprintf");
  TCase *tc_average = tcase_create("average");

  tcase_add_loop_test(tc_average, all_tipes_test, 1, 3);
  tcase_add_loop_test(tc_average, c_test, 1, 3);
  tcase_add_loop_test(tc_average, d_test, 1, 3);
  tcase_add_loop_test(tc_average, i_test, 1, 3);
  tcase_add_loop_test(tc_average, e_test, 1, 3);
  tcase_add_loop_test(tc_average, E_test, 1, 3);
  tcase_add_loop_test(tc_average, f_test, 1, 3);
  tcase_add_loop_test(tc_average, g_test, 1, 3);
  tcase_add_loop_test(tc_average, G_test, 1, 3);
  tcase_add_loop_test(tc_average, o_test, 1, 3);
  tcase_add_loop_test(tc_average, s_test, 1, 3);
  tcase_add_loop_test(tc_average, u_test, 1, 3);
  tcase_add_loop_test(tc_average, x_test, 1, 3);
  tcase_add_loop_test(tc_average, X_test, 1, 3);
  tcase_add_loop_test(tc_average, p_test, 1, 3);
  tcase_add_loop_test(tc_average, long_double_e, 1, 3);
  tcase_add_loop_test(tc_average, long_double_E, 1, 3);
  tcase_add_loop_test(tc_average, long_double_f, 1, 3);
  tcase_add_loop_test(tc_average, long_double_g, 1, 3);
  tcase_add_loop_test(tc_average, long_double_G, 1, 3);
  tcase_add_test(tc_average, da_test);

  suite_add_tcase(s, tc_average);

  return s;
}
