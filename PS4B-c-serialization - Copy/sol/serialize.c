//https://stackoverflow.com/questions/6002528/c-serialization-techniques
//https://mikeloomisgg.github.io/2019-07-02-making-a-serialization-library/
#include "serialize.h"
#include "buffer.h"
#include <string.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>

void serialize_int(int x, Buffer *b) {
    reserve_space(b, sizeof(int));
    memcpy(((char *)b->data) + b->top, &x, sizeof(int));
    b->top += sizeof(int);
}

void deserialize_int(int* x, Buffer *b) {
    memcpy(x, ((char *)b->data) + b->top - sizeof(int), sizeof(int));
    b->top -= sizeof(int);
}

void serialize_float(float x, Buffer *b) {
    reserve_space(b, sizeof(float));
    memcpy(((char *)b->data) + b->top, &x, sizeof(float));
    b->top += sizeof(float);
}

void deserialize_float(float* x, Buffer *b) {
    memcpy(x, ((char *)b->data) + b->top - sizeof(float), sizeof(float));
    b->top -= sizeof(float);
}

void serialize_char(char x, Buffer *b) {
    reserve_space(b, sizeof(char));
    memcpy(((char *)b->data) + b->top, &x, sizeof(char));
    b->top += sizeof(char);
}

void serialize_bool(bool x, Buffer *b) {
    unsigned char value = x ? 1 : 0;

    reserve_space(b, sizeof(unsigned char));
    memcpy((char *)b->data + b->top, &value, sizeof(unsigned char));
    b->top += sizeof(unsigned char);
}

void deserialize_bool(bool *x, Buffer *b) {
    unsigned char value;

    memcpy(&value, (char *)b->data + b->top - sizeof(unsigned char),
           sizeof(unsigned char));

    b->top -= sizeof(unsigned char);
    *x = (value != 0);
}

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
