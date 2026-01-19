#include "point.h"

#include <math.h>

struct Point Point(const db x, const db y) {
    struct Point p;
    p.x = x;
    p.y = y;
    return p;
}

db distance(const struct Point p1, const struct Point p2) {
    db dx = p2.x - p1.x;
    db dy = p2.y - p1.y;
    return sqrt(dx * dx + dy * dy);
}

void rotate(struct Point* p, const struct Point center, const db angle_radians) {
    // Translate point to origin
    db translated_x = p->x - center.x;
    db translated_y = p->y - center.y;
    
    // Rotate
    db cos_theta = cos(angle_radians);
    db sin_theta = sin(angle_radians);
    db new_x = translated_x * cos_theta - translated_y * sin_theta;
    db new_y = translated_x * sin_theta + translated_y * cos_theta;
    
    // Translate back
    p->x = new_x + center.x;
    p->y = new_y + center.y;
}

void orotate(struct Point* p, const db angle_radians) {
    rotate(p, ORIGIN, angle_radians);
}

db slope(const struct Point p1, const struct Point p2) {
    db dx = p2.x - p1.x;
    
    // Check if denominator is near zero (vertical line)
    if (fabs(dx) < EPSILON) {
        return INFINITY;
    }
    
    return (p2.y - p1.y) / dx;
}

int areCollinear(const struct Point p1, const struct Point p2, const struct Point p3) {
    // triangle method: if the triangle's area is 0, they're coll.
    db area = p1.x * (p2.y - p3.y) +
              p2.x * (p3.y - p1.y) +
              p3.x * (p1.y - p2.y);
    
    return fabs(area) < EPSILON;
}