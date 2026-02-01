#ifndef PAPERML_HELPERS_H
#define PAPERML_HELPERS_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "vector.h"
#include "point.h"
#include "math_utils.h"

#ifdef __STDC__
#ifdef __STDC_VERSION__
#define checkAlloc(a) {  \
    if (!a) { \
        printf("memory alloc failed in %s.", __func__); \
        exit(EXIT_FAILURE); \
    } \
}
#else
#define checkAlloc(a) {  \
    if (!a) { \
        printf("memory alloc failed."); \
        exit(EXIT_FAILURE); \
    } \
}
#endif
#endif
void printErr(const char* msg);

#endif /* PAPERML_HELPERS_H */