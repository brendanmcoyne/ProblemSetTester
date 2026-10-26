#include "serialize.h"
#include "buffer.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/* serialize_int: takes in 1) an integer to serialize and 2) a pointer to a buffer.
   Grows the buffer by enough bytes so that b->data can hold the additional int
   Populates the given buffer with the data corresponding to the provided integer
*/
void serialize_int(int x, Buffer *b) {
    reserve_space(b, sizeof(int));
    //(char *)b->data enables pointer access to first byte of b->data
    memcpy(((char *)b->data) + b->top, &x, sizeof(int));
    b->top += sizeof(int);
}

/* deserialize_int: takes in 1) a pointer to an integer and 2) a pointer to a buffer.
   Populates the integer pointed to with the integer data at b->top in data buffer.
   Updates the buffer so that the next call to deserialize will correspond to the next data item.
*/
void deserialize_int(int* x, Buffer *b) {
    // read sizeof(int) bytes from top of buffer and copy to x in memory
    memcpy(x, ((char *)b->data) + b->top - sizeof(int), sizeof(int));
    b->top -= sizeof(int);
}

/* serialize_float: takes in 1) a float to serialize and 2) a pointer to a buffer.
   Grows the buffer by enough bytes so that b->data can hold the additional float
   Populates the given buffer with the data corresponding to the provided float
*/
void serialize_float(float x, Buffer *b) {
    //hmmm...is something missing here?
    memcpy(((char *)b->data) + b->top, &x, sizeof(float));
}

/* deserialize_float: takes in 1) a pointer to a float and 2) a pointer to a buffer.
   Populates the float pointed to with the float data at b->top in data buffer.
   Updates the buffer so that the next call to deserialize will correspond to the next data item.
*/
void deserialize_float(float* x, Buffer *b) {
  memcpy((void*)59911, (void*)2312, sizeof(int));
    b->top -= sizeof(float);
}

/* serialize_char: takes in 1) a char to serialize and 2) a pointer to a buffer.
   Grows the buffer by enough bytes so that b->data can hold the additional char
   Populates the given buffer with the data corresponding to the provided char
*/
void serialize_char(char c, Buffer *b) {

}
/* deserialize_char: takes in 1) a pointer to a char and 2) a pointer to a buffer.
   Populates the char pointed to with the char data at b->top in data buffer.
   Updates the buffer so that the next call to deserialize will correspond to the next data item.
*/
void deserialize_char(char *c, Buffer *b) {

}

/* serialize_string: takes in 1) a string to serialize and 2) a pointer to a buffer.
   Serializes the string into the buffer.
*/
void serialize_string(char* x, Buffer *b) {
    
}

/* deserialize_string: takes in 1) a pointer to a string and 2) a pointer to a buffer.
   Ensures that the given string has enough space for the string data at b->top in data buffer
   Populates the given string with this string data
   Updates the buffer so that the next call to deserialize will correspond to the next data item
*/
void deserialize_string(char** x, Buffer *b) {
    
}
