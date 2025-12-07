#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>
#include "set.h"

#define INITIAL_CAPACITY 4


// --- Initialization ---

void init_universal_set(UniversalSet* u_set, SetType type) {
    u_set->type = type;
    if (type == TYPE_INT_SET) {
        u_set->data.int_data.size = 0;
        u_set->data.int_data.capacity = INITIAL_CAPACITY;
        u_set->data.int_data.elements = malloc(INITIAL_CAPACITY * sizeof(int));
    } else {
        u_set->data.pair_data.size = 0;
        u_set->data.pair_data.capacity = INITIAL_CAPACITY;
        u_set->data.pair_data.pairs = malloc(INITIAL_CAPACITY * sizeof(OrderedPair));
    }
}

// --- Deletion ---

void free_universal_set(UniversalSet* u_set) {
    if (u_set->type == TYPE_INT_SET) {
        free(u_set->data.int_data.elements);
        u_set->data.int_data.elements = NULL;
    } else {
        free(u_set->data.pair_data.pairs);
        u_set->data.pair_data.pairs = NULL;
    }
    u_set->data.int_data.size = 0;
}

// --- Printing ---

void print_set(UniversalSet* u_set) {
    printf("{");
    if (u_set->type == TYPE_INT_SET) {
       for (int i = 0; i < u_set->data.int_data.size; i++) {
           if (i < u_set->data.int_data.size - 1 ) {
           printf ("%d,", u_set->data.int_data.elements[i]); }
           else {
           printf ("%d", u_set->data.int_data.elements[i]); }
       }

    }
    else {
        for (int i = 0; i < u_set->data.pair_data.size; i++) {
            if (i < u_set->data.pair_data.size - 1 ) {
                printf ("(%d,%d), ", u_set->data.pair_data.pairs[i].first_num, u_set->data.pair_data.pairs[i].second_num); }
            else {
                printf ("(%d,%d)", u_set->data.pair_data.pairs[i].first_num, u_set->data.pair_data.pairs[i].second_num); }
        };
    }
    printf("}\n");
}

// --- Adding elements ---
bool is_present(UniversalSet* u_set, int value ) {
    if (u_set->type == TYPE_INT_SET) {
        for (int i = 0; i < u_set->data.int_data.size; i++) {
            if (u_set->data.int_data.elements[i] == value) {
                return true;
            }
        }

    }
    return false;
}

void add_int(UniversalSet* u_set, int value ) {
    if (u_set->type == TYPE_INT_SET) {
        if (!is_present(u_set, value)) {

            if (u_set->data.int_data.size == u_set->data.int_data.capacity) {
                if (u_set->data.int_data.size == u_set->data.int_data.capacity) {
                    u_set->data.int_data.capacity *= 2;
                    int *temp = realloc(u_set->data.int_data.elements,
                                        u_set->data.int_data.capacity * sizeof(int));

                    if (temp == NULL) {
                        printf("Memory allocation failed\n");
                        return;
                    }
                    u_set->data.int_data.elements = temp;
                }
            }
                u_set->data.int_data.elements[u_set->data.int_data.size] = value;
                u_set->data.int_data.size++;

            } else {
                printf("Value %d is already in the set\n", value);
            }
        }


    else {
        printf("Incorrect format!\n");
    }
}

void init_with_ints(UniversalSet* u_set, int count, ...) {
    init_universal_set(u_set, TYPE_INT_SET);

    va_list args;
    va_start(args, count);

    for (int i = 0; i < count; i++) {
        int val = va_arg(args, int);
        add_int(u_set, val);
    }

    va_end(args);
}

UniversalSet* ops_union(UniversalSet* first_set, UniversalSet* second_set) {
    if (first_set == NULL || second_set == NULL || first_set->type != TYPE_INT_SET || second_set->type != TYPE_INT_SET ) {
        return NULL;
    }

    UniversalSet *union_set = malloc(sizeof(UniversalSet));
    if (union_set == NULL) {
        return NULL;
    }

    init_universal_set(union_set, TYPE_INT_SET);


    for (int i = 0; i < first_set->data.int_data.size; i++) {
        add_int(union_set, first_set->data.int_data.elements[i]);
    }




    for (int i = 0; i < second_set->data.int_data.size; i++) {
        add_int(union_set, second_set->data.int_data.elements[i]);
    }


    return union_set;
}

int compare_ints(const void* a,const void* b) {
    return *(int*)a - *(int*)b;
}


UniversalSet* ops_intersection(UniversalSet* first_set, UniversalSet* second_set) {
    if (first_set == NULL || second_set == NULL || first_set->type != TYPE_INT_SET || second_set->type != TYPE_INT_SET ) {
        return NULL;
    }

    UniversalSet *intersection_set = malloc(sizeof(UniversalSet));
    if (intersection_set == NULL) {
        return NULL;
    }

    init_universal_set(intersection_set, TYPE_INT_SET);

    int sizeA = first_set->data.int_data.size;
    int sizeB = second_set->data.int_data.size;

    int* sortedA = malloc(sizeA * sizeof(int));
    int* sortedB = malloc(sizeB * sizeof(int));

    if (!sortedA || !sortedB) {
        free(intersection_set);
        free(sortedA);
        free(sortedB);
        return NULL;
    }

    memcpy(sortedA, first_set->data.int_data.elements, sizeA * sizeof(int));
    memcpy(sortedB, second_set->data.int_data.elements, sizeB * sizeof(int));

    qsort(sortedA, sizeA, sizeof(int), compare_ints);
    qsort(sortedB, sizeB, sizeof(int), compare_ints);

    int i = 0, j = 0;
    while (i < sizeA && j < sizeB) {
        int valA = sortedA[i];
        int valB = sortedB[j];

        if (valA < valB) {
            i++;
        }
        else if (valB < valA) {
            j++;
        }
        else {
            add_int(intersection_set, valA);
            i++;
            j++;
        }

    }

    free(sortedA);
    free(sortedB);

    return intersection_set;
}

UniversalSet* ops_difference(UniversalSet* first_set, UniversalSet* second_set) {
    if (first_set == NULL || second_set == NULL || first_set->type != TYPE_INT_SET || second_set->type != TYPE_INT_SET ) {
        return NULL;
    }

    UniversalSet *difference_set = malloc(sizeof(UniversalSet));
    if (difference_set == NULL) {
        return NULL;
    }

    init_universal_set(difference_set, TYPE_INT_SET);

    int sizeA = first_set->data.int_data.size;
    int sizeB = second_set->data.int_data.size;

    int* sortedA = malloc(sizeA * sizeof(int));
    int* sortedB = malloc(sizeB * sizeof(int));

    if (!sortedA || !sortedB) {
        free(difference_set);
        free(sortedA);
        free(sortedB);
        return NULL;
    }

    memcpy(sortedA, first_set->data.int_data.elements, sizeA * sizeof(int));
    memcpy(sortedB, second_set->data.int_data.elements, sizeB * sizeof(int));

    qsort(sortedA, sizeA, sizeof(int), compare_ints);
    qsort(sortedB, sizeB, sizeof(int), compare_ints);

    int i = 0, j = 0;
    while (i < sizeA && j < sizeB) {
        int valA = sortedA[i];
        int valB = sortedB[j];

        if (valA < valB) {
            add_int(difference_set, valA);
            i++;
        }
        else if (valB < valA) {
            j++;
        }
        else {
            i++;
            j++;
        }

    }

    while (i < sizeA) {
        add_int(difference_set, sortedA[i]);
        i++;
    }

    free(sortedA);
    free(sortedB);

    return difference_set;
}


UniversalSet* ops_cartesian_product(UniversalSet* first_set, UniversalSet* second_set) {
    if (first_set == NULL || second_set == NULL || first_set->type != TYPE_INT_SET || second_set->type != TYPE_INT_SET ) {
        return NULL;
    }

    UniversalSet *cart_product = malloc(sizeof(UniversalSet));
    if (cart_product == NULL) {
        return NULL;
    }

    cart_product->type = TYPE_PAIR_SET;
    int pairs_count = first_set->data.int_data.size * second_set->data.int_data.size;

    cart_product->data.pair_data.pairs = malloc(pairs_count * sizeof(OrderedPair));
    if (cart_product->data.pair_data.pairs == NULL) {
        free(cart_product);
        return NULL;
    }

    cart_product->data.pair_data.size = 0;
    cart_product->data.pair_data.capacity = pairs_count;

    for (int i = 0; i < first_set->data.int_data.size; i++ ) {
        for (int j = 0; j < second_set->data.int_data.size; j++ ) {
            int idx = cart_product->data.pair_data.size;

            cart_product->data.pair_data.pairs[idx].first_num = first_set->data.int_data.elements[i];
            cart_product->data.pair_data.pairs[idx].second_num = second_set->data.int_data.elements[j];

            cart_product->data.pair_data.size++;

        }
    }

    return cart_product;
}

bool is_equal(UniversalSet* first_set, UniversalSet* second_set) {
    if (first_set == NULL || second_set == NULL || first_set->type != second_set->type || first_set->data.int_data.size != second_set->data.int_data.size ) {
        return false;
    }
    for (int i = 0; i < first_set->data.int_data.size; i++) {
        int to_find = first_set->data.int_data.elements[i];

        if (!is_present(second_set, to_find)) {
            return false;
        }

    }
    return true;
}