#include <stdlib.h>
#include "buffer.h"

/*
  Creates a new empty buffer struct.
  Returns a pointer to the buffer allocated on the heap.
*/
struct Buffer *new_buffer() {
    struct Buffer *b = malloc(sizeof(Buffer));

    b->data = malloc(INITIAL_SIZE);
    b->size = INITIAL_SIZE;
    b->top = 0;
    
    return b;
}

/*
  Ensures that the buffer pointed to by b can store an additional bytes, bytes.
  If nessecary will grow the buffer's size. If buffer is already big enough, there is no effect.
*/
void reserve_space(Buffer *b, size_t bytes) {
  //if used space in buffer, plus requested,
  //is greater than current allocation, realloc
    if((b->top + bytes) > b->size) {
        b->data = realloc(b->data, b->top + bytes);
        b->size = b->top + bytes;
    }
}
