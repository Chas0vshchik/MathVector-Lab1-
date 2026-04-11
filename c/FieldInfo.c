#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>

#include "../headers/FieldInfo.h"
#include "../headers/UsersStructs.h"

static FieldInfo *int_field_info = NULL;
static FieldInfo *comp_field_info = NULL;

static bool int_assign(void *res, const void *arg) {
    if (res == NULL || arg == NULL) {
        errno = EINVAL;
        return false;
    }

    int *int_res = (int *) res;
    int *int_arg = (int *) arg;
    *int_res = *int_arg;

    return true;
}

static bool comp_assign(void *res, const void *arg) {
    if (res == NULL || arg == NULL) {
        errno = EINVAL;
        return false;
    }

    Complex *comp_res = (Complex *) res;
    Complex *comp_arg = (Complex *) arg;
    *comp_res = *comp_arg;

    return true;
}

static bool int_sum(const void *a, const void *b, void *res) {
    if (a == NULL || b == NULL || res == NULL) {
        errno = EINVAL;
        return false;
    }

    int *int_a = (int *) a;
    int *int_b = (int *) b;
    int *int_sum = (int *) res;

    *int_sum = *int_a + *int_b;

    return true;
}

static bool comp_sum(const void *a, const void *b, void *res) {
    if (a == NULL || b == NULL || res == NULL) {
        errno = EINVAL;
        return false;
    }

    Complex *comp_a = (Complex *) a;
    Complex *comp_b = (Complex *) b;
    Complex *comp_sum = (Complex *) res;

    comp_sum->real = comp_a->real + comp_b->real;
    comp_sum->imag = comp_a->imag + comp_b->imag;

    return true;
}

static bool int_mult(const void *a, const void *b, void *res) {
    if (a == NULL || b == NULL || res == NULL) {
        errno = EINVAL;
        return false;
    }

    int *int_a = (int *) a;
    int *int_b = (int *) b;
    int *int_mult = (int *) res;

    *int_mult = *int_a * *int_b;

    return true;
}

static bool comp_mult(const void *a, const void *b, void *res) {
    if (a == NULL || b == NULL || res == NULL) {
        errno = EINVAL;
        return false;
    }

    Complex *comp_a = (Complex *) a;
    Complex *comp_b = (Complex *) b;
    Complex *comp_mult = (Complex *) res;

    comp_mult->real = comp_a->real * comp_b->real - comp_a->imag * comp_b->imag;
    comp_mult->imag = comp_a->imag * comp_b->real + comp_a->real * comp_b->imag;

    return true;
}

const FieldInfo *get_int_field_info() {
    if (int_field_info == NULL) {
        int_field_info = (FieldInfo *) malloc(sizeof(FieldInfo));

        if (int_field_info == NULL) {
            errno = ENOMEM;
            return NULL;
        }

        int_field_info->size = sizeof(int);
        int_field_info->name = "int";
        int_field_info->assign = int_assign;
        int_field_info->sum = int_sum;
        int_field_info->mult = int_mult;
    }

    return int_field_info;
}

const FieldInfo *get_comp_field_info() {
    if (comp_field_info == NULL) {
        comp_field_info = (FieldInfo *) malloc(sizeof(FieldInfo));

        if (comp_field_info == NULL) {
            errno = ENOMEM;
            return NULL;
        }

        comp_field_info->size = sizeof(Complex);
        comp_field_info->name = "Complex";
        comp_field_info->assign = comp_assign;
        comp_field_info->sum = comp_sum;
        comp_field_info->mult = comp_mult;
    }

    return comp_field_info;
}
