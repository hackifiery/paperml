#pragma once

#include "types.h"

#define LIST_INIT_SIZE 10
#define LIST_GROWTH_FAC 2

struct List {
    db* arr;
    unsigned int len;
};

struct List List(void);
void appendList(struct List* ls, const db n);
db popList(struct List* list);
void attachList(const struct List src, struct List* dest);