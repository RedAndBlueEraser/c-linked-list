/*
 * linkedlist.c
 * Version 20160926
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

int linkedlist_clone(linkedlist_t *src, linkedlist_t *dest) {
    linkedlist_node_t *srccurr, *destcurr, *destprev;

    /* Empty and create a new list for dest. */
    linkedlist_destroy(dest);

    /* Copy nodes from src to dest. */
    if (src->size == 0) {
    } else {
        /* Copy head node from src to dest. */
        srccurr = src->head;

        destcurr = (linkedlist_node_t*)malloc(sizeof *destcurr);
        if (!destcurr) {
            fprintf(stderr, "Out of memory\n");
            return 1;
        }
        destcurr->next = NULL;
        destcurr->data = srccurr->data;

        dest->head = destcurr;

        destprev = destcurr;
        srccurr = srccurr->next;

        /* Copy body nodes from src to dest. */
        while (srccurr) {
            destcurr = (linkedlist_node_t*)malloc(sizeof *destcurr);
            if (!destcurr) {
                fprintf(stderr, "Out of memory\n");
                return 1;
            }
            destcurr->next = NULL;
            destcurr->data = srccurr->data;

            destprev->next = destcurr;

            destprev = destcurr;
            srccurr = srccurr->next;
        }

        /* Initialise dest attributes. */
        dest->foot = destprev;
        dest->size = src->size;
    }

    return 0;
}


size_t linkedlist_size(linkedlist_t *list) {
    return list->size;
}

int linkedlist_isempty(linkedlist_t *list) {
    return list->size == 0;
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

int linkedlist_add(linkedlist_t *list, size_t index, void *data) {
    linkedlist_node_t *node, *curr, *prev;

    /* Cannot add to index beyond list size. */
    if (index > list->size) {
        fprintf(stderr, "List out of range\n");
        return 1;
    }

    /* Add node to list. */
    if (index == 0) {
        return linkedlist_unshift(list, data);
    } else if (index == list->size) {
        return linkedlist_push(list, data);
    } else {
        /* Iterate until index. */
        curr = list->head;
        while (index-- > 0) {
            prev = curr;
            curr = curr->next;
        }

        /* Create new node. */
        node = (linkedlist_node_t*)malloc(sizeof *node);
        if (!node) {
            fprintf(stderr, "Out of memory\n");
            return 1;
        }

        /* Initialise node attributes. */
        node->next = curr;
        node->data = data;

        /* Add node to list. */
        prev->next = node;
        list->size++;
        return 0;
    }
}

void *linkedlist_remove(linkedlist_t *list, size_t index) {
    void *data;
    linkedlist_node_t *curr, *prev;

    /* Cannot remove from empty list. */
    if (list->size == 0) {
        fprintf(stderr, "List is empty\n");
        return NULL;
    }

    /* Cannot remove from index beyond list size. */
    if (index >= list->size) {
        fprintf(stderr, "List out of range\n");
        return NULL;
    }

    if (index == 0) {
        return linkedlist_shift(list);
    } else if (index == list->size - 1) {
        return linkedlist_pop(list);
    } else {
        /* Iterate until index. */
        curr = list->head;
        while (index-- > 0) {
            prev = curr;
            curr = curr->next;
        }

        /* Get item. */
        data = curr->data;

        /* Remove node from list. */
        prev->next = curr->next;
        free(curr);
        list->size--;

        return data;
    }
}

int linkedlist_set(linkedlist_t *list, size_t index, void *data) {
    linkedlist_node_t *curr;

    /* Cannot set in empty list. */
    if (list->size == 0) {
        fprintf(stderr, "List is empty\n");
        return 1;
    }

    /* Cannot set from index beyond list size. */
    if (index >= list->size) {
        fprintf(stderr, "List out of range\n");
        return 1;
    }

    /* Iterate until index. */
    curr = list->head;
    while (index-- > 0) {
        curr = curr->next;
    }
    curr->data = data;
    return 0;
}

int linkedlist_addarray(linkedlist_t *dest, void *src[]) {
    void *data;
    size_t i = 0;

    /* Add nodes from src to dest. */
    while ((data = src[i++])) {
        if (linkedlist_push(dest, data) != 0) {
            return 1;
        }
    }
    return 0;
}

int linkedlist_removearray(linkedlist_t *dest, void *src[]) {
    void *data;
    size_t i = 0, dataindex;

    /* Remove nodes from src to dest. */
    while (dest->size > 0 && (data = src[i++])) {
        dataindex = linkedlist_indexof(dest, data);
        if (dataindex < dest->size) {
            linkedlist_remove(dest, dataindex);
        }
    }
    return 0;
}

int linkedlist_addlinkedlist(linkedlist_t *dest, linkedlist_t *src) {
    linkedlist_node_t *srccurr = src->head;

    /* Add nodes from src to dest. */
    while (srccurr) {
        if (linkedlist_push(dest, srccurr->data) != 0) {
            return 1;
        }
        srccurr = srccurr->next;
    }
    return 0;
}

int linkedlist_removelinkedlist(linkedlist_t *dest, linkedlist_t *src) {
    linkedlist_node_t *srccurr = src->head;
    size_t dataindex;

    /* Remove nodes from src to dest. */
    while (srccurr) {
        dataindex = linkedlist_indexof(dest, srccurr->data);
        if (dataindex < dest->size) {
            linkedlist_remove(dest, dataindex);
        }
        srccurr = srccurr->next;
    }
    return 0;
}


void *linkedlist_get(linkedlist_t *list, size_t index) {
    linkedlist_node_t *curr;

    /* Cannot get from empty list. */
    if (list->size == 0) {
        fprintf(stderr, "List is empty\n");
        return NULL;
    }

    /* Cannot get from index beyond list size. */
    if (index >= list->size) {
        fprintf(stderr, "List out of range\n");
        return NULL;
    }

    /* Iterate until index. */
    curr = list->head;
    while (index-- > 0) {
        curr = curr->next;
    }
    return curr->data;
}

void *linkedlist_first(linkedlist_t *list) {
    /* Cannot get from empty list. */
    if (list->size == 0) {
        fprintf(stderr, "List is empty\n");
        return NULL;
    }

    return list->head->data;
}

void *linkedlist_last(linkedlist_t *list) {
    /* Cannot get from empty list. */
    if (list->size == 0) {
        fprintf(stderr, "List is empty\n");
        return NULL;
    }

    return list->foot->data;
}

size_t linkedlist_indexof(linkedlist_t *list, void *data) {
    linkedlist_node_t *curr = list->head;
    size_t index = 0;

    /* Test each item until an item passes the test. */
    while (curr) {
        if (curr->data == data) {
            break;
        }
        curr = curr->next;
        index++;
    }
    return index;
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

int linkedlist_foreach(linkedlist_t *list, void (*f)(void *)) {
    linkedlist_node_t *curr = list->head;

    /* Execute function on every item. */
    while (curr) {
        f(curr->data);
        curr = curr->next;
    }
    return 0;
}


int linkedlist_slice(linkedlist_t *list, size_t start, size_t end) {
    size_t size;
    linkedlist_node_t *curr, *next;

    /* Slice to empty list. */
    if (start >= end || start >= list->size) {
        return linkedlist_destroy(list);
    }
    /* Slice to end of list. */
    if (end > list->size) {
        end = list->size;
    }
    size = end - start;

    /* Free nodes until start. */
    curr = list->head;
    while (start-- > 0) {
        next = curr->next;
        free(curr);
        list->size--;
        curr = next;
    }
    /* Assign new list head. */
    list->head = curr;

    /* Iterate until before end. */
    while (--size > 0) {
        curr = curr->next;
    }
    /* Assign new list foot. */
    list->foot = curr;
    next = curr->next;
    curr->next = NULL;

    /* Free nodes. */
    curr = next;
    while (curr) {
        next = curr->next;
        free(curr);
        list->size--;
        curr = next;
    }
    return 0;
}
