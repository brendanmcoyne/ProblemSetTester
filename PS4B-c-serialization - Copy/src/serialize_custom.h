#include "buffer.h"

struct P {
  int x;
  int y;
  char icon;
};

struct T {
  int x,y;
  char icon;
  float value;
  char currency;
};

// a struct representing a wrapper around the head of a linked list
struct linked_list {
  struct node* head; // pointer to head of linked list
  int len; // length of ll (number of nodes)
};

// a struct representing a node of a linked list
struct node {
  int data; // integer data item
  struct node* next; // pointer to next linked list node
};


void serialize_P(struct P *p, struct Buffer *output);
void deserialize_P(struct P *p, struct Buffer *input);

void serialize_T(struct T *t, struct Buffer *output);
void deserialize_T(struct T *t, struct Buffer *input);

void serialize_linked_list(struct linked_list *ll, struct Buffer *output);
void deserialize_linked_list(struct linked_list *ll, struct Buffer *output);

