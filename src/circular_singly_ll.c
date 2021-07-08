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
 * @return ForwardNode_t*
 */
ForwardNode_t* __new_head(CircularSinglyLinkedList* ll, ForwardNode_t* node) {
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
 * @return ForwardNode_t*
 */
ForwardNode_t* __find_node_before(CircularSinglyLinkedList* ll, ForwardNode_t* target) {
	ForwardNode_t* tmp = ll->head;

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
 * @return ForwardNode_t*
 */
ForwardNode_t* __move(CircularSinglyLinkedList* ll, ForwardNode_t* node, ForwardNode_t* at) {
	ForwardNode_t* tmp = __find_node_before(ll, node);

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
 * @return ForwardNode_t*
 */
ForwardNode_t* __make_node(char value) {
	ForwardNode_t* n = malloc(sizeof(ForwardNode_t));

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
 * @return ForwardNode_t*
 */
ForwardNode_t* prev(CircularSinglyLinkedList* ll, ForwardNode_t* node) {
	if (!node || !node->list || node->list != ll) return NULL;

	ForwardNode_t* p = __find_node_before(ll, node);

	return p ? p : NULL;
}

/**
 * @brief Returns the next list node, if extant; else, NULL
 *
 * @param ll
 * @param node
 * @return ForwardNode_t*
 */
ForwardNode_t* next(CircularSinglyLinkedList* ll, ForwardNode_t* node) {
	if (!node || !node->list || node->list != ll) return NULL;

	ForwardNode_t* p = node->next;

	return p ? p : NULL;
}

/**
 * @brief Push a new node with value `value` to the back of the list
 *
 * @param ll
 * @param value
 * @return ForwardNode_t*
 */
ForwardNode_t* push_back(CircularSinglyLinkedList* ll, char value) {
	ForwardNode_t* node = __make_node(value);

	if (!ll->head) return __new_head(ll, node);

	if (ll->head && ll->size == 1) {
		ll->head->next = node;
	} else {
		ForwardNode_t* tmp = __find_node_before(ll, ll->head);
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
 * @return ForwardNode_t*
 */
ForwardNode_t* push_front(CircularSinglyLinkedList* ll, char value) {
	ForwardNode_t* node = __make_node(value);

	if (!ll->head) return __new_head(ll, node);

	ForwardNode_t* tmp = __find_node_before(ll, ll->head);

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
int move_after (CircularSinglyLinkedList* ll, ForwardNode_t* node, ForwardNode_t* mark) {
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
int move_before (CircularSinglyLinkedList* ll, ForwardNode_t* node, ForwardNode_t* mark) {
	if (!node || !mark) return -1;

	if (node->list != ll || node == mark || mark->list != ll) {
		return -1;
	}

	if (node->next == mark) return -1;

	ForwardNode_t* tmp = __find_node_before(ll, mark);
	__move(ll, node, tmp);
	return 0;
}

/**
 * @brief Remove a given node from the list
 *
 * @param ll
 * @param node
 * @return ForwardNode_t*
 */
ForwardNode_t* remove_node(CircularSinglyLinkedList* ll, ForwardNode_t* node) {
	if (!ll->head || !node) return NULL;

	if (node->list != ll) return NULL;

	ForwardNode_t* tmp1 = ll->head;
	ForwardNode_t* tmp2 = NULL;

	while (tmp1 != node) {
		tmp2 = tmp1;
		tmp1 = tmp1->next;
	}

	if (tmp1 == ll->head) {
		tmp2 = ll->head;

		while (tmp2->next != ll->head) tmp2 = tmp2->next;

		ll->head = ll->head->next;
		tmp2->next = ll->head;
	} else {
		tmp2->next = tmp1->next;
	}

	node->list = NULL;

	ll->size--;

	return node;
}

/**
 * @brief Remove the last node from the list
 *
 * @param ll
 * @return ForwardNode_t*
 */
ForwardNode_t* pop(CircularSinglyLinkedList* ll) {
	if (!ll->head) return NULL;

	ForwardNode_t* tmp = ll->head;

	while (tmp->next != ll->head) tmp = tmp->next;

	return remove_node(ll, tmp);
}

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
ForwardNode_t* insert_after(CircularSinglyLinkedList* ll, char value, ForwardNode_t* mark) {
	if (!mark || mark->list != ll) return NULL;

	ForwardNode_t* n = __make_node(value);

	if (!ll->head) return __new_head(ll, n);

	ForwardNode_t* tmp = __find_node_before(ll, mark->next);

	if (tmp->next == ll->head) {
		tmp->next = n;
		n->next = ll->head;
	} else {
		n->next = tmp->next;
		tmp->next = n;
	}

	n->list = ll;
	ll->size++;

	return n;
}

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
ForwardNode_t* insert_before(CircularSinglyLinkedList* ll, char value, ForwardNode_t* mark) {
	if (!mark || mark->list != ll) return NULL;

	return insert_after(ll, value, prev(ll, mark));
}

/**
 * @brief Iterate over the list and invoke `callback` with each node
 *
 * @param ll
 * @param callback
 */
void iterate(CircularSinglyLinkedList* ll, void (*callback)(void*)) {
	ForwardNode_t* n = ll->head;

	do {
		callback(n);
		n = n->next;
	} while (n->next && n->next != ll->head);
}
