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

static void _resizeIfNeeded(struct List* l) {
	if (l->len >= l->capacity) {
		unsigned int newCapacity = l->capacity * LIST_GROWTH_FAC;
		if (newCapacity < LIST_INIT_SIZE) newCapacity = LIST_INIT_SIZE;
		db* newArr = (db*)realloc(l->arr, newCapacity * sizeof(db));
		checkAlloc(newArr);
		l->arr = newArr;
		l->capacity = newCapacity;
	}
}

struct List List(void) {
	struct List out;
	out.arr = (db*)calloc(LIST_INIT_SIZE, sizeof(db));
	checkAlloc(out.arr);
	out.len = 0;
	out.capacity = LIST_INIT_SIZE;
	return out;
}

void appendList(struct List* l, const db n) {
	_resizeIfNeeded(l);
	l->arr[l->len] = n;
	l->len++;
}

db popList(struct List* l) {
	l->len--;
	return l->arr[l->len];
}
