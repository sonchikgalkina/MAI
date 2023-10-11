#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

bool integer(const char *str) {
    if (strlen(str) > 10) {
        return false;
    }
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

bool string(char *str) {
    if (strlen(str) > 6) {
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

int multiple(int a, int b) {
    if (b == 0) {
        return false;
    }
    if (a % b == 0) {
        return 1;
    }
    else {
        return 0;
    }
}

bool triangle(double num1, double num2, double num3, double epsilon) {
    if (num1 <= 0 || num2 <= 0 || num3 <= 0) {
        return false;
    }
    if (fabs((num1 * num1) + (num2 * num2) - (num3 * num3)) <= epsilon || fabs((num1 * num1) + (num3 * num3) - (num2 * num2)) <= epsilon || fabs((num2 * num2) + (num3 * num3) - (num1 * num1)) <= epsilon) {
        return true;
    }
    else {
        return false;
    }
}

void permutation(double* array, int count, double eps, double* roots) {
    double a, b, c;
    int root_index = 0;
    for (int i = 0; i < count; i += 3)
    {
        a = array[i];
        b = array[i+1];
        c = array[i+2];
        double D = b*b - 4*a*c;
        if (D > eps)
        {
            double x1 = (-b + sqrt(D)) / (2*a);
            double x2 = (-b - sqrt(D)) / (2*a);
            roots[root_index++] = x1;
            roots[root_index++] = x2;
        }
        else if (fabs(D) < eps)
        {
            double x = -b / (2*a);
            roots[root_index] = x;
            root_index++;
        } else
        {
            printf("No real roots\n");
        }
    }
}


void swap(double *a, double *b) {
    double temp = *a;
    *a = *b;
    *b = temp;
}

int koeficients_permutation(double lst[], int n, double* array) {
    int count = 0;
    if (n < 2) {
        for (int i = 0; i < 3; i++) {
            array[count] = lst[i];
            count++;
        }
        return count;
    }
    for (int i = 0; i < n; i++) {
        swap(&lst[i], &lst[n-1]);
        count += koeficients_permutation(lst, n-1, array + count);
        swap(&lst[i], &lst[n-1]);
    }
    return count;
}

int main(int argc, char *argv[]) {
    if (strlen(argv[1]) != 2 || argv[1][0] != '-' && argv[1][0] != '/') {
        printf("invalid flag\n");
        return 0;
    }
    else {
        if (argv[1][1] == 'q') {
            if (argc != 6) {
                printf("error\n");
            }
            else {
                if ((string(argv[2])) && (string(argv[3])) && (string(argv[4])) && (string(argv[5]))) {
                    double eps = atof(argv[2]);
                    int n = 3;
                    double lst[n];
                    for (int i = 0; i < n; i ++) {
                        lst[i] = atof(argv[i+3]);
                    }
                    double roots[12] = {0};
                    double array[18] = {0};
                    int count = koeficients_permutation(lst, n, array);
                    permutation(array, count, eps, roots);
                    for(int j = 0; j < 12; j++) {
                        printf("%.1f ", roots[j]);
                        printf("\n");
                    }
                    printf("\n");
                }
                else {
                    printf("error\n");
                }
            }
        }
        else if (argv[1][1] == 'm') {
            if (argc != 4) {
                printf("error\n");
                return 0;
            }
            else {
                if (integer(argv[2]) && integer(argv[3])) {
                    if (multiple(atoi(argv[2]), atoi(argv[3]))) {
                        printf("yes\n");
                    }
                    else {
                        printf("no\n");
                    }
                }
                else {
                    printf("error\n");
                }
            }
        }
        else if (argv[1][1] == 't') {
            if (argc != 6) {
                printf("error\n");
                return 0;
            }
            else {
                if ((string(argv[2])) && (string(argv[3])) && string(argv[4]) && string(argv[5])) {
                    if (triangle(atof(argv[2]), atof(argv[3]), atof(argv[4]), atof(argv[5]))) {
                        printf("it is triangle\n");
                    }
                    else {
                        printf("it is not triangle\n");
                    }
                }
                else {
                    printf("error\n");
                }
            }
        }
        else {
            printf("invalid flag\n");
        }
    }
}
