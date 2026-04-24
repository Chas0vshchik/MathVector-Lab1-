#ifndef FIRSTLAB_FIELDINFO_H
#define FIRSTLAB_FIELDINFO_H

#include <stdbool.h>
#include <stddef.h>

typedef bool (*UnaryOperator)(void *, const void *);
typedef bool (*BinaryOperator)(const void *, const void *, void *);

typedef struct {
    size_t size;
    UnaryOperator assign;
    BinaryOperator sum;
    BinaryOperator mult;
} FieldInfo;

const FieldInfo *get_int_field_info(void);
const FieldInfo *get_comp_field_info(void);

#endif //FIRSTLAB_FIELDINFO_H