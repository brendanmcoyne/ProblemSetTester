#include "buffer.h"
#include "file_loader.h"
#include "serialize.h"
#include "serialize_custom.h"
#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

const int VERBOSE = 0;

int compare_ll(struct linked_list x1, struct linked_list x2) {
    if (x1.len != x2.len) {
        if (VERBOSE) {
            printf("LEN MISMATCH: %d != %d\n", x1.len, x2.len);
        }
        return 0;
    }

    struct node *n1 = x1.head;
    struct node *n2 = x2.head;
    while (n1 != NULL) {
        if (n1->data != n2->data) {
            if (VERBOSE) {
                printf("DATA MISMATCH: %d != %d\n", n1->data, n2->data);
            }
            return 0;
        } else {
            if (VERBOSE) {
                printf("match: %d == %d\n", n1->data, n2->data);
            }
        }
        n1 = n1->next;
        n2 = n2->next;
    }
    if (VERBOSE) {
        printf("last n1 = %p, last n2 = %p\n", n1, n2);
    }
    return n2 == NULL; // if at end, n1==NULL and n2==NULL, we should pass, else
                       // some element differs
}

int compare_T(struct T x1, struct T x2) {
    return x1.x == x2.x && x2.y == x1.y && x2.icon == x1.icon &&
           x2.value == x1.value && x2.currency == x1.currency;
}

int compare_P(struct P y1, struct P y2) {
    return y1.x == y2.x && y2.y == y1.y && y1.icon == y2.icon;
}

int test_serialize_int() {
    Buffer *b = new_buffer();
    serialize_int(4, b);

    if (VERBOSE) {
        printf("Byte Array:");
        for (long unsigned int i = 0; i < b->size; i++) {
            printf(" %d ", ((char *)(b->data))[i]);
        }
        printf("\n");
    }

    int x = 0;

    deserialize_int(&x, b);

    return x == 4;
}

int test_serialize_int2() {
    Buffer *b = new_buffer();
    serialize_int(4, b);
    serialize_int(-341, b);

    if (VERBOSE) {
        printf("Byte Array:");
        for (long unsigned int i = 0; i < b->size; i++) {
            printf(" %d ", ((char *)(b->data))[i]);
        }
        printf("\n");
    }

    int x = 0;
    int y = 0;

    deserialize_int(&y, b);
    deserialize_int(&x, b);

    if (VERBOSE) {
        printf("%d %d\n", x, y);
    }

    return x == 4 && y == -341;
}

int test_serialize_float() {
    Buffer *b = new_buffer();
    serialize_float(4.1, b);

    if (VERBOSE) {
        printf("Byte Array:");
        for (long unsigned int i = 0; i < b->size; i++) {
            printf(" %d ", ((char *)(b->data))[i]);
        }
        printf("\n");
    }

    float x = 0;

    deserialize_float(&x, b);

    if (VERBOSE) {
        printf("%f\n", x);
    }

    return fabs(x - 4.1) < 0.0001;
}

int test_serialize_char() {
    Buffer *b = new_buffer();
    serialize_char('a', b);

    if (VERBOSE) {
        printf("Byte Array:");
        for (long unsigned int i = 0; i < b->size; i++) {
            printf(" %d ", ((char *)(b->data))[i]);
        }
        printf("\n");
    }

    char x = 0;

    deserialize_char(&x, b);

    if (VERBOSE) {
        printf("%c\n", x);
    }

    return x == 'a';
}

int test_serialize_char2() {
    Buffer *b = new_buffer();
    serialize_char('a', b);
    serialize_char('b', b);
    serialize_char('c', b);

    if (VERBOSE) {
        printf("Byte Array:");
        for (long unsigned int i = 0; i < b->size; i++) {
            printf(" %d ", ((char *)(b->data))[i]);
        }
        printf("\n");
    }

    char x, y, z = 0;

    deserialize_char(&x, b);
    deserialize_char(&y, b);
    deserialize_char(&z, b);

    if (VERBOSE) {
        printf("%c %c %c\n", x, y, z);
    }

    return z == 'a' && y == 'b' && x == 'c';
}

int test_serialize_string1() {
    Buffer *b = new_buffer();
    serialize_string("cs210 is a fun class!", b);

    if (VERBOSE) {
        printf("Byte Array:");
        for (size_t i = 0; i < sizeof(char); i++) {
            printf(" %d ", ((char *)(b->data))[i]);
        }
        printf("\n");
    }

    char *str = malloc(1);

    deserialize_string(&str, b);

    /* printf("string: %s\n", str); */

    return strcmp(str, "cs210 is a fun class!") == 0;
}

int test_serialize_string2() {
    Buffer *b = new_buffer();
    serialize_string("cs210 is a fun class!", b);
    serialize_string("I am good at serializing data!", b);

    char *str = malloc(1);
    char *str2 = malloc(1);

    deserialize_string(&str2, b);
    deserialize_string(&str, b);

    /* printf("string: %s %s\n", str, str2); */

    return strcmp(str, "cs210 is a fun class!") == 0 &&
           strcmp(str2, "I am good at serializing data!") == 0;
}

int test_serialize_struct1() {
    Buffer *b = new_buffer();
    struct P input = {3, 2, 'a'};
    serialize_P(&input, b);

    if (VERBOSE) {
        printf("Byte Array:");
        for (long unsigned int i = 0; i < b->size; i++) {
            printf(" %d ", ((char *)(b->data))[i]);
        }
        printf("\n");
    }

    struct P output;

    deserialize_P(&output, b);

    if (VERBOSE) {
        printf("output: %d %d %c\n", output.x, output.y, output.icon);
    }

    return compare_P(input, output);
}

int test_serialize_struct2() {
    Buffer *b = new_buffer();
    struct T input = {3, 2, 'Y', -213.12, 'L'};
    serialize_T(&input, b);

    if (VERBOSE) {
        printf("Byte Array:");
        for (long unsigned int i = 0; i < b->size; i++) {
            printf(" %d ", ((char *)(b->data))[i]);
        }
        printf("\n");
    }

    struct T output;

    deserialize_T(&output, b);

    if (VERBOSE) {
        printf("output: %d %d %c %f %c\n", output.x, output.y, output.icon,
               output.value, output.currency);
    }
    return compare_T(input, output);
}

int test_serialize_struct3() {
    Buffer *b = new_buffer();
    struct T input1 = {3, 2, 'Y', -213.12, 'L'};
    serialize_T(&input1, b);
    struct P input2 = {3, 0, 'a'};
    serialize_P(&input2, b);

    if (VERBOSE) {
        printf("Byte Array:");
        for (long unsigned int i = 0; i < b->size; i++) {
            printf(" %d ", ((char *)(b->data))[i]);
        }
        printf("\n");
    }

    struct P output2;
    deserialize_P(&output2, b);

    struct T output1;
    deserialize_T(&output1, b);

    if (VERBOSE) {
        printf("output: %d %d %c %f %c\n", output1.x, output1.y, output1.icon,
               output1.value, output1.currency);
        printf("output: %d %d %c\n", output2.x, output2.y, output2.icon);
    }

    return compare_T(input1, output1) && compare_P(input2, output2);
}

int test_serialize_linked_list() {
    struct linked_list ll = {NULL, 0};

    for (int i = 0; i < 10; i++) {
        struct node *n = malloc(sizeof(struct node));
        n->data = i;
        n->next = ll.head;
        ll.head = n;
        ll.len += 1;
    }

    Buffer *b = new_buffer();
    serialize_linked_list(&ll, b);

    if (VERBOSE) {
        printf("Byte Array:");
        for (long unsigned int i = 0; i < b->size; i++) {
            printf(" %d ", ((char *)(b->data))[i]);
        }
        printf("\n");
    }

    struct linked_list output;

    deserialize_linked_list(&output, b);

    return compare_ll(ll, output);
}

int test_serialize_linked_list2() {
    struct linked_list ll = {NULL, 0};
    for (int i = 0; i < 11; i++) {
        struct node *n = malloc(sizeof(struct node));
        n->data = i;
        n->next = ll.head;
        ll.head = n;
        ll.len += 1;
    }
    struct linked_list ll2 = {NULL, 0};
    for (int i = 0; i < 31; i++) {
        struct node *n = malloc(sizeof(struct node));
        n->data = i;
        n->next = ll2.head;
        ll2.head = n;
        ll2.len += 1;
    }

    Buffer *b = new_buffer();
    serialize_linked_list(&ll, b);
    serialize_linked_list(&ll2, b);

    if (VERBOSE) {
        printf("Byte Array:");
        for (long unsigned int i = 0; i < b->size; i++) {
            printf(" %d ", ((char *)(b->data))[i]);
        }
        printf("\n");
    }

    struct linked_list output;
    struct linked_list output2;

    deserialize_linked_list(&output2, b);
    deserialize_linked_list(&output, b);

    return compare_ll(ll, output) && compare_ll(ll2, output2);
}

int test_serialize_file() {
    Buffer *b = new_buffer();
    struct P input = {3, 2, 'a'};
    serialize_P(&input, b);

    if (VERBOSE) {
        printf("Byte Array:");
        for (long unsigned int i = 0; i < b->size; i++) {
            printf(" %d ", ((char *)(b->data))[i]);
        }
        printf("\n");
    }
    int fd = open("data.pepper", O_RDWR | O_CREAT | O_TRUNC, 0644);
    serialize_file(fd, b);
    if (VERBOSE) {
        printf("size: %ld %ld %ld\n", b->size, b->top, sizeof(struct P));
    }

    close(fd);

    struct P output;

    Buffer *nb = new_buffer();
    int fd2 = open("data.pepper", O_RDWR, 0644);
    deserialize_file(fd2, nb);

    if (VERBOSE) {
        printf("size: %ld %ld\n", nb->size, nb->top);
        printf("Byte Array:");
        for (long unsigned int i = 0; i < nb->size; i++) {
            printf(" %d ", ((char *)(nb->data))[i]);
        }
        printf("\n");
    }

    deserialize_P(&output, nb);

    if (VERBOSE) {
        printf("output: %d %d %c\n", output.x, output.y, output.icon);
    }
    close(fd);
    return compare_P(input, output);
}

int run_test(char *test_name, int (*test_func)()) {
    int test_res = test_func();
    printf("Test %-25s: %d/1\n", test_name, test_res);
    return test_res;
}

char *test_list[] = {
    "Serialize Int 1",       "Serialize Int 2",       "Serialize Float 1",
    "Serialize Char 1",      "Serialize Char 2",      "Serialize String 1",
    "Serialize String 2",    "Serialize Struct P",    "Serialize Struct T",
    "Serialize Struct P+T",  "Serialize Linked List", "Serialize Linked List 2",
    "Serialize to/from File"};
int (*test_func[])() = {
    &test_serialize_int,         &test_serialize_int2,
    &test_serialize_float,       &test_serialize_char,
    &test_serialize_char2,       &test_serialize_string1,
    &test_serialize_string2,     &test_serialize_struct1,
    &test_serialize_struct2,     &test_serialize_struct3,
    &test_serialize_linked_list, &test_serialize_linked_list2,
    &test_serialize_file};
#define NUM_TESTS 13
#define STRINGIFY2(X) #X
#define STRINGIFY(X) STRINGIFY2(X)

int test_one(int test_num) {
    int passed = 0;

    passed += run_test(test_list[test_num], test_func[test_num]);

    return passed;
}

int test_all() {
    int passed = 0;
    for (int i = 0; i < NUM_TESTS; i++) {
        passed += run_test(test_list[i], test_func[i]);
    }

    printf("Total: %d/" STRINGIFY(NUM_TESTS) "\n", passed);
    return passed;
}

int main(int argc, char **argv) {
    if (argc == 2) {
        return test_one(atoi(argv[1]));
    } else {
        return test_all();
    }
}
