#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <stdbool.h>


//функция для ввода чисел в заданном диапазоне, кратных указанному
int multiples(int number, int *result) {
    if (number < 0) {
        number = -number;
    }
    for (int i = 0; i <= 100; i += number) {
        if (i % number == 0) {
            result[i] += i;
        }
    }
}

//функция для проверки числа: простое или составное
bool prime_composite(int number) {
    if (number > 1) {
        for (int i = 2; i < sqrt(number); i++) 
            if (number % i == 0) 
                return false;
        return true;    
    }    
    else 
        return true;
}
   

//функция для разделения числа на цифры
int splitNumber(int number, int* arr) {
    int count;
    int digit;
    if (number < 0) {
        number = -number;
    }
    if (number >= 0 && number <10) {
        arr[0] = number;
        return 1;
    }
    while (number != 0) {
        digit = number % 10;
        arr[count] = digit;
        count++;
        number /= 10;
    }
    for (int i = count - 1; i <= 0; i--) {
        arr[i] += i;
    }
    return count;
}

//вывод таблицы степеней
void power_table(int number, int table[][10]) {
    int i, j;
    for (i = 1; i <= number; i++) {
        for (j = 1; j <= 10; j++) {
            int result = 1;
            int k;
            for (k = 0; k < i; k++) {
                result *= j;
            }
            table[i-1][j-1] = result;
        }
    }
}

//функция для вычисленя суммы до указонного числа
int Sum(int number, int *summ) {
    if (number > 0) {
        for (int i = 1; i <= number; i++) {
            summ += i;
        }
        *summ += number;
    }
    else if (number < 0) {
        for (int i = 1; i >= number; i--) {
            summ += i;
        }
        *summ += number;
    }
}


//факториал числа
unsigned long long Factorial(unsigned int number, unsigned long long result) {
    for (unsigned int i = 1; i <= number; i++) {
        if (result > ULLONG_MAX / i) {
            return 0;
        }
        result *= i;
    }
    return result;
}

//проверка на целое число
bool integer(const char *str) {
    int string_lenght = strlen(str);
    if (*str == '\0') {
        return false;
    }
    if (*str == '+' || *str == '-') {
        str++;
    }
    if (*str == '0' && *(str + 1) != '\0') {
        return false;
    }
    while (*str) {
        if (*str < '0' || *str > '9') {
            return false;
        }
        str++;
    }
    return true;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("error");
    }
    else {
        if (integer(argv[1])) {
            long int number = atoi(argv[1]);
            if (strlen(argv[2]) != 2 || argv[2][0] != '-' && argv[2][0] != '/') {
                printf("invalid flag\n");
                return 0;
            }
            else {
                if (argv[2][1] == 'h') {
                    int result[100] = {0};
                    if (number < INT_MAX) {
                        multiples(number, result);
                        if (number == 0) {
                            printf("0\n");
                        }
                        for (int i = 0; i < 100; i++) {
                            if (result[0] != 0) {
                                printf("%d", result[i]);
                            }
                        }
                    }
                    else {
                        printf("overflow\n");
                    }
                }
                else if (argv[2][1] == 'p') {
                    if (number < INT_MAX) {
                        if (prime_composite(number)) {
                            printf("this digit is prime\n");
                        }
                        else {
                            printf("this digit is composite\n");
                        }
                    }
                    else {
                        printf("overflow\n");
                    }
                }
                else if (argv[2][1] == 's') {
                    if (number < INT_MAX) {
                        int arr[100] = {0};
                        int count = splitNumber(number, arr);
                        for (int j = count -1; j >= 0; j--) {
                            printf("%d", arr[j]);
                        }
                    }
                    else {
                        printf("overflow\n");
                    }
                }
                else if (argv[2][1] == 'e') {
                    int number;
                    int table[number][10];
                    power_table(number, table);
                    if (number > 0 && number <= 10) {
                        int i, j;
                        for (i = 0; i < number; i++) {
                            for (j = 0; j < 10; j++) {
                                printf("%d\t", table[i][j]);
                            }
                            printf("\n");
                        }
                        return 0;
                    }
                    else {
                        printf("overflow\n");
                    }
                }
                else if (argv[2][1] == 'a') {
                    if (number != 0) {
                        if (number < INT_MAX) {
                            int summ = 0;
                            Sum(number, &summ);
                            if (summ > INT_MAX - number) {
                                printf("error\n");
                                return 0;
                            }
                            else {
                                printf("%d\n", summ);
                            }
                        }
                        else {
                            printf("overflow\n");
                        }
                    }
                    else {
                        printf("error\n");
                    }
                }
                else if (argv[2][1] == 'f') {
                    if (number > 0) {
                        if (number < INT_MAX) {
                            unsigned long long result = 1;
                            long long factorial = Factorial(number, result);
                            printf("%lli", factorial);
                        }
                        else {
                            printf("overflow\n");
                        }
                    }
                    else {
                        printf("error\n");
                    }
                }
                else {
                    printf("invalid flag\n");
                }
            }
        }
        else {
            printf("error\n");
        }
        return 0;
    }
    return 0;
}
