#pragma once
#define EPSILON 1e-12

#include "types.h"

struct Point {
    db x;
    db y;
};

struct Point Point(const db x, const db y);
struct Point getOrigin(void);
db distance(const struct Point* p1, const struct Point* p2);
void rotate(struct Point* p, const db angle_radians);
int areCollinear(const struct Point* p1, const struct Point* p2, const struct Point* p3);
db slope(const struct Point* p1, const struct Point* p2);