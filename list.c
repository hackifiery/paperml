#include "list.h"
#include "helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* internal */
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
	if (l->len == 0) printErr("Error: can't pop from empty List");

	l->len--;
	return l->arr[l->len];
}

void attachList(const struct List src, struct List* dest) {
    for (int i = 0; i < src.len; i++) {
        appendList(dest, src.arr[i]);
    }
}

db getList(const struct List l, const unsigned int idx) {
    if (idx >= l.len) {
        char error_msg[100];
        snprintf(error_msg, sizeof(error_msg), 
                 "Error: index %u out of bounds (list length: %u)\n", idx, l.len);
        printErr(error_msg);
    }
    return l.arr[idx];
}

int findList(const struct List* list, db value) {
    if (!list) return -1;
    
    for (unsigned int i = 0; i < list->len; i++) {
        // Compare floating point values with epsilon
        if (fabs(list->arr[i] - value) < 1e-12) {
            return (int)i;
        }
    }
    return -1;
}

void insertList(struct List* list, unsigned int index, db value) {
    if (!list) return;
    
    if (index > list->len) {
        char error_msg[100];
        snprintf(error_msg, sizeof(error_msg),
                 "Error: index %u out of bounds (list length: %u)\n", index, list->len);
        printErr(error_msg);
    }
    
    // Ensure there's enough capacity
    _resizeIfNeeded(list);
    
    // Shift elements to the right
    for (unsigned int i = list->len; i > index; i--) {
        list->arr[i] = list->arr[i - 1];
    }
    
    // Insert the new value
    list->arr[index] = value;
    list->len++;
}

db popAtList(struct List* list, unsigned int index) {
    if (!list) return 0.0;
    
    if (index >= list->len) {
        char error_msg[100];
        snprintf(error_msg, sizeof(error_msg),
                 "Error: index %u out of bounds (list length: %u)\n", index, list->len);
        printErr(error_msg);
    }
    
    // Store the value to be removed
    db removed_value = list->arr[index];
    
    // Shift elements to the left
    for (unsigned int i = index; i < list->len - 1; i++) {
        list->arr[i] = list->arr[i + 1];
    }
    
    list->len--;
    return removed_value;
}

void reverseList(struct List* list) {
    if (!list || list->len <= 1) return;
    
    unsigned int left = 0;
    unsigned int right = list->len - 1;
    
    while (left < right) {
        // Swap elements
        db temp = list->arr[left];
        list->arr[left] = list->arr[right];
        list->arr[right] = temp;
        
        left++;
        right--;
    }
}

void sortList(struct List* list) {
    // bubblesort for now
    if (!list || list->len <= 1) return;
    
    for (unsigned int i = 0; i < list->len - 1; i++) {
        int swapped = 0;
        
        for (unsigned int j = 0; j < list->len - i - 1; j++) {
            if (list->arr[j] > list->arr[j + 1]) {
                db temp = list->arr[j];
                list->arr[j] = list->arr[j + 1];
                list->arr[j + 1] = temp;
                swapped = 1;
            }
        }
        
        // If no swaps occurred, the list is already sorted
        if (!swapped) break;
    }
}