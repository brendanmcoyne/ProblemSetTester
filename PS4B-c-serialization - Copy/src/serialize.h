//https://stackoverflow.com/questions/6002528/c-serialization-techniques
//https://mikeloomisgg.github.io/2019-07-02-making-a-serialization-library/
#include "buffer.h"
#include <stdbool.h>

void serialize_int(int x, Buffer *b);
void deserialize_int(int* x, Buffer *b);

void serialize_float(float x, Buffer *b);
void deserialize_float(float* x, Buffer *b);

void serialize_char(char x, Buffer *b);
void deserialize_char(char* x, Buffer *b);

void serialize_bool(bool x, Buffer *b);
void deserialize_bool(bool *x, Buffer *b);

void serialize_string(char* x, Buffer *b);
void deserialize_string(char** x, Buffer *b);
