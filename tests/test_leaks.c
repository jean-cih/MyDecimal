#include "../s21_string.h"

int main(void){
    // s21_insert - тест 1
    const char *str_copy1 = {
      " from English translate on Russian like a нитки but sound like стринги "
      "what means thongs"};
    const char str_past1[120] = "String";
    char *result1 = s21_insert(str_past1, str_copy1, s21_strlen(str_past1));
    if (result1 != NULL) {
        free(result1);
    }

    // s21_insert - тест 2 (с NULL)
    const char *str_copy2 = NULL;
    const char str_past2[100] = "HELLO";
    char *result2 = s21_insert(str_past2, str_copy2, s21_strlen(str_past2));
    if (result2 != NULL) {
        free(result2);
    }

    // s21_memchr тест
    char string1[128];
    for (int i = 0; i < 128; i++) {
        string1[i] = i;
    }
    for (int i = 0; i < 128; i++) {
        s21_memchr(string1, i, 128);
    }

    // s21_memcmp тест
    const char *str2 = {
      "String from English translate on Russian like a нитки but sound like "
      "стринги what means thongs"};
    const char *str1 = {
      "String from English translate on Russian like a нитки but sound like "
      "стринги what means"};
    size_t size = s21_strlen(str2);
    for (int i = 0; i < (int)size; i++) {
        s21_memcmp(str2, str1, i);
    }

    // s21_memcpy тест
    const char *str3 = {
      "String from English translate on Russian like a нитки but sound like "
      "стринги what means thongs"};
    size_t size1 = s21_strlen(str3);
    for (size_t i = 0; i < size1; i++) {
        char s21_copy[320] = "str";
        s21_memcpy(s21_copy, str3, i);
    }

    // s21_memset тест
    char str4[40] = " ";
    for (size_t i = 0; i < 128; i++) {
        s21_memset(str4, i, 35);
    }

    // s21_sprintf тест
    char c = 'A';
    wint_t C = 'B';
    int s21_n1;
    char s21_string1[1000] = {0};
    s21_sprintf(s21_string1, " %c %-c %3c %lc %n", c, c, c, C, &s21_n1);

    // s21_sscanf тест
    const char s21_string2[] = "50000 red balls 223372036854775807 blue balls";
    char s21_s1[50], s21_str[10], s21_str2[10];
    wchar_t symb[255];
    int s21_i;
    unsigned long long s21_u2 = 0;
    s21_sscanf(s21_string2, "%d %9s %9s %Lu %9s %9ls", &s21_i, s21_s1, s21_str, &s21_u2, s21_str2, symb);

    const char src[] =
      "A 123 123 76 0x3AF 54.0032e-3 54.1200045 0.12E3 0.12001 9.97E-3 93.971 "
      "12e12 12404.10023 12E12 13.123 123123 hello 123124 13aF A123F af130000 ";
    char s21_c;
    int s21_d;
    int s21_i10, s21_i8, s21_i16;
    float s21_e, s21_e_dot;
    float s21_E, s21_E_dot;
    float s21_f, s21_f_dot;
    float s21_g, s21_g_dot;
    float s21_G, s21_G_dot;
    unsigned int s21_o;
    char s21_s[50];
    unsigned int s21_u;
    unsigned int s21_x;
    unsigned int s21_X;
    void *s21_p;
    int s21_n;
    s21_sscanf(src, "%c %d %i %i %i %e %e %E %E %f %f %g %g %G %G %o %20s %u %x %X %p %n", &s21_c, &s21_d, &s21_i10, &s21_i8, &s21_i16, &s21_e, &s21_e_dot, &s21_E, &s21_E_dot, &s21_f, &s21_f_dot, &s21_g, &s21_g_dot, &s21_G, &s21_G_dot, &s21_o, s21_s, &s21_u, &s21_x, &s21_X, &s21_p, &s21_n);

    // s21_strchr тест
    const char *str5 = {
      "String from English translate on Russian like a нитки but sound like "
      "стринги what means thongs"};
    for (int i = 0; i < 200; i++) {
        s21_strchr(str5, i);
    }

    // s21_strcspn тест
    const char *str6 = {"asdfg"};
    const char *str_pat6 = {"zxc"};
    s21_strcspn(str6, str_pat6);

    // s21_strncat тест
    const char *str8 = {"like a нитки but sound like стринги what means thongs"};
    char dest_s21[200] = {0};
    s21_strncat(dest_s21, str8, s21_strlen(str8));

    // s21_strncmp тест
    const char *str9 = {
      "String from English translate on Russian like a нитки but sound like "
      "стринги what means thongs"};
    const char *str10 = {
      "String from English translate on Russian like a нитки but sound like "
      "стринги what means"};
    size_t size2 = s21_strlen(str9);
    for (int i = 0; i < (int)size2; i++) {
        s21_strncmp(str9, str10, i);
    }

    // s21_strncpy тест
    char str11[128];
    for (int i = 0; i < 128; i++) {
        str11[i] = i;
    }
    char copy[120];
    size_t size3 = s21_strlen(str11);
    for (size_t i = 0; i < size3; i++) {
        s21_strncpy(copy, str11, i);
    }

    // s21_strpbrk тест
    const char *str12 = {
      "String from English translate on Russian like a нитки but sound like "
      "стринги what means thongs"};
    const char *str13 = "trans";
    s21_strpbrk(str12, str13);

    // s21_strrchr тест - ИСПРАВЛЕНО
    char *str14 = malloc(150 * sizeof(char));
    if (str14 != NULL) {
        // Инициализируем память перед использованием
        for (int i = 0; i < 149; i++) {
            str14[i] = 'a' + (i % 26);
        }
        str14[149] = '\0';
        
        for (int i = 0; i < 128; i++) {
            s21_strrchr(str14, i);
        }
        free(str14);
    }

    // s21_strstr тест
    char *str15 = (char*) {
        "String from English translate on Russian like a нитки but sound like "
        "стринги what means thongs"};
    const char *str16 = "Russian";
    s21_strstr(str15, str16);

    // s21_strtok тест
    char str17[200] =
      "String. from English, translate on Russian like/ a нитки but, sound "
      "like стринги what means. thongs";
    const char *delim = ".,/";
    s21_strtok(str17, delim);

    // s21_to_lower тест - ИСПРАВЛЕНО
    const char *str18 = {
      "STRING FROM ENGLISH TRANSLATE ON RUSSIAN LIKE A нитки BUT SOUND LIKE "
      "стринги WHAT MEANS THONGS"};
    char *lower_result = s21_to_lower(str18);
    if (lower_result != NULL) {
        free(lower_result);
    }

    // s21_to_upper тест - ИСПРАВЛЕНО
    const char *str19 = {
      "String from English translate on Russian like a нитки but sound like "
      "стринги what means thongs"};
    // Вызываем только один раз и освобождаем память
    char *upper_result = s21_to_upper(str19);
    if (upper_result != NULL) {
        free(upper_result);
    }

    // s21_trim тест
    const char *str20 = {
      "acdrhj1234567890String from English translate on Russian like a нитки "
      "but sound like стринги what means thongsdhjrca9807465321"};
    void *ptr2 = NULL;
    ptr2 = s21_trim(str20, "acdrhj1234567890");
    if (ptr2 != NULL) {
        free(ptr2);
    }

    return 0;
}
