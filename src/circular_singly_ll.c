#include "libcartilage.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

char __rand_letter(void) {
	char a;

	do {
		a = "ABCDEFHIJKLMNOPQRSTUVWXYZ"[random() % 26];
	} while (!a);

	return a;
}

Node_t* __new_head(LinkedList* ll, Node_t* node) {
	ll->head = node;
	node->next = ll->head;

	ll->size++;

	return node;
}

Node_t* __find_node_before(LinkedList* ll, Node_t* target) {
	Node_t* tmp = ll->head;

	while (tmp->next != target) {
		tmp = tmp->next;

		if (!tmp->next) break;
	}

	return tmp;
}


Node_t* __move(LinkedList* ll, Node_t* node, Node_t* at) {
	Node_t* tmp = __find_node_before(ll, node);

	tmp->next = node->next;
	node->next = at->next;
	at->next = node;

	return node;
}


LinkedList* make_list(void) {
	LinkedList* ll = malloc(sizeof(LinkedList));

	ll->head = NULL;
	ll->size = 0;

	return ll;
}

Node_t* make_node(char value) {
	Node_t* n = malloc(sizeof(Node_t));

	n->data = value;
	n->next = NULL;

	return n;
}

Node_t* push_back(LinkedList* ll, char value) {
	Node_t* node = make_node(value);

	if (!ll->head) return __new_head(ll, node);

	if (ll->head && ll->size == 1) {
		ll->head->next = node;
	} else {
		Node_t* tmp = __find_node_before(ll, ll->head);
		tmp->next = node;
	}

	node->next = ll->head;

	ll->size++;
	return node;
}

Node_t* push_front(LinkedList* ll, char value) {
	Node_t* node = make_node(value);

	if (!ll->head) return __new_head(ll, node);

	Node_t* tmp = __find_node_before(ll, ll->head);

	node->next = ll->head;
	ll->head = node;
	tmp->next = ll->head;

	ll->size++;
	return node;
}

void print_node_d(Node_t* n) {
	COUT(n->data);
}

void iterate(LinkedList* ll, void (*callback)(void*)) {
	Node_t* n = ll->head;

	do {
		callback(n);
		n = n->next;
	} while (n->next && n->next != ll->head);
}
