#ifndef LIBCARTILAGE_H
#define LIBCARTILAGE_H

#include <stdint.h>

#define COUT(c) printf(#c " = %c\n", c)
#define DOUT(c) printf(#c " = %d\n", c)

typedef struct Node {
	char data;
	struct Node* next;
} Node_t;

typedef struct {
	Node_t* head;
	uint32_t size;
} LinkedList;

LinkedList* make_list(void);

Node_t* make_node(char value);

Node_t* push_back(LinkedList* ll, char value);

Node_t* push_front(LinkedList* ll, char value);

void print_node_d(Node_t* n);

void iterate(LinkedList* ll, void (*callback)(void*));

#endif
