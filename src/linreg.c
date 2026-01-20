#include "linreg.h"
#include "helpers.h"
#include "list.h"
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
    switch (pst) {
        case X: {
            return sumList(pl.xVals);
        }
        case Y: {
            return sumList(pl.yVals);
        }
        case XTimesX: {
            db sum = 0;
            int i;
            for (i = 0; i < pl.size; i++) sum += pow(pl.xVals.arr[i], 2);
            return sum;
        }
        case XTimesY: {
            db sum = 0;
            int i;
            for (i = 0; i < pl.size; i++) sum += pl.xVals.arr[i] * pl.yVals.arr[i];
            return sum;
        }
    }
    return 0.0;
}

static db getErr(const Point p1, const Point p2) {
    return p1.y - p2.y;
}

db getTss(const Plane pl) {
    db meanY = sumList(pl.yVals) / (db)pl.size;
    db totSumSq = 0;
    for (int i = 0; i < pl.size; i++) {
        db diff = pl.yVals.arr[i] - meanY;
        totSumSq += diff * diff;
    }
    return totSumSq;
}

db getRSquared(const db resSumSq, const db totSumSq) {
    return 1 - (resSumSq / totSumSq);
}

db getRss(const Plane pl, const Linear ln) {
    db sumSqErr = 0;
    int i;
    for (i = 0; i < pl.size; i++) {
        Point predicted;
        predicted.x = pl.xVals.arr[i];
        predicted.y = getLinY(ln, pl.xVals.arr[i]);
        
        Point actual;
        actual.x = pl.xVals.arr[i];
        actual.y = pl.yVals.arr[i];
        
        db err = getErr(actual, predicted);
        sumSqErr += err * err;
    }
    return sumSqErr;
}

db getMse(const Plane pl, const Linear ln) {
    return getRss(pl, ln) / pl.size;
}

LinReg linreg(const Plane pl) {
    LinReg out;
    db n = (db)pl.size;
    db sumX = planeSum(pl, X);
    db sumY = planeSum(pl, Y);
    db sumXX = planeSum(pl, XTimesX);
    db sumXY = planeSum(pl, XTimesY);
    
    /* Least squares formulas */
    db slope = (n * sumXY - sumX * sumY) / (n * sumXX - sumX * sumX);
    db intercept = (sumY - slope * sumX) / n;
    
    out.line = initLinear(slope, intercept);
    out.error = getMse(pl, out.line);
    
    /* Calculate R-squared */
    db rss = getRss(pl, out.line);
    db tss = getTss(pl);
    out.rSquared = getRSquared(rss, tss);
    
    return out;
}

void printLinReg(const LinReg lr) {
    printf("Linear Regression results:\n");
    printf("Final line: y = %gx+%g\n", lr.line.slope, lr.line.intercept);
    printf("Error (MSE): %g\n", lr.error);
    printf("R-Squared percentage: %g%%\n", 100*lr.rSquared);
}