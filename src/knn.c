#include "knn.h"
#include "knndataset.h"
#include "vector.h"
#include "helpers.h"
#include "math_utils.h"
#include <assert.h>
#include <math.h>
#include <stdlib.h>

typedef struct { db dist; db label; } DistLabel;

static int cmp(const void* a, const void* b) {
    const DistLabel* A = a;
    const DistLabel* B = b;
    if (A->dist < B->dist) return -1;
    if (A->dist > B->dist) return 1;
    return 0;
}

db findKNearestNeighbors(const KNearestNeighborsDataset dataset, const Vector query, unsigned int k) { /* K-NN classification: majority vote of neighbor labels */
    int i;
    DistLabel* arr;
    Vector kLabels;
    db result;

    assert(query.len == dataset.base.dim);
    assert(k <= dataset.base.size);

    arr = (DistLabel*)malloc(dataset.base.size * sizeof(DistLabel));
    checkAlloc(arr);

    for (i = 0; i < dataset.base.size; i++) {
        arr[i].dist = nDimensionalEuclidianDist(dataset.base.dim, getSampleKNearestNeighborsDataset(dataset, i), query);
        arr[i].label = getSampleLabelKNearestNeighborsDataset(dataset, i);
    }
    /* sort by distance */
    qsort(arr, dataset.base.size, sizeof(DistLabel), cmp);

    /* collect k nearest labels */
    kLabels = initVector();
    for (i = 0; i < k; i++) {
        appendVector(&kLabels, arr[i].label);
    }
    free(arr);
    
    /* use majority vote */
    result = majorityVoteVector(kLabels);
    free(kLabels.arr);
    return result;
}

db findKNearestFromPlane(const Plane dataset, const Point query, unsigned int k) {
    /* TODO: make it directly use findKNearestNeighbors */
    Vector allDists;
    Vector kDists;
    int i;
    double dx;
    double dy;
    db avg;

    assert(k <= dataset.size);
    allDists = initVector();
    kDists = initVector();
    for (i = 0; i < (int)dataset.size; i++) {
        dx = getPoint(dataset, i).x - query.x;
        dy = getPoint(dataset, i).y - query.y;
        appendVector(&allDists, sqrt(dx*dx + dy*dy));
    }
    sortVector(&allDists);
    for (i = 0; i < (int)k; i++) {
        appendVector(&kDists, getVector(allDists, i));
    }
    /* uniform (non-weighted) average like findKNearestNeighbors */
    minMaxNormalization(&kDists);
    avg = sumVector(kDists) / k;
    
    return avg;
}