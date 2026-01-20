#pragma once

#include "types.h"

#define LIST_INIT_SIZE 10
#define LIST_GROWTH_FAC 2

/**
* @brief A dynamically resizing array with other cool features & stuff.
*/
typedef struct {
    db* arr; /** @warning DO NOT directly index, use getList() instead. */
    unsigned int len; /** @brief The length (or size) of the List. */
    unsigned int capacity; /** @brief internal use. @warning Don't modify! */
} List;

/** Initializes a List. */
List initList(void);

/**
* @brief Append the value n to l.
* @param l The List you are appending to.
* @param n The value to append.
*/
void appendList(List* ls, const db n);

/**
* @brief Pops the last value of l and returns it.
* @param l The List to pop.
*/
db popList(List* list);

/**
* @brief Attaches all of src to dest.
* @param src The source List.
* @param dest The destination List.
*/
void attachList(const List src, List* dest);

/**
* @brief Gets the value at index idx in List l.
* @param l The list to get the value of.
* @param idx The index of the value to get.
*/
db getList(const List l, const unsigned int idx);

/**
* @brief Finds the first occurence of value in List list, otherwise returns -1.
* @param list The List.
* @param value The value to find.
*/
int findList(const List* list, db value);

/**
* @brief Inserts value at index in list.
* @param list The List.
* @param index The index to insert.
* @param value The value to insert.
*/
void insertList(List* list, unsigned int index, db value);

/**
* @brief Pops and returns the value at index in list.
* @param list The List.
* @param index The index of the value to remove.
*/
db popAtList(List* list, unsigned int index);

/**
* @brief Reverse list (in-place).
* @param list The List to be reversed.
*/
void reverseList(List* list);

/**
* @brief Bubble-sorts list.
* TODO: implement a better sorting algo
* @param list The List to be sorted.
*/
void sortList(List* list);