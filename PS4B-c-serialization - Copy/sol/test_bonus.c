#include "serialize.h"
#include "serialize_custom.h"
#include "buffer.h"
#include "file_loader.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

const int VERBOSE = 1;



int test_serialize_string1() {
    Buffer *b = new_buffer();
    serialize_string("cs210 is a fun class!", b);


    if(VERBOSE) {
        printf("Byte Array:");
        for(size_t i = 0 ; i < sizeof(char); i++) {
            printf(" %d ",  ((char*)(b->data))[i]);
        }
        printf("\n");
    }

    char* str = malloc(0);

    deserialize_string(&str, b);

    printf("string: %s\n", str);
    
    return strcmp(str, "cs210 is a fun class!") == 0;
}

int test_serialize_string2() {
    Buffer *b = new_buffer();
    serialize_string("cs210 is a fun class!", b);
    serialize_string("I am good at serializing data!", b);


    char* str = malloc(0);
    char* str2 = malloc(0);

    deserialize_string(&str2, b);
    deserialize_string(&str, b);


    printf("string: %s %s\n", str, str2);
    
    return strcmp(str, "cs210 is a fun class!") == 0 && strcmp(str2, "I am good at serializing data!") == 0;
}


int main(void){
    int passed = 0;

    printf("Test Serialize String 1: %d/1\n", passed += test_serialize_string1());
    printf("Test Serialize String 2: %d/1\n", passed += test_serialize_string2());

    printf("BONUS Total: %d/2\n", passed);
    return passed;
}