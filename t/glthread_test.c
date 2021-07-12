#include "test_util.h"

#include "libcartilage.h"
#include <stdarg.h>

#define MAX_TEST_CYCLES 9
#define OFFSET(struct, member) (unsigned int)&(((struct*)0)->member)

/**
 * Environment
 */

typedef struct test_data {
	int x;
	int y;
	glthread_t glthread;
} test_t;

int comparator(test_t* meta_a, test_t* meta_b) {
	if (meta_a->x == meta_b->x) return 0;
	if (meta_a->x < meta_b->x) return 1;
	return -1;
}

/**
 * Lifecycle
 */

int run_test(glthread_t* (*setup)(void), void (*teardown)(glthread_t*), glthread_t* (*test)(glthread_t*)) {
	teardown(test(setup()));
}

glthread_t* setup(void) {
	glthread_t* t;

	glthread_init(t);

	return t;
}

void teardown(glthread_t* thread) {
	while (thread) {
		thread = thread->next;
		glthread_remove(thread);
	}
}

/**
 * Tests
 */

glthread_t* test_glthread(glthread_t* thread) {
	test_t td[MAX_TEST_CYCLES];

	for (int i = 0; i < MAX_TEST_CYCLES; i++) {
		td[i].x = i;
		td[i].y = i + 1;
	}

	glthread_t base;
	glthread_init(&base);

	// TODO

	return thread;
}

int main(void) {
	return 0;
}
