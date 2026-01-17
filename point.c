#include "point.h"

#include <math.h>

struct Point Point(const db x, const db y) {
    struct Point p;
    p.x = x;
    p.y = y;
    return p;
}

struct Point getOrigin(void) {return Point(0, 0);}

db distance(const struct Point* p1, const struct Point* p2) {
    db dx = p2->x - p1->x;
    db dy = p2->y - p1->y;
    return sqrt(dx * dx + dy * dy);
}

void rotate(struct Point* p, const db angle_radians) {
    db cos_theta = cos(angle_radians);
    db sin_theta = sin(angle_radians);
    db new_x = p->x * cos_theta - p->y * sin_theta;
    db new_y = p->x * sin_theta + p->y * cos_theta;
    
    p->x = new_x;
    p->y = new_y;
}

db slope(const struct Point* p1, const struct Point* p2) {
    db dx = p2->x - p1->x;
    
    // Check if denominator is near zero (vertical line)
    if (fabs(dx) < EPSILON) {
        return INFINITY;
    }
    
    return (p2->y - p1->y) / dx;
}
int areCollinear(const struct Point* p1, const struct Point* p2, const struct Point* p3) {
    // triangle method: if the triangle's area is 0, they're coll.
    db area = p1->x * (p2->y - p3->y) +
              p2->x * (p3->y - p1->y) +
              p3->x * (p1->y - p2->y);
    
    return fabs(area) < EPSILON;
}