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
	return csll_make_list();
}

void teardown(LinkedList* ll) {
	csll_iterate(ll, free);
	free(ll);
}

/**
 * Helpers
 */

void assert_ordinal_pointers(LinkedList* ll, int nodes_n, ...) {
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

void assert_ordinal_data(LinkedList* ll, int vals_n, ...) {
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

LinkedList* test_csll_push_back(LinkedList* ll) {
	DESCRIBE();

	Node* n = csll_push_back(ll, 'A');

	ASSERT(n->next == ll->head, "inserts a node as the head when the list is empty");
	ASSERT(n->next->data == ll->head->data, "maintains rule such that tail->next == head");

	ASSERT(ll->size == 1, "maintains proper list size");
	return ll;
}

LinkedList* test_csll_push_back_2(LinkedList* ll) {
	DESCRIBE();

	int iterations = 4;

	for (int i = iterations; i > 0; i--) {
		csll_push_back(ll, (void*)randch());
	}

	Node* n = csll_push_back(ll, (void*)randch());

	ASSERT(n->next == ll->head, "inserts a node as the last node in a non-empty list");
	ASSERT(ll->size == iterations + 1, "maintains proper list size");

	return ll;
}

LinkedList* test_csll_push_front(LinkedList* ll) {
	DESCRIBE();

	Node *n = csll_push_front(ll, (void*)randch());

	ASSERT(n->next == ll->head, "a) inserts a node as the head when the list is empty");
	ASSERT(n == ll->head->next, "b) inserts a node as the head when the list is empty");

	ASSERT(ll->size == 1, "maintains proper list size");

	return ll;
}

LinkedList* test_csll_push_front_2(LinkedList* ll) {
	DESCRIBE();

	int iterations = 4;

	for (int i = iterations; i > 0; i--) {
		csll_push_front(ll, (void*)randch());
	}

	Node* n = csll_push_front(ll, (void*)randch());

	ASSERT(n == ll->head, "a) inserts a node as the head in a non-empty list");
	ASSERT(n->next == ll->head->next, "b) inserts a node as the head in a non-empty list");

	ASSERT(ll->size == iterations + 1, "maintains proper list size");

	return ll;
}

LinkedList* test_head(LinkedList* ll) {
	DESCRIBE();
	char value = 'z';

	Node* n = csll_push_front(ll, value);

	ASSERT(value == ll->head->data, "value congruence");
	ASSERT(value == n->data, "value congruence");

	csll_push_front(ll, (void*)randch());
	csll_push_front(ll, (void*)randch());
	csll_push_front(ll, (void*)randch());

	Node *n1 = csll_push_front(ll, value);

	ASSERT(n1 == ll->head, "a) sets the new head of the list");
	ASSERT(value == *(char*)ll->head->next->data, "b) sets the new head of the list");
	ASSERT(value == *(char*)(csll_prev(ll, ll->head))->data, "c) sets the new head of the list");

	ASSERT(ll->size == 5, "maintains proper list size");

	return ll;
}

LinkedList* test_multi_node_ll(LinkedList* ll) {
	DESCRIBE();

	Node* n2 = csll_push_front(ll, (void*)randch());
	Node* n1 = csll_push_front(ll, (void*)randch());
	Node* n3 = csll_push_back(ll, (void*)randch());
	Node* n4 = csll_push_back(ll, (void*)randch());

	assert_ordinal_pointers(ll, 4, n1, n2, n3, n4);

	csll_remove_node(ll, n2);
	assert_ordinal_pointers(ll, 3, n1, n3, n4);

	csll_remove_node(ll, n2);
	assert_ordinal_pointers(ll, 3, n1, n3, n4);

	csll_remove_node(ll, ll->head);
	assert_ordinal_pointers(ll, 2, n3, n4);

	Node* t1 = csll_pop(ll);

	assert(t1 == n4);
	assert_ordinal_pointers(ll, 1, n3);

	assert(csll_insert_after(ll, (void*)randch(), t1) == NULL); // no-op

	assert(ll->head == csll_prev(ll, ll->head)); // head = tail

	n2 = csll_insert_after(ll, (void*)randch(), n3); // insert after tail
	assert_ordinal_pointers(ll, 2, n3, n2);

	assert(csll_prev(ll, ll->head) == n2);
	assert(ll->head == n3);

	n4 = csll_insert_after(ll, 4, n2); // insert after tail
	assert_ordinal_pointers(ll, 3, n3, n2, n4);
	assert(n4->next == ll->head);
	assert(csll_prev(ll, n3) == n4);

	Node *n5 = csll_insert_after(ll, (void*)randch(), n2); // insert after head
	assert_ordinal_pointers(ll, 4, n3, n2, n5, n4);

	csll_remove_node(ll, n2);
	n2 = csll_insert_after(ll, (void*)randch(), n5); // insert after middle
	assert_ordinal_pointers(ll, 4, n3, n5, n2, n4);

	csll_remove_node(ll, n2);
	n2 = csll_insert_after(ll, (void*)randch(), n4); // insert after tail
	assert_ordinal_pointers(ll, 4, n3, n5, n4, n2);

	csll_remove_node(ll, n2);

	csll_pop(ll);

	assert_ordinal_pointers(ll, 2, n3, n5);

	assert(csll_pop(ll) == n5);
	assert(csll_pop(ll) == n3);
	assert(csll_pop(ll) == NULL); // no-op
	assert(ll->size == 0);

	assert(csll_insert_before(ll, (void*)randch(), n5) == NULL); // no-op

	Node* m2 = csll_push_front(ll, (void*)randch());
	Node* m3 = csll_push_back(ll, (void*)randch());
	Node* m1 = csll_push_front(ll, (void*)randch());

	assert_ordinal_pointers(ll, 3, m1, m2, m3);

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

	csll_push_front(ll, (void*)n1);
	csll_push_front(ll, (void*)n2);
	csll_push_front(ll, (void*)n3);

	Node* n = ll->head;

	csll_iterate(ll, increment);
	csll_iterate(ll, assert_n);

	return ll;
}

LinkedList* test_extensibility(LinkedList* ll) {
	DESCRIBE();

	LinkedList* l2 = csll_make_list();
	LinkedList* l3 = csll_make_list();
	LinkedList* l4 = csll_make_list();

	csll_push_back(ll, (void*)'A');
	csll_push_back(ll, (void*)'B');
	csll_push_back(ll, (void*)'C');

	csll_push_back(l2, (void*)'D');
	csll_push_back(l2, (void*)'E');

	csll_push_back_list(l3, ll); // merge into an empty list
	assert_ordinal_data(l3, 3, 'A', 'B', 'C');

	ASSERT(l3->size == ll->size, "lists remain congruent");

	csll_push_back_list(l3, l2);
	assert_ordinal_data(l3, 5, 'A', 'B', 'C', 'D', 'E');

	csll_push_front_list(l4, l2); // merge into an empty list
	assert_ordinal_data(l4, 2, 'D', 'E');

	csll_push_front_list(l4, ll);
	assert_ordinal_data(l4, 5, 'A', 'B', 'C', 'D', 'E');

	assert_ordinal_data(ll, 3, 'A', 'B', 'C');
	assert_ordinal_data(l2, 2, 'D', 'E');

	teardown(l2);
	teardown(l3);
	teardown(l4);

	return ll;
}


LinkedList* test_removal(LinkedList* ll) {
	DESCRIBE();

	Node* n1 = csll_push_back(ll, (void*)'A');
	Node* n2 = csll_push_back(ll, (void*)'B');

	assert_ordinal_pointers(ll, 2, n1, n2);

	Node* n = ll->head;

	csll_remove_node(ll, n);
	assert_ordinal_pointers(ll, 1, n2);

	csll_remove_node(ll, n);
	assert_ordinal_pointers(ll, 1, n2);

	ASSERT(1 == 1, "maintains integrity across varietied removals");

	return ll;
}

LinkedList* test_noop(LinkedList* ll) {
	DESCRIBE();

	LinkedList* l2 = csll_make_list();

	csll_push_back(ll, (void*)'A');
	csll_push_back(ll, (void*)'B');

	csll_push_back(l2, (void*)'C');
	csll_push_back(l2, (void*)'D');

	Node* n = ll->head;
	csll_remove_node(l2, n); // l2 should not change because n is not a node of l2

	int s1 = l2->size;
	ASSERT(s1 == 2, "size should remain unaffected given no-ops");

	csll_insert_before(ll, (void*)'A', n);

	int s2 = ll->size;
	ASSERT(s2 == 3, "size should remain unaffected given no-ops");

	ASSERT(1 == 1, "should not be modified when invoking operations upon non-member nodes");

	teardown(l2);

	return ll;
}

LinkedList* test_move(LinkedList* ll) {
	DESCRIBE();

	Node* n1 = csll_push_back(ll, (void*)'A');
	Node* n2 = csll_push_back(ll, (void*)'B');
	Node* n3 = csll_push_back(ll, (void*)'C');
	Node* n4 = csll_push_back(ll, (void*)'D');

	csll_move_after(ll, n3, n3); // noop
	assert_ordinal_pointers(ll, 4, n1, n2, n3, n4);

	csll_move_before(ll, n2, n2); // noop
	assert_ordinal_pointers(ll, 4, n1, n2, n3, n4);

	csll_move_after(ll, n3, n2); // noop
	assert_ordinal_pointers(ll, 4, n1, n2, n3, n4);

	csll_move_before(ll, n2, n3); // noop
	assert_ordinal_pointers(ll, 4, n1, n2, n3, n4);

	csll_move_before(ll, n2, n4);
	assert_ordinal_pointers(ll, 4, n1, n3, n2, n4);

	csll_move_before(ll, n4, n1);
	assert_ordinal_pointers(ll, 4, n1, n3, n2, n4);

	ASSERT(1 == 1, "maintains integrity across varietied moves");

	return ll;
}

LinkedList* test_modification(LinkedList* ll) {
	DESCRIBE();

	csll_push_back(ll, (void*)'A');
	csll_push_back(ll, (void*)'B');
	csll_push_back(ll, (void*)'C');
	csll_insert_after(ll, (void*)randch(), __csll_make_node((void*)randch()));

	assert_ordinal_data(ll, 3, 'A', 'B', 'C');

	ASSERT(1 == 1, "is not modified when invoking 'csll_insert_after' with a mark that is not a node thereof");

	LinkedList* l1 = csll_make_list();
	LinkedList* l2 = csll_make_list();

	Node* n1 = csll_push_back(l1, (void*)'A');
	Node* n2 = csll_push_back(l2, (void*)'B');

	csll_move_after(l1, n1, n2);
	assert_ordinal_data(l1, 1, 'A');
	assert_ordinal_data(l2, 1, 'B');

	csll_move_before(l1, n1, n2);
	assert_ordinal_data(l1, 1, 'A');
	assert_ordinal_data(l2, 1, 'B');

	ASSERT(1 == 1, "is not modified when invoking 'csll_move_after', 'csll_move_before' with a mark that is not a node thereof");

	LinkedList* l3 = csll_make_list();

	csll_push_back(l3, NULL);
	csll_push_front(l3, NULL);
	csll_move_after(l3, NULL, NULL);
	csll_move_before(l3, NULL, NULL);
	csll_insert_after(l3, NULL, NULL);
	csll_insert_before(l3, NULL, NULL);
	csll_next(l3, NULL);
	csll_prev(l3, NULL);
	csll_push_front_list(l3, NULL);
	csll_push_back_list(l3, NULL);
	csll_remove_node(l3, NULL);
	csll_remove_node(l3, NULL);
	csll_pop(l3);

	ASSERT(l3->size == 1, "is not modified when operations are invoked on an empty list");

	teardown(l1);
	teardown(l2);
	teardown(l3);

	return ll;
}

LinkedList* test_single_node_ll(LinkedList* ll) {
	DESCRIBE();

	Node* n = csll_push_front(ll, (void*)'B');

	ASSERT(csll_next(ll, n) == n, "points to itself");
	ASSERT(csll_prev(ll, n) == n, "points to itself");

	assert_ordinal_pointers(ll, 1, n);

	LinkedList* l2 = csll_make_list();
	Node* n2 = csll_push_front(l2, (void*)'A');

	assert_ordinal_pointers(l2, 1, n2);

	csll_push_front_list(ll, l2);
	assert_ordinal_data(ll, 2, 'A', 'B');

	csll_push_back_list(ll, l2);
	assert_ordinal_data(ll, 3, 'A', 'B', 'A');

	LinkedList* l3 = csll_make_list();

	Node* n3 = csll_push_front(l3, (void*)'B');

	ASSERT(csll_next(l3, n3) == n3, "points to itself");
	ASSERT(csll_prev(l3, n3) == n3, "points to itself");

	assert_ordinal_pointers(l3, 1, n3);

	ASSERT(1 == 1, "maintains integrity when operating upon a single-node list");

	teardown(l2);
	teardown(l3);

	return ll;
}


/**
 * Runner
 */

int main() {
	run_test(setup, teardown, test_csll_push_back);
	run_test(setup, teardown, test_csll_push_back_2);
	run_test(setup, teardown, test_csll_push_front);
	run_test(setup, teardown, test_csll_push_front_2);
	run_test(setup, teardown, test_multi_node_ll);
	run_test(setup, teardown, test_iteration);
	run_test(setup, teardown, test_extensibility);
	run_test(setup, teardown, test_removal);
	run_test(setup, teardown, test_noop);
	run_test(setup, teardown, test_move);
	run_test(setup, teardown, test_modification);
	run_test(setup, teardown, test_single_node_ll);

	return EXIT_SUCCESS;
}
