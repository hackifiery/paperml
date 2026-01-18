#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define checkAlloc(a) {  \
    if (!a) { \
        printf("memory alloc failed in %s.", __func__); \
        exit(EXIT_FAILURE); \
    } \
}

static void _resize(struct List* l) {
	if (ls->len >= ls->capacity) {
		unsigned int capacity_new = ls->capacity * GROWTH_FACTOR;
		if (capacity_new < INITIAL_CAPACITY) capacity_new = INITIAL_CAPACITY;
		db* new_arr = (db*)realloc(ls->arr, capacity_new * sizeof(db));
		checkAlloc(new_arr);
		ls->arr = new_arr;
		ls->capacity = capacity_new;
	}
}

struct List List(void) {
	struct List out;
	out.arr = (db*) 
}
