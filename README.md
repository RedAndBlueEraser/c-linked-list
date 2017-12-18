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

- `linkedlist_t *list` - A pointer to a linked list struct to be initialised. Cannot be `NULL`.

Initialise a new empty list in your C program. This function always succeeds and returns `0`. For example:

```C
int main() {
    linkedlist_t l, *list;
    list = &l;                 /* Create a pointer to the linked list struct. */
    linkedlist_create(list);   /* Initialise a new empty list. */

    /* Do something with list. */

    linkedlist_destroy(list);  /* Empty the list. */
    return 0;
}
```

### `linkedlist_destroy()`

```C
int linkedlist_destroy(linkedlist_t *list);
```

- `linkedlist_t *list` - A pointer to a linked list struct to be emptied. Cannot be `NULL` and must be valid (had been initialised).

Empty a used list. It frees memory allocated to its nodes **but does not free memory allocated to its data items**. You can immediately use the empty list again. This function always succeeds and returns `0`. For example:

```C
int main() {
    linkedlist_t l, *list = &l;
    int i = 5;
    linkedlist_create(list);    /* Initialise a new empty list. */
    linkedlist_push(list, &i);  /* Add something to the list. */
    linkedlist_destroy(list);   /* Empty the list. */
    return 0;
}
```

### `linkedlist_clone()`

```C
int linkedlist_clone(linkedlist_t *src, linkedlist_t *dest);
```

- `linkedlist_t *src` - A pointer to a linked list struct to be copied **from**. Cannot be `NULL` and must be valid (had been initialised).
- `linkedlist_t *dest` - A pointer to a linked list struct to be copied **to**. Cannot be `NULL` and should be empty (or had not been initialised).

Makes a **shallow copy** of a list. It does not empty the destination list and therefore **does not free memory allocated to the destination list's nodes. If the destination list is not empty, use `linkedlist_destroy()` before using this function.** This function returns `0` on success. For example:

```C
int main() {
    linkedlist_t l1, l2, *list1 = &l1, *list2 = &l2;
    int i = 5, j = 10;
    linkedlist_create(list1);        /* Initialise a new empty list. */
    linkedlist_push(list1, &i);      /* Add something to list 1. */
    linkedlist_clone(list1, list2);  /* Copies the contents of list 1 to list 2. */
    linkedlist_push(list2, &j);      /* List 2 is now [i = 5, j = 10]. */
    linkedlist_destroy(list1);       /* Empty the lists. */
    linkedlist_destroy(list2);
    return 0;
}
```

### `linkedlist_size()`

```C
size_t linkedlist_size(linkedlist_t *list);
```

- `linkedlist_t *list` - A pointer to a linked list struct to get the count of data items. Cannot be `NULL` and must be valid (had been initialised).

Get the count of data items in the list. Returns the count of data items. For example:

```C
int main() {
    linkedlist_t l, *list = &l;
    int i = 5, j = 10;
    linkedlist_create(list);                             /* Initialise a new empty list. */
    linkedlist_push(list, &i);                           /* Add something to the list. */
    linkedlist_push(list, &j);
    printf("List has %d items", linkedlist_size(list));  /* Prints "List has 2 items" */
    linkedlist_destroy(list);                            /* Empty the list. */
    return 0;
}
```

### `linkedlist_isempty()`

```C
int linkedlist_isempty(linkedlist_t *list);
```

- `linkedlist_t *list` - A pointer to a linked list struct to check if empty. Cannot be `NULL` and must be valid (had been initialised).

Check whether the list is empty. Returns `1` if the list is empty or `0` if the list is not empty. For example:

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

- `linkedlist_t *list` - A pointer to a linked list struct to add with a data item. Cannot be `NULL` and must be valid (had been initialised).
- `void *data` - A pointer to a data item to be added. **Be careful of using a pointer to a stack variable**.

Add a data item to the end of the list. This function returns `0` on success. For example:

```C
int main() {
    linkedlist_t l, *list = &l;
    int i = 5, j = 10;
    linkedlist_create(list);    /* Initialise a new empty list. */
    linkedlist_push(list, &i);  /* List is now [5]. */
    linkedlist_push(list, &j);  /* List is now [5, 10]. */
    linkedlist_destroy(list);   /* Empty the list. */
    return 0;
}
```

### `linkedlist_pop()`

```C
void *linkedlist_pop(linkedlist_t *list);
```

- `linkedlist_t *list` - A pointer to a linked list struct to remove a data item from. Cannot be `NULL` and must be valid (had been initialised).

Remove a data item from the end of the list. Returns the removed data item or `NULL` if the list is empty. For example:

```C
int main() {
    linkedlist_t l, *list = &l;
    int i = 5, j = 10;
    linkedlist_create(list);    /* Initialise a new empty list. */
    linkedlist_push(list, &i);  /* List is now [5]. */
    linkedlist_push(list, &j);  /* List is now [5, 10]. */

    /* Prints "Removed last item '10' from list". */
    printf("Removed last item '%d' from list", *(int *)linkedlist_pop(list));
    /* List is now [5]. */

    linkedlist_destroy(list);   /* Empty the list. */
    return 0;
}
```

### `linkedlist_unshift()`

```C
int linkedlist_unshift(linkedlist_t *list, void *data);
```

- `linkedlist_t *list` - A pointer to a linked list struct to add with a data item. Cannot be `NULL` and must be valid (had been initialised).
- `void *data` - A pointer to a data item to be added. **Be careful of using a pointer to a stack variable**.

Add a data item to the start of the list. This function returns `0` on success. For example:

```C
int main() {
    linkedlist_t l, *list = &l;
    int i = 5, j = 10;
    linkedlist_create(list);       /* Initialise a new empty list. */
    linkedlist_unshift(list, &i);  /* List is now [5]. */
    linkedlist_unshift(list, &j);  /* List is now [10, 5]. */
    linkedlist_destroy(list);      /* Empty the list. */
    return 0;
}
```

### `linkedlist_shift()`

```C
void *linkedlist_shift(linkedlist_t *list);
```

- `linkedlist_t *list` - A pointer to a linked list struct to remove a data item from. Cannot be `NULL` and must be valid (had been initialised).

Remove a data item from the start of the list. Returns the removed data item or `NULL` if the list is empty. For example:

```C
int main() {
    linkedlist_t l, *list = &l;
    int i = 5, j = 10;
    linkedlist_create(list);       /* Initialise a new empty list. */
    linkedlist_unshift(list, &i);  /* List is now [5]. */
    linkedlist_unshift(list, &j);  /* List is now [10, 5]. */

    /* Prints "Removed first item '10' from list". */
    printf("Removed first item '%d' from list", *(int *)linkedlist_shift(list));
    /* List is now [5]. */

    linkedlist_destroy(list);      /* Empty the list. */
    return 0;
}
```

### `linkedlist_add()`

```C
int linkedlist_add(linkedlist_t *list, size_t index, void *data);
```

- `linkedlist_t *list` - A pointer to a linked list struct to add with a data item. Cannot be `NULL` and must be valid (had been initialised).
- `size_t index` - The position of the list to add a data item. Must be an integer between 0 and the list size, inclusive.
- `void *data` - A pointer to a data item to be added. **Be careful of using a pointer to a stack variable**.

Add a data item at the specified position of the list. This function returns `0` on success. For example:

```C
int main() {
    linkedlist_t l, *list = &l;
    int a = 10, b = 12, c = 11, d = 13;
    linkedlist_create(list);      /* Initialise a new empty list. */
    linkedlist_add(list, 0, &a);  /* List is now [10]. */
    linkedlist_add(list, 1, &b);  /* List is now [10, 12]. */
    linkedlist_add(list, 1, &c);  /* List is now [10, 11, 12]. */
    linkedlist_add(list, 3, &d);  /* List is now [10, 11, 12, 13]. */
    linkedlist_destroy(list);     /* Empty the list. */
    return 0;
}
```

### `linkedlist_remove()`

```C
void *linkedlist_remove(linkedlist_t *list, size_t index);
```

- `linkedlist_t *list` - A pointer to a linked list struct to remove a data item from. Cannot be `NULL` and must be valid (had been initialised).
- `size_t index` - The position of the list to remove a data item. Must be an integer from 0 (included) up to list size (excluded).

Remove a data item at the specified location of the list. Returns the removed data item or `NULL` if the list is empty. For example:

```C
int main() {
    linkedlist_t l, *list = &l;
    int a = 10, b = 11, c = 12, d = 13;
    linkedlist_create(list);       /* Initialise a new empty list. */
    linkedlist_add(list, 0, &d);  /* List is now [13]. */
    linkedlist_add(list, 0, &c);  /* List is now [12, 13]. */
    linkedlist_add(list, 0, &b);  /* List is now [11, 12, 13]. */
    linkedlist_add(list, 0, &a);  /* List is now [10, 11, 12, 13]. */

    /* Prints "list[2] = 12 removed". */
    printf("list[2] = %d removed", *(int *)linkedlist_remove(list, 2));
    /* List is now [10, 11, 13]. */

    /* Prints "list[0] = 10 removed". */
    printf("list[0] = %d removed", *(int *)linkedlist_remove(list, 0));
    /* List is now [11, 13]. */

    /* Prints "list[1] = 13 removed". */
    printf("list[1] = %d removed", *(int *)linkedlist_remove(list, 1));
    /* List is now [13]. */

    linkedlist_destroy(list);      /* Empty the list. */
    return 0;
}
```

### `linkedlist_set()`

```C
int linkedlist_set(linkedlist_t *list, size_t index, void *data);
```

- `linkedlist_t *list` - A pointer to a linked list struct to change a data item in. Cannot be `NULL` and must be valid (had been initialised).
- `size_t index` - The position of the list to change a data item. Must be an integer from 0 (included) up to list size (excluded).
- `void *data` - A pointer to a data item to be changed with. **Be careful of using a pointer to a stack variable**.

Change a data item at the specified position of the list. This function returns `0` on success. For example:

```C
int main() {
    linkedlist_t l, *list = &l;
    int i = 5, j = 10, ii = 25, jj = 30;
    linkedlist_create(list);       /* Initialise a new empty list. */
    linkedlist_push(list, &i);     /* List is now [5]. */
    linkedlist_push(list, &j);     /* List is now [5, 10]. */
    linkedlist_set(list, 0, &ii);  /* List is now [25, 10]. */
    linkedlist_set(list, 1, &jj);  /* List is now [25, 30]. */
    linkedlist_destroy(list);      /* Empty the list. */
    return 0;
}
```

### `linkedlist_addarray()`

```C
int linkedlist_addarray(linkedlist_t *dest, void *src[]);
```

- `linkedlist_t *dest` - A pointer to a linked list struct to add with data items. Cannot be `NULL` and must be valid (had been initialised).
- `void *src[]` - A null-terminated array of pointers to data items to be added. **Be careful of using pointers to stack variables**.

Add data items from an array to the end of the list. This function returns `0` on success. For example:

```C
int main() {
    linkedlist_t l, *list = &l;
    int a = 10, b = 11, c = 12, d = 13;
    int *array[] = { &a, &b, &c, &d, NULL };
    linkedlist_create(list);           /* Initialise a new empty list. */
    linkedlist_addarray(list, array);  /* List is now [10, 11, 12, 13]. */
    linkedlist_destroy(list);          /* Empty the list. */
    return 0;
}
```

### `linkedlist_removearray()`

```C
int linkedlist_removearray(linkedlist_t *dest, void *src[]);
```

- `linkedlist_t *dest` - A pointer to a linked list struct to remove data items from. Cannot be `NULL` and must be valid (had been initialised).
- `void *src[]` - A null-terminated array of pointers to data items to be removed.

Remove data items in an array from the list. This function returns `0` on success. For example:

```C
int main() {
    linkedlist_t l, *list = &l;
    int a = 0, b = 1, c = 2, d = 3, e = 4, f = 5, g = 6, h = 7;
    int *array1[] = { &a, &b, &c, &d, &e, &f, &g, NULL },
        *array2[] = { &b, &d, &f, &h, NULL };
    linkedlist_create(list);               /* Initialise a new empty list. */
    linkedlist_addarray(list, array1);     /* List is now [0, 1, 2, 3, 4, 5, 6]. */
    linkedlist_removearray(list, array2);  /* List is now [0, 2, 4, 6]. */
    linkedlist_destroy(list);              /* Empty the list. */
    return 0;
}
```

### `linkedlist_addlinkedlist()`

```C
int linkedlist_addlinkedlist(linkedlist_t *dest, linkedlist_t *src);
```

- `linkedlist_t *dest` - A pointer to a linked list struct to add with data items. Cannot be `NULL` and must be valid (had been initialised).
- `linkedlist_t *src` - A pointer to a linked list struct with data items to be added. **Be careful of using pointers to stack variables**.

Add data items from a list to the end of another list. This function returns `0` on success. For example:

```C
int main() {
    linkedlist_t l1, l2, *list1 = &l1, *list2 = &l2;
    int a = 10, b = 11, c = 12, d = 13;
    linkedlist_create(list1);                /* Initialise new empty lists. */
    linkedlist_create(list2);
    linkedlist_push(list1, &a);              /* List 1 is now [10]. */
    linkedlist_push(list1, &b);              /* List 1 is now [10, 11]. */
    linkedlist_push(list2, &c);              /* List 2 is now [12]. */
    linkedlist_push(list2, &d);              /* List 2 is now [12, 13]. */
    linkedlist_addlinkedlist(list1, list2);  /* List 1 is now [10, 11, 12, 13]. */
    linkedlist_destroy(list1);               /* Empty the lists. */
    linkedlist_destroy(list2);
    return 0;
}
```

### `linkedlist_removelinkedlist()`

```C
int linkedlist_removelinkedlist(linkedlist_t *dest, linkedlist_t *src);
```

- `linkedlist_t *dest` - A pointer to a linked list struct to remove data items from. Cannot be `NULL` and must be valid (had been initialised).
- `linkedlist_t *src` - A pointer to a linked list struct with data items to be removed.

Remove data items in a list from another list. This function returns `0` on success. For example:

```C
int main() {
    linkedlist_t l1, l2, *list1 = &l1, *list2 = &l2;
    int a = 0, b = 1, c = 2, d = 3, e = 4, f = 5, g = 6, h = 7;
    int *array1[] = { &a, &b, &c, &d, &e, &f, &g, NULL },
        *array2[] = { &b, &d, &f, &h, NULL };
    linkedlist_create(list1);                   /* Initialise new empty lists. */
    linkedlist_create(list2);
    linkedlist_addarray(list1, array1);         /* List 1 is now [0, 1, 2, 3, 4, 5, 6]. */
    linkedlist_addarray(list2, array2);         /* List 2 is now [0, 1, 2, 3, 4, 5, 6]. */
    linkedlist_removelinkedlist(list1, list2);  /* List 1 is now [0, 2, 4, 6]. */
    linkedlist_destroy(list1);                  /* Empty the lists. */
    linkedlist_destroy(list2);
    return 0;
}
```

### `linkedlist_get()`

```C
void *linkedlist_get(linkedlist_t *list, size_t index);
```

- `linkedlist_t *list` - A pointer to a linked list struct to get a data item from. Cannot be `NULL` and must be valid (had been initialised).
- `size_t index` - The position of the list to get a data item. Must be an integer from 0 (included) up to list size (excluded).

Get a data item at the specified position of the list. Returns the retrieved data item or `NULL` if the list is empty. For example:

```C
int main() {
    linkedlist_t l, *list = &l;
    int a = 10, b = 11, c = 12, d = 13;
    int *array[] = { &a, &b, &c, &d, NULL };
    linkedlist_create(list);           /* Initialise a new empty list. */
    linkedlist_addarray(list, array);  /* List is now [10, 11, 12, 13]. */

    /* Prints "list[0] = 10". */
    printf("list[0] = %d", *(int *)linkedlist_get(list, 0));

    /* Prints "list[1] = 12". */
    printf("list[1] = %d", *(int *)linkedlist_get(list, 1));

    /* Prints "list[3] = 13". */
    printf("list[3] = %d", *(int *)linkedlist_get(list, 3));

    linkedlist_destroy(list);          /* Empty the list. */
    return 0;
}
```

### `linkedlist_first()`

```C
void *linkedlist_first(linkedlist_t *list);
```

- `linkedlist_t *list` - A pointer to a linked list struct to get the data item from. Cannot be `NULL` and must be valid (had been initialised).

Get the first data item in the list. Returns the retrieved data item or `NULL` if the list is empty. For example:

```C
int main() {
    linkedlist_t l, *list = &l;
    int i = 5, j = 10;
    linkedlist_create(list);    /* Initialise a new empty list. */
    linkedlist_push(list, &i);  /* List is now [5]. */
    linkedlist_push(list, &j);  /* List is now [5, 10]. */

    /* Prints "First item in list is '5'". */
    printf("First item in list is '%d'", *(int *)linkedlist_first(list));

    linkedlist_destroy(list);   /* Empty the list. */
    return 0;
}
```

### `linkedlist_last()`

```C
void *linkedlist_last(linkedlist_t *list);
```

- `linkedlist_t *list` - A pointer to a linked list struct to get the data item from. Cannot be `NULL` and must be valid (had been initialised).

Get the last data item in the list. Returns the retrieved data item or `NULL` if the list is empty. For example:

```C
int main() {
    linkedlist_t l, *list = &l;
    int i = 5, j = 10;
    linkedlist_create(list);    /* Initialise a new empty list. */
    linkedlist_push(list, &i);  /* List is now [5]. */
    linkedlist_push(list, &j);  /* List is now [5, 10]. */

    /* Prints "Last item in list is '10'". */
    printf("Last item in list is '%d'", *(int *)linkedlist_last(list));

    linkedlist_destroy(list);   /* Empty the list. */
    return 0;
}
```

### `linkedlist_indexof()`

```C
size_t linkedlist_indexof(linkedlist_t *list, void *data);
```

- `linkedlist_t *list` - A pointer to a linked list struct to get the position of a data item from. Cannot be `NULL` and must be valid (had been initialised).
- `void *data` - A pointer to a data item to get the position of.

Get the position of the first occurrence of a data item in the list. **The data item is matched by comparing the pointer to the data item**. Returns the index of the data item or the size of the list if the data item is not found. For example:

```C
int main() {
    linkedlist_t l, *list = &l;
    int a = 10, b = 11, c = 12, d = 13;
    int *array[] = { &a, &b, &c, &d, NULL };
    linkedlist_create(list);           /* Initialise a new empty list. */
    linkedlist_addarray(list, array);  /* List is now [10, 11, 12, 13]. */

    /* Prints "Index of '10' in list is 0". */
    printf("Index of '10' in list is %zd", linkedlist_indexof(list, &a));

    /* Prints "Index of '11' in list is 1". */
    printf("Index of '11' in list is %zd", linkedlist_indexof(list, &b));

    /* Prints "Index of '13' in list is 3". */
    printf("Index of '13' in list is %zd", linkedlist_indexof(list, &d));

    linkedlist_destroy(list);          /* Empty the list. */
    return 0;
}
```

### `linkedlist_find()`

```C
void *linkedlist_find(linkedlist_t *list, int (*f)(void *));
```

- `linkedlist_t *list` - A pointer to a linked list struct to get a data item from. Cannot be `NULL` and must be valid (had been initialised).
- `int (*f)(void *)` - A function that takes in a pointer to a data item as an argument, and tests data items, and returns `1` if the data item passes the test or `0` if the data item fails the test.

Get the first data item in the list that passes a test. Returns the retrieved data item or `NULL` if data item is not found. For example:

```C
/* Test to find whether integer is completely divisible by 6. */
int test(void *data) {
    return *(int *)data % 6 == 0;
}

int main() {
    linkedlist_t l, *list = &l;
    int a = 10, b = 11, c = 12, d = 13;
    int *array[] = { &a, &b, &c, &d, NULL };
    linkedlist_create(list);           /* Initialise a new empty list. */
    linkedlist_addarray(list, array);  /* List is now [10, 11, 12, 13]. */

    /* Prints "'12' in list is divisible by 6". */
    printf("'%d' in list is divisible by 6", *(int *)linkedlist_find(list, test));

    linkedlist_destroy(list);          /* Empty the list. */
    return 0;
}
```

### `linkedlist_findindex()`

```C
size_t linkedlist_findindex(linkedlist_t *list, int (*f)(void *));
```

- `linkedlist_t *list` - A pointer to a linked list struct to get the position of a data item from. Cannot be `NULL` and must be valid (had been initialised).
- `int (*f)(void *)` - A function that takes in a pointer to a data item as an argument, and tests data items, and returns `1` if the data item passes the test or `0` if the data item fails the test.

Get the position of the first data item in the list that passes a test. Returns the index of the data item or the size of the list if the data item is not found. For example:

```C
/* Test to find whether integer is completely divisible by 6. */
int test(void *data) {
    return *(int *)data % 6 == 0;
}

int main() {
    linkedlist_t l, *list = &l;
    int a = 10, b = 11, c = 12, d = 13;
    int *array[] = { &a, &b, &c, &d, NULL };
    linkedlist_create(list);           /* Initialise a new empty list. */
    linkedlist_addarray(list, array);  /* List is now [10, 11, 12, 13]. */

    /* Prints "list[2] is divisible by 6". */
    printf("list[%zd] is divisible by 6", linkedlist_findindex(list, test));

    linkedlist_destroy(list);          /* Empty the list. */
    return 0;
}
```

### `linkedlist_foreach()`

```C
int linkedlist_foreach(linkedlist_t *list, void (*f)(void *));
```

- `linkedlist_t *list` - A pointer to a linked list struct to iterate through each data item. Cannot be `NULL` and must be valid (had been initialised).
- `void (*f)(void *)` - A function that takes in a pointer to a data item as an argument, and performs an action on the data.

Iterate over every data item in the list and perform an action each data item. **Do not use this function to change the list**, such as adding or removing data items. This function returns `0` on success. For example:

```C
/* Test to find whether integer is completely divisible by 6. */
void add6(void *data) {
    *(int *)data += 6;
}

int main() {
    linkedlist_t l, *list = &l;
    int a = 10, b = 11, c = 12, d = 13;
    int *array[] = { &a, &b, &c, &d, NULL };
    linkedlist_create(list);           /* Initialise a new empty list. */
    linkedlist_addarray(list, array);  /* List is now [10, 11, 12, 13]. */
    linkedlist_foreach(list, add6);    /* List is now [16, 17, 18, 19]. */
    linkedlist_destroy(list);          /* Empty the list. */
    return 0;
}
```

### `linkedlist_slice()`

```C
int linkedlist_slice(linkedlist_t *list, size_t start, size_t end);
```

- `linkedlist_t *list` - A pointer to a linked list struct to iterate through each data item. Cannot be `NULL` and must be valid (had been initialised).
- `size_t start` - The position of the first data item to include in the sliced list.
- `size_t end` - The position of the data item to exclude onwards in the sliced list.

Slice a list. The data item in the `start` position of the list is included in the slice and the data item in the `end` position of the list is excluded from the slice. This function always succeeds and returns `0`. For example:

```C
int main() {
    linkedlist_t l, *list = &l;
    int a = 10, b = 11, c = 12, d = 13;
    int *array[] = { &a, &b, &c, &d, NULL };
    linkedlist_create(list);           /* Initialise a new empty list. */
    linkedlist_addarray(list, array);  /* List is now [10, 11, 12, 13]. */
    linkedlist_slice(list, 1, 3);      /* List is now [11, 12]. */
    linkedlist_destroy(list);          /* Empty the list. */
    return 0;
}
```

### `linkedlist_toarray()`

```C
int linkedlist_toarray(linkedlist_t *src, void *dest[]);
```

- `linkedlist_t *src` - A pointer to a linked list struct to be represented as an array. Cannot be `NULL` and must be valid (had been initialised).
- `void *dest[]` - An array of pointers to data items large enough to hold the count of data items in the list plus one pointers to data items.

Get the null-terminated array representation of the list. This function always succeeds and returns `0`. For example:

```C
int main() {
    linkedlist_t l, *list = &l;
    int a = 10, b = 11, c = 12, d = 13;
    int *array[10];
    linkedlist_create(list);           /* Initialise a new empty list. */
    linkedlist_push(list, &a);
    linkedlist_push(list, &b);
    linkedlist_push(list, &c);
    linkedlist_push(list, &d);         /* List is now [a, b, c, d]. */
    linkedlist_toarray(list, array);   /* Get the array [a, b, c, d]. */
    linkedlist_destroy(list);          /* Empty the list. */
    return 0;
}
```

### `linkedlist_reverse()`

```C
int linkedlist_reverse(linkedlist_t *list);
```

- `linkedlist_t *src` - A pointer to a linked list struct to be reversed. Cannot be `NULL` and must be valid (had been initialised).

Reverse the order of data items in the list. This function returns `0` on success. For example:

```C
int main() {
    linkedlist_t l, *list = &l;
    int a = 10, b = 11, c = 12, d = 13;
    int *array[] = { &a, &b, &c, &d, NULL };
    linkedlist_create(list);           /* Initialise a new empty list. */
    linkedlist_addarray(list, array);  /* List is now [10, 11, 12, 13]. */
    linkedlist_reverse(list);          /* List is now [13, 12, 11, 10]. */
    linkedlist_destroy(list);          /* Empty the list. */
    return 0;
}
```

### `linkedlist_sort()`

```C
int linkedlist_sort(linkedlist_t *list, int (*f)(const void *, const void *));
```

- `linkedlist_t *src` - A pointer to a linked list struct to be sorted. Cannot be `NULL` and must be valid (had been initialised).
- `int (*f)(const void *, const void *)` - A function that takes in two pointers to data items as arguments, and compares the data items, and returns a value greater than 0 if the first data item comes after the second data item, a value less than 0 if the first data item comes before the second data item or `0` if the two data items are equal.

Sort the order of data items in the list with a comparison function. This function uses qsort from the C standard library, meaning **it is not guaranteed to be a stable sort**. This function returns `0` on success. For example:

```C
int sort(const void *a, const void *b) {
    return **(int **)a - **(int **)b;
}

int main() {
    linkedlist_t l, *list = &l;
    int a = 40, b = 20, c = 10, d = 30;
    int *array[] = { &a, &b, &c, &d, NULL };
    linkedlist_create(list);           /* Initialise a new empty list. */
    linkedlist_addarray(list, array);  /* List is now [40, 20, 10, 30]. */
    linkedlist_sort(list, sort);       /* List is now [10, 20, 30, 40]. */
    linkedlist_destroy(list);          /* Empty the list. */
    return 0;
}
```

## Warnings

- Be careful of using pointers to stack variables. If a list is used inside a function to store pointers to stack variables as its data items and the function returns, the list would now be storing invalid pointers. This is how the variable scope and stack works in C. Instead, if you need to return data items from a function in the list, use heap variables created by malloc or calloc or use global variables.
- Remember to call `linkedlist_destroy` after you have finished using a list to avoid memory leaks. You should also call `linkedlist_destroy` before you call `linkedlist_create` or `linkedlist_clone` to overwrite a used list to prevent memory leaks.
- `linkedlist_destroy`, `linkedlist_remove` and `linkedlist_set` does not free memory allocated to data items. You may have to free them first before calling these methods.
- `linkedlist_clone` creates a **shallow copy** of a list. This means the copied list acts independently of the original list **but points to the same data items**. Changes in the data items would affect both lists.
- The provided sample program `main.c` stores integers rather than pointers by converting integers to pointers. This is not the correct usage! It is only used to test the linked list implementation. If you want to store integers, store it as pointers to integers.
- `linkedlist_find`, `linkedlist_findindex`, `linkedlist_foreach` and `linkedlist_sort` all take a function as an argument which does not accept any useful custom arguments. You might want to use global variables, or if you want, you can copy and change these implementations similarly to changing `qsort` to `qsort_r`.

## Author

Harry Wong (RedAndBlueEraser)
