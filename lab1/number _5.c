#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

bool string(char *str) {
    if (strlen(str) > 10) {
        return 6;
    }
    int count = 0;
    if (*str == '\0') {
        return false;
    }
    if (*str == '+' || *str == '-') {
        str++;
        if (*str == '\0') {
            return false;
        }
    }
    while (*str) {
        if (*str >= '0' && *str <= '9') {
            str++;
            if (*str == '.') {
                count += 1;
                str++;
                if (*str == '\0') {
                    return false;
                }
            }
        }
        else {
            return false;
        }
    }
    if (count == 0 || count > 1) {
        return false;
    }
    return true;
}

double factorial(int a) {
    double res = 1.0;
    for (int i = 1; i <= a; i++) {
        res *= i;
    }
    return res;
}

unsigned long long Factorial(unsigned long long a) {
    if (a <= 1) {
        return 1;
    }
    return a * Factorial(a - 2);
}

double function_a(double x, double epsilon) {
    double summ = 0;
    double y = exp(x);
    while (fabs(summ) > epsilon) {
        x--;
        y = cos(x);
    }
    summ += y;
    return summ;
}

double function_b(double x, double epsilon) {
    double summ = 0;
    double y = cos(x);
    while (fabs(summ) > epsilon) {
        x--;
        y = cos(x);
    }
    summ += y;
    return summ;
}

double function_c(double x, double epsilon) {
    double result = 1.0;
    double summ = 0.0;
    int n = 0;
    while (fabs(summ) > epsilon) {
        result = (pow(3, 3 * n) * pow(factorial(n), 3) * (x, 2 * n)) / factorial(3 * n);
        summ += result;
        n++;
    }
    return summ;
}

double function_d(double x, double epsilon) {
    double summ = 0.0;
    int n = 1;
    double term;
    do {
        term = pow(-1, n) * Factorial(2 * n - 1) * pow(x, 2 * n) / Factorial(2 * n);
        summ += term;
        n++;
    }
    while (fabs(term) > epsilon);
    return summ;
}


int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("error\n");
        return 1;
    }
    if (!string(argv[1])) {
        printf("invalid epsilon\n");
        return 1;
    }
    if (!string(argv[2])) {
        printf("invalid x\n");
        return 1;
    }

    double epsilon = atof(argv[1]);
    double x = atof(argv[2]);

    if (epsilon <= 0) {
        printf("invalid epsilon\n");
        return 1;
    }

    double result1 = function_a(x, epsilon);
    double result2 = function_b(x, epsilon);
    printf("%lf\n", result1);
    printf("%lf\n", result2);

    if (abs(x) < 1) {
        double result3 = function_c(x, epsilon);
        double result4 = function_d(x, epsilon);
        printf("%lf\n", result3);
        printf("%lf\n", result4);
    }
    else {
        printf("invalid x\n");
        return 1;
    }
    return 0;
}
