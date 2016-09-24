/*
 * main.c
 * Version 20160923
 * Written by Harry Wong (RedAndBlueEraser)
 */

#include <stdio.h>
#include "linkedlist.h"

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

    linkedlist_destroy(list);
    return 0;
}
