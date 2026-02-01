#ifndef PAPERML_VECTOR_H
#define PAPERML_VECTOR_H

#include "types.h"

#define VECTOR_INIT_SIZE 10
#define VECTOR_GROWTH_FAC 2

/* A dynamically resizing array with other cool features & stuff */
typedef struct {
    db* arr;
    unsigned int len;
    unsigned int capacity;
} Vector;

/* Initialize a Vector */
Vector initVector(void);

/* Initialize a Vector from a C-style array */
Vector arrToVector(db arr[], unsigned int size);

/* Append a value to the vector */
void appendVector(Vector* vec, const db n);

/* Remove and return the last value */
db popVector(Vector* vec);

/* Attach all elements from src to dest */
void attachVector(const Vector src, Vector* dest);

/* Get the value at an index */
db getVector(const Vector vec, const unsigned int idx);

/* Replaces a value at an index with another */
void replaceVector(Vector* vec, const unsigned int idx, const db val);

/* Find the first occurrence of a value, returns -1 if not found */
int findVector(const Vector* vec, db value);

/* Insert a value at an index */
void insertVector(Vector* vec, unsigned int index, db value);

/* Remove and return the value at an index */
db popAtVector(Vector* vec, unsigned int index);

/* Reverse the vector in-place */
void reverseVector(Vector* vec);

/* Get the sum of all values in a vector*/
db sumVector(const Vector vec);

/* Sort the vector using bubble sort */
void sortVector(Vector* vec);

/* Find the most frequent value (majority vote) */
db majorityVoteVector(const Vector vec);

#endif /* PAPERML_VECTOR_H */