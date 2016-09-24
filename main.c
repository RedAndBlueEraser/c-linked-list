/*
 * main.c
 * Version 20160923
 * Written by Harry Wong (RedAndBlueEraser)
 */

#include <stdio.h>
#include "linkedlist.h"

int linkedlist_printint(linkedlist_t *list) {
    int i, ret = printf("[");
    if (!linkedlist_isempty(list)) {
        ret += printf("%d", (int)linkedlist_get(list, 0));
    }
    for (i = 1; i < linkedlist_size(list); i++) {
        ret += printf(", %d", (int)linkedlist_get(list, i));
    }
    ret += printf("] (n = %zd) @%p\n", linkedlist_size(list), list);
    return ret;
}

int test50(void *data) {
    return (int)data == 50;
}
int test90(void *data) {
    return (int)data > 0 && (int)data % 45 == 0;
}
int test180(void *data) {
    return (int)data > 0 && (int)data % 60 == 0;
}
int testfalse(void *data) {
    return 0;
}

int main(int argc, char *argv[]) {
    int i;
    linkedlist_t l, *list = &l, l2, *list2 = &l2;
    linkedlist_create(list);
    linkedlist_create(list2);

    printf("List size is %d\n", linkedlist_size(list));

    linkedlist_push(list, (void*)30);
    linkedlist_push(list, (void*)50);
    linkedlist_push(list, (void*)70);
    printf("List popped with %d\n", (int)linkedlist_pop(list));
    linkedlist_push(list, (void*)90);
    linkedlist_push(list, (void*)180);
    linkedlist_unshift(list, (void*)20);
    linkedlist_unshift(list, (void*)10);
    linkedlist_unshift(list, (void*)0);
    linkedlist_unshift(list, (void*)-10);
    printf("List shifted with %d\n", (int)linkedlist_shift(list));
    printf("List size is %d\n", linkedlist_size(list));
    for (i = 0; i < linkedlist_size(list); i++) {
        printf("List %dth item is %d\n", i, linkedlist_get(list, i));
    }
    printf("Item 50 is the %dth item in the list counting from 0\n", linkedlist_findindex(list, test50));
    printf("Item %d in the list is divisible by 45\n", (int)linkedlist_find(list, test90));
    printf("Item %d in the list is divisible by 60\n", (int)linkedlist_find(list, test180));
    printf("Unable to find item is fine? %d\n", (int)linkedlist_findindex(list, testfalse) == linkedlist_size(list));
    linkedlist_shift(list);
    linkedlist_pop(list);
    printf("List first item is %d\n", (int)linkedlist_first(list));
    printf("List last item is %d\n", (int)linkedlist_last(list));
    printf("List size is %d\n", linkedlist_size(list));
    for (i = 0; i < linkedlist_size(list); i++) {
        printf("List %dth item is %d\n", i, linkedlist_get(list, i));
    }
    printf("List 2 is empty? %d\n", linkedlist_isempty(list2));
    linkedlist_clone(list, list2);
    printf("List size is %d\n", linkedlist_size(list));
    for (i = 0; i < linkedlist_size(list); i++) {
        printf("List %dth item is %d\n", i, linkedlist_get(list, i));
    }
    printf("List is empty? %d\n", linkedlist_isempty(list));
    linkedlist_destroy(list);
    printf("List is empty? %d\n", linkedlist_isempty(list));
    printf("List 2 size is %d\n", linkedlist_size(list2));
    for (i = 0; i < linkedlist_size(list2); i++) {
        printf("List 2 %dth item is %d\n", i, linkedlist_get(list2, i));
    }
    printf("List 2 is empty? %d\n", linkedlist_isempty(list2));
    linkedlist_destroy(list2);
    printf("List 2 is empty? %d\n", linkedlist_isempty(list2));
    for (i = 0; i < linkedlist_size(list); i++) {
        printf("List %dth item is %d\n", i, linkedlist_get(list, i));
    }

    printf("Unable to pop item is fine? %d\n", linkedlist_pop(list) == NULL);
    printf("Unable to shift item is fine? %d\n", linkedlist_shift(list) == NULL);
    printf("Unable to remove item is fine? %d\n", linkedlist_remove(list, 0) == NULL);
    linkedlist_add(list, 0, (void*)11);
    linkedlist_add(list, 1, (void*)13);
    linkedlist_add(list, 0, (void*)10);
    linkedlist_add(list, 2, (void*)12);
    linkedlist_add(list, 4, (void*)14);
    printf("Unable to add item is fine? %d\n", linkedlist_add(list, 50, (void*)50) == 1);
    printf("Unable to remove item is fine? %d\n", linkedlist_remove(list, 50) == NULL);
    printf("List: "); linkedlist_printint(list);
    linkedlist_add(list, 1, (void*)-1);
    linkedlist_add(list, 2, (void*)-2);
    linkedlist_add(list, 3, (void*)-3);
    linkedlist_add(list, 4, (void*)-4);
    linkedlist_add(list, 5, (void*)-5);
    printf("List: "); linkedlist_printint(list);
    linkedlist_remove(list, 1);
    linkedlist_remove(list, 1);
    linkedlist_remove(list, 3);
    linkedlist_remove(list, 2);
    linkedlist_remove(list, 1);
    printf("List: "); linkedlist_printint(list);
    linkedlist_destroy(list);
    return 0;
}
