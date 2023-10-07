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

void permution(double new_arr[][3], double arr[], int n, int *count) {
    if (n == 1) {
        for (int i = 0; i < 3; i++) {
            new_arr[*count][i] = arr[i];
        }
        (*count)++;
        return;
    }
    for (int i = 0; i < n; i++) {
        permution(new_arr, arr, n - 1, count);
        if (n % 2 == 0) {
            double temp = arr[i];
            arr[i] = arr[n - 1];
            arr[n - 1] = temp;
        }
        else {
            double temp = arr[0];
            arr[0] = arr[n -1];
            arr[n - 1] = temp;
        }
    }
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
                    int count = 0;
                    double new_arr[100][3] = {0.0};
                    double arr[3];
                    double n1 = atof(argv[3]);
                    double n2 = atof(argv[4]);
                    double n3 = atof(argv[5]);
                    double epsilon = atof(argv[2]);
                    arr[0] = n1;
                    arr[1] = n2;
                    arr[3] = n3;

                    permution(new_arr, arr, 3, &count);
                    for (int i = 0; i < count; i++) {
                        double discriminant = pow(new_arr[i][1], 2) - 4 * new_arr[i][0] * new_arr[i][2];
                        if (discriminant > epsilon) {
                            double x1 = (-new_arr[i][1] + sqrt(discriminant)) / (2 * new_arr[i][0]);
                            double x2 = (-new_arr[i][1] - sqrt(discriminant)) / (2 * new_arr[i][0]);
                            printf("%lf %lf %lf\n", new_arr[i][0], new_arr[i][1], new_arr[i][2]);
                            printf("%lf %lf\n", x1, x2);
                            printf("\n");
                        }
                        else if (fabs(discriminant) < epsilon) {
                            double x = - new_arr[i][1] / (2 * new_arr[i][0]);
                            printf("%lf %lf % lf\n", new_arr[i][0], new_arr[i][1], new_arr[i][2]);
                            printf("%lf\n", x);
                            printf("\n");
                        }
                        else {
                            printf("%lf %lf % lf\n", new_arr[i][0], new_arr[i][1], new_arr[i][2]);
                            printf("error\n");
                            printf("\n");
                        }
                    }
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
