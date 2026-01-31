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
    int i;
    for (i = 0; i < src.len; i++) {
        appendVector(dest, src.arr[i]);
    }
}

db getVector(const Vector v, const unsigned int idx) {
    assert (idx < v.len);
    return v.arr[idx];
}

void replaceVector(Vector* v, const unsigned int idx, const db val) {
    assert(idx < v->len);
    v->arr[idx] = val;
}

int findVector(const Vector* vec, db value) {
    int i;
    if (!vec) return -1;
    
    for (i = 0; i < vec->len; i++) {
        /* Compare floating point values with epsilon */
        if (fabs(vec->arr[i] - value) < 1e-12) {
            return (int)i;
        }
    }
    return -1;
}

void insertVector(Vector* vec, unsigned int index, db value) {
    int i;
    if (!vec) return;
    
    assert(index <= vec->len) ;
    
    /* Ensure there's enough capacity */
    _resizeIfNeeded(vec);
    
    /* Shift elements to the right */
    for (i = vec->len; i > index; i--) {
        vec->arr[i] = vec->arr[i - 1];
    }
    
    /* Insert the new value */
    vec->arr[index] = value;
    vec->len++;
}

db popAtVector(Vector* vec, unsigned int index) {
    int i;
    db removed_value;
    if (!vec) return 0.0;

    assert(index < vec->len);
    /* Store the value to be removed */
    removed_value = vec->arr[index];
    
    /* Shift elements to the left */
    for (i = index; i < vec->len - 1; i++) {
        vec->arr[i] = vec->arr[i + 1];
    }
    
    vec->len--;
    return removed_value;
}

void reverseVector(Vector* vec) {
    db temp;
    unsigned int left;
    unsigned int right;
    if (!vec || vec->len <= 1) return;
    
    left = 0;
    right = vec->len - 1;
    
    while (left < right) {
        /* Swap elements */
        temp = vec->arr[left];
        vec->arr[left] = vec->arr[right];
        vec->arr[right] = temp;
        
        left++;
        right--;
    }
}

db sumVector(const Vector vec) {
    int i;
    db sum = 0;
    for (i = 0; i < (int)vec.len; i++) sum += vec.arr[i];
    return sum;
}

void sortVector(Vector* vec) {
    int i, j;
    int swapped;
    /* bubblesort for now */
    if (!vec || vec->len <= 1) return;
    
    for (i = 0; i < vec->len - 1; i++) {
        swapped = 0;
        
        for (j = 0; j < vec->len - i - 1; j++) {
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

db majorityVoteVector(const Vector v) {
    int i, j;
    int maxCount = 0;
    unsigned int count;
    db maxVal = 0;
    
    if (v.len == 0) return 0;
    
    /* Find the value that appears most frequently */
    for (i = 0; i < v.len; i++) {
        count = 0;
        for (j = 0; j < v.len; j++) {
            if (fabs(v.arr[i] - v.arr[j]) < 1e-12) {
                count++;
            }
        }
        if (count > maxCount) {
            maxCount = count;
            maxVal = v.arr[i];
        }
    }
    return maxVal;
}