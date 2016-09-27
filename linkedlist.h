/*
 * linkedlist.h
 * Version 20160927
 * Written by Harry Wong (RedAndBlueEraser)
 */

#include <stddef.h>

typedef struct linkedlist_node_t {
    struct linkedlist_node_t *next;
    void *data;
} linkedlist_node_t;

typedef struct linkedlist_t {
    linkedlist_node_t *head;
    linkedlist_node_t *foot;
    size_t size;
} linkedlist_t;

/* Create a new empty list. Returns 0 on success. */
int linkedlist_create(linkedlist_t *list);
/* Empty the list. Returns 0 on success. */
int linkedlist_destroy(linkedlist_t *list);
/* Copies a list. */
int linkedlist_clone(linkedlist_t *src, linkedlist_t *dest);

/* Get and return the number of items in the list. */
size_t linkedlist_size(linkedlist_t *list);
/* Check if list contains no items. */
int linkedlist_isempty(linkedlist_t *list);

/* Add an item to the end of the list. Returns 0 on success. */
int linkedlist_push(linkedlist_t *list, void *data);
/* Remove and return the item on the end of the list. */
void *linkedlist_pop(linkedlist_t *list);
/* Add an item to the start of the list. Returns 0 on success. */
int linkedlist_unshift(linkedlist_t *list, void *data);
/* Remove and return the item on the start of the list. */
void *linkedlist_shift(linkedlist_t *list);
/* Add an item to the specified position in the list. Returns 0 on success. */
int linkedlist_add(linkedlist_t *list, size_t index, void *data);
/* Remove and return the item in the specified position of the list. */
void *linkedlist_remove(linkedlist_t *list, size_t index);
/* Replace an item in the specified position of the list. Returns 0 on success.
 */
int linkedlist_set(linkedlist_t *list, size_t index, void *data);
/* Add the items from the null-terminated array to the end of the list. Returns
 * 0 on success.
 */
int linkedlist_addarray(linkedlist_t *dest, void *src[]);
/* Remove the items in the null-terminated array from the list. Returns 0 on
 * success.
 */
int linkedlist_removearray(linkedlist_t *dest, void *src[]);
/* Add the items from the src list to the end of the dest list. Returns 0 on
 * success.
 */
int linkedlist_addlinkedlist(linkedlist_t *dest, linkedlist_t *src);
/* Remove the items in the src list from the dest list. Returns 0 on success. */
int linkedlist_removelinkedlist(linkedlist_t *dest, linkedlist_t *src);

/* Get and return the item in the specified position in the list. */
void *linkedlist_get(linkedlist_t *list, size_t index);
/* Get and return the first item in the list. */
void *linkedlist_first(linkedlist_t *list);
/* Get and return the last item in the list. */
void *linkedlist_last(linkedlist_t *list);
/* Find and return the index of the specified item in the list. Returns the
 * number of items in the list if the item is not found.
 */
size_t linkedlist_indexof(linkedlist_t *list, void *data);
/* Find and return the first item in the list that pass the test (provided as a
 * function where a pass is 1). Returns null if no items pass the test.
 */
void *linkedlist_find(linkedlist_t *list, int (*f)(void *));
/* Find and return the index of the first item in the list that pass the test
 * (provided as a function where a pass is 1). Returns the number of items in
 * the list if no items pass the test.
 */
size_t linkedlist_findindex(linkedlist_t *list, int (*f)(void *));
/* Iterate over the list and execute a function on each item. Returns 0 on
 * success.
 */
int linkedlist_foreach(linkedlist_t *list, void (*f)(void *));

/* Slice the list from including start to excluding end. Returns 0 on
 * success.
 */
int linkedlist_slice(linkedlist_t *list, size_t start, size_t end);
/* Represents the list as a null-terminated array. Returns 0 on success. */
int linkedlist_toarray(linkedlist_t *src, void *dest[]);
