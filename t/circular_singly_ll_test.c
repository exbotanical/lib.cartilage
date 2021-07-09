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

/**
 * Helpers
 */

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

void try_fail_data(LinkedList* ll, int vals_n, ...) {
	va_list args;

	va_start(args, vals_n);

	Node* tmp = ll->head;

	int iterations = vals_n;

	do {
		char n = (char)va_arg(args, int);

		assert(tmp->data == n);
		tmp = tmp->next;
	} while (--iterations);

	ASSERT(ll->size == vals_n, "has the expected list order and size");

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

void increment(Node* n) {
	n->data = 'Z';
}

void assert_n(Node* n) {
	ASSERT(n->data == 'Z', "iterator updated value");
}

LinkedList* test_iteration(LinkedList* ll) {
	DESCRIBE();

	char n1 = 'A', n2 = 'B', n3 = 'C';

	push_front(ll, n1);
	push_front(ll, n2);
	push_front(ll, n3);

	Node* n = ll->head;

	iterate(ll, increment);
	iterate(ll, assert_n);

	return ll;
}

LinkedList* test_extensibility(LinkedList* ll) {
	DESCRIBE();

	LinkedList* l2 = make_list();
	LinkedList* l3 = make_list();
	LinkedList* l4 = make_list();

	push_back(ll, 'A');
	push_back(ll, 'B');
	push_back(ll, 'C');

	push_back(l2, 'D');
	push_back(l2, 'E');

	push_back_list(l3, ll); // merge into an empty list
	try_fail_data(l3, 3, 'A', 'B', 'C');

	ASSERT(l3->size == ll->size, "lists remain congruent");

	push_back_list(l3, l2);
	try_fail_data(l3, 5, 'A', 'B', 'C', 'D', 'E');

	push_front_list(l4, l2); // merge into an empty list
	try_fail_data(l4, 2, 'D', 'E');

	push_front_list(l4, ll);
	try_fail_data(l4, 5, 'A', 'B', 'C', 'D', 'E');

	try_fail_data(ll, 3, 'A', 'B', 'C');
	try_fail_data(l2, 2, 'D', 'E');

	teardown(l2);
	teardown(l3);
	teardown(l4);

	return ll;
}


LinkedList* test_removal(LinkedList* ll) {
	DESCRIBE();

	Node* n1 = push_back(ll, 'A');
	Node* n2 = push_back(ll, 'B');

	try_fail(ll, 2, n1, n2);

	Node* n = ll->head;

	remove_node(ll, n);
	try_fail(ll, 1, n2);

	remove_node(ll, n);
	try_fail(ll, 1, n2);

	ASSERT(1 == 1, "maintains integrity across varietied removals");

	return ll;
}

LinkedList* test_noop(LinkedList* ll) {
	DESCRIBE();

	LinkedList* l2 = make_list();

	push_back(ll, 1);
	push_back(ll, 2);

	push_back(l2, 3);
	push_back(l2, 4);

	Node* n = ll->head;
	remove_node(l2, n); // l2 should not change because n is not a node of l2

	int s1 = l2->size;
	ASSERT(s1 == 2, "size should remain unaffected given no-ops");

	insert_before(ll, 'A', n);

	int s2 = ll->size;
	ASSERT(s2 == 3, "size should remain unaffected given no-ops");

	ASSERT(1 == 1, "should not be modified when invoking operations upon non-member nodes");

	teardown(l2);

	return ll;
}

LinkedList* test_move(LinkedList* ll) {
	DESCRIBE();

	Node* n1 = push_back(ll, 'A');
	Node* n2 = push_back(ll, 'B');
	Node* n3 = push_back(ll, 'C');
	Node* n4 = push_back(ll, 'D');

	move_after(ll, n3, n3); // noop
	try_fail(ll, 4, n1, n2, n3, n4);

	move_before(ll, n2, n2); // noop
	try_fail(ll, 4, n1, n2, n3, n4);

	move_after(ll, n3, n2); // noop
	try_fail(ll, 4, n1, n2, n3, n4);

	move_before(ll, n2, n3); // noop
	try_fail(ll, 4, n1, n2, n3, n4);

	move_before(ll, n2, n4);
	try_fail(ll, 4, n1, n3, n2, n4);

	move_before(ll, n4, n1);
	try_fail(ll, 4, n1, n3, n2, n4);

	ASSERT(1 == 1, "maintains integrity across varietied moves");

	return ll;
}

LinkedList* test_modification(LinkedList* ll) {
	DESCRIBE();

	push_back(ll, 'A');
	push_back(ll, 'B');
	push_back(ll, 'C');
	insert_after(ll, randch(), __make_node(randch()));

	try_fail_data(ll, 3, 'A', 'B', 'C');

	ASSERT(1 == 1, "is not modified when invoking 'insert_after' with a mark that is not a node thereof");

	LinkedList* l1 = make_list();
	LinkedList* l2 = make_list();

	Node* n1 = push_back(l1, 'A');
	Node* n2 = push_back(l2, 'B');

	move_after(l1, n1, n2);
	try_fail_data(l1, 1, 'A');
	try_fail_data(l2, 1, 'B');

	move_before(l1, n1, n2);
	try_fail_data(l1, 1, 'A');
	try_fail_data(l2, 1, 'B');

	ASSERT(1 == 1, "is not modified when invoking 'move_after', 'move_before' with a mark that is not a node thereof");

	LinkedList* l3 = make_list();

	push_back(l3, NULL);
	push_front(l3, NULL);
	move_after(l3, NULL, NULL);
	move_before(l3, NULL, NULL);
	insert_after(l3, NULL, NULL);
	insert_before(l3, NULL, NULL);
	next(l3, NULL);
	prev(l3, NULL);
	push_front_list(l3, NULL);
	push_back_list(l3, NULL);
	remove_node(l3, NULL);
	remove_node(l3, NULL);
	pop(l3);

	ASSERT(l3->size == 1, "is not modified when operations are invoked on an empty list");

	teardown(l1);
	teardown(l2);
	teardown(l3);

	return ll;
}

LinkedList* test_single_node_ll(LinkedList* ll) {
	DESCRIBE();

	Node* n = push_front(ll, 'B');

	ASSERT(next(ll, n) == n, "points to itself");
	ASSERT(prev(ll, n) == n, "points to itself");

	try_fail(ll, 1, n);

	LinkedList* l2 = make_list();
	Node* n2 = push_front(l2, 'A');

	try_fail(l2, 1, n2);

	push_front_list(ll, l2);
	try_fail_data(ll, 2, 'A', 'B');

	push_back_list(ll, l2);
	try_fail_data(ll, 3, 'A', 'B', 'A');

	LinkedList* l3 = make_list();

	Node* n3 = push_front(l3, 'B');

	ASSERT(next(l3, n3) == n3, "points to itself");
	ASSERT(prev(l3, n3) == n3, "points to itself");

	try_fail(l3, 1, n3);

	ASSERT(1 == 1, "maintains integrity when operating upon a single-node list");

	teardown(l2);
	teardown(l3);

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
	run_test(setup, teardown, test_iteration);
	run_test(setup, teardown, test_extensibility);
	run_test(setup, teardown, test_removal);
	run_test(setup, teardown, test_noop);
	run_test(setup, teardown, test_move);
	run_test(setup, teardown, test_modification);
	run_test(setup, teardown, test_single_node_ll);
}
