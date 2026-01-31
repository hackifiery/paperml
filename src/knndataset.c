#include "knndataset.h"
#include "nddataset.h"
#include "vector.h"
#include <stdlib.h>
#include <assert.h>

KNearestNeighborsDataset initKNearestNeighborsDataset(unsigned int dim) {
    KNearestNeighborsDataset out;
    out.base = initNDDataset(dim);
    out.labels = initVector();
    return out;
}

void addSampleKNearestNeighborsDataset(KNearestNeighborsDataset* ds, const Vector sample, const db label) {
    if (ds->base.size >= ds->base.capacity) {
        ds->base.capacity *= VECTOR_GROWTH_FAC;
        ds->base.samples = realloc(ds->base.samples, ds->base.capacity * sizeof(Vector));
    }
    ds->base.samples[ds->base.size] = sample;
    appendVector(&ds->labels, label);
    ds->base.size++;
}

Vector getSampleKNearestNeighborsDataset(const KNearestNeighborsDataset ds, unsigned int idx) {
    assert(idx < ds.base.size);
    return ds.base.samples[idx];
}

db getSampleLabelKNearestNeighborsDataset(const KNearestNeighborsDataset ds, unsigned int idx) {
    assert(idx < ds.base.size);
    return getVector(ds.labels, idx);
}
