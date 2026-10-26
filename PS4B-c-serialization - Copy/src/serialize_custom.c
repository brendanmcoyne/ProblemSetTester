#include "serialize_custom.h"
#include "serialize.h"
#include <stdlib.h>

/* serialize_T: takes in 1) a struct T to serialize and 2) a pointer to a buffer.
   Grows the buffer by enough bytes so that b->data can hold the additional struct T
   Populates the given buffer with the data corresponding to the provided T
*/
void serialize_T(struct T *t, struct Buffer *output) {
  *((int *) 0) = 1; // This line always segfaults, can you see why?

  //serialization for struct T is not quite right!
  //Open serialize_custom.h to see the definition for what a struct T looks like!
  serialize_int(t->x, output);
  serialize_char(t->icon, output);
  serialize_float(t->value, output);
  serialize_char(t->currency, output);
}

/* deserialize_T: takes in 1) a pointer to a struct T and 2) a pointer to a buffer.
   Populates the struct T pointed to with the data at b->top in data buffer.
   Updates the buffer so that the next call to deserialize will correspond to the next data item.
*/
void deserialize_T(struct T *t, struct Buffer *input) {
   // TODO: complete deserialization for struct T
   // why do we pass by reference here?
   deserialize_int(&(t->x), input);
}

/* serialize_P: takes in 1) a struct P to serialize and 2) a pointer to a buffer.
   Grows the buffer by enough bytes so that b->data can hold the additional struct P
   Populates the given buffer with the data corresponding to the provided P
*/
void serialize_P(struct P *p, struct Buffer *output) {
   serialize_int(p->x, output);
   serialize_int(p->y, output);
   serialize_char(p->icon, output);
}

/* deserialize_P: takes in 1) a pointer to a struct P and 2) a pointer to a buffer.
   Populates the struct P pointed to with the data at b->top in data buffer.
   Updates the buffer so that the next call to deserialize will correspond to the next data item.
*/
void deserialize_P(struct P *p, struct Buffer *input) {
  //hmm... it seems like there is a bug in how we deserialize our struct
  deserialize_int(&(p->x), input);
  deserialize_int(&(p->y), input);
  deserialize_char(&(p->icon), input);
}

/* serialize_linked_list: takes in 1) a pointer to linked list struct and 2) a pointer to a buffer.
   Grows the buffer by enough bytes so that b->data can hold the entire linked list
   Populates the given buffer with the data corresponding to: the length of the linked list, each data item of each node in the linked list.
*/
void serialize_linked_list(struct linked_list *ll, struct Buffer *output) {
    struct node* temp = ll->head;
    // does it matter if we do this first or last? see deserialize_linked_list()...
    serialize_int(ll->len, output);
    
    /* TODO: implement creating the linked list by serializing each node into the buffer */
    // See the definition for a linked list in serialize_custom.h
}

/* deserialize_linked_list: takes in 1) a pointer to a linked list and 2) a pointer to a buffer.
   Populates the linked list pointed to with the data at b->top in data buffer.
   Updates the buffer so that the next call to deserialize will correspond to the next data item.
*/
void deserialize_linked_list(struct linked_list *ll, struct Buffer *input) {
    int n;
    deserialize_int(&n, input);

    ll->len = n;
    ll->head = NULL;
    
    /* TODO: implement recreating the linked list by deserializing each element, and attaching it to ll->head */ 
}

