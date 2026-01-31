#include "nddataset.h"
#include "vector.h"
#include <stdlib.h>
#include <assert.h>

NDDataset initNDDataset(unsigned int dim) {
    NDDataset out;
    out.samples = calloc(VECTOR_INIT_SIZE, sizeof(Vector));
    out.capacity = VECTOR_INIT_SIZE;
    out.dim = dim;
    out.size = 0;
    return out;
}

void addSampleNDDataset(NDDataset* ds, const Vector sample) {
    if (ds->size >= ds->capacity) {
        ds->capacity *= VECTOR_GROWTH_FAC;
        ds->samples = realloc(ds->samples, ds->capacity * sizeof(Vector));
    }
    ds->samples[ds->size] = sample;
    ds->size++;
}

Vector getSampleNDDataset(const NDDataset ds, unsigned int idx) {
    assert(idx < ds.size);
    return ds.samples[idx];
}
