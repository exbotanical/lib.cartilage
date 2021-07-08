#ifndef LIBCARTILAGE_H
#define LIBCARTILAGE_H

#include <stdint.h>

#define COUT(c) printf(#c " = %c\n", c)
#define DOUT(c) printf(#c " = %d\n", c)

/*****************************
 *	CircularSinglyLinkedList
 *****************************/

typedef struct CircularSinglyLinkedList;

typedef struct ForwardNode {
	char data;
	struct ForwardNode* next;
	struct CircularSinglyLinkedList* list;
} ForwardNode_t;

typedef struct CircularSinglyLinkedList {
	ForwardNode_t* head;
	uint32_t size;
} CircularSinglyLinkedList;

CircularSinglyLinkedList* make_list(void);

ForwardNode_t* push_back(CircularSinglyLinkedList* ll, char value);

ForwardNode_t* push_front(CircularSinglyLinkedList* ll, char value);

void iterate(CircularSinglyLinkedList* ll, void (*callback)(void*));

ForwardNode_t* prev(CircularSinglyLinkedList* ll, ForwardNode_t* node);

#endif
