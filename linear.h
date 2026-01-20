#pragma once
#include "types.h"
#include "point.h"

/* A univariate linear equation */
typedef struct {
    db slope;
    db intercept;
} Linear;

/* Initialize a linear equation */
Linear initLinear(const db slope, const db intercept);

/* Solves for y, given x in a linear equation */
db getLinY(const Linear ln, const db x);

/* Solves for x, given y in a linear equation */
db getLinX(const Linear ln, const db y);

/* Checks if a point is on the line or not */
int onLinear(const Linear ln, const Point pt);