#include "linreg.h"
#include "helpers.h"
#include "vector.h"
#include "plane.h"
#include "point.h"
#include "types.h"

#include <math.h>

typedef enum {
    X,
    Y,
    XTimesX,
    XTimesY
} PlaneSumType;

static db planeSum(const Plane pl, const PlaneSumType pst) {
    db sum;
    int i;
    switch (pst) {
        case X: {
            return sumVector(pl.xVals);
        }
        case Y: {
            return sumVector(pl.yVals);
        }
        case XTimesX: {
            sum = 0;
            for (i = 0; i < pl.size; i++) sum += pow(pl.xVals.arr[i], 2);
            return sum;
        }
        case XTimesY: {
            sum = 0;
            for (i = 0; i < pl.size; i++) sum += pl.xVals.arr[i] * pl.yVals.arr[i];
            return sum;
        }
    }
    return 0.0;
}

static db getErr(const Point p1, const Point p2) {
    return p1.y - p2.y;
}

db getTotalSumSquared(const Plane pl) {
    int i;
    db meanY = sumVector(pl.yVals) / (db)pl.size;
    db totSumSq = 0;
    for (i = 0; i < pl.size; i++) {
        db diff = pl.yVals.arr[i] - meanY;
        totSumSq += diff * diff;
    }
    return totSumSq;
}

db getRSquared(const db resSumSq, const db totSumSq) {
    return 1 - (resSumSq / totSumSq);
}

db getResidualSumSquared(const Plane pl, const Linear ln) {
    db sumSqErr = 0;
    int i;
    Point predicted;
    Point actual;
    db err;
    for (i = 0; i < pl.size; i++) {
        predicted.x = pl.xVals.arr[i];
        predicted.y = getLinY(ln, pl.xVals.arr[i]);
        
        actual.x = pl.xVals.arr[i];
        actual.y = pl.yVals.arr[i];
        
        err = getErr(actual, predicted);
        sumSqErr += err * err;
    }
    return sumSqErr;
}

db getMeanSquaredError(const Plane pl, const Linear ln) {
    return getResidualSumSquared(pl, ln) / pl.size;
}

LinearRegression linreg(const Plane pl) {
    LinearRegression out;
    db n;
    db sumX;
    db sumY;
    db sumXX;
    db sumXY;
    db slope;
    db intercept;
    db rss;
    db tss;
    
    n = (db)pl.size;
    sumX = planeSum(pl, X);
    sumY = planeSum(pl, Y);
    sumXX = planeSum(pl, XTimesX);
    sumXY = planeSum(pl, XTimesY);
    
    /* Least squares formulas */
    slope = (n * sumXY - sumX * sumY) / (n * sumXX - sumX * sumX);
    intercept = (sumY - slope * sumX) / n;
    
    out.line = initLinear(slope, intercept);
    out.error = getMeanSquaredError(pl, out.line);
    
    /* Calculate R-squared */
    rss = getResidualSumSquared(pl, out.line);
    tss = getTotalSumSquared(pl);
    out.rSquared = getRSquared(rss, tss);
    
    return out;
}

void printLinearRegression(const LinearRegression lr) {
    /* ANSI color codes */
    #define RED     "\x1b[31m"
    #define YELLOW  "\x1b[33m"
    #define GREEN   "\x1b[32m"
    #define RESET   "\x1b[0m"
    /* Determine color based on R-squared value */
    const char* color;
    if (lr.rSquared > 0.7) {
        color = GREEN;
    } else if (lr.rSquared > 0.4) {
        color = YELLOW;
    } else {
        color = RED;
    }
    #undef RED
    #undef YELLOW
    #undef GREEN
    
    printf("Linear Regression results:\n");
    printf("Final line: y = %gx + %g\n", lr.line.slope, lr.line.intercept);
    printf("Error (MSE): %g\n", lr.error);
    printf("R-Squared percentage: %s%g%%%s\n", color, 100*lr.rSquared, RESET);
    #undef RESET
}