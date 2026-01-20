#include "point.h"

#include <math.h>

Point initPoint(const db x, const db y) {
    Point p;
    p.x = x;
    p.y = y;
    return p;
}

db distance(const Point p1, const Point p2) {
    db dx = p2.x - p1.x;
    db dy = p2.y - p1.y;
    return sqrt(dx * dx + dy * dy);
}

void rotate(Point* p, const Point center, const db angleRadians) {
    /* Translate point to origin */
    db translatedX = p->x - center.x;
    db translatedY = p->y - center.y;
    
    /* Rotate */
    db cosTheta = cos(angleRadians);
    db sinTheta = sin(angleRadians);
    db newX = translatedX * cosTheta - translatedY * sinTheta;
    db newY = translatedX * sinTheta + translatedY * cosTheta;
    
    /* Translate back */
    p->x = newX + center.x;
    p->y = newY + center.y;
}

void orotate(Point* p, const db angleRadians) {
    rotate(p, ORIGIN, angleRadians);
}

db slope(const Point p1, const Point p2) {
    db dx = p2.x - p1.x;
    
    /* Check if denominator is near zero (vertical line) */
    if (fabs(dx) < EPSILON) {
        return INFINITY;
    }
    
    return (p2.y - p1.y) / dx;
}

int areCollinear(const Point p1, const Point p2, const Point p3) {
    /* triangle method: if the triangle's area is 0, they're collinear */
    db area = p1.x * (p2.y - p3.y) +
              p2.x * (p3.y - p1.y) +
              p3.x * (p1.y - p2.y);
    
    return fabs(area) < EPSILON;
}