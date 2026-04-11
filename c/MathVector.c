#include "../headers/MathVector.h"
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>

MathVector *create_math_vector(size_t dimension, const FieldInfo *field_info) {
    if (field_info == NULL) {
        errno = EINVAL;
        return NULL;
    }

    MathVector *math_vector = (MathVector *) malloc(sizeof(MathVector));
    if (math_vector == NULL) {
        errno = ENOMEM;
        return NULL;
    }

    math_vector->dimension = dimension;
    math_vector->field_info = field_info;
    math_vector->data = malloc(dimension * field_info->size);;
    if (math_vector->data == NULL) {
        errno = ENOMEM;
        free(math_vector);
        return NULL;
    }

    return math_vector;
}

void *get_value(const MathVector *math_vector, size_t index) {
    if (math_vector == NULL || index >= math_vector->dimension) {
        errno = EINVAL;
        return NULL;
    }

    return math_vector->data + math_vector->field_info->size * index;
}

bool set_value(MathVector *math_vector, size_t index, const void *value) {
    if (math_vector == NULL || index >= math_vector->dimension || value == NULL) {
        errno = EINVAL;
        return false;
    }

    void *value_ptr = get_value(math_vector, index);

    if (value_ptr == NULL || !math_vector->field_info->assign(value_ptr, value)) {
        return false;
    }

    return true;
}

static bool two_vectors_is_correct(const MathVector *V1, const MathVector *V2) {
    if (V1 != NULL && V2 != NULL &&
        V1->dimension == V2->dimension &&
        V1->field_info->name == V2->field_info->name) {
        return true;
        }
    return false;
}

static bool three_vectors_is_correct(const MathVector *V1, const MathVector *V2, const MathVector *V3) {
    if (V1 != NULL && V2 != NULL && V3 != NULL &&
        V1->dimension == V2->dimension && V2->dimension == V3->dimension &&
        V1->field_info->name == V2->field_info->name &&
        V2->field_info->name == V3->field_info->name) {
        return true;
    }
    return false;
}

bool sum(const MathVector *V1, const MathVector *V2, MathVector *res) {
    if (!three_vectors_is_correct(V1, V2, res)) {
        errno = EINVAL;
        return false;
    }

    for (size_t index = 0; index < res->dimension; ++index) {
        if (!res->field_info->sum(get_value(V1, index), get_value(V2, index), get_value(res, index))) {
            return false;
        }
    }

    return true;
}

bool dot_product(const MathVector *V1, const MathVector *V2, void *res, void *mult) {
    if (!two_vectors_is_correct(V1, V2)) {
        errno = EINVAL;
        return false;
    }

    for (size_t index = 0; index < V1->dimension; ++index) {
        if (!V1->field_info->mult(get_value(V1, index), get_value(V2, index), mult)) {
            return false;
        }
        if (!V1->field_info->sum(mult, res, res)) {
            return false;
        }
    }
    return true;
}

// bool destroy(MathVector *math_vector) {
//     if (math_vector == NULL) {
//         errno = EINVAL;
//         return false;
//     }
//     free(math_vector->data);
//     free(math_vector);
//     return true;
// }