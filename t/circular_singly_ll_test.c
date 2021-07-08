#include "test_util.h"

#include "libcartilage.h"


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
	Node* n1 = push_front(ll, randch());
	Node* n3 = push_back(ll, randch());
	Node* n4 = push_back(ll, randch());

	// try_fail(ll, [ n1, n2, n3, n4 ]);

	// remove(ll, n2);
	// try_fail(l, [ n1, n3, n4 ]);

	// remove(ll, n2);
	// try_fail(l, [ n1, n3, n4 ]);

	// remove(ll, head());
	// try_fail(l, [ n3, n4 ]);circular

	// const t1 = pop(ll);

	// ASSERT(t1, n4);
	// try_fail(l, [n3]);

	// ASSERT(insert_after(ll, 2, t1), null); // no-op

	// ASSERT(l.head, l.prev(l.head)); // head = tail

	// n2 = insert_after(ll, 2, n3) // insert after tail
	// 		 try_fail(l, [ n3, n2 ]);
	// ASSERT(l.prev(l.head), n2);
	// ASSERT(l.head, n3);

	// n4 = insert_after(ll, 4, n2) // insert after tail
	// 		 try_fail(l, [ n3, n2, n4 ]);
	// ASSERT(n4.next, l.head);
	// ASSERT(l.prev(n3), n4);

	// let n5 = insert_after(ll, 5, n2); // insert after head
	// try_fail(l, [ n3, n2, n5, n4 ]);

	// remove(ll, n2);
	// n2 = insert_after(ll, 2, n5); // insert after middle
	// try_fail(l, [ n3, n5, n2, n4 ]);

	// remove(ll, n2);
	// n2 = insert_after(ll, 2, n4); // insert after tail
	// try_fail(l, [ n3, n5, n4, n2 ]);

	// remove(ll, n2);

	// pop(ll);

	// try_fail(l, [ n3, n5 ]);

	// ASSERT(pop(ll), n5);
	// ASSERT(pop(ll), n3);
	// ASSERT(pop(ll), null); // no-op
	// ASSERT(l.size(), 0);

	// ASSERT(l.insertBefore(11, n5), null); // no-op

	// let m2 = l.push_front(22);
	// let m3 = l.push_back(33);
	// let m1 = l.push_front(11);

	// try_fail(l, [ m1, m2, m3 ]);

	// t.end();
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
