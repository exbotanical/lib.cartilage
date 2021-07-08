#include "libcartilage.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

/**
 * @brief Bootstrap a new head node
 * @private
 *
 * @param ll
 * @param node
 * @return Node_t*
 */
Node_t* __new_head(CircularSinglyLinkedList* ll, Node_t* node) {
	ll->head = node;
	node->next = ll->head;

	node->list = ll;
	ll->size++;
	return node;
}

/**
 * @brief Find the node prior to the given target
 * @private
 *
 * @param ll
 * @param target
 * @return Node_t*
 */
Node_t* __find_node_before(CircularSinglyLinkedList* ll, Node_t* target) {
	Node_t* tmp = ll->head;

	while (tmp->next != target) {
		tmp = tmp->next;

		if (!tmp->next) break;
	}

	return tmp;
}

/**
 * @brief Move given node after `at`, where `node` and `at` must be a member of the list
 * @private
 *
 * @param ll
 * @param node
 * @param at
 * @return Node_t*
 */
Node_t* __move(CircularSinglyLinkedList* ll, Node_t* node, Node_t* at) {
	Node_t* tmp = __find_node_before(ll, node);

	tmp->next = node->next;
	node->next = at->next;
	at->next = node;

	return node;
}

/**
 * @brief Generate a new node
 * @private
 *
 * @param value
 * @return Node_t*
 */
Node_t* __make_node(char value) {
	Node_t* n = malloc(sizeof(Node_t));

	n->data = value;
	n->next = NULL;
	n->list = NULL;

	return n;
}

/**
 * @brief Instantiate an empty circular singly linked list
 *
 * @return CircularSinglyLinkedList*
 */
CircularSinglyLinkedList* make_list(void) {
	CircularSinglyLinkedList* ll = malloc(sizeof(CircularSinglyLinkedList));

	ll->head = NULL;
	ll->size = 0;

	return ll;
}

/**
 * @brief Returns the previous list node, if extant; else, NULL
 *
 * @param ll
 * @param node
 * @return Node_t*
 */
Node_t* prev(CircularSinglyLinkedList* ll, Node_t* node) {
	if (!node || !node->list || node->list != ll) return NULL;

	Node_t* p = __find_node_before(ll, node);

	return p ? p : NULL;
}

/**
 * @brief Returns the next list node, if extant; else, NULL
 *
 * @param ll
 * @param node
 * @return Node_t*
 */
Node_t* next(CircularSinglyLinkedList* ll, Node_t* node) {
	if (!node || !node->list || node->list != ll) return NULL;

	Node_t* p = node->next;

	return p ? p : NULL;
}

/**
 * @brief Push a new node with value `value` to the back of the list
 *
 * @param ll
 * @param value
 * @return Node_t*
 */
Node_t* push_back(CircularSinglyLinkedList* ll, char value) {
	Node_t* node = __make_node(value);

	if (!ll->head) return __new_head(ll, node);

	if (ll->head && ll->size == 1) {
		ll->head->next = node;
	} else {
		Node_t* tmp = __find_node_before(ll, ll->head);
		tmp->next = node;
	}

	node->next = ll->head;

	node->list = ll;
	ll->size++;

	return node;
}

/**
 * @brief Push a new node with value `value` to the front of the list
 *
 * @param ll
 * @param value
 * @return Node_t*
 */
Node_t* push_front(CircularSinglyLinkedList* ll, char value) {
	Node_t* node = __make_node(value);

	if (!ll->head) return __new_head(ll, node);

	Node_t* tmp = __find_node_before(ll, ll->head);

	node->next = ll->head;
	ll->head = node;
	tmp->next = ll->head;

	node->list = ll;
	ll->size++;

	return node;
}

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
int move_after (CircularSinglyLinkedList* ll, Node_t* node, Node_t* mark) {
	if (!node || !mark) return -1;

	if (node->list != ll || node == mark || mark->list != ll) {
		return -1;
	}

	if (mark->next == node) return -1;

	__move(ll, node, mark);
	return 0;
}

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
int move_before (CircularSinglyLinkedList* ll, Node_t* node, Node_t* mark) {
	if (!node || !mark) return -1;

	if (node->list != ll || node == mark || mark->list != ll) {
		return -1;
	}

	if (node->next == mark) return -1;

	Node_t* tmp = __find_node_before(ll, mark);
	__move(ll, node, tmp);
	return 0;
}

void iterate(CircularSinglyLinkedList* ll, void (*callback)(void*)) {
	Node_t* n = ll->head;

	do {
		callback(n);
		n = n->next;
	} while (n->next && n->next != ll->head);
}
