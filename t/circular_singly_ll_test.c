#include "test_util.h"

#include "libcartilage.h"

/* Lifecycle */

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

/* Tests */

LinkedList* test_push_back(LinkedList* ll) {
	Node_t* n = push_back(ll, 'A');

	describe();

	do_assert(n->next == ll->head, "inserts a node as the head when the list is empty");
	do_assert(n->next->data == ll->head->data, "maintains rule such that tail->next == head");

	do_assert(ll->size == 1, "maintains proper list size");
	return ll;
}

/* Runner */

int main() {
	run_test(setup, teardown, test_push_back);
}


// test(`${subject} (pushBack) should insert a node as the head when the list is empty`, t => {
// 	const l = init();

// 	const n = l.pushBack(1);

// 	t.equals(n.next, l.head);
// 	t.equals(n, l.head.next);
// 	t.equals(l.size(), 1);
// 	t.end();
// });


// test(`${subject} (pushBack) should insert a node as the last node in a non-empty list`, t => {
// 	const l = init();

// 	l.pushBack(1);
// 	l.pushBack(2);
// 	l.pushBack(3);
// 	l.pushBack(4);
// 	const n = l.pushBack(5);

// 	t.equals(n.next, l.head);
// 	t.equals(l.size(), 5);
// 	t.end();
// });
