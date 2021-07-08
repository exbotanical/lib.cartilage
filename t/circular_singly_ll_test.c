#include "test_util.h"

#include "libcartilage.h"

/**
 * Lifecycle
 */

int run_test(CircularSinglyLinkedList* (*setup)(void), void (*teardown)(CircularSinglyLinkedList*), CircularSinglyLinkedList* (*test)(CircularSinglyLinkedList*)) {
	teardown(test(setup()));
}

CircularSinglyLinkedList* setup(void) {
	return make_list();
}

void teardown(CircularSinglyLinkedList* ll) {
	iterate(ll, free);
	free(ll);
}

/**
 * Tests
 */

CircularSinglyLinkedList* test_push_back(CircularSinglyLinkedList* ll) {
	DESCRIBE();

	ForwardNode_t* n = push_back(ll, 'A');

	ASSERT(n->next == ll->head, "inserts a node as the head when the list is empty");
	ASSERT(n->next->data == ll->head->data, "maintains rule such that tail->next == head");

	ASSERT(ll->size == 1, "maintains proper list size");
	return ll;
}

CircularSinglyLinkedList* test_push_back_2(CircularSinglyLinkedList* ll) {
	DESCRIBE();

	int iterations = 4;

	for (int i = iterations; i > 0; i--) {
		push_back(ll, randch());
	}

	ForwardNode_t* n = push_back(ll, randch());

	ASSERT(n->next == ll->head, "inserts a node as the last node in a non-empty list");
	ASSERT(ll->size == iterations + 1, "maintains proper list size");

	return ll;
}

CircularSinglyLinkedList* test_push_front(CircularSinglyLinkedList* ll) {
	DESCRIBE();

	ForwardNode_t *n = push_front(ll, randch());

	ASSERT(n->next == ll->head, "a) inserts a node as the head when the list is empty");
	ASSERT(n == ll->head->next, "b) inserts a node as the head when the list is empty");

	ASSERT(ll->size == 1, "maintains proper list size");

	return ll;
}

CircularSinglyLinkedList* test_push_front_2(CircularSinglyLinkedList* ll) {
	DESCRIBE();

	int iterations = 4;

	for (int i = iterations; i > 0; i--) {
		push_front(ll, randch());
	}

	ForwardNode_t* n = push_front(ll, randch());

	ASSERT(n == ll->head, "a) inserts a node as the head in a non-empty list");
	ASSERT(n->next == ll->head->next, "b) inserts a node as the head in a non-empty list");

	ASSERT(ll->size == iterations + 1, "maintains proper list size");

	return ll;
}

CircularSinglyLinkedList* test_head(CircularSinglyLinkedList* ll) {
	DESCRIBE();
	char value = 'z';

	ForwardNode_t* n = push_front(ll, value);

	ASSERT(value == ll->head->data, "value congruence");
	ASSERT(value == n->data, "value congruence");

	push_front(ll, randch());
	push_front(ll, randch());
	push_front(ll, randch());

	ForwardNode_t *n1 = push_front(ll, value);

	ASSERT(n1 == ll->head, "a) sets the new head of the list");
	ASSERT(value == ll->head->next->data, "b) sets the new head of the list");
	ASSERT(value == (prev(ll, ll->head))->data, "c) sets the new head of the list");

	ASSERT(ll->size == 5, "maintains proper list size");

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
}
