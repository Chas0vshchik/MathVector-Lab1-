#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/FieldInfo.h"
#include "../headers/MathVector.h"
#include "../headers/UsersStructs.h"
#include "../headers/UI.h"

#define NUMBER_OF_VECTORS 50

static MathVector *vectors[NUMBER_OF_VECTORS];
static int current_size = 0;

extern const FieldInfo *get_int_field_info(void);
extern const FieldInfo *get_comp_field_info(void);

static int read_int(const char *phrase) {
    int value = 0;
    int result;

    while (1) {
        printf("%s", phrase);
        result = scanf("%d", &value);
        if (result == 1) {
            while (getchar() != '\n') {}
            return value;
        }
        printf("Invalid input. Please enter an integer.\n\n");
        while (getchar() != '\n');
    }
}

static Complex read_complex(const char *phrase1, const char *phrase2) {
    Complex value;
    value.real = read_int(phrase1);
    value.imag = read_int(phrase2);
    return value;
}

static void print_vector(const int index) {
    if (index >= current_size) {
        printf("Invalid index.\n\n");
    }

    if (strcmp(vectors[index]->field_info->name, "int") == 0) {
        printf("Vector number %d: [", index);
        int *elem = NULL;
        for (int i = 0; i < vectors[index]->dimension - 1; i++) {
            elem = get_value(vectors[index], i);
            printf("%d, ", *elem);
        }
        elem = get_value(vectors[index], vectors[index]->dimension - 1);
        printf("%d]\n", *elem);

        return;
    }

    if (strcmp(vectors[index]->field_info->name, "Complex") == 0) {
        printf("Vector number %d: [", index);
        Complex *elem = NULL;
        for (int i = 0; i < vectors[index]->dimension - 1; i++) {
            elem = get_value(vectors[index], i);
            printf("%d", elem->real);
            if (elem->imag >= 0) {
                printf("+");
            }
            printf("%di, ", elem->imag);
        }
        elem = get_value(vectors[index], vectors[index]->dimension - 1);
        printf("%d", elem->real);
        if (elem->imag >= 0) {
            printf("+");
        }
        printf("%di]\n", elem->imag);

        return;
    }
}

void ui() {
    int choice;
    int dimension;
    int int_value;
    int V1, V2;
    void *res = malloc(sizeof(int));
    void *mult = malloc(sizeof(int));
    int *int_null = NULL;
    Complex *comp_null = NULL;
    int *int_res = NULL;
    Complex *comp_res = NULL;
    Complex comp_value;

    while (1) {
        printf("\n=== Math Vectors UI ===\n");
        printf("1. Create vector with int numbers\n");
        printf("2. Create vector with complex numbers\n");
        printf("3. View all vectors\n");
        printf("4. Sum two vectors\n");
        printf("5. Dot product for two vectors\n");
        printf("0. Exit\n\n");

        choice = read_int("Enter your choice: ");

        switch (choice) {
            case 1:
                if (current_size >= NUMBER_OF_VECTORS) {
                    printf("Warning: There are too many vectors, please restart the program. \n\n");
                    break;
                }

                dimension = read_int("Enter dimension: ");
                vectors[current_size] = create_math_vector(dimension, get_int_field_info());

                printf("Enter %d values\n", dimension);
                for (int i = 0; i < dimension; i++) {
                    int_value = read_int("Enter int value: ");
                    set_value(vectors[current_size], i, &int_value);
                }

                ++current_size;
                break;
            case 2:
                if (current_size >= NUMBER_OF_VECTORS) {
                    printf("Warning: There are too many vectors, please restart the program. \n\n");
                    break;
                }

                dimension = read_int("Enter dimension: ");
                vectors[current_size] = create_math_vector(dimension, get_comp_field_info());

                printf("Enter %d values\n", dimension);

                for (int i = 0; i < dimension; i++) {
                    comp_value = read_complex("Enter real part: ", "Enter imag part: ");
                    set_value(vectors[current_size], i, &comp_value);
                }

                ++current_size;
                break;
            case 3:
                if (current_size == 0) {
                    printf("No vectors yet. \n\n");
                    break;
                }

                printf("There are %d vectors.\n", current_size);
                for (int i = 0; i < current_size; i++) {
                    print_vector(i);
                }
                printf("\n");
                break;
            case 4:
                if (current_size == 0) {
                    printf("There are not enough vectors. \n\n");
                    break;
                }

                printf("Write the numbers of the vectors for sum \n\n");
                while (1) {
                    V1 = read_int("Enter first number: ");
                    if (V1 >= current_size) {
                        printf("Invalid index.\n\n");
                    }
                    else {
                        break;
                    }
                }
                while (1) {
                    V2 = read_int("Enter second number: ");
                    if (V1 >= current_size) {
                        printf("Invalid index.\n\n");
                    }
                    else {
                        break;
                    }
                }
                if (strcmp(vectors[V1]->field_info->name, vectors[V2]->field_info->name) != 0) {
                    printf("The program cannot work with vectors of different types. \n\n");
                    break;
                }
                if (vectors[V1]->dimension != vectors[V2]->dimension) {
                    printf("Vectors have different dimensions. \n\n");
                    break;
                }

                vectors[current_size] = create_math_vector(vectors[V1]->dimension, vectors[V1]->field_info);
                sum(vectors[V1],vectors[V2],vectors[current_size]);
                ++current_size;

                printf("Sum: ");
                print_vector(current_size - 1);

                printf("\n");
                break;
            case 5:
                if (current_size == 0) {
                    printf("There are not enough vectors. \n\n");
                    break;
                }

                printf("Write the numbers of the vectors for dot product \n\n");
                while (1) {
                    V1 = read_int("Enter first number: ");
                    if (V1 >= current_size) {
                        printf("Invalid index.\n\n");
                    }
                    else {
                        break;
                    }
                }
                while (1) {
                    V2 = read_int("Enter second number: ");
                    if (V1 >= current_size) {
                        printf("Invalid index.\n\n");
                    }
                    else {
                        break;
                    }
                }
                if (strcmp(vectors[V1]->field_info->name, vectors[V2]->field_info->name) != 0) {
                    printf("The program cannot work with vectors of different types. \n\n");
                    break;
                }
                if (vectors[V1]->dimension != vectors[V2]->dimension) {
                    printf("Vectors have different dimensions. \n\n");
                    break;
                }

                if (strcmp(vectors[V1]->field_info->name, "int") == 0) {
                    int_null = res;
                    *int_null = 0;
                    dot_product(vectors[V1], vectors[V2], res, mult);
                    printf("Dot product: ");
                    int_res = res;
                    printf("%d\n\n", *int_res);
                    break;
                }
                if (strcmp(vectors[V1]->field_info->name, "Complex") == 0) {
                    comp_null = res;
                    comp_null->real = 0;
                    comp_null->imag = 0;
                    dot_product(vectors[V1], vectors[V2], res, mult);
                    printf("Dot product: ");
                    comp_res = res;
                    printf("%d", comp_res->real);
                    if (comp_res->imag >= 0) {
                        printf("+");
                    }
                    printf("%di]\n\n", comp_res->imag);
                    break;
                }
                break;
            case 0:
                return;
        }
    }
}