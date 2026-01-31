#ifndef PAPERML_POINT_H
#define PAPERML_POINT_H

#define EPSILON 1e-12
#define ORIGIN initPoint(0, 0)

#include "types.h"

/* A point at (x, y) */
typedef struct {
    db x;
    db y;
} Point;

/* Initialize a point at (x, y) */
Point initPoint(const db x, const db y);

/* Calculate the euclidian distance between two points */
db distance(const Point p1, const Point p2);

/* Rotate a point by angleRadians about a center */
void rotate(Point* p, const Point center, const db angleRadians);

/* Rotate a point by angleRadians about the origin */
void orotate(Point* p, const db angleRadians);

/* Calculate the slope of the line formed by two points */
db slope(const Point p1, const Point p2);

/* Check if three points are collinear */
#endif /* PAPERML_POINT_H */
int areCollinear(const Point p1, const Point p2, const Point p3);
