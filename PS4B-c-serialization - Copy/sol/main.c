#include "buffer.h"
#include "serialize.h"
#include <unistd.h>
#include <string.h>
#include <stdio.h> 


void serialize_write() {
    Buffer *b = new_buffer();
    serialize_int(123, b);
    serialize_int(456, b);

    write(1, b->data, 8);
}

void deserialize_read() {
    Buffer *b = new_buffer();
    reserve_space(b, 8);
    read(0, b->data,8);
    b->top = 8;

    int x,y;
    deserialize_int(&y,b);
    deserialize_int(&x,b);

    printf("%d %d\n", x,y);
}

void main(int argc, char** argv) {
    if (strcmp(argv[1],"deserialize") == 0) {
        deserialize_read();
    } else if (strcmp(argv[1],"serialize") == 0){
        serialize_write();
    } else {
        printf("ERROR: Unrecognized mode\n");
    }
}
