#include "test_util.h"

#include "libcartilage.h"
#include <stdarg.h>

/**
 * Environment
 */

typedef ForwardNode_t Node;

typedef CircularSinglyLinkedList LinkedList;

/**
 * Lifecycle
 */

int run_test(LinkedList* (*setup)(void), void (*teardown)(LinkedList*), LinkedList* (*test)(LinkedList*)) {
	teardown(test(setup()));
}

LinkedList* setup(void) {
	return make_list();
}

void teardown(LinkedList* ll) {
	iterate(ll, free);
	free(ll);
}

void try_fail(LinkedList* ll, int nodes_n, ...) {
	va_list args;

	va_start(args, nodes_n);

	Node* tmp = ll->head;

	int iterations = nodes_n;

	do {
		Node* nN = va_arg(args, Node*);

		assert(tmp == nN);
		tmp = tmp->next;
	} while (--iterations);

	ASSERT(ll->size == nodes_n, "has the expected list order and size");

	va_end(args);
}

/**
 * Tests
 */

LinkedList* test_push_back(LinkedList* ll) {
	DESCRIBE();

	Node* n = push_back(ll, 'A');

	ASSERT(n->next == ll->head, "inserts a node as the head when the list is empty");
	ASSERT(n->next->data == ll->head->data, "maintains rule such that tail->next == head");

	ASSERT(ll->size == 1, "maintains proper list size");
	return ll;
}

LinkedList* test_push_back_2(LinkedList* ll) {
	DESCRIBE();

	int iterations = 4;

	for (int i = iterations; i > 0; i--) {
		push_back(ll, randch());
	}

	Node* n = push_back(ll, randch());

	ASSERT(n->next == ll->head, "inserts a node as the last node in a non-empty list");
	ASSERT(ll->size == iterations + 1, "maintains proper list size");

	return ll;
}

LinkedList* test_push_front(LinkedList* ll) {
	DESCRIBE();

	Node *n = push_front(ll, randch());

	ASSERT(n->next == ll->head, "a) inserts a node as the head when the list is empty");
	ASSERT(n == ll->head->next, "b) inserts a node as the head when the list is empty");

	ASSERT(ll->size == 1, "maintains proper list size");

	return ll;
}

LinkedList* test_push_front_2(LinkedList* ll) {
	DESCRIBE();

	int iterations = 4;

	for (int i = iterations; i > 0; i--) {
		push_front(ll, randch());
	}

	Node* n = push_front(ll, randch());

	ASSERT(n == ll->head, "a) inserts a node as the head in a non-empty list");
	ASSERT(n->next == ll->head->next, "b) inserts a node as the head in a non-empty list");

	ASSERT(ll->size == iterations + 1, "maintains proper list size");

	return ll;
}

LinkedList* test_head(LinkedList* ll) {
	DESCRIBE();
	char value = 'z';

	Node* n = push_front(ll, value);

	ASSERT(value == ll->head->data, "value congruence");
	ASSERT(value == n->data, "value congruence");

	push_front(ll, randch());
	push_front(ll, randch());
	push_front(ll, randch());

	Node *n1 = push_front(ll, value);

	ASSERT(n1 == ll->head, "a) sets the new head of the list");
	ASSERT(value == ll->head->next->data, "b) sets the new head of the list");
	ASSERT(value == (prev(ll, ll->head))->data, "c) sets the new head of the list");

	ASSERT(ll->size == 5, "maintains proper list size");

	return ll;
}

LinkedList* test_multi_node_ll(LinkedList* ll) {
	DESCRIBE();
	Node* n2 = push_front(ll, randch());
	Node* n1 = push_front(ll, randch());
	Node* n3 = push_back(ll, randch());
	Node* n4 = push_back(ll, randch());

	try_fail(ll, 4, n1, n2, n3, n4);

	remove_node(ll, n2);
	try_fail(ll, 3, n1, n3, n4);

	remove_node(ll, n2);
	try_fail(ll, 3, n1, n3, n4);

	remove_node(ll, ll->head);
	try_fail(ll, 2, n3, n4);

	Node* t1 = pop(ll);

	assert(t1 == n4);
	try_fail(ll, 1, n3);

	assert(insert_after(ll, randch(), t1) == NULL); // no-op

	assert(ll->head == prev(ll, ll->head)); // head = tail

	n2 = insert_after(ll, randch(), n3); // insert after tail
	try_fail(ll, 2, n3, n2);

	assert(prev(ll, ll->head) == n2);
	assert(ll->head == n3);

	n4 = insert_after(ll, 4, n2); // insert after tail
	try_fail(ll, 3, n3, n2, n4);
	assert(n4->next == ll->head);
	assert(prev(ll, n3) == n4);

	Node *n5 = insert_after(ll, randch(), n2); // insert after head
	try_fail(ll, 4, n3, n2, n5, n4);

	remove_node(ll, n2);
	n2 = insert_after(ll, randch(), n5); // insert after middle
	try_fail(ll, 4, n3, n5, n2, n4);

	remove_node(ll, n2);
	n2 = insert_after(ll, randch(), n4); // insert after tail
	try_fail(ll, 4, n3, n5, n4, n2);

	remove_node(ll, n2);

	pop(ll);

	try_fail(ll, 2, n3, n5);

	assert(pop(ll) == n5);
	assert(pop(ll) == n3);
	assert(pop(ll) == NULL); // no-op
	assert(ll->size == 0);

	assert(insert_before(ll, randch(), n5) == NULL); // no-op

	Node* m2 = push_front(ll, randch());
	Node* m3 = push_back(ll, randch());
	Node* m1 = push_front(ll, randch());

	try_fail(ll, 3, m1, m2, m3);

	return ll;
}

/**
 * Runner
 */

int main() {
	run_test(setup, teardown, test_push_back);
	run_test(setup, teardown, test_push_back_2);
	run_test(setup, teardown, test_push_front);
	run_test(setup, teardown, test_push_front_2);
	run_test(setup, teardown, test_multi_node_ll);
}
