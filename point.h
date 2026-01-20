#pragma once

#define EPSILON 1e-12
#define ORIGIN initPoint(0, 0)

#include "types.h"

/** @brief a point at (x, y). */
typedef struct {
    db x;
    db y;
} Point;

/**
* @brief Initializes a point at (x, y).
* @param x The x-coordinate.
* @param y The y-coordinate.
*/
Point initPoint(const db x, const db y);

/**
* @brief Finds the euclidian distance between Points p1 and p2.
* @param p1 The first point.
* @param p2 The second point.
*/
db distance(const Point p1, const Point p2);


/**
* @brief Rotates Point p by angle_radians radians about center.
* @param p The Point to rotate.
* @param center The Point to rotate about.
* @param angle_radians The angle to roatate, in radians.
*/
void rotate(Point* p, const Point center, const db angle_radians);

/**
* @brief Rotates Point p by angle_radians about the origin.
* @param p The Point to rotate.
* @param angle_radians The angle to roatate, in radians.
*/
void orotate(Point* p, const db angle_radians);

/**
* @brief Compute the slope of the line formed by p1 and p2.
* @param p1 The first point.
* @param p2 The second point.
*/
db slope(const Point p1, const Point p2);

/**
* @brief Check if three points are collinear.
* @param p1 The first point.
* @param p2 The second point.
* @param p3 The third point.
*/
int areCollinear(const Point p1, const Point p2, const Point p3);
