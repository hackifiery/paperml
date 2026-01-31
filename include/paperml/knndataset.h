#pragma once
#include "nddataset.h"
#include "vector.h"

/* Used by all KNN-related stuff, just a NDDataset with labels */
typedef struct {
    NDDataset base; /* the NDDataset without labels */
    Vector labels;
} KNearestNeighborsDataset;

/* initialize a KNN dataset */
KNearestNeighborsDataset initKNearestNeighborsDataset(unsigned int dim);

/* add a sample (with label) to the KNN dataset */
void addSampleKNearestNeighborsDataset(KNearestNeighborsDataset* ds, const Vector sample, const db label);

/* get a sample from KNN dataset at index */
Vector getSampleKNearestNeighborsDataset(const KNearestNeighborsDataset ds, unsigned int idx);

/* get the label/target for a sample at index */
db getSampleLabelKNearestNeighborsDataset(const KNearestNeighborsDataset ds, unsigned int idx);
