#pragma once

#include "types.h"

#define LIST_INIT_SIZE 10
#define LIST_GROWTH_FAC 2

/* A dynamically resizing array with other cool features & stuff. */
typedef struct {
    db* arr;
    unsigned int len;
    unsigned int capacity;
} List;

/* Initialize a List. */
List initList(void);

/* Append a value to the list. */
void appendList(List* ls, const db n);

/* Remove and return the last value. */
db popList(List* list);

/* Attach all elements from src to dest. */
void attachList(const List src, List* dest);

/* Get the value at an index. */
db getList(const List l, const unsigned int idx);

/* Find the first occurrence of a value, returns -1 if not found. */
int findList(const List* list, db value);

/* Insert a value at an index. */
void insertList(List* list, unsigned int index, db value);

/* Remove and return the value at an index. */
db popAtList(List* list, unsigned int index);

/* Reverse the list in-place. */
void reverseList(List* list);

/* Sort the list using bubble sort. */
void sortList(List* list);