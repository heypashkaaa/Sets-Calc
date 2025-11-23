typedef enum {
    TYPE_INT_SET,
    TYPE_PAIR_SET
} SetType;

typedef struct {
    int* elements;
    int size;
    int capacity;
} IntSet;

typedef struct {
    int first_num;
    int second_num;
} OrderedPair;

typedef struct {
    OrderedPair* pairs;
    int size;
    int capacity;
} PairSet;

typedef struct {
    SetType type;
    union {
        IntSet int_data;
        PairSet pair_data;
    } data;
} UniversalSet;

void init_universal_set(UniversalSet* u_set, SetType type);
void free_universal_set(UniversalSet* u_set);
void print_set(UniversalSet* u_set);
bool is_present(UniversalSet* u_set, int value );
void add_int(UniversalSet* u_set, int value );
void init_with_ints(UniversalSet* u_set, int count, ...);
UniversalSet* ops_union(UniversalSet* first_set, UniversalSet* second_set);
UniversalSet* ops_intersection(UniversalSet* first_set, UniversalSet* second_set);
UniversalSet* ops_difference(UniversalSet* first_set, UniversalSet* second_set);
UniversalSet* ops_cartesian_product(UniversalSet* first_set, UniversalSet* second_set); //not done yet
bool is_equal(UniversalSet* first_set, UniversalSet* second_set);



