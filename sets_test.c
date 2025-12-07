#include "set.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    UniversalSet s1, s2, s6;

    // 1. Initialize Integer Sets
    init_universal_set(&s1, TYPE_INT_SET);
    init_universal_set(&s2, TYPE_INT_SET);


    add_int(&s1, 1);
    add_int(&s1, 2);
    add_int(&s1, 3);

    init_with_ints(&s2, 3, 3,4,5);
    init_with_ints(&s6, 3, 3,4,5);


    printf("Set 1: ");
    print_set(&s1);

    printf("Set 2: ");
    print_set(&s2);

    UniversalSet * s3 = ops_union(&s1, &s2);
    printf("Union: ");
    print_set(s3);

    UniversalSet * s4 = ops_intersection(&s1, s3);
    printf("Intersection: ");
    print_set(s4);

    UniversalSet * s5 = ops_difference(&s2, &s1);
    printf("Difference: ");
    print_set(s5);

    is_equal(&s1, &s2) ? printf("The sets are equal\n") : printf("The sets are not equal\n");
    is_equal(&s6, &s2) ? printf("The sets are equal\n") : printf("The sets are not equal\n");

    UniversalSet * s7 = ops_cartesian_product(&s1, &s2);
    printf("Cartesian product: ");
    print_set(s7);

    // 4. Cleanup
    free_universal_set(&s1);
    free_universal_set(&s2);
    free_universal_set(s3);
    free(s3);
    free_universal_set(s4);
    free(s4);
    free_universal_set(s5);
    free(s5);
    free_universal_set(&s6);
    free_universal_set(s7);
    free(s7);


    return 0;
}

