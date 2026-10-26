#include "serialize_custom.h"
#include "serialize.h"
#include <stdlib.h>

void serialize_T(struct T *t, struct Buffer *output) {
    serialize_int(t->x, output);
    serialize_int(t->y, output);
    serialize_char(t->icon, output);
    serialize_float(t->value, output);
    serialize_char(t->currency, output);
}

void deserialize_T(struct T *t, struct Buffer *input) {
    deserialize_char(&(t->currency), input);
    deserialize_float(&(t->value), input);
    deserialize_char(&(t->icon), input);
    deserialize_int(&(t->y), input);
    deserialize_int(&(t->x), input);
}

void serialize_P(struct P *p, struct Buffer *output) {
   serialize_int(p->x, output);
   serialize_int(p->y, output);
   serialize_char(p->icon, output);
}

void deserialize_P(struct P *p, struct Buffer *input) {
    deserialize_char(&(p->icon), input);
    deserialize_int(&(p->y), input);
    deserialize_int(&(p->x), input);
}

void serialize_linked_list(struct linked_list *ll, struct Buffer *output) {
    struct node* temp = ll->head;
    while(temp != NULL) {
        serialize_int(temp->data, output);
        temp = temp->next;
    }
    serialize_int(ll->len, output);
}

void deserialize_linked_list(struct linked_list *ll, struct Buffer *input) {
    int n;
    deserialize_int(&n, input);

    ll->len = n;
    ll->head = NULL;

    for(int i = 0; i < n; i++) {
        struct node* node = malloc(sizeof(struct node));
        deserialize_int(&node->data, input);
        node->next = ll->head;
        ll->head = node;
    }

}

