#include "plane.h"
#include "helpers.h"
#include <stdlib.h>

Plane initPlane(void) {
    Plane p;
    p.xVals = initVector();
    p.yVals = initVector();
    p.size = 0;
    return p;
}

void addPoint(Plane* p, const Point point) {
    appendVector(&p->xVals, point.x);
    appendVector(&p->yVals, point.y);
    p->size++;
}

void addPoints(Plane* p, const Point* points, unsigned int count) {
    for (int i = 0; i < count; i++) {
        appendVector(&p->xVals, points[i].x);
        appendVector(&p->yVals, points[i].y);
    }
    p->size += count;
}

Plane planeFromLists(const Vector xList, const Vector yList) {
    Plane p = initPlane();
    
    if (xList.len != yList.len) {
        printErr("Error: x and y vectors must have the same length\n");
    }
    
    for (unsigned int i = 0; i < xList.len; i++) {
        appendVector(&p.xVals, getVector(xList, i));
        appendVector(&p.yVals, getVector(yList, i));
    }
    p.size = xList.len;
    
    return p;
}

Point getPoint(const Plane p, unsigned int index) {
    Point point;
    point.x = getVector(p.xVals, index);
    point.y = getVector(p.yVals, index);
    return point;
}

Point* getAllPoints(const Plane p) {
    Point* points = (Point*)malloc(p.size * sizeof(Point));
    checkAlloc(points);
    
    for (unsigned int i = 0; i < p.size; i++) {
        points[i].x = getVector(p.xVals, i);
        points[i].y = getVector(p.yVals, i);
    }
    
    return points;
}

void clearPlane(Plane* p) {
    if (!p) return;
    
    /* Reset lists but keep allocated memory */
    p->xVals.len = 0;
    p->yVals.len = 0;
    p->size = 0;
}

void freePlane(Plane* p) {
    if (!p) return;
    
    free(p->xVals.arr);
    free(p->yVals.arr);
    p->size = 0;
    /* Don't free p itself since it might be stack allocated */
}