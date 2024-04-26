#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef LABA26_UDT_H
#define LABA26_UDT_H
typedef int value_type;
typedef struct udt {
    int start;
    int depth;
    int len;
    value_type* mas;
} udt;

void udt_create(udt *, int len);
bool udt_is_empty(udt *);
void udt_push_front(udt *, value_type);
void resize_udt(udt * Udt, int l);
void udt_delete(udt *);
void udt_copy(udt* , udt *);
void udt_pop_back(udt * );
void udt_print(udt * );
void udt_push_back(udt *, value_type);
void udt_pop_front(udt * );
int udt_size(udt *);
void swap(value_type *, value_type *);
void bubbleSort(udt *);

#endif
