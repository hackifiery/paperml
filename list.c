#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define checkAlloc(a) { \
    if (!a) { \
        printf("memory alloc failed in %s.", __func__);\
        exit(EXIT_FAILURE); \
    } \
}

static void _resize(struct List* l) {

}