#ifndef PAPERML_KNN_H
#define PAPERML_KNN_H
#include "plane.h"
#include "vector.h"
#include "knndataset.h"

/* apply k-nearest neighbors on a KNN dataset using majority vote */
db findKNearestNeighbors(const KNearestNeighborsDataset dataset, const Vector query, unsigned int k);

/* Backwards-compatible 2D helper using Plane */
db findKNearestFromPlane(const Plane dataset, const Point query, unsigned int k);

#endif /* PAPERML_KNN_H */