/*
 * linkedlist.h
 * Version 20160916
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
