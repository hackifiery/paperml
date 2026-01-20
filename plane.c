#include "plane.h"
#include "helpers.h"
#include <stdlib.h>

Plane initPlane(void) {
    Plane p;
    p.xVals = initList();
    p.yVals = initList();
    p.size = 0;
    return p;
}

void addPoint(Plane* p, const Point point) {
    appendList(&p->xVals, point.x);
    appendList(&p->yVals, point.y);
    p->size++;
}

void addPoints(Plane* p, const Point* points, unsigned int count) {
    for (int i = 0; i < count; i++) {
        appendList(&p->xVals, points[i].x);
        appendList(&p->yVals, points[i].y);
    }
    p->size += count;
}

Plane planeFromLists(const List xList, const List yList) {
    Plane p = initPlane();
    
    if (xList.len != yList.len) {
        printErr("Error: x and y lists must have the same length\n");
    }
    
    for (unsigned int i = 0; i < xList.len; i++) {
        appendList(&p.xVals, getList(xList, i));
        appendList(&p.yVals, getList(yList, i));
    }
    p.size = xList.len;
    
    return p;
}

Point getPoint(const Plane p, unsigned int index) {
    Point point;
    point.x = getList(p.xVals, index);
    point.y = getList(p.yVals, index);
    return point;
}

Point* getAllPoints(const Plane p) {
    Point* points = (Point*)malloc(p.size * sizeof(Point));
    checkAlloc(points);
    
    for (unsigned int i = 0; i < p.size; i++) {
        points[i].x = getList(p.xVals, i);
        points[i].y = getList(p.yVals, i);
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