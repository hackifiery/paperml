#include "plane.h"
#include "helpers.h"
#include <stdlib.h>

Plane initPlane(void) {
    Plane p;
    p.x_vals = initList();
    p.y_vals = initList();
    p.size = 0;
    return p;
}

void addPoint(Plane* p, const Point* point) {
    appendList(&p->x_vals, point->x);
    appendList(&p->y_vals, point->y);
    p->size++;
}

void addPoints(Plane* p, const Point* points, unsigned int count) {
    for (int i = 0; i < count; i++) {
        appendList(&p->x_vals, points[i].x);
        appendList(&p->y_vals, points[i].y);
    }
    p->size += count;
}

Plane planeFromLists(const List* x_list, const List* y_list) {
    Plane p = initPlane();
    
    if (x_list->len != y_list->len) {
        printErr("Error: x and y lists must have the same length\n");
    }
    
    for (unsigned int i = 0; i < x_list->len; i++) {
        appendList(&p.x_vals, getList(*x_list, i));
        appendList(&p.y_vals, getList(*y_list, i));
    }
    p.size = x_list->len;
    
    return p;
}

Point getPoint(const Plane* p, unsigned int index) {
    Point point;
    point.x = getList(p->x_vals, index);
    point.y = getList(p->y_vals, index);
    return point;
}

Point* getAllPoints(const Plane* p) {
    Point* points = (Point*)malloc(p->size * sizeof(Point));
    checkAlloc(points);
    
    for (unsigned int i = 0; i < p->size; i++) {
        points[i].x = getList(p->x_vals, i);
        points[i].y = getList(p->y_vals, i);
    }
    
    return points;
}

unsigned int planeSize(const Plane* p) {
    return p ? p->size : 0;
}

void clearPlane(Plane* p) {
    if (!p) return;
    
    /* Reset lists but keep allocated memory */
    p->x_vals.len = 0;
    p->y_vals.len = 0;
    p->size = 0;
}

void freePlane(Plane* p) {
    if (!p) return;
    
    free(p->x_vals.arr);
    free(p->y_vals.arr);
    p->size = 0;
    /* Don't free p itself since it might be stack allocated */
}