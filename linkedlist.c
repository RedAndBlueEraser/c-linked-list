/*
 * linkedlist.c
 * Version 20160923
 * Written by Harry Wong (RedAndBlueEraser)
 */

#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

int linkedlist_create(linkedlist_t *list) {
    /* Initialise list attributes. */
    list->head = list->foot = NULL;
    list->size = 0;
    return 0;
}

int linkedlist_destroy(linkedlist_t *list) {
    /* Free memory allocated for nodes in the list. */
    linkedlist_node_t *curr = list->head, *next;
    while (curr) {
        next = curr->next;
        free(curr);
        curr = next;
    }

    /* Create a new empty list. */
    return linkedlist_create(list);
}


size_t linkedlist_size(linkedlist_t *list) {
    return list->size;
}


int linkedlist_push(linkedlist_t *list, void *data) {
    linkedlist_node_t *node = (linkedlist_node_t*)malloc(sizeof *node);
    if (!node) {
        fprintf(stderr, "Out of memory\n");
        return 1;
    }

    /* Initialise node attributes. */
    node->next = NULL;
    node->data = data;

    /* Add node to list. */
    if (list->size == 0) {
        list->head = list->foot = node;
        list->size = 1;
    } else {
        list->foot->next = node;
        list->foot = node;
        list->size++;
    }
    return 0;
}

void *linkedlist_pop(linkedlist_t *list) {
    void *data;
    linkedlist_node_t *foot, *curr, *prev;

    /* Cannot pop empty list. */
    if (list->size == 0) {
        fprintf(stderr, "List is empty\n");
        return NULL;
    }

    /* Get item from list foot. */
    foot = list->foot;
    data = foot->data;

    /* Remove node from list. */
    if (list->size == 1) {
        free(foot);
        linkedlist_create(list);
    } else {
        /* Assign new list foot. */
        curr = list->head;
        while (curr != foot) {
            prev = curr;
            curr = curr->next;
        }
        free(foot);
        prev->next = NULL;
        list->foot = prev;
        list->size--;
    }
    return data;
}

int linkedlist_unshift(linkedlist_t *list, void *data) {
    linkedlist_node_t *node = (linkedlist_node_t*)malloc(sizeof *node);
    if (!node) {
        fprintf(stderr, "Out of memory\n");
        return 1;
    }

    /* Initialise node attributes. */
    node->next = list->head;
    node->data = data;

    /* Add node to list. */
    if (list->size == 0) {
        list->head = list->foot = node;
        list->size = 1;
    } else {
        list->head = node;
        list->size++;
    }
    return 0;
}

void *linkedlist_shift(linkedlist_t *list) {
    void *data;
    linkedlist_node_t *head;

    /* Cannot shift empty list. */
    if (list->size == 0) {
        fprintf(stderr, "List is empty\n");
        return NULL;
    }

    /* Get item from list head. */
    head = list->head;
    data = head->data;

    /* Remove node from list. */
    if (list->size == 1) {
        free(head);
        linkedlist_create(list);
    } else {
        /* Assign new list head. */
        list->head = head->next;
        free(head);
        list->size--;
    }
    return data;
}


void *linkedlist_get(linkedlist_t *list, size_t index) {
    linkedlist_node_t *curr = list->head;
    while (index-- > 0) {
        curr = curr->next;
    }
    return curr->data;
}

void *linkedlist_first(linkedlist_t *list) {
    return list->head->data;
}

void *linkedlist_last(linkedlist_t *list) {
    return list->foot->data;
}

void *linkedlist_find(linkedlist_t *list, int (*f)(void *)) {
    linkedlist_node_t *curr = list->head;

    /* Test each item until an item passes the test. */
    while (curr) {
        if (f(curr->data) == 1) {
            return curr->data;
        }
        curr = curr->next;
    }
    return NULL;
}

size_t linkedlist_findindex(linkedlist_t *list, int (*f)(void *)) {
    linkedlist_node_t *curr = list->head;
    size_t index = 0;

    /* Test each item until an item passes the test. */
    while (curr) {
        if (f(curr->data) == 1) {
            break;
        }
        curr = curr->next;
        index++;
    }
    return index;
}
