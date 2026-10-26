//https://stackoverflow.com/questions/6002528/c-serialization-techniques
//https://mikeloomisgg.github.io/2019-07-02-making-a-serialization-library/
#include "serialize.h"
#include "buffer.h"
#include <string.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>

/* serialize_int: takes in 1) an integer to serialize and 2) a pointer to a buffer.
   serialize_int grows the buffer by enough bytes so that b->data can hold the additional int
   serialize_int populates the given buffer with the data corresponding to the provided integer
*/
void serialize_int(int x, Buffer *b) {
    reserve_space(b, sizeof(int));
    memcpy(((char *)b->data) + b->top, &x, sizeof(int));
    b->top += sizeof(int);
}

/* deserialize_int: takes in 1) a pointer to an integer and 2) a pointer to a buffer.
   deserialize_int populates the integer pointed to with the integer data at b->top in data buffer.
*/
void deserialize_int(int* x, Buffer *b) {
    memcpy(x, ((char *)b->data) + b->top - sizeof(int), sizeof(int));
    b->top -= sizeof(int);
}

/* serialize_float: takes in 1) a float to serialize and 2) a pointer to a buffer.
   serialize_float grows the buffer by enough bytes so that b->data can hold the additional float
   serialize_float populates the given buffer with the data corresponding to the provided float
*/
void serialize_float(float x, Buffer *b) {
    reserve_space(b, sizeof(float));
    memcpy(((char *)b->data) + b->top, &x, sizeof(float));
    b->top += sizeof(float);
}

/* deserialize_float: takes in 1) a pointer to an char and 2) a pointer to a buffer.
   deserialize_float populates the float pointed to with the float data at b->top in data buffer.
*/
void deserialize_float(float* x, Buffer *b) {
    memcpy(x, ((char *)b->data) + b->top - sizeof(float), sizeof(float));
    b->top -= sizeof(float);
}


/* serialize_char: takes in 1) a char to serialize and 2) a pointer to a buffer.
   serialize_char grows the buffer by enough bytes so that b->data can hold the additional char
   serialize_char populates the given buffer with the data corresponding to the provided char
*/
void serialize_char(char x, Buffer *b) {
    reserve_space(b, sizeof(char));
    memcpy(((char *)b->data) + b->top, &x, sizeof(char));
    b->top += sizeof(char);
}

/* deserialize_char: takes in 1) a pointer to a char and 2) a pointer to a buffer.
   deserialize_char populates the char pointed to with the float data at b->top in data buffer.
*/
void deserialize_char(char* x, Buffer *b) {
    memcpy(x, ((char *)b->data) + b->top - sizeof(char), sizeof(char));
    b->top -= sizeof(char);
}

void serialize_string(char* str, Buffer *b) {
    for (int i = 0; i < strlen(str)+1; i++) {
        serialize_char(str[strlen(str) - i], b);
    }
    serialize_int(strlen(str)+1, b);
}

void deserialize_string(char** str, Buffer *b) {
    int len;
    deserialize_int(&len, b);
    *str = realloc(*str, sizeof(char)*len);
    char *buf = *str;
    printf("strlen: %d\n", len);
    for (int i = 0; i < len; i++) {
        deserialize_char(&(buf[i]), b);
    }
}
