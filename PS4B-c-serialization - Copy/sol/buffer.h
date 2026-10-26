#include <stddef.h>

// a macro which encodes the default initial size for the underlying array
// of the buffer struct
#define INITIAL_SIZE 32

#ifndef BUFFER_H
#define BUFFER_H

/* struct representing a buffer of serialized bytes */
typedef struct Buffer {
  void *data;  // pointer to underlying data array of bytes
  size_t top;  // index of the top (first free byte), in the data array
  size_t size; // capacity of the buffer in bytes 
} Buffer;

struct Buffer *new_buffer();
void reserve_space(Buffer *b, size_t bytes);

#endif
