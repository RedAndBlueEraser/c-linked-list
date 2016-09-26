/*
 * main.c
 * Version 20160926
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
    ret += printf("] (n = %zd) @%p", linkedlist_size(list), list);
    return ret;
}

int test40(void *data) {
    return (int)data == 40;
}
int test50(void *data) {
    return (int)data > 0 && (int)data % 25 == 0;
}
int test70(void *data) {
    return (int)data > 0 && (int)data % 35 == 0;
}
int testfalse(void *data) {
    return 0;
}
void testprint(void *data) {
    printf("% d + 5 = %d\n", (int)data, (int)data + 5);
}

int main(int argc, char *argv[]) {
    linkedlist_t l1, *list1 = &l1, l2, *list2 = &l2;
    linkedlist_create(list1);
    linkedlist_create(list2);

    printf(" list1 "); linkedlist_printint(list1); printf("\n");
    printf(" list2 "); linkedlist_printint(list2); printf("\n");

    printf(" list1 pushed with %d\n", 30); linkedlist_push(list1, (void *)30);
    printf(" list1 pushed with %d\n", 40); linkedlist_push(list1, (void *)40);
    printf(" list1 pushed with %d\n", 50); linkedlist_push(list1, (void *)50);
    printf(" list1 pushed with %d\n", 55); linkedlist_push(list1, (void *)55);
    printf(" list1 popped with %d\n", (int)linkedlist_pop(list1));
    printf(" list1 pushed with %d\n", 60); linkedlist_push(list1, (void *)60);
    printf(" list1 pushed with %d\n", 70); linkedlist_push(list1, (void *)70);
    printf(" list1 unshifted with %d\n", 20); linkedlist_unshift(list1, (void *)20);
    printf(" list1 unshifted with %d\n", 10); linkedlist_unshift(list1, (void *)10);
    printf(" list1 unshifted with %d\n", 0); linkedlist_unshift(list1, (void *)0);
    printf(" list1 unshifted with %d\n", -10); linkedlist_unshift(list1, (void *)-10);
    printf(" list1 shifted with %d\n", (int)linkedlist_shift(list1));
    printf(" list1 "); linkedlist_printint(list1); printf("\n");
    printf(" 30 = list1[%zd]\n", linkedlist_indexof(list1, (void *)30));
    printf(" 50 = list1[%zd]\n", linkedlist_indexof(list1, (void *)50));
    printf(" 70 = list1[%zd]\n", linkedlist_indexof(list1, (void *)70));
    printf(" 90 = list1[%zd]\n", linkedlist_indexof(list1, (void *)90));
    printf(" == 40 = list1[%zd]\n", linkedlist_findindex(list1, test40));
    printf(" == (> 0 && %%25 == 0) = list1[%zd]\n", linkedlist_findindex(list1, test50));
    printf(" == (> 0 && %%35 == 0) = list1[%zd]\n", linkedlist_findindex(list1, test70));
    printf(" false = list1[%zd]\n", linkedlist_findindex(list1, testfalse));
    printf(" list1 shifted with %d\n", (int)linkedlist_shift(list1));
    printf(" list1 popped with %d\n", (int)linkedlist_pop(list1));
    printf(" list1[0] = %d\n", (int)linkedlist_first(list1));
    printf(" list1[-1] = %d\n", (int)linkedlist_last(list1));
    printf(" list1 "); linkedlist_printint(list1); printf("\n");
    printf(" ?list2 empty? %d\n", linkedlist_isempty(list2));
    printf(" list2 cloned with list1\n"); linkedlist_clone(list1, list2);
    printf(" list1 "); linkedlist_printint(list1); printf("\n");
    printf(" ?list1 empty? %d\n", linkedlist_isempty(list1));
    printf(" list1 destroyed\n"); linkedlist_destroy(list1);
    printf(" ?list1 empty? %d\n", linkedlist_isempty(list1));
    printf(" list2 "); linkedlist_printint(list2); printf("\n");
    printf(" ?list2 empty? %d\n", linkedlist_isempty(list2));
    printf(" list2 destroyed\n"); linkedlist_destroy(list2);
    printf(" ?list2 empty? %d\n", linkedlist_isempty(list2));
    printf(" list2 "); linkedlist_printint(list2); printf("\n");

    printf(" --------\n");

    printf(" ?list1 popped with fail? %d\n", linkedlist_pop(list1) == NULL);
    printf(" ?list1 shifted with fail? %d\n", linkedlist_pop(list1) == NULL);
    printf(" ?list1[0] removed with fail? %d\n", linkedlist_remove(list1, 0) == NULL);
    printf(" list1[0] added with %d\n", 11); linkedlist_add(list1, 0, (void *)11);
    printf(" list1[1] added with %d\n", 13); linkedlist_add(list1, 1, (void *)13);
    printf(" list1[0] added with %d\n", 10); linkedlist_add(list1, 0, (void *)10);
    printf(" list1[2] added with %d\n", 12); linkedlist_add(list1, 2, (void *)12);
    printf(" list1[4] added with %d\n", 14); linkedlist_add(list1, 4, (void *)14);
    printf(" ?list1[50] added with fail? %d\n", linkedlist_add(list1, 50, (void *)50) == 1);
    printf(" ?list1[50] removed with fail? %d\n", linkedlist_remove(list1, 50) == NULL);
    printf(" list1 "); linkedlist_printint(list1); printf("\n");
    printf(" list1[1] added with %d\n", -1); linkedlist_add(list1, 1, (void *)-1);
    printf(" list1[2] added with %d\n", -2); linkedlist_add(list1, 2, (void *)-2);
    printf(" list1[3] added with %d\n", -3); linkedlist_add(list1, 3, (void *)-3);
    printf(" list1[4] added with %d\n", -4); linkedlist_add(list1, 4, (void *)-4);
    printf(" list1[5] added with %d\n", -5); linkedlist_add(list1, 5, (void *)-5);
    printf(" list1 "); linkedlist_printint(list1); printf("\n");
    printf(" list1[1] removed with %d\n", (int)linkedlist_remove(list1, 1));
    printf(" list1[1] removed with %d\n", (int)linkedlist_remove(list1, 1));
    printf(" list1[3] removed with %d\n", (int)linkedlist_remove(list1, 3));
    printf(" list1[2] removed with %d\n", (int)linkedlist_remove(list1, 2));
    printf(" list1[1] removed with %d\n", (int)linkedlist_remove(list1, 1));
    printf(" list1 "); linkedlist_printint(list1); printf("\n");
    printf(" ?list2[0] setted with fail? %d\n", linkedlist_set(list2, 0, (void *)-1) == 1);
    printf(" ?list1[9] setted with fail? %d\n", linkedlist_set(list1, 9, (void *)-1) == 1);
    printf(" list1[0] setted with %d\n", 20); linkedlist_set(list1, 0, (void *)20);
    printf(" list1[1] setted with %d\n", 21); linkedlist_set(list1, 1, (void *)21);
    printf(" list1[2] setted with %d\n", 22); linkedlist_set(list1, 2, (void *)22);
    printf(" list1[3] setted with %d\n", 23); linkedlist_set(list1, 3, (void *)23);
    printf(" list1[4] setted with %d\n", 24); linkedlist_set(list1, 4, (void *)24);
    printf(" list1 "); linkedlist_printint(list1); printf("\n");
    linkedlist_foreach(list2, testprint);
    linkedlist_foreach(list1, testprint);
    printf(" list1 "); linkedlist_printint(list1); printf("\n");

    printf(" --------\n");

    void *array1[5] = { (void *)25, (void *)26, (void *)27, (void *)28, NULL },
        *array2[5] = { (void *)20, (void *)23, (void *)26, (void *)29, NULL };
    printf(" list1 added array with array1\n"); linkedlist_addarray(list1, array1);
    printf(" list1 "); linkedlist_printint(list1); printf("\n");
    printf(" list1 removed array with array2\n"); linkedlist_removearray(list1, array2);
    printf(" list1 "); linkedlist_printint(list1); printf("\n");
    printf(" list2 "); linkedlist_printint(list2); printf("\n");
    printf(" list2 removed array with array2\n"); linkedlist_removearray(list2, array2);
    printf(" list2 "); linkedlist_printint(list2); printf("\n");
    printf(" list2 added array with array1\n"); linkedlist_addarray(list2, array1);
    printf(" list2 "); linkedlist_printint(list2); printf("\n");
    printf(" list2 removed array with array2\n"); linkedlist_removearray(list2, array2);
    printf(" list2 "); linkedlist_printint(list2); printf("\n");
    printf(" list2 destroyed\n"); linkedlist_destroy(list2);
    printf(" list2 unshifted with %d\n", 105); linkedlist_unshift(list2, (void *)105);
    printf(" list2 unshifted with %d\n", 106); linkedlist_unshift(list2, (void *)106);
    printf(" list2 unshifted with %d\n", 107); linkedlist_unshift(list2, (void *)107);
    printf(" list2 unshifted with %d\n", 108); linkedlist_unshift(list2, (void *)108);
    printf(" list2 "); linkedlist_printint(list2); printf("\n");
    printf(" list1 added list with list2\n"); linkedlist_addlinkedlist(list1, list2);
    printf(" list1 "); linkedlist_printint(list1); printf("\n");
    printf(" list2 destroyed\n"); linkedlist_destroy(list2);
    printf(" list2 unshifted with %d\n", 21); linkedlist_unshift(list2, (void *)21);
    printf(" list2 unshifted with %d\n", 24); linkedlist_unshift(list2, (void *)24);
    printf(" list2 unshifted with %d\n", 105); linkedlist_unshift(list2, (void *)105);
    printf(" list2 unshifted with %d\n", 108); linkedlist_unshift(list2, (void *)108);
    printf(" list2 "); linkedlist_printint(list2); printf("\n");
    printf(" list1 removed list with list2\n"); linkedlist_removelinkedlist(list1, list2);
    printf(" list1 "); linkedlist_printint(list1); printf("\n");
    printf(" list2 removed list with list1\n"); linkedlist_removelinkedlist(list2, list1);
    printf(" list2 "); linkedlist_printint(list2); printf("\n");
    return 0;
}
