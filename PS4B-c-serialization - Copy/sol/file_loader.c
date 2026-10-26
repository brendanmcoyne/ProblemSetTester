#include "buffer.h"
#include "serialize.h"
#include <unistd.h>
#include <string.h>
#include <stdio.h> 


void serialize_file(int fp, Buffer *b) {
  size_t total_wrote = 0;
  write(fp, &b->size, sizeof(b->size));
  write(fp, &b->top, sizeof(b->top));
  while(total_wrote < b->size) {
    int num_write = write(fp, b->data+total_wrote, b->size - total_wrote);
    printf("wrote %d\n", num_write);
    total_wrote += num_write;
  }
}
void deserialize_file(int fp, Buffer *b) {
    size_t size, next;
    read(fp, &size, sizeof(b->size));
    read(fp, &next, sizeof(b->top));
    
    printf("size %ld next %ld\n", size,next);  
    reserve_space(b, size);
    size_t total_read = 0;
    while(total_read < size) {
      //printf("read so far: %d", total_read);
      size_t num_read = read(fp, b->data + total_read,size-total_read);
      total_read += num_read;
    }
    b->top = next;
}



