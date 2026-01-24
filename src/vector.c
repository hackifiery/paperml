#include "vector.h"
#include "helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* internal */
static void _resizeIfNeeded(Vector* vec) {
	if (vec->len >= vec->capacity) {
		unsigned int newCapacity = vec->capacity * VECTOR_GROWTH_FAC;
		if (newCapacity < VECTOR_INIT_SIZE) newCapacity = VECTOR_INIT_SIZE;
		db* newArr = (db*)realloc(vec->arr, newCapacity * sizeof(db));
		checkAlloc(newArr);
		vec->arr = newArr;
		vec->capacity = newCapacity;
	}
}

Vector initVector(void) {
	Vector out;
	out.arr = (db*)calloc(VECTOR_INIT_SIZE, sizeof(db));
	checkAlloc(out.arr);
	out.len = 0;
	out.capacity = VECTOR_INIT_SIZE;
	return out;
}

void appendVector(Vector* vec, const db n) {
	_resizeIfNeeded(vec);
	vec->arr[vec->len] = n;
	vec->len++;
}

db popVector(Vector* vec) {
	if (vec->len == 0) printErr("Error: can't pop from empty Vector");

	vec->len--;
	return vec->arr[vec->len];
}

void attachVector(const Vector src, Vector* dest) {
    for (int i = 0; i < src.len; i++) {
        appendVector(dest, src.arr[i]);
    }
}

db getVector(const Vector v, const unsigned int idx) {
    if (idx >= v.len) {
        char errorMsg[100];
        snprintf(errorMsg, sizeof(errorMsg), 
                 "Error: index %u out of bounds (vector length: %u)\n", idx, v.len);
        printErr(errorMsg);
    }
    return v.arr[idx];
}

int findVector(const Vector* vec, db value) {
    if (!vec) return -1;
    
    for (unsigned int i = 0; i < vec->len; i++) {
        /* Compare floating point values with epsilon */
        if (fabs(vec->arr[i] - value) < 1e-12) {
            return (int)i;
        }
    }
    return -1;
}

void insertVector(Vector* vec, unsigned int index, db value) {
    if (!vec) return;
    
    if (index > vec->len) {
        char errorMsg[100];
        snprintf(errorMsg, sizeof(errorMsg),
                 "Error: index %u out of bounds (vector length: %u)\n", index, vec->len);
        printErr(errorMsg);
    }
    
    /* Ensure there's enough capacity */
    _resizeIfNeeded(vec);
    
    /* Shift elements to the right */
    for (unsigned int i = vec->len; i > index; i--) {
        vec->arr[i] = vec->arr[i - 1];
    }
    
    /* Insert the new value */
    vec->arr[index] = value;
    vec->len++;
}

db popAtVector(Vector* vec, unsigned int index) {
    if (!vec) return 0.0;
    
    if (index >= vec->len) {
        char errorMsg[100];
        snprintf(errorMsg, sizeof(errorMsg),
                 "Error: index %u out of bounds (vector length: %u)\n", index, vec->len);
        printErr(errorMsg);
    }
    
    /* Store the value to be removed */
    db removed_value = vec->arr[index];
    
    /* Shift elements to the left */
    for (unsigned int i = index; i < vec->len - 1; i++) {
        vec->arr[i] = vec->arr[i + 1];
    }
    
    vec->len--;
    return removed_value;
}

void reverseVector(Vector* vec) {
    if (!vec || vec->len <= 1) return;
    
    unsigned int left = 0;
    unsigned int right = vec->len - 1;
    
    while (left < right) {
        /* Swap elements */
        db temp = vec->arr[left];
        vec->arr[left] = vec->arr[right];
        vec->arr[right] = temp;
        
        left++;
        right--;
    }
}

db sumVector(const Vector vec) {
    db sum = 0;
    for (int i = 0; i < vec.len; i++) sum += vec.arr[i];
    return sum;
}

void sortVector(Vector* vec) {
    /* bubblesort for now */
    if (!vec || vec->len <= 1) return;
    
    for (unsigned int i = 0; i < vec->len - 1; i++) {
        int swapped = 0;
        
        for (unsigned int j = 0; j < vec->len - i - 1; j++) {
            if (vec->arr[j] > vec->arr[j + 1]) {
                db temp = vec->arr[j];
                vec->arr[j] = vec->arr[j + 1];
                vec->arr[j + 1] = temp;
                swapped = 1;
            }
        }
        
        /* If no swaps occurred, the vector is already sorted */
        if (!swapped) break;
    }
}