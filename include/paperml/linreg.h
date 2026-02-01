
#ifndef PAPERML_LINREG_H
#define PAPERML_LINREG_H
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
db getTotalSumSquared(const Plane pl);

/* Calculate residual sum of squares */
db getResidualSumSquared(const Plane pl, const Linear ln);

/* Calculate mean squared error */
db getMeanSquaredError(const Plane pl, const Linear ln);

/* Calculate R-squared from RSS and TSS */
db getRSquared(const db resSumSq, const db totSumSq);

/* Perform linear regression on a plane of points */
LinearRegression linreg(const Plane pl);

/* Print linear regression results */
void printLinearRegression(const LinearRegression lr);

#endif /* PAPERML_LINREG_H */