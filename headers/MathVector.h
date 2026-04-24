#ifndef FIRSTLAB_MATHVECTOR_H
#define FIRSTLAB_MATHVECTOR_H

#include "FieldInfo.h"
#include <stdbool.h>
#include <stddef.h>

typedef struct {
    const size_t dimension;
    const FieldInfo *field_info;
    void *data;
} MathVector;

MathVector *create_math_vector(size_t dimension, const FieldInfo *field_info);
void *get_value(const MathVector *math_vector, size_t index);
bool set_value(const MathVector *math_vector, size_t index, const void *value);
bool sum(const MathVector *V1, const MathVector *V2, const MathVector *res);
bool dot_product(const MathVector *V1, const MathVector *V2, void *res, void *mult);
bool destroy(MathVector *math_vector);

#endif //FIRSTLAB_MATHVECTOR_H