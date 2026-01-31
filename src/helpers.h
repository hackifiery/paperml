#ifndef PAPERML_HELPERS_H
#define PAPERML_HELPERS_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "vector.h"
#include "point.h"
#include "math_utils.h"

#define checkAlloc(a) {  \
    if (!a) { \
        printf("memory alloc failed in %s.", __func__); \
        exit(EXIT_FAILURE); \
    } \
}

void printErr(const char* msg);

#endif