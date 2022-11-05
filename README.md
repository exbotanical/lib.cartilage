# lib.cartilage

classical implementations of list and ring data structures for the C programming language

# Install

Via [clib](https://github.com/clibs/clib/):

```bash
clib install exbotanical/lib.cartilage
```

From Source:
```bash
git clone https://github.com/exbotanical/lib.cartilage
cd lib.cartilage && make
```

## Dynamic Linking

Linking to `lib.cartilage`:

```bash
# 1) include and use lib.cartilage in your project
# 2) generate object file for your project
gcc -I ../path/to/libcartilage -c main.c -o main.o
# 3) generate shared object file
make
# 4) link your project to lib.cartilage
gcc -o main main.o -L../path/to/libcartilage -llibcartilage
# you may need to add the lib location to your PATH
```

Linking to `lib.cartilage` on Windows:

```bash
# 1) include and use lib.cartilage in your project
# 2) generate object file for your project
gcc -I ../path/to/libcartilage -c main.c -o main.o
# 3) generate shared object file
make win
# 3) link your project to lib.cartilage
gcc -o main.exe main.o -L /path/to/lib.cartilage -llib_cartilage.dll
# you may need to add the lib location to your PATH
```

## API and Documentation

- Circular Singly Linked List

- GlThread (aka 'Glue Linked List') - stores data at a memory offset

### CircularSinglyLinkedList

```c
/**
 * @brief Node type; atomic - points to next Node*
 */
typedef struct ForwardNode {
	void* data;
	struct ForwardNode* next;
	struct CircularSinglyLinkedList* list; /* A pointer to the list to which the node belongs */
} ForwardNode_t;
```

```c
/**
 * @brief CircularSinglyLinkedList type
 */
typedef struct CircularSinglyLinkedList {
	ForwardNode_t* head;
	uint32_t size;
} CircularSinglyLinkedList;
```

```c
/**
 * @brief Instantiate an empty circular singly linked list
 *
 * @return CircularSinglyLinkedList*
 */
CircularSinglyLinkedList* csll_make_list(void);

ForwardNode_t* __csll_make_node(void* value);
```

```c
/**
 * @brief Push a new node with value `value` to the back of the list
 *
 * @param ll
 * @param value
 * @return ForwardNode_t*
 */
ForwardNode_t* csll_push_back(CircularSinglyLinkedList* ll, void* value);
```

```c
/**
 * @brief Push a new node with value `value` to the front of the list
 *
 * @param ll
 * @param value
 * @return ForwardNode_t*
 */
ForwardNode_t* csll_push_front(CircularSinglyLinkedList* ll, void* value);

```c
/**
 * @brief Iterate over the list and invoke `callback` with each node
 *
 * @param ll
 * @param callback
 */
void csll_iterate(CircularSinglyLinkedList* ll, void (*callback)(void*));
```

```c
/**
 * @brief Returns the next list node, if extant; else, NULL
 *
 * @param ll
 * @param node
 * @return ForwardNode_t*
 */
ForwardNode_t* csll_next(CircularSinglyLinkedList* ll, ForwardNode_t* node);
```

```c
/**
 * @brief Returns the previous list node, if extant; else, NULL
 *
 * @param ll
 * @param node
 * @return ForwardNode_t*
 */
ForwardNode_t* csll_prev(CircularSinglyLinkedList* ll, ForwardNode_t* node);

```c
/**
 * @brief Remove a given node from the list
 *
 * @param ll
 * @param node
 * @return ForwardNode_t*
 */
ForwardNode_t* csll_remove_node(CircularSinglyLinkedList* ll, ForwardNode_t* node);
```

```c
/**
 * @brief Remove the last node from the list
 *
 * @param ll
 * @return ForwardNode_t*
 */
ForwardNode_t* csll_pop(CircularSinglyLinkedList* ll);

```c
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
ForwardNode_t* csll_insert_after(CircularSinglyLinkedList* ll, void* value, ForwardNode_t* mark);
```

```c
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
ForwardNode_t* csll_insert_before(CircularSinglyLinkedList* ll, void* value, ForwardNode_t* mark);
```

```c
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
int csll_move_before(CircularSinglyLinkedList* ll, ForwardNode_t* node, ForwardNode_t* mark);
```

```c
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
int csll_move_after(CircularSinglyLinkedList* ll, ForwardNode_t* node, ForwardNode_t* mark);
```

```c
/**
 * @brief Insert a copy of another list at the back of the caller list
 *
 * The lists may be the same, but must not be NULL
 *
 * @param ll
 * @param other
 * @return CircularSinglyLinkedList*
 */
CircularSinglyLinkedList* csll_push_back_list(CircularSinglyLinkedList* ll, CircularSinglyLinkedList* other);
```


```c
/**
 * @brief Insert a copy of another list at the front of the caller list
 *
 * The lists may be the same, but must not be NULL
 *
 * @param ll
 * @param other
 * @return CircularSinglyLinkedList*
 */
CircularSinglyLinkedList* csll_push_front_list(CircularSinglyLinkedList* ll, CircularSinglyLinkedList* other);
```

### GlThread

This data structure is a linked list that points to a memory offset (at which the node data resides) instead of an address; it is thereby leaner than a traditional linked list.

Other advantages include:

- accommodates being referenced by multiple data structures
- data objects' memory can be freed without the need to remove multiple pointer references

```c
/**
 * @brief glthread meta container
 */
typedef struct glthread {
	struct glthread* prev;
	struct glthread* next;
} glthread_t;
```

```c
/**
 * @brief Initialize a new glthread
 *
 * @param glthread
 */
void glthread_init(glthread_t* glthread);
```

```c
/**
 * @brief Insert a new glthread node after the given mark
 *
 * @param mark
 * @param next
 */
void glthread_insert_after(glthread_t* mark, glthread_t* next);
```

```c
/**
 * @brief Insert a new glthread node before the given mark
 *
 * @param mark
 * @param next
 */
void glthread_insert_before(glthread_t* mark, glthread_t* next);
```

```c
/**
 * @brief Remove a given glthread node
 *
 * @param mark
 */
void glthread_remove(glthread_t* mark);
```

```c
/**
 * @brief Push new glthread node to tail
 *
 * @param head
 * @param next
 */
void glthread_push(glthread_t* head, glthread_t* next);
```

```c
/**
 * @brief Delete all nodes in a given glthread
 *
 * @param head
 */
void glthread_del_list(glthread_t* head);
```

```c
/**
 * @brief Get current size of glthread
 *
 * @param head
 * @return unsigned int
 */
unsigned int glthread_size(glthread_t* head);
```

```c
/**
 * @brief Prioritized insertion
 *
 * @param head
 * @param glthread
 * @param comparator
 * @param offset
 */
void glthread_priority_insert(
	glthread_t* head,
	glthread_t* glthread,
	int(*comparator)(void*, void*),
	int offset
);
```

```c
/**
 * @brief Dequeue the head node
 *
 * @param head
 * @return glthread_t*
 */
glthread_t* glthread_dequeue_first(glthread_t* head);
```
