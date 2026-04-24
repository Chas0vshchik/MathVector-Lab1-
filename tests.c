#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>

#include "headers/MathVector.h"
#include "headers/FieldInfo.h"
#include "headers/UsersStructs.h"

void complex_mult_test() {
    printf("complex_mult_test: ");

    const Complex a = {1, 2};
    const Complex b = {3, 4};

    const void *f = &a;
    const void *s = &b;
    void *ans = malloc(sizeof(Complex));

    const FieldInfo *field_info = get_comp_field_info();
    field_info->mult(f, s, ans);
    const Complex *res = ans;

    assert(res->real == -5);
    assert(res->imag == 10);

    free(ans);
}

void create_int_vector_test() {
    printf("create_int_vector_test: ");

    //Valid creation
    MathVector *vector = create_math_vector(3, get_int_field_info());
    assert(vector != NULL);
    assert(vector->dimension == 3);
    assert(vector->field_info == get_int_field_info());
    assert(vector->data != NULL);

    //Invalid creation (NULL FieldInfo)
    errno = 0;
    vector = create_math_vector(3, NULL);
    assert(vector == NULL);
    assert(errno == EINVAL);

    printf("OK\n");

    destroy(vector);
}

void set_get_value_test() {
    printf("set_get_value_test: ");

    //Valid creation
    MathVector *vector = create_math_vector(3, get_int_field_info());
    assert(vector != NULL);
    assert(vector->dimension == 3);
    assert(vector->field_info == get_int_field_info());
    assert(vector->data != NULL);

    int value = 1;

    //Valid set and get
    set_value(vector, 0, &value);
    const int *check = get_value(vector, 0);
    assert(*check == value);

    value = 2;
    set_value(vector, 1, &value);
    check = get_value(vector, 1);
    assert(*check == value);

    value = 3;
    set_value(vector, 2, &value);
    check = get_value(vector, 2);
    assert(*check == value);

    //Invalid get (NULL math_vector)
    errno = 0;
    assert(get_value(NULL, 0) == NULL);
    assert(errno == EINVAL);

    //Invalid get (Big index)
    errno = 0;
    assert(get_value(vector, 100) == NULL);
    assert(errno == EINVAL);

    //Invalid set (NULL math_vector)
    errno = 0;
    assert(set_value(NULL, 0, &value) == false);
    assert(errno == EINVAL);

    //Invalid set (Big index)
    errno = 0;
    assert(set_value(vector, 100, &value) == false);
    assert(errno == EINVAL);

    //Invalid set (NULL value)
    errno = 0;
    assert(set_value(vector, 0, NULL) == false);
    assert(errno == EINVAL);

    printf("OK\n");

    destroy(vector);
}

void vector_sum_int_test() {
    printf("vector_sum_int_test: ");

    //Valid creation
    MathVector *vector = create_math_vector(3, get_int_field_info());
    assert(vector != NULL);
    assert(vector->dimension == 3);
    assert(vector->field_info == get_int_field_info());
    assert(vector->data != NULL);
    int value = 1;
    set_value(vector, 0, &value);
    const int *check = get_value(vector, 0);
    assert(*check == value);
    value = 2;
    set_value(vector, 1, &value);
    check = get_value(vector, 1);
    assert(*check == value);
    value = 3;
    set_value(vector, 2, &value);
    check = get_value(vector, 2);
    assert(*check == value);

    MathVector *vector1 = create_math_vector(3, get_int_field_info());
    assert(vector1 != NULL);
    assert(vector1->dimension == 3);
    assert(vector1->field_info == get_int_field_info());
    assert(vector1->data != NULL);
    int value1 = 4;
    set_value(vector1, 0, &value1);
    const int *check1 = get_value(vector1, 0);
    assert(*check1 == value1);
    value1 = 5;
    set_value(vector1, 1, &value1);
    check1 = get_value(vector1, 1);
    assert(*check1 == value1);
    value1 = 6;
    set_value(vector1, 2, &value1);
    check1 = get_value(vector1, 2);
    assert(*check1 == value1);

    //Valid sum
    MathVector *ans = create_math_vector(3, get_int_field_info());

    sum(vector, vector1, ans);
    check1 = get_value(ans, 0);
    assert(*check1 == 5);
    check1 = get_value(ans, 1);
    assert(*check1 == 7);
    check1 = get_value(ans, 2);
    assert(*check1 == 9);

    //Invalid sum
    MathVector *err1 = create_math_vector(4, get_int_field_info());
    MathVector *err2 = create_math_vector(3, get_comp_field_info());

    //NULL
    errno = 0;
    assert(sum(NULL, vector1, ans) == false);
    assert(errno == EINVAL);

    //Different dimensions
    errno = 0;
    assert(sum(vector, err1, ans) == false);
    assert(errno == EINVAL);

    //Different field_info
    errno = 0;
    assert(sum(vector, vector1, err2) == false);
    assert(errno == EINVAL);

    printf("OK\n");

    destroy(vector);
    destroy(vector1);
    destroy(ans);
    destroy(err1);
    destroy(err2);
}

void vector_sum_comp_test() {
    printf("vector_sum_comp_test: ");

    //Valid creation
    MathVector *vector = create_math_vector(1, get_comp_field_info());
    assert(vector != NULL);
    assert(vector->dimension == 1);
    assert(vector->field_info == get_comp_field_info());
    assert(vector->data != NULL);
    const Complex value = {1, 2};
    set_value(vector, 0, &value);
    const Complex *check = get_value(vector, 0);
    assert(check->real == value.real);
    assert(check->imag == value.imag);

    MathVector *vector1 = create_math_vector(1, get_comp_field_info());
    assert(vector1 != NULL);
    assert(vector1->dimension == 1);
    assert(vector1->field_info == get_comp_field_info());
    assert(vector1->data != NULL);
    const Complex value1 = {3, 4};
    set_value(vector1, 0, &value1);
    const Complex *check1 = get_value(vector1, 0);
    assert(check1->real == value1.real);
    assert(check1->imag == value1.imag);

    //Valid sum
    MathVector *ans = create_math_vector(1, get_comp_field_info());

    sum(vector, vector1, ans);
    check1 = get_value(ans, 0);
    assert(check1->real == 4);
    assert(check1->imag == 6);

    //Invalid sum
    MathVector *err1 = create_math_vector(4, get_comp_field_info());
    MathVector *err2 = create_math_vector(1, get_int_field_info());

    //NULL
    errno = 0;
    assert(sum(NULL, vector1, ans) == false);
    assert(errno == EINVAL);

    //Different dimensions
    errno = 0;
    assert(sum(vector, err1, ans) == false);
    assert(errno == EINVAL);

    //Different field_info
    errno = 0;
    assert(sum(vector, vector1, err2) == false);
    assert(errno == EINVAL);

    printf("OK\n");

    destroy(vector);
    destroy(vector1);
    destroy(ans);
    destroy(err1);
    destroy(err2);
}

void vector_dot_product_int_test() {
    printf("vector_dot_product_int_test: ");

    //Valid creation
    MathVector *vector = create_math_vector(2, get_int_field_info());
    assert(vector != NULL);
    assert(vector->dimension == 2);
    assert(vector->field_info == get_int_field_info());
    assert(vector->data != NULL);
    int value = 1;
    set_value(vector, 0, &value);
    const int *check = get_value(vector, 0);
    assert(*check == value);
    value = 2;
    set_value(vector, 1, &value);
    check = get_value(vector, 1);
    assert(*check == value);

    //Valid dot product
    void *res = malloc(sizeof(int));
    void *mult = malloc(sizeof(int));

    int *int_null = res;
    *int_null = 0;
    dot_product(vector, vector, res, mult);
    const int *int_res = res;

    assert(*int_res == 5);

    //Invalid dot product
    MathVector *err1 = create_math_vector(4, get_int_field_info());
    MathVector *err2 = create_math_vector(2, get_comp_field_info());

    //NULL
    errno = 0;
    assert(dot_product(NULL, vector, res, mult) == false);
    assert(errno == EINVAL);

    //Different dimensions
    errno = 0;
    assert(dot_product(vector, err1, res, mult) == false);
    assert(errno == EINVAL);

    //Different field_info
    errno = 0;
    assert(dot_product(vector, err2, res, mult) == false);
    assert(errno == EINVAL);

    printf("OK\n");

    free(res);
    free(mult);
    destroy(vector);
    destroy(err1);
    destroy(err2);
}

void vector_dot_product_comp_test() {
    printf("vector_dot_product_comp_test: ");

    //Valid creation
    MathVector *vector = create_math_vector(2, get_comp_field_info());
    assert(vector != NULL);
    assert(vector->dimension == 2);
    assert(vector->field_info == get_comp_field_info());
    assert(vector->data != NULL);
    const Complex value = {1, 2};
    set_value(vector, 0, &value);
    const Complex *check = get_value(vector, 0);
    assert(check->real == value.real);
    assert(check->imag == value.imag);
    const Complex value1 = {3, 4};
    set_value(vector, 1, &value1);
    check = get_value(vector, 1);
    assert(check->real == value1.real);
    assert(check->imag == value1.imag);

    //Valid dot product
    void *res = malloc(sizeof(int));
    void *mult = malloc(sizeof(int));

    Complex *comp_null = res;
    comp_null->real = 0;
    comp_null->imag = 0;
    dot_product(vector, vector, res, mult);
    const Complex *comp_res = res;

    assert(comp_res->real == -10);
    assert(comp_res->imag == 28);

    //Invalid dot product
    MathVector *err1 = create_math_vector(4, get_comp_field_info());
    MathVector *err2 = create_math_vector(2, get_int_field_info());

    //NULL
    errno = 0;
    assert(dot_product(NULL, vector, res, mult) == false);
    assert(errno == EINVAL);

    //Different dimensions
    errno = 0;
    assert(dot_product(vector, err1, res, mult) == false);
    assert(errno == EINVAL);

    //Different field_info
    errno = 0;
    assert(dot_product(vector, err2, res, mult) == false);
    assert(errno == EINVAL);

    printf("OK\n");

    free(res);
    free(mult);
    destroy(vector);
    destroy(err1);
    destroy(err2);
}

int main() {
    printf("Starting DynamicArray tests\n\n");

    complex_mult_test();
    create_int_vector_test();
    set_get_value_test();
    vector_sum_int_test();
    vector_sum_comp_test();
    vector_dot_product_int_test();
    vector_dot_product_comp_test();

    printf("\nAll tests passed successfully\n");

    return 0;
}
