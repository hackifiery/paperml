#include "types.h"
#include "math_utils.h"
#include "vector.h"
#include "point.h"
#include <math.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>

db drand(const db lower, const db upper) {
    db range;
    db div_;

    _RAND_SEED();

    range = (upper - lower);
    div_ = RAND_MAX / range;
    return lower + (rand() / div_);
}

int irand(const int lower, const int upper) {
    return (rand() % (upper - lower + 1)) + lower;
}

db minMaxNormalization(Vector* vec) {
    int i;
    db min;
    db max;
    db range;
    if (!vec || vec->len == 0) return 0.0;
    min = vec->arr[0];
    max = vec->arr[0];
    for (i = 0; i < (int)vec->len; i++) {
        if (vec->arr[i] < min) min = vec->arr[i];
        if (vec->arr[i] > max) max = vec->arr[i];
    }
    /* prevent div by 0 */
    if (max == min) {
        for (i = 0; i < (int)vec->len; i++) vec->arr[i] = 0.0;
        return 0.0;
    }
    range = max - min;
    for (i = 0; i < (int)vec->len; i++) {
        vec->arr[i] = (vec->arr[i] - min) / range;
    }
    return range;
}

db nDimensionalEuclidianDist(const unsigned int dim, const Vector vec1, const Vector vec2) {
    int i;
    db sum = 0;
    db a;
    db b;
    assert(vec1.len == vec2.len && vec1.len >= dim);
    for (i = 0; i < dim; i++) {
        a = getVector(vec1, i);
        b = getVector(vec2, i);
        sum += sqr(a - b);
    }
    return sqrt(sum);
}

db distance(const Point p1, const Point p2) {
    db dx = p2.x - p1.x;
    db dy = p2.y - p1.y;
    return sqrt(dx * dx + dy * dy);
}