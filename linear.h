#pragma once
#include "types.h"

/* A univariate linear equation. */
typedef struct {
    db slope;
    db intercept;
} Linear;

/* Initialize a linear equation. */
Linear initLinear(const db slope, const db intercept);
