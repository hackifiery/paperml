#ifndef PAPERML_MATH_UTILS_H
#define PAPERML_MATH_UTILS_H
#include "types.h"
#include "vector.h"
#include "point.h"
#include <math.h>

#ifndef _RAND_SEEDED
#define _RAND_SEEDED 0
#endif

#ifndef INFINITY
/* fallback */
#define INFINITY HUGE_VAL
#endif

#define _RAND_SEED() if (_RAND_SEEDED) srand(time(NULL));

#define sqr(x) pow((x), 2)
#define inv(x) 1/x

/* Generates a random double from lower to upper. */
db randDouble(const db lower, const db upper);

/* Generates a random integer from lower to upper. */
int randInt(const int lower, const int upper);


/* N-dimensional Euclidean distance between two Vectors */
db nDimensionalEuclidianDist(const unsigned int dim, const Vector vec1, const Vector vec2);

/* 2D point distance */
db distance(const Point p1, const Point p2);

/* Min-max normalizer / scaler */
db minMaxNormalization(Vector* vec);

#endif /* PAPERML_MATH_UTILS_H */