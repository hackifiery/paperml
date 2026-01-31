#pragma once
#include "types.h"
#include "linear.h"
#include "plane.h"

/* output of a linear regression */
typedef struct {
    Linear line;
    db error;
    db rSquared;
} LinearRegression;

/* Calculate total sum of squares */
db getTss(const Plane pl);

/* Calculate residual sum of squares */
db getRss(const Plane pl, const Linear ln);

/* Calculate mean squared error */
db getMse(const Plane pl, const Linear ln);

/* Calculate R-squared from RSS and TSS */
db getRSquared(const db resSumSq, const db totSumSq);

/* Perform linear regression on a plane of points */
LinearRegression linreg(const Plane pl);

/* Print linear regression results */
void printLinearRegression(const LinearRegression lr);