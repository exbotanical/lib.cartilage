#ifndef LIBCARTILAGE_H
#define LIBCARTILAGE_H

#include <stdint.h>

#define COUT(c) printf(#c " = %c\n", c)
#define DOUT(c) printf(#c " = %d\n", c)

typedef struct CircularSinglyLinkedList;

typedef struct Node {
	char data;
	struct Node* next;
	struct CircularSinglyLinkedList* list;
} Node_t;

typedef struct CircularSinglyLinkedList {
	Node_t* head;
	uint32_t size;
} CircularSinglyLinkedList;

CircularSinglyLinkedList* make_list(void);

Node_t* push_back(CircularSinglyLinkedList* ll, char value);

Node_t* push_front(CircularSinglyLinkedList* ll, char value);

void iterate(CircularSinglyLinkedList* ll, void (*callback)(void*));

Node_t* prev(CircularSinglyLinkedList* ll, Node_t* node);

#endif
