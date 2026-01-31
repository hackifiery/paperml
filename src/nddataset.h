#pragma once
#include "vector.h"

/* N-dimensional dataset (without labels) */
typedef struct {
    Vector* samples;
    unsigned int size; 
    unsigned int capacity;
    unsigned int dim; /* dimensionality of each sample */
} NDDataset;

/* initialize an ndd */
NDDataset initNDDataset(unsigned int dim);

/* add a sample to the ndd */
void addSampleNDDataset(NDDataset* ds, const Vector sample);

/* get a sample from ndd at index */
Vector getSampleNDDataset(const NDDataset ds, unsigned int idx);

/* TODO: add freeing function */