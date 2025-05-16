#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>


typedef struct {
    int bit[4];
} s21_decimal;

typedef struct {
    int bit[3];
} uint96_t;

typedef struct {
    int bit[6];
} uint192_t;

typedef enum s21_arithmetic_result {
    S21_AR_OK = 0,
    S21_AR_BIG = 1,
    S21_AR_SMALL = 2,
    S21_AR_ZERO_DIV = 3
} s21_ar_result;

typedef enum s21_compare_result {
    S21_CR_FALSE = 0,
    S21_CR_TRUE = 1
} s21_cr_result;

typedef enum s21_manip_result {
    S21_MP_OK = 0,
    S21_MP_CALCULATION_ERROR = 1
} s21_mp_result;

typedef enum s21_convertor_result {
    S21_CV_OK = 0,
    S21_CV_ERROR = 1
} s21_cv_result;


void print_binary_32(int number);
void print_decimal(s21_decimal number);
void set_sign(s21_decimal *number, bool sign);
bool get_sign(s21_decimal number);
void set_scale(s21_decimal *number, uint8_t scale);
int get_scale(s21_decimal number);
void parser_decimal(s21_decimal *number, bool *sign, uint8_t *scale, uint96_t *mantissa);
s21_decimal create_decimal(bool sign, uint8_t scale, uint96_t *mantissa);
uint96_t shift_right_96(uint96_t number, int shift);
uint96_t shift_left_96(uint96_t number, int shift);
int bitwise_add(int a, int b);
void exps_alignment(uint8_t *scale_1, uint8_t *scale_2, uint96_t *mantissa_1, uint96_t *mantissa_2);
uint96_t supporting_add_96(uint96_t *number_1, uint96_t *number_2);
uint96_t supporting_sub_96(uint96_t *number_1, uint96_t *number_2, bool v1_is_larger, bool *sign_result);
uint96_t cycle_sub(uint96_t *number_1, uint96_t *number_2);
uint192_t karatsuba_algorithm_96(uint96_t a, uint96_t b);
s21_decimal copy_decimal(s21_decimal number);
bool is_correct_decimal(s21_decimal number);
s21_decimal s21_decimal_get_max(void);
s21_decimal s21_decimal_get_min(void);
s21_decimal s21_decimal_get_inf(void);
void clear_decimal(s21_decimal *number);


int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int s21_is_less(s21_decimal value_1, s21_decimal value_2);
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2); 
int s21_is_greater(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2);

int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);


//Вывод
uint32_t uint192_div10(uint192_t *number);
int uint192_is_zero(const uint192_t number);
void print_192(const uint192_t number);

//Ввод
void string_to_uint192(const char *str, uint192_t *num);
bool sdigit(char c);
void uint192_add_digit(uint192_t *num, uint8_t digit);
void uint192_multiply_by_10(uint192_t *num);


int main(void){
    
    s21_decimal a, b, result_sum, result_sub, result_mul;

    uint96_t mantissa_a = {1200, 20, 0};

    a = create_decimal(false, 0, &mantissa_a);
    bool sign_a;
    uint8_t scale_a;
    parser_decimal(&a, &sign_a, &scale_a, &mantissa_a);

    uint96_t mantissa_b = {1200, 10, 00};

    b = create_decimal(false, 0, &mantissa_b);
    bool sign_b;
    uint8_t scale_b;
    parser_decimal(&b, &sign_b, &scale_b, &mantissa_b);

    printf("Число A:\n");
    print_decimal(a);
    printf("A: Sign: %d Exponent: %u Mantissa: %d\n", sign_a, scale_a, mantissa_a.bit[0]);
    printf("Mantissa:\n");
    print_binary_32(mantissa_a.bit[2]);
    print_binary_32(mantissa_a.bit[1]);
    print_binary_32(mantissa_a.bit[0]);

    printf("Число B:\n");
    print_decimal(b);
    printf("B: Sign: %d Exponent: %u Mantissa: %d\n", sign_b, scale_b, mantissa_b.bit[0]);
    printf("Mantissa:\n");
    print_binary_32(mantissa_b.bit[2]);
    print_binary_32(mantissa_b.bit[1]);
    print_binary_32(mantissa_b.bit[0]);

    
    // printf("\n\nTESTING\n");
    // print_decimal(a);
    // bool sign;
    // uint8_t scale;
    // uint96_t mantissa;
    // parser_decimal(&a, &sign, &scale, &mantissa);
    // shift_right_96(&mantissa, 3);
    // printf("\n");
    // print_decimal(create_decimal(sign, scale, &mantissa));
    // shift_left_96(&mantissa, 3);
    // printf("\n");
    // print_decimal(create_decimal(sign, scale, &mantissa));

    printf("\n\nTESTING\n");
    printf("Число A:\n");
    print_decimal(a);
    printf("A: Sign: %d Exponent: %u Mantissa: %d\n", sign_a, scale_a, mantissa_a.bit[0]);
    printf("Число B:\n");
    print_decimal(b);
    printf("B: Sign: %d Exponent: %u Mantissa: %d\n", sign_b, scale_b, mantissa_b.bit[0]);

    s21_add(a, b, &result_sum);
    printf("RESULT ADD\n");
    print_decimal(result_sum);

    bool sign_sum;
    uint8_t scale_sum;
    uint96_t mantissa_sum;
    parser_decimal(&result_sum, &sign_sum, &scale_sum, &mantissa_sum);
    printf("Result: Sign: %d Exponent: %u Mantissa: %d\n", sign_sum, scale_sum, mantissa_sum.bit[0]);
    printf("Mantissa:\n");
    print_binary_32(mantissa_sum.bit[2]);
    print_binary_32(mantissa_sum.bit[1]);
    print_binary_32(mantissa_sum.bit[0]);

    s21_sub(a, b, &result_sub);
    printf("RESULT SUB\n");
    print_decimal(result_sub);

    bool sign_sub;
    uint8_t scale_sub;
    uint96_t mantissa_sub;
    parser_decimal(&result_sub, &sign_sub, &scale_sub, &mantissa_sub);
    printf("Result: Sign: %d Exponent: %u Mantissa: %d\n", sign_sub, scale_sub, mantissa_sub.bit[0]);
    printf("Mantissa:\n");
    print_binary_32(mantissa_sub.bit[2]);
    print_binary_32(mantissa_sub.bit[1]);
    print_binary_32(mantissa_sub.bit[0]);
    

    printf("RESULT MUL\n");
    s21_mul(a, b, &result_mul);
    print_decimal(result_mul);

    bool sign_mul;
    uint8_t scale_mul;
    uint96_t mantissa_mul;
    parser_decimal(&result_mul, &sign_mul, &scale_mul, &mantissa_mul);
    printf("Result: Sign: %d Exponent: %u Mantissa: %d\n", sign_mul, scale_mul, mantissa_mul.bit[0]);

    uint192_t a_192 = {a.bit[0], a.bit[1], a.bit[2], 0, 0, 0};
    uint192_t b_192 = {b.bit[0], b.bit[1], b.bit[2], 0, 0, 0};
    uint192_t r_192 = {result_mul.bit[0], result_mul.bit[1], result_mul.bit[2], 0, 0, 0};
    print_192(a_192);
    printf("\n");
    print_192(b_192);
    printf("\n");
    print_192(r_192);



    // Это тоже
    // printf("Mantissa:\n");
    // print_binary(mantissa_sub[2]);
    // print_binary(mantissa_sub[1]);
    // print_binary(mantissa_sub[0]);
    // int mantissa_res = bitwise_add(mantissa_a[0], mantissa_b[0]);
    // printf("\n%d\n", mantissa_res);
    // print_binary(mantissa_res);
    printf("\n");

    printf("Less: %d\n", s21_is_less(a, b));
    printf("Less or equal: %d\n", s21_is_less_or_equal(a, b));
    printf("Greater: %d\n", s21_is_greater(a, b));
    printf("Greater or equal: %d\n", s21_is_greater_or_equal(a, b));
    printf("Equal: %d\n", s21_is_equal(a, b));
    printf("Not equal: %d\n", s21_is_not_equal(a, b));

   // Это тоже 
    // uint192_t mantissa_a_new = {mantissa_a.bit[0], mantissa_a.bit[1], mantissa_a.bit[2], 0, 0, 0};
    // printf("A: "); 
    // print_192(mantissa_a_new);
    // printf("\n");
    //
    // uint192_t mantissa_b_new = {mantissa_b.bit[0], mantissa_b.bit[1], mantissa_b.bit[2], 0, 0, 0};
    // printf("B: ");
    // print_192(mantissa_b_new);
    // printf("\n");
    //
    // uint192_t mantissa_sum_new = {mantissa_sum.bit[0], mantissa_sum.bit[1], mantissa_sum.bit[2], 0, 0, 0};
    // printf("SUM: ");
    // print_192(mantissa_sum_new);
    // printf("\n");



    // Этот алгоритм нормально не работате
    uint96_t x = {1210, 1, 0};
    uint96_t y = {1223, 0, 0};
    //uint192_t result = karatsuba_algorithm_96(x, y);

    uint192_t x_p = {x.bit[0], x.bit[1], x.bit[2], 0, 0, 0};
    uint192_t y_p = {y.bit[0], y.bit[1], y.bit[2], 0, 0, 0};
    // Это тоже
    printf("\n");
    print_192(x_p);
    printf("\n");
    print_192(y_p);
    printf("\n");


    s21_decimal reg1;
    s21_negate(a, &reg1);
    print_decimal(reg1);
    s21_decimal reg2;
    s21_negate(b, &reg2);
    print_decimal(reg2);

    // Тест ввода
    // char num1[100] = {0};
    // char num2[100] = {0};
    // scanf("%99s", num1);
    // scanf("%99s", num2);

    // uint192_t res1 = {0};
    // string_to_uint192(num1, &res1);
    // print_192(res1);
    // printf("\n");
    //
    // uint192_t res2 = {0};
    // string_to_uint192(num1, &res2);
    // print_192(res2);
    // printf("\n");
    //
    // uint96_t a1 = {res1.bit[0], res1.bit[1], res1.bit[2]};
    // uint96_t b1 = {res2.bit[0], res2.bit[1], res2.bit[2]};
    // uint96_t res3 = supporting_add_96(&a1, &b1);
    //
    // uint192_t res4 = {res3.bit[0], res3.bit[1], res3.bit[2], 0, 0, 0};
    // print_192(res4);
    // printf("\n");


    printf("FROM INT TO DECIMAL\n");
    s21_decimal dst = {0};
    printf("%d\n", INT32_MAX);
    s21_from_int_to_decimal(INT32_MAX, &dst);
    print_decimal(dst);

    printf("FROM DECIMAL TO INT\n");
    uint96_t mantissa_src = {1024, 0, 0};
    s21_decimal src = create_decimal(false, 4, &mantissa_src);
    int dst_int = 0;
    s21_from_decimal_to_int(src, &dst_int);
    print_decimal(src);
    printf("%d\n", dst_int);

    printf("TRUNCATE\n");
    uint96_t mantissa1 = {1024, 20, 20};
    s21_decimal value1 = create_decimal(false, 4, &mantissa1);
    s21_decimal result1 = {0};
    s21_truncate(value1, &result1);
    print_decimal(value1);
    printf("\n");
    print_decimal(result1);

    float f = 1024.64;
    printf("%f\n", f);

    s21_from_float_to_decimal(f, NULL);


    uint192_t test = {100, 100, 100, 100, 100, 100};
    print_192(test);

    return 0;
}

void string_to_uint192(const char *str, uint192_t *num){
    while(*str == 0){
        str++;
    }

    while(*str){
        if(!sdigit(*str)){
            return;
        }

        uint8_t digit = *str - '0';
        uint192_multiply_by_10(num);
        uint192_add_digit(num, digit);

        str++;
    }
}

void uint192_add_digit(uint192_t *num, uint8_t digit){
    uint64_t temp = (uint64_t)num->bit[0] + digit;
    num->bit[0] = (uint32_t)(temp & 0xFFFFFFFF);
    uint64_t carry = temp >> 32;

    for(int i = 1; i < 6 && carry != 0; i++){
        temp = (uint64_t)num->bit[i] + carry;
        num->bit[i] = (uint32_t)(temp & 0xFFFFFFFF);
        carry = temp >> 32;
    }

    if(carry != 0){
        printf("Overflow 192 bits");
    }
}

void uint192_multiply_by_10(uint192_t *num){
    uint64_t carry = 0;
    for(int i = 0; i < 6; i++){
        uint64_t temp = (uint64_t)num->bit[i] * 10 + carry;
        num->bit[i] = (uint32_t)(temp & 0xFFFFFFFF);
        carry = temp >> 32;
    }

    if(carry != 0){
        printf("Overflow 192 bits");
    }
}

bool sdigit(char c){
    return true; 
}

int bitwise_add(int a, int b){
    while(b != 0){
        int carry = a & b;
        a = a ^ b;
        b = carry << 1;
    }
    return a;
}

void print_binary_32(int number){
    for(int i = 31; i >= 0; i--){
        printf("%d", (number >> i) & 1);
    }
    printf("\n");
}



void print_decimal(s21_decimal number){
    for(int i = 3; i >=0; i--){
        print_binary_32(number.bit[i]);
    }
}

void set_sign(s21_decimal *number, bool sign){
    number->bit[3] |= sign << 31; 
}

bool get_sign(s21_decimal number){
    return number.bit[3] >> 31;
}

void set_scale(s21_decimal *number, uint8_t scale){
    number->bit[3] |= scale << 16;
}

int get_scale(s21_decimal number){
    return (number.bit[3] >> 16) & 0x0F;
}

void parser_decimal(s21_decimal *number, bool *sign, uint8_t *scale, uint96_t *mantissa){
   *sign = (number->bit[3] >> 31) & 1;

   *scale = (number->bit[3] >> 16) & 0xFF;

   mantissa->bit[0] = number->bit[0];
   mantissa->bit[1] = number->bit[1];
   mantissa->bit[2] = number->bit[2];
}

s21_decimal create_decimal(bool sign, uint8_t scale, uint96_t *mantissa){
    s21_decimal result;

    result.bit[0] = mantissa->bit[0];
    result.bit[1] = mantissa->bit[1];
    result.bit[2] = mantissa->bit[2];

    result.bit[3] = (sign << 31) | (scale << 16);

    return result;
}
// Нужно еще сдвиг 32 бит
uint96_t shift_right_96(uint96_t number, int shift){
    if (shift <= 0){
        return number;
    }
    if(shift >= 96){
        return (uint96_t){ .bit = {0, 0, 0} };
    }

    while(shift >= 32){
        number.bit[0] = number.bit[1];
        number.bit[1] = number.bit[2];
        number.bit[2] = 0;
        shift -= 32;
    }

    while(shift != 0){
        bool carry1 = (number.bit[1] & 1);
        bool carry2 = (number.bit[2] & 1);

        number.bit[0] >>= 1;
        number.bit[1] >>= 1;
        number.bit[2] >>= 1;

        if(carry1){
            number.bit[0] |= (UINT32_C(1) << 30);
        }

        if(carry2){
            number.bit[1] |= (UINT32_C(1) << 30);
        }

        shift--;
    }

    return number;
}
// Нужно еще сдвиг 32 бит
uint96_t shift_left_96(uint96_t number, int shift){
    if (shift <= 0){
        return  number;
    }

    if(shift >= 96){
        return (uint96_t){ .bit = {0, 0, 0} };
    }


    while(shift >= 32){
        number.bit[2] = number.bit[1];
        number.bit[1] = number.bit[0];
        number.bit[0] = 0;
        shift -= 32;
    }

    while(shift > 0){
        bool carry0 = (number.bit[0] >> 30) & 1;
        bool carry1 = (number.bit[1] >> 30) & 1;

        number.bit[2] <<= 1;
        number.bit[1] <<= 1;
        number.bit[0] <<= 1;

        if(carry1){
            number.bit[2] |= 1;
        }

        if(carry0){
            number.bit[1] |= 1;
        }
        
        shift--;
    }

    return number;
}

void exps_alignment(uint8_t *scale_1, uint8_t *scale_2, uint96_t *mantissa_1, uint96_t *mantissa_2){
    // Выравнивание экспонент
    if(*scale_1 < *scale_2){
        int shift = scale_2 - scale_1;

        *mantissa_1 = shift_right_96(*mantissa_1, shift);

        *scale_1 = *scale_2;
    }
    else if(*scale_1 > *scale_2){
        int shift = scale_1 - scale_2;

        *mantissa_2 = shift_right_96(*mantissa_2, shift);

        *scale_2 = *scale_1;
    }
}

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result){

    s21_ar_result status = S21_AR_OK;

    bool sign_1, sign_2, sign_result;
    uint8_t scale_1, scale_2, scale_result;
    uint96_t mantissa_1 = {0}, mantissa_2 = {0}, mantissa_result = {0};

    parser_decimal(&value_1, &sign_1, &scale_1, &mantissa_1);
    parser_decimal(&value_2, &sign_2, &scale_2, &mantissa_2);
    
    // Выравнивание экспонент
    exps_alignment(&scale_1, &scale_2, &mantissa_1, &mantissa_2);

    scale_result = scale_1;

    if(sign_1 == sign_2){
        // Складываем
        mantissa_result = supporting_add_96(&mantissa_1, &mantissa_2);

        sign_result = sign_1;
    }
    else{
        // Вычитаем
        bool v1_is_larger = false;
        if(mantissa_1.bit[2] > mantissa_2.bit[2]){
            v1_is_larger = true;
        }
        else if(mantissa_1.bit[1] > mantissa_2.bit[1] && mantissa_1.bit[2] == mantissa_2.bit[2]){
            v1_is_larger = true;
        } 
        else if(mantissa_1.bit[0] > mantissa_2.bit[0] && mantissa_1.bit[1] == mantissa_2.bit[1] && mantissa_1.bit[2] == mantissa_2.bit[2]){
            v1_is_larger = true;
        }

        mantissa_result = supporting_sub_96(&mantissa_1, &mantissa_2, v1_is_larger, &sign_result);
    }

    *result = create_decimal(sign_result, scale_result, &mantissa_result);

    return status;
}

uint96_t supporting_add_96(uint96_t *number_1, uint96_t *number_2){

    uint96_t result = {0};

    uint64_t carry = 0;
    for(int i = 0; i < 3; i++){
        uint64_t temp = (uint64_t)number_1->bit[i] + number_2->bit[i] + carry;
        if(temp <= UINT32_MAX){
            result.bit[i] = temp;
        }
        else{
            result.bit[i] = UINT32_MAX;
            if(i < 2){
                result.bit[i + 1] = UINT32_MAX - temp;
                carry = result.bit[i + 1];
            }
        }
    }
    return result;
}

uint96_t cycle_sub(uint96_t *number_1, uint96_t *number_2){
    uint96_t result = {0};

    uint64_t borrow = 0;
    for(int i = 0; i < 3; i++){
        uint64_t temp = (uint64_t)number_1->bit[i] - number_2->bit[i] - borrow;
        result.bit[i] = (uint32_t)(temp & 0xFFFFFFFF);
        borrow = (temp < 0) ? 1: 0;
    }

    return result;
}

uint96_t supporting_sub_96(uint96_t *number_1, uint96_t *number_2, bool v1_is_larger, bool *sign_result){

    uint96_t result = {0};
    if(v1_is_larger){  
        
        result = cycle_sub(number_1, number_2);

        *sign_result = false;
    }
    else{            
        result = cycle_sub(number_2, number_1);

        *sign_result = true;
    }

    if(result.bit[0] == 0 && result.bit[1] == 0 && result.bit[2] == 0){
        *sign_result = false;
    }

    return result;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result){

    s21_ar_result status = S21_AR_OK;

    bool sign_1, sign_2, sign_result;
    uint8_t scale_1, scale_2, scale_result;
    uint96_t mantissa_1 = {0}, mantissa_2 = {0}, mantissa_result = {0};

    parser_decimal(&value_1, &sign_1, &scale_1, &mantissa_1);
    parser_decimal(&value_2, &sign_2, &scale_2, &mantissa_2);
    
    // Выравнивание экспонент
    exps_alignment(&scale_1, &scale_2, &mantissa_1, &mantissa_2);
    
    scale_result = scale_1;

    if((sign_1 && sign_2) || (!sign_1 && sign_2)){ 
        // Складываем
        mantissa_result = supporting_add_96(&mantissa_1, &mantissa_2);

        sign_result = sign_1;
    }
    else{
        // Вычитаем
        bool v1_is_larger = false;
        if(mantissa_1.bit[2] > mantissa_2.bit[2]){
            v1_is_larger = true;
        }
        else if(mantissa_1.bit[1] > mantissa_2.bit[1] && mantissa_1.bit[2] == mantissa_2.bit[2]){
            v1_is_larger = true;
        } 
        else if(mantissa_1.bit[0] > mantissa_2.bit[0] && mantissa_1.bit[1] == mantissa_2.bit[1] && mantissa_1.bit[2] == mantissa_2.bit[2]){
            v1_is_larger = true;
        }

         mantissa_result = supporting_sub_96(&mantissa_1, &mantissa_2, v1_is_larger, &sign_result);
    }

    *result = create_decimal(sign_result, scale_result, &mantissa_result);

    return status;
}


uint192_t karatsuba_algorithm_96(uint96_t a, uint96_t b){

    uint192_t result = {0};

    if(a.bit[2] == 0 && b.bit[2] == 0 && a.bit[1] == 0 && b.bit[1] == 0){
        uint64_t product = (uint64_t)a.bit[0] * b.bit[0];

        result.bit[0] = (uint32_t)(product & 0xFFFFFFFF);
        result.bit[1] = (uint32_t)(product >> 32);

        return result;
    }

    uint96_t high_a = {a.bit[1] >> 16, a.bit[2], 0};
    uint96_t low_a = {a.bit[0], a.bit[1] & 0xFFFF, 0};

    uint96_t high_b = {b.bit[1] >> 16, b.bit[2], 0};
    uint96_t low_b = {b.bit[0], b.bit[1] & 0xFFFF, 0};

    uint192_t P1 = karatsuba_algorithm_96(high_a, high_b);
    uint192_t P2 = karatsuba_algorithm_96(low_a, low_b);
    return result;
    uint96_t sum_a = supporting_add_96(&high_a, &low_a);
    uint96_t sum_b = supporting_add_96(&high_b, &low_b);

    uint192_t P3 = karatsuba_algorithm_96(sum_a, sum_b);
    
// Комбинируем результаты
    uint192_t term1 = P1;                            // term1 = P1 * 2^96
    for (int i = 5; i >= 2; i--) term1.bit[i] = term1.bit[i - 2];
    term1.bit[0] = term1.bit[1] = 0;

    uint192_t temp = P3;
    for (int i = 0; i < 6; i++) temp.bit[i] -= P1.bit[i] + P2.bit[i];  // temp = P3 - P1 - P2

    uint192_t term2 = temp;                          // term2 = (P3 - P1 - P2) * 2^48
    for (int i = 5; i >= 1; i--) term2.bit[i] = term2.bit[i - 1];
    term2.bit[0] = 0;

    // Суммируем все части
    for (int i = 0; i < 6; i++) {
        uint64_t sum = (uint64_t)term1.bit[i] + term2.bit[i] + P2.bit[i];
        result.bit[i] = (uint32_t)(sum & 0xFFFFFFFF);
        if (i < 5) result.bit[i + 1] += (uint32_t)(sum >> 32);
    }


    // uint96_t term1 = shift_left_96(P1, 96);
    // uint96_t res1 = supporting_sub_96(&P3, &P1, true, false);
    // uint96_t term2 = shift_left_96(supporting_sub_96(&res1, &P2, true, false), 48);
    // uint96_t res2 = supporting_add_96(&term1, &term2);
    // result  = supporting_add_96(&res2, &P2);
  
    return result;
    
}

//Работает очень коряво
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result){
    s21_ar_result status = S21_AR_OK;

    bool sign_1, sign_2, sign_result;
    uint8_t scale_1, scale_2, scale_result;
    uint96_t mantissa_1 = {0}, mantissa_2 = {0}, mantissa_result = {0};

    parser_decimal(&value_1, &sign_1, &scale_1, &mantissa_1);
    parser_decimal(&value_2, &sign_2, &scale_2, &mantissa_2);

    sign_result = sign_1 ^ sign_2;

    scale_result = scale_1 + scale_2;

    uint192_t big_mantissa = {0};

    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            uint64_t temp = (uint64_t)mantissa_1.bit[i] * mantissa_2.bit[j];
            uint32_t lower_temp = (uint32_t)(temp & 0xFFFFFFFF);
            uint32_t upper_temp = (uint32_t)(temp >> 32);

            uint64_t sum = (uint64_t)big_mantissa.bit[i + j] + lower_temp;
            big_mantissa.bit[i + j] = (uint32_t)(sum & 0xFFFFFFFF);
            uint32_t carry = (uint32_t)(sum >> 32);

            int k = i + j + 1;
            while(carry && k < 6){
                sum = (uint64_t)big_mantissa.bit[k] + carry;
                big_mantissa.bit[k] = (uint32_t)(sum & 0xFFFFFFFF);
                carry = (uint32_t)(sum >> 32);
                k++;
            }
        }
    }

    if(big_mantissa.bit[3] != 0 || big_mantissa.bit[4] != 0 || big_mantissa.bit[5] != 0){
        while((big_mantissa.bit[3] != 0 && big_mantissa.bit[4] != 0 && big_mantissa.bit[5] != 0) && scale_result > 0){
            uint64_t remainder = 0;
            for(int i = 6; i >= 0; i--){
                uint64_t value = (remainder << 32) | big_mantissa.bit[i];
                big_mantissa.bit[i] = (uint32_t)(value / 10);
                remainder = value % 10;
            }
            scale_result--;
        }
    }

    mantissa_result.bit[0] = big_mantissa.bit[0];
    mantissa_result.bit[1] = big_mantissa.bit[1];
    mantissa_result.bit[2] = big_mantissa.bit[2];

    *result = create_decimal(sign_result, scale_result, &mantissa_result);

    return status;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result){
    s21_ar_result status = S21_AR_OK;

    bool v2_is_zero = value_2.bit[0] == 0 && value_2.bit[1] == 0 && value_2.bit[2] == 0;
    if(v2_is_zero){
        status = S21_AR_ZERO_DIV;
        return status;
    }

    bool sign_1, sign_2, sign_result;
    uint8_t scale_1, scale_2, scale_result;
    uint96_t mantissa_1 = {0}, mantissa_2 = {0}, mantissa_result = {0};

    parser_decimal(&value_1, &sign_1, &scale_1, &mantissa_1);
    parser_decimal(&value_2, &sign_2, &scale_2, &mantissa_2);

    sign_result = sign_1 ^ sign_2;

    scale_result = scale_1 - scale_2;


    return status;
}

int s21_is_less(s21_decimal value_1, s21_decimal value_2){
    s21_decimal result;
    s21_ar_result status = s21_sub(value_1, value_2, &result);

    if(status != 0){
        return 0;
    }

    s21_cr_result compare = (result.bit[3] >> 31) & 1;

    return compare;
}

int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2){ 
    s21_decimal result;
    s21_ar_result status = s21_sub(value_1, value_2, &result);

    if(status != 0){
        return 0;
    }

    s21_cr_result compare = (result.bit[3] >> 31) & 1;

    return compare || (result.bit[0] == 0 && result.bit[1] == 0 && result.bit[2] == 0);
}


int s21_is_greater(s21_decimal value_1, s21_decimal value_2){
    s21_decimal result;
    s21_ar_result status = s21_sub(value_1, value_2, &result);

    if(status != 0 || (result.bit[0] == 0 && result.bit[1] == 0 && result.bit[2] == 0)){
        return 0;
    }

    s21_cr_result compare = !((result.bit[3] >> 31) & 1);

    return compare; 
}

int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2){
    s21_decimal result;
    s21_ar_result status = s21_sub(value_1, value_2, &result);

    if(status != 0){
        return 0;
    }

    s21_cr_result compare = !((result.bit[3] >> 31) & 1);

    return compare || (result.bit[0] == 0 && result.bit[1] == 0 && result.bit[2] == 0); 
}

int s21_is_equal(s21_decimal value_1, s21_decimal value_2){
    s21_decimal result;
    s21_ar_result status = s21_sub(value_1, value_2, &result);

    if(status != 0){
        return 0;
    }

    return (result.bit[0] == 0 && result.bit[1] == 0 && result.bit[2] == 0);
}

int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2){
    return !s21_is_equal(value_1, value_2);
}

int s21_negate(s21_decimal value, s21_decimal *result){
   
    s21_mp_result status = S21_MP_OK;

    *result = copy_decimal(value);
    
    set_sign(result, !get_sign(value)); 

    return status;
}

s21_decimal copy_decimal(s21_decimal value){
    bool sign;
    uint8_t scale;
    uint96_t mantissa = {0};
    parser_decimal(&value, &sign, &scale, &mantissa);

    return create_decimal(!sign, scale, &mantissa);
}

uint32_t uint192_div10(uint192_t *number){
    uint64_t remainder = 0;
    for(int i = 5; i >= 0; i--){
        uint64_t value = ((uint64_t)remainder << 32) | number->bit[i];
        number->bit[i] = (uint32_t)(value / 10);
        remainder = value % 10;
    }
    return (uint32_t)remainder;
}

int uint192_is_zero(const uint192_t number){
    for(int i = 0; i < 6; i++){
        if(number.bit[i] != 0){
            return 0;
        }
    }
    return 1;
}

void print_192(uint192_t num) {
    char decimal[60] = {0};
    int pos = 0;

    uint32_t temp[6];
    memcpy(temp, num.bit, sizeof(num.bit));

    int is_zero = 1;
    for (int i = 0; i < 6; i++) {
        if (temp[i] != 0) {
            is_zero = 0;
            break;
        }
    }
    if (is_zero) {
        printf("0\n");
        return;
    }

    while (1) {
        is_zero = 1;
        for (int i = 0; i < 6; i++) {
            if (temp[i] != 0) {
                is_zero = 0;
                break;
            }
        }
        if (is_zero){
            break;
        }

        uint64_t remainder = 0;
        for (int i = 5; i >= 0; i--) {
            uint64_t value = ((uint64_t)remainder << 32) | temp[i];
            temp[i] = value / 10;
            remainder = value % 10;
        }

        decimal[pos++] = '0' + remainder;
    }

    for (int i = pos - 1; i >= 0; i--) {
        putchar(decimal[i]);
    }
    putchar('\n');
}

int s21_from_int_to_decimal(int src, s21_decimal *dst){

    s21_cv_result status = S21_CV_OK;

    bool sign = true;
    int new_src = src;
    if(src == INT32_MIN){
        new_src = INT32_MAX;
    }
    else if(src < 0){
        new_src *= -1;
    }
    else{
        sign = false;
    }

    uint96_t mantissa = {new_src, 0, 0}; 
    *dst = create_decimal(sign, 0, &mantissa);

    return status;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst){

    s21_cv_result status = S21_CV_OK;

    bool sign = false;
    if(src < 0.0){
        sign = true;
        src *= -1;
    }

    // uint8_t scale = 0;
    // double src_scale = src - (int)src;
    // while(src_scale < ){
    //     src_scale *= 10;
    //     scale++;
    // }
    //
    // printf("%lf\n", src_scale);
    //
    //
    
    return status;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst){
    s21_cv_result status = S21_CV_OK;
    
    bool sign;
    uint8_t scale;
    uint96_t mantissa;
    parser_decimal(&src, &sign, &scale, &mantissa);

    uint96_t new_mantissa = shift_right_96(mantissa, scale);

    *dst = new_mantissa.bit[0];

    return status;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst){

    s21_cv_result status = S21_CV_OK;

    bool sign;
    uint8_t scale;
    uint96_t mantissa;
    parser_decimal(&src, &sign, &scale, &mantissa);

    
    return status;
}

int s21_truncate(s21_decimal value, s21_decimal *result){
    s21_cv_result status = S21_CV_OK;
    
    bool sign;
    uint8_t scale = 0;
    uint96_t mantissa = {0};
    parser_decimal(&value, &sign, &scale, &mantissa);

    uint96_t mantissa_result = shift_right_96(mantissa, scale);

    *result = create_decimal(sign, 0, &mantissa_result);

   return status;
}

bool is_correct_decimal(s21_decimal number){
     
    bool status = true;

    int scale = get_scale(number); 
    if(scale < 0 || scale > 28){
        status = false;
    }
    else{
        if(number.bit[3] << 16 == 0){
            status = false;
        }
    }

    return status;
}

s21_decimal s21_decimal_get_max(void){
    return (s21_decimal){ .bit = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0} };
}

s21_decimal s21_decimal_get_min(void){
    return (s21_decimal){ .bit = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000} };
}

s21_decimal s21_decimal_get_inf(void){
    return (s21_decimal){ .bit = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0} };
}  

void clear_decimal(s21_decimal *number){
    number->bit[0] = 0;
    number->bit[1] = 0;
    number->bit[2] = 0;
    number->bit[3] = 0;
}
