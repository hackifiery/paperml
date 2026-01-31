#include "point.h"
#include "math_utils.h"

#include <math.h>

Point initPoint(const db x, const db y) {
    Point p;
    p.x = x;
    p.y = y;
    return p;
}

void rotate(Point* p, const Point center, const db angleRadians) {
    /* Translate point to origin */
    db translatedX;
    db translatedY;
    db cosTheta;
    db sinTheta;
    db newX;
    db newY;
    
    translatedX = p->x - center.x;
    translatedY = p->y - center.y;
    
    /* Rotate */
    cosTheta = cos(angleRadians);
    sinTheta = sin(angleRadians);
    newX = translatedX * cosTheta - translatedY * sinTheta;
    newY = translatedX * sinTheta + translatedY * cosTheta;
    
    /* Translate back */
    p->x = newX + center.x;
    p->y = newY + center.y;
}

void orotate(Point* p, const db angleRadians) {
    rotate(p, ORIGIN, angleRadians);
}

db slope(const Point p1, const Point p2) {
    db dx;
    
    dx = p2.x - p1.x;
    
    /* Check if denominator is near zero (vertical line) */
    if (fabs(dx) < EPSILON) {
        return INFINITY;
    }
    
    return (p2.y - p1.y) / dx;
}

int areCollinear(const Point p1, const Point p2, const Point p3) {
    /* triangle method: if the triangle's area is 0, they're collinear */
    db area;
    
    area = p1.x * (p2.y - p3.y) +
           p2.x * (p3.y - p1.y) +
           p3.x * (p1.y - p2.y);
    
    return fabs(area) < EPSILON;
}