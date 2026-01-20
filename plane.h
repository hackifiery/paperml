// plane.h
#pragma once

#include "point.h"
#include "list.h"

/**
 * @brief Represents a collection of points (a "plane" or dataset)
 */
typedef struct {
    List x_vals;  /* List of x coordinates */
    List y_vals;  /* List of y coordinates */
    unsigned int size;   /* Number of points (should equal both list lengths) */
} Plane;

/** Initialize an empty plane */
Plane initPlane(void);

/**
 * @brief Add a point to the plane
 */
void addPoint(Plane* p, const Point* point);

/**
 * @brief Add multiple points from arrays
 */
void addPoints(Plane* p, const Point* points, unsigned int count);

/**
 * @brief Create a plane from separate x and y lists
 * @warning Lists must be the same length
 */
Plane planeFromLists(const List* x_list, const List* y_list);

/**
 * @brief Get a point at index from the plane
 */
Point getPoint(const Plane* p, unsigned int index);

/**
 * @brief Get all points as an array (caller must free)
 */
Point* getAllPoints(const Plane* p);

/** Get the number of points in the plane */
unsigned int planeSize(const Plane* p);

/** Clear all points from the plane */
void clearPlane(Plane* p);

/** Free plane memory */
void freePlane(Plane* p);