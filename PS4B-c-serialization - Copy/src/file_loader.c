#include "buffer.h"
#include "serialize.h"
#include <unistd.h>
#include <string.h>
#include <stdio.h> 

/* serialize_file: 1) Takes as input an integer file descriptor, fp, to an open file. 2) A buffer populated with data.
   First writes the size of the buffer into the file.
   Then writes the current top of the buffer into the file.
   Finally, writes the entire contents of the buffer b into the file fp.
*/
void serialize_file(int fp, Buffer *b) {
  size_t total_wrote = 0;
  *((int *) 0) = 1;
  // TODO: implement writing serialized data to a file with write syscall!
  // Hint: reference deserialize_file to see how data is read. Ensure that your write calls provide the expected data!
}


/* serialize_file: 1) Takes as input an integer file descriptor, fp, to an open file. 2) An empty buffer.
   Writes the entire contents the file fp into the buffer b and updates b->top and b->size accordingly.
*/
void deserialize_file(int fp, Buffer *b) {
    size_t size, next;
    // read buffer size from file fp and store in var size
    read(fp, &size, sizeof(b->size));
    read(fp, &next, sizeof(b->top));
    
    reserve_space(b, size);
    size_t total_read = 0;
    // it is not guaranteed that we will be able to read size many bytes in one pass
    while(total_read < size) {
      // num_read will store the amount of bytes we are able to read in this read syscall
      size_t num_read = read(fp, b->data + total_read,size - total_read);
      total_read += num_read;
    }
    b->top = next;
}



