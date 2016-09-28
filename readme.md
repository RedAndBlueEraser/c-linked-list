# C Linked List

An implementation of generic linked lists in pure C.

## How to use?

### Setup

Place `linkedlist.h` and `linkedlist.c` next to your C program source files.

Add `#include "linkedlist.h"` to your program's `#include` directives.

You can now use generic linked lists in your C program.

### Compiling

Create the `linkedlist.o` object file by running:

```Shell
gcc -c linkedlist.c
```

Then compile and link your C program by running:

```Shell
gcc linkedlist.o yourprogram.c -o yourprogram
```

## Structs

`linkedlist.h` defines two structs as follows:

```C
typedef struct linkedlist_node_t {
    struct linkedlist_node_t *next;
    void *data;
} linkedlist_node_t;

typedef struct linkedlist_t {
    linkedlist_node_t *head;
    linkedlist_node_t *foot;
    size_t size;
} linkedlist_t;
```

A linked list is represented as a `linkedlist_t` object which contains a pointer to the first node of the list `head`, a pointer to the last node of the list `foot`, and the number of nodes in the list `size`.

The nodes in the list are represented as `linkedlist_node_t` objects which contain a pointer to the node next in the list `next`, and a generic pointer to your data item `data`.

You should **avoid directly accessing and changing the structs’ contents**, because you may create inconsistent list states if you don’t know what you are doing. Instead, use the provided functions to perform actions on the list.

All the provided functions accept a pointer to a linked list struct `linkedlist_t *`.

## Functions

### `linkedlist_create()`

```C
int linkedlist_create(linkedlist_t *list);
```

Use this function to initialise a new empty list in your C program. For example:

```C
int main() {
    linkedlist_t l, *list;
    list = &l;  /* Create a pointer to the linked list struct. */

    linkedlist_create(list);  /* Initialise a new empty list. */

    /* Do something with list. */

    linkedlist_destroy(list);  /* Empty the list. */

    return 0;
}
```

This function takes in one argument `list` which must be pointing to available memory space. This function always succeeds and returns 0.

### `linkedlist_destroy()`

```C
int linkedlist_destroy(linkedlist_t *list);
```

Use this function to empty a list. You can immediately use the empty list again. For example:

```C
int main() {
    linkedlist_t l, *list = &l;
    int i = 5;

    linkedlist_create(list);  /* Initialise a new empty list. */

    linkedlist_push(list, &i);  /* Add something to the list. */

    linkedlist_destroy(list);  /* Empty the list. */

    return 0;
}
```

This function would free memory allocated to the list nodes **but does not free memory allocated to the data item**. This function always succeeds and returns 0.

### `linkedlist_clone()`

```C
int linkedlist_clone(linkedlist_t *src, linkedlist_t *dest);
```

Use this function to make a copy of a list. For example:

```C
int main() {
    linkedlist_t l1, l2, *list1 = &l1, *list2 = &l2;
    int i = 5, j = 10;

    linkedlist_create(list1);  /* Initialise new empty lists. */
    linkedlist_create(list2);

    linkedlist_push(list1, &i);

    linkedlist_clone(list1, list2);  /* Copies the contents of list1 to list2. */

    linkedlist_push(list2, &j);  /* List 2 is now [i = 5, j = 10]. */

    linkedlist_destroy(list1);  /* Empty the lists. */
    linkedlist_destroy(list2);

    return 0;
}
```

This function takes in two arguments `src` and `dest`. It makes a shallow copy of `src` to `dest`. The lists act independently **but points to the same data item**. This function returns 0 on success.

### `linkedlist_size()`

```C
size_t linkedlist_size(linkedlist_t *list);
```

Use this function to get the number of data items in the list. For example:

```C
int main() {
    linkedlist_t l, *list = &l;
    int i = 5, j = 10;

    linkedlist_create(list);  /* Initialise a new empty list. */
    linkedlist_push(list, &i);
    linkedlist_push(list, &j);

    printf("List has %d items", linkedlist_size(list));  /* Prints "List has 2 items" */

    linkedlist_destroy(list);  /* Empty the list. */

    return 0;
}
```

### `linkedlist_isempty()`

```C
int linkedlist_isempty(linkedlist_t *list);
```

Use this function to check whether the list is empty. Returns 1 if true or 0 if false. For example:

```C
int main() {
    linkedlist_t l, *list = &l;
    int i = 5;

    linkedlist_create(list);  /* Initialise a new empty list. */

    /* Prints "List is empty". */
    if (linkedlist_isempty(list))
        printf("List is empty");
    else
        printf("List is not empty");

    linkedlist_push(list, &i);

    /* Prints "List is not empty". */
    if (linkedlist_isempty(list))
        printf("List is empty");
    else
        printf("List is not empty");

    linkedlist_destroy(list);  /* Empty the list. */

    /* Prints "List is empty". */
    if (linkedlist_isempty(list))
        printf("List is empty");
    else
        printf("List is not empty");

    return 0;
}
```

### `linkedlist_push()`

```C
int linkedlist_push(linkedlist_t *list, void *data);
```

Use this function to add a data item to the end of the list. For example:

```C
int main() {
    linkedlist_t l, *list = &l;
    int i = 5, j = 10;

    linkedlist_create(list);  /* Initialise a new empty list. */
    linkedlist_push(list, &i);  /* List is now [5]. */
    linkedlist_push(list, &j);  /* List is now [5, 10]. */

    linkedlist_destroy(list);  /* Empty the list. */

    return 0;
}
```

This function takes in two arguments `list` and `data`. `data` should be a pointer to your data item. **Be careful of using a pointer to a local variable.** This function returns 0 on success.

### `linkedlist_pop()`

```C
void *linkedlist_pop(linkedlist_t *list);
```

Use this function to remove the data item from the end of the list. Returns the removed data item or `NULL` if the list is empty.

### `linkedlist_unshift()`

```C
int linkedlist_unshift(linkedlist_t *list, void *data);
```

Use this function to add a data item to the start of the list.

This function takes in two arguments `list` and `data`. `data` should be a pointer to your data item. **Be careful of using a pointer to a local variable.** This function returns 0 on success.

### `linkedlist_shift()`

```C
void *linkedlist_shift(linkedlist_t *list);
```

Use this function to remove the data item from the start of the list. Returns the removed data item or `NULL` if the list is empty.

### `linkedlist_add()`

```C
int linkedlist_add(linkedlist_t *list, size_t index, void *data);
```

Use this function to add a data item at the specified position in the list.

This function takes in three arguments `list`, `index` and `data`. `data` should be a pointer to your data item. **Be careful of using a pointer to a local variable.** This function returns 0 on success.

### `linkedlist_remove()`

```C
void *linkedlist_remove(linkedlist_t *list, size_t index);
```

Use this function to remove the data item from the specified position of the list. Returns the removed data item or `NULL` if the list is empty.

### `linkedlist_set()`

```C
int linkedlist_set(linkedlist_t *list, size_t index, void *data);
```

Use this function to replace a data item in the specified position of the list.

This function takes in three arguments `list`, `index` and `data`. `data` should be a pointer to your data item. **Be careful of using a pointer to a local variable.** This function returns 0 on success.

### `linkedlist_addarray()`

```C
int linkedlist_addarray(linkedlist_t *dest, void *src[]);
```

Use this function to add data items from an array to the end of the list.

This function takes in two arguments `dest` and `src`. `src` should be a null-terminated array of pointers to data items. **Be careful of using pointers to local variables.** This function returns 0 on success.

### `linkedlist_removearray()`

```C
int linkedlist_removearray(linkedlist_t *dest, void *src[]);
```

Use this function to remove data items in an array from the list.

This function takes in two arguments `dest` and `src`. `src` should be a null-terminated array of pointers to data items. This function returns 0 on success.

### `linkedlist_addlinkedlist()`

```C
int linkedlist_addlinkedlist(linkedlist_t *dest, linkedlist_t *src);
```

Use this function to add data items from a list to the end of another list.

**Be careful of using pointers to local variables.** This function returns 0 on success.

### `linkedlist_removelinkedlist()`

```C
int linkedlist_removelinkedlist(linkedlist_t *dest, linkedlist_t *src);
```

Use this function to remove data items in a list from another list.

This function returns 0 on success.

### `linkedlist_get()`

```C
void *linkedlist_get(linkedlist_t *list, size_t index);
```

Use this function to retrieve the data item in the specified position of the list. Returns the retrieved data item or `NULL` if error.

### `linkedlist_first()`

```C
void *linkedlist_first(linkedlist_t *list);
```

Use this function to retrieve the first data item in the list. Returns the retrieved data item or `NULL` if error.

### `linkedlist_last()`

```C
void *linkedlist_last(linkedlist_t *list);
```

Use this function to retrieve the last data item in the list. Returns the retrieved data item or `NULL` if error.

### `linkedlist_indexof()`

```C
size_t linkedlist_indexof(linkedlist_t *list, void *data);
```

Use this function to get the position of the specified data item in the list. Returns the index of the data item or the size of the list if the data item is not found.

**The data item is matched by comparing the pointer to the data item.**

### `linkedlist_find()`

```C
void *linkedlist_find(linkedlist_t *list, int (*f)(void *));
```

Use this function to retrieve the first data item in the list that passes a specified test. Returns the retrieved data item or `NULL` if data item is not found.

This function takes in two arguments `list` and `f`. `f` should be a function that takes in a pointer to the data item as an argument, and returns `1` if the data item passes the test or `0` if the data item fails the test.

### `linkedlist_findindex()`

```C
size_t linkedlist_findindex(linkedlist_t *list, int (*f)(void *));
```

Use this function to get the position of the first data item in the list that passes a specified test. Returns the index of the data item or the size of the list if the data item is not found.

This function takes in two arguments `list` and `f`. `f` should be a function that takes in a pointer to the data item as an argument, and returns `1` if the data item passes the test or `0` if the data item fails the test.

### `linkedlist_foreach()`

```C
int linkedlist_foreach(linkedlist_t *list, void (*f)(void *));
```

Use this function to iterate over every data item in the list and execute a function on each data item.

This function takes in two arguments `list` and `f`. `f` should be a function that takes in a pointer to the data item as an argument. **Do not use this function to change the list**, such as adding or removing data items. This function returns 0 on success.

### `linkedlist_slice()`

```C
int linkedlist_slice(linkedlist_t *list, size_t start, size_t end);
```

Use this function to slice the list.

This function takes in three arguments `list`, `start` and `end`. `start` refers to the position of the first data item to include in the sliced list. `end` refers to the position of the data item to stop being included the sliced list. That is, the data item in the `start` position is included and the data item in the `end` position is excluded. This function always succeeds and returns 0.

### `linkedlist_toarray()`

```C
int linkedlist_toarray(linkedlist_t *src, void *dest[]);
```

Use this function to get the null-terminated array representation of the list. The data items in the array would be ordered the same as the list.

This function takes in two arguments `list` and `dest`. `dest` should be a pointer to an array large enough to hold the number of data items in the list plus one pointers to data items. That is, the array should be at least `(list->size + 1) * sizeof void *` big. This function always succeeds and returns 0.

### `linkedlist_reverse()`

```C
int linkedlist_reverse(linkedlist_t *list);
```

Use this function to reverse the order of data items in the list.

This function returns 0 on success.

### `linkedlist_sort()`

```C
int linkedlist_sort(linkedlist_t *list, int (*f)(const void *, const void *));
```

Use this function to sort the order of data items in the list with a comparison function.

This function takes in two arguments `list` and `f`. `f` should be a function that takes in two pointers to data items as arguments, and returns a value greater than 0 if the first data item comes after the second data item, a value less than 0 if the first data item comes before the second data item, or `0` if the two data items are equal. This function uses qsort from the C standard library, meaning **it is not guaranteed to be a stable sort**. This function returns 0 on success.

## Warnings

- Be careful of using pointers to local variables. If a list is used inside a function to store pointers to local variables as its data items and the function returns, the list would now be storing invalid pointers. This is how the variable scope and stack works in C. Instead, if you need to return data items from a function in the list, use heap variables created by malloc or calloc or use global variables.
- Remember to call `linkedlist_destroy` after you have finished using a list to avoid memory leaks.
- linkedlist_destroy does not free memory allocated to data items. You would have to free them first before calling `linkedlist_destroy`.
- The provided sample program `main.c` stores integers rather than pointers by converting integers to pointers. This is not the correct usage! It is only used to test the linked list implementation. If you want to store integers, store it as pointers to integers.
- `linkedlist_find`, `linkedlist_findindex`, `linkedlist_foreach` and `linkedlist_sort` all take a function as an argument which does not accept any useful custom arguments. You might want to use global variables, or if you want, you can copy and change these implementations similarly to changing `qsort` to `qsort_r`.

## Authors

Harry Wong (RedAndBlueEraser) <RedAndBlueEraser@outlook.com>
