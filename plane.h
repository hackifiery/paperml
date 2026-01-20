#pragma once

#include "point.h"
#include "list.h"

/* A collection of points aka a plane */
typedef struct {
    List x_vals;
    List y_vals;
    unsigned int size;
} Plane;

/* Initialize an empty plane */
Plane initPlane(void);

/* Add a point to the plane */
void addPoint(Plane* p, const Point* point);

/* Add multiple points to the plane */
void addPoints(Plane* p, const Point* points, unsigned int count);

/* Create a plane from separate x and y lists */
Plane planeFromLists(const List* x_list, const List* y_list);

/* Get a point at an index from the plane */
Point getPoint(const Plane* p, unsigned int index);

/* Get all points as an array (caller must free) */
Point* getAllPoints(const Plane* p);

/* Get the number of points in the plane */
unsigned int planeSize(const Plane* p);

/* Clear all points from the plane */
void clearPlane(Plane* p);

/* Free plane memory */
void freePlane(Plane* p);