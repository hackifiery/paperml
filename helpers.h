#pragma once
#include <stdio.h>
#include <stdlib.h>
#define checkAlloc(a) {  \
    if (!a) { \
        printf("memory alloc failed in %s.", __func__); \
        exit(EXIT_FAILURE); \
    } \
}

inline void printErr(const char* msg) {
    printf("%s", msg);
    exit(EXIT_FAILURE);
}