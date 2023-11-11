#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <stdarg.h>

struct Employee {
    int id;
    char name[256];
    char surname[256];
    double salary;
}typedef employee;

enum checker {
    ok,
    error_memory,
    invalid
};

int comparator_up(const void* a, const void* b) {
    const employee* worker1 = (const employee*)a;
    const employee* worker2 = (const employee*)b;
    if (worker1->salary != worker2->salary) {
        return worker1->salary - worker2->salary;
    }
    else if (strcmp(worker1->surname, worker2->surname) != 0) {
        return strcmp(worker1->surname, worker2->surname);
    }
    else if(strcmp(worker1->name, worker2->name) != 0) {
        return strcmp(worker1->name, worker2->name);
    }
    else {
        return worker1->id - worker2 -> id;
    }
}

int comparator_down(const void* a, const void* b) {
    const employee* worker1 = (const employee*)a;
    const employee* worker2 = (const employee*)b;
    if (worker1->salary < worker2->salary) {
        return 1;
    }
    else if (worker1->salary > worker2->salary) {
        return -1;
    }
    else if (strcmp(worker1->surname, worker2->surname) != 0) {
        return strcmp(worker2->surname, worker1->surname);
    }
    else if(strcmp(worker1->name, worker2->name) != 0) {
        return strcmp(worker2->name, worker1->name);
    }
    else {
        return worker2->id - worker1 -> id;
    }
}

void my_sort(employee* workers, int count, int (*comp)(const void*, const void*)) {
    qsort(workers, count, sizeof(employee), comp);
}

enum checker load_info(FILE* in, employee** res, int* len) {
    *len = 0;
    char line[256];
    while (fgets(line, sizeof(line), in) != NULL) {
        (*len)++;
    }
    *res = (employee*)malloc(sizeof(employee) *(*len));
    if (!(*res)) {
        return error_memory;
    }
    fseek(in, 0, SEEK_SET);
    int index = 0;
    for (int i = 0; i < (*len); i++) {
        int id;
        char name[256], surname[256];
        float salary;
        fgets(line, sizeof(line), in);
        sscanf(line, "%d %s %s %lf", &((*res)[i].id), (*res)[i].name, (*res)[i].surname, &((*res)[i].salary));
         if ((*res)[i].id < 0 || (*res)[i].salary < 0 || strlen((*res)[i].name) < 2 || strlen((*res)[i].surname) < 2) {
            free(*res);
            return invalid;
        }
    }
    return ok;
}

void out_info(FILE* out, employee* res, int count) {
    for (int i = 0; i < count; i++) {
        fprintf(out, "%d %s %s %lf\n", res[i].id, res[i].name, res[i].surname, res[i].salary);
    }
}

int main(int argc, char*argv[]) {
    if( (argc != 4) || (strlen(argv[2]) != 2) || ((argv[2][0]!='-') && (argv[2][0]!='/')) || (argv[2][1] != 'a' && argv[2][1] != 'd')) {
        printf("invalid input\n");
        return 0;
    }
    FILE* in;
    FILE* out;
    if(!(in = fopen(argv[1], "r"))) {
        printf("the input file could not to be opened\n");
        return 0;
    }
    int count;
    employee* res;
    enum checker load_check = load_info(in, &res, &count);
    if (load_check == error_memory) {
        printf("memory allocation error\n");
        fclose(in);
        return 0;
    }
    if (load_check == invalid ) {
        printf("error\n");
        fclose(in);
        return 0;
    }
    if(!(out = fopen(argv[3], "w"))) {
        printf("the output file could not to be opened\n");
        fclose(in);
        return 0;
    }
    if (argv[2][1] == 'a') {
        my_sort(res, count, comparator_up);
        out_info(out, res, count);
    }
    if (argv[2][1] == 'd') {
        my_sort(res, count, comparator_down);
        out_info(out, res, count);
    }
    free(res);
    fclose(in);
    fclose(out);
    return 0;
}
