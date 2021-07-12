#ifndef LIBCARTILAGE_H
#define LIBCARTILAGE_H

#include <stdint.h>

#define COUT(c) printf(#c " = %c\n", c)
#define DOUT(c) printf(#c " = %d\n", c)

/*****************************
 *	CircularSinglyLinkedList
 *****************************/

/**
 * @brief Node type; atomic - points to next Node*
 */
typedef struct ForwardNode {
	void* data;
	struct ForwardNode* next;
	struct CircularSinglyLinkedList* list; /* A pointer to the list to which the node belongs */
} ForwardNode_t;

/**
 * @brief CircularSinglyLinkedList type
 */
typedef struct CircularSinglyLinkedList {
	ForwardNode_t* head;
	uint32_t size;
} CircularSinglyLinkedList;

/**
 * @brief Instantiate an empty circular singly linked list
 *
 * @return CircularSinglyLinkedList*
 */
CircularSinglyLinkedList* csll_make_list(void);

ForwardNode_t* __csll_make_node(void* value);

/**
 * @brief Push a new node with value `value` to the back of the list
 *
 * @param ll
 * @param value
 * @return ForwardNode_t*
 */
ForwardNode_t* csll_push_back(CircularSinglyLinkedList* ll, void* value);

/**
 * @brief Push a new node with value `value` to the front of the list
 *
 * @param ll
 * @param value
 * @return ForwardNode_t*
 */
ForwardNode_t* csll_push_front(CircularSinglyLinkedList* ll, void* value);

/**
 * @brief Iterate over the list and invoke `callback` with each node
 *
 * @param ll
 * @param callback
 */
void csll_iterate(CircularSinglyLinkedList* ll, void (*callback)(void*));

/**
 * @brief Returns the next list node, if extant; else, NULL
 *
 * @param ll
 * @param node
 * @return ForwardNode_t*
 */
ForwardNode_t* csll_next(CircularSinglyLinkedList* ll, ForwardNode_t* node);

/**
 * @brief Returns the previous list node, if extant; else, NULL
 *
 * @param ll
 * @param node
 * @return ForwardNode_t*
 */
ForwardNode_t* csll_prev(CircularSinglyLinkedList* ll, ForwardNode_t* node);

/**
 * @brief Remove a given node from the list
 *
 * @param ll
 * @param node
 * @return ForwardNode_t*
 */
ForwardNode_t* csll_remove_node(CircularSinglyLinkedList* ll, ForwardNode_t* node);

/**
 * @brief Remove the last node from the list
 *
 * @param ll
 * @return ForwardNode_t*
 */
ForwardNode_t* csll_pop(CircularSinglyLinkedList* ll);

/**
 * @brief Insert a new node with value `value` immediately after `mark`
 *
 * If `mark` is not an element of the list, the list is not modified
 *
 * `mark` must not be NULL
 *
 * @param ll
 * @param value
 * @param mark
 * @return ForwardNode_t*
 */
ForwardNode_t* csll_insert_after(CircularSinglyLinkedList* ll, void* value, ForwardNode_t* mark);

/**
 * @brief Insert a new node with value `value` immediately before `mark`
 *
 * If `mark` is not an element of the list, the list is not modified
 *
 * `mark` must not be NULL
 *
 * @param ll
 * @param value
 * @param mark
 * @return ForwardNode_t*
 */
ForwardNode_t* csll_insert_before(CircularSinglyLinkedList* ll, void* value, ForwardNode_t* mark);

/**
 * @brief Move a given node to its new position before `mark`
 *
 * If either the given node or mark are not an element of the list; node == mark; or node.next == mark, the list is not modified
 *
 * Both the node and mark must not be NULL
 *
 * @param ll
 * @param node
 * @param mark
 * @return int - 0 if success, else -1
 */
int csll_move_before(CircularSinglyLinkedList* ll, ForwardNode_t* node, ForwardNode_t* mark);

/**
 * @brief Move a given node to its new position after `mark`
 *
 * If either the given node or mark are not an element of the list; node == mark; or mark.next == node, the list is not modified
 *
 * Both the node and mark must not be NULL
 *
 * @param ll
 * @param node
 * @param mark
 * @return int - 0 if success, else -1
 */
int csll_move_after(CircularSinglyLinkedList* ll, ForwardNode_t* node, ForwardNode_t* mark);

/**
 * @brief Insert a copy of another list at the back of the caller list
 *
 * The lists may be the same, but must not be NULL
 *
 * @param ll
 * @param other
 * @return CircularSinglyLinkedList*
 */
CircularSinglyLinkedList* csll_push_back_list(CircularSinglyLinkedList* ll, CircularSinglyLinkedList* other);

/**
 * @brief Insert a copy of another list at the front of the caller list
 *
 * The lists may be the same, but must not be NULL
 *
 * @param ll
 * @param other
 * @return CircularSinglyLinkedList*
 */
CircularSinglyLinkedList* csll_push_front_list(CircularSinglyLinkedList* ll, CircularSinglyLinkedList* other);

/*****************************
 *	GlThread
 *****************************/

typedef struct glthread {
	struct glthread* prev;
	struct glthread* next;
} glthread_t;

void glthread_insert_after(glthread_t* base, glthread_t*next);

// void glthread_insert_before()
#endif
