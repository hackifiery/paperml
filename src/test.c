#include "linreg.h"
#include "math_utils.h"
#include "knn.h"
#include "knndataset.h"
#include "vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    KNearestNeighborsDataset ds;
    Vector samples[10];
    Vector query1;
    Vector query2;
    Vector query3;
    int i;
    int k;
    db res;

    /* Initialize 5D dataset */
    ds = initKNearestNeighborsDataset(5);

    /* Add 10 samples with class labels (0.0, 1.0, 2.0) */
    for (i = 0; i < 10; i++) {
        int j;
        db label;
        samples[i] = initVector();
        
        /* Create varied sample features */
        for (j = 0; j < 5; j++) {
            appendVector(&samples[i], (db)(i + j) * 0.5);
        }
        
        /* Alternate class labels */
        label = (db)(i % 3);
        addSampleKNearestNeighborsDataset(&ds, samples[i], label);
    }

    /* Print all samples */
    printf("=== Dataset Samples (10 total, 5D features) ===\n");
    for (i = 0; i < 10; i++) {
        int j;
        printf("Sample %d [", i+1);
        for (j = 0; j < 5; j++) {
            printf("%g", getVector(samples[i], j));
            if (j < 4) printf(", ");
        }
        printf("] -> Label: %g\n", getSampleLabelKNearestNeighborsDataset(ds, i));
    }
    printf("\n");
    query1 = initVector();
    appendVector(&query1, 0.5);
    appendVector(&query1, 1.0);
    appendVector(&query1, 1.5);
    appendVector(&query1, 2.0);
    appendVector(&query1, 2.5);
    
    printf("=== Query 1: [0.5, 1.0, 1.5, 2.0, 2.5] ===\n");
    for (k = 3; k <= 7; k += 2) {
        res = findKNearestNeighbors(ds, query1, (unsigned int)k);
        printf("  k=%d: result=%f\n", k, res);
    }

    /* Test query 2: Should be close to middle samples */
    query2 = initVector();
    appendVector(&query2, 2.5);
    appendVector(&query2, 3.0);
    appendVector(&query2, 3.5);
    appendVector(&query2, 4.0);
    appendVector(&query2, 4.5);
    
    printf("\n=== Query 2: [2.5, 3.0, 3.5, 4.0, 4.5] ===\n");
    for (k = 3; k <= 7; k += 2) {
        res = findKNearestNeighbors(ds, query2, (unsigned int)k);
        printf("  k=%d: result=%f\n", k, res);
    }

    /* Test query 3: Should be close to higher samples */
    query3 = initVector();
    appendVector(&query3, 4.0);
    appendVector(&query3, 4.5);
    appendVector(&query3, 5.0);
    appendVector(&query3, 5.5);
    appendVector(&query3, 6.0);
    
    printf("\n=== Query 3: [4.0, 4.5, 5.0, 5.5, 6.0] ===\n");
    for (k = 3; k <= 7; k += 2) {
        res = findKNearestNeighbors(ds, query3, (unsigned int)k);
        printf("  k=%d: result=%f\n", k, res);
    }

    /* Cleanup */
    for (i = 0; i < 10; i++) {
        free(samples[i].arr);
    }
    free(query1.arr);
    free(query2.arr);
    free(query3.arr);
    free(ds.base.samples);
    free(ds.labels.arr);
    return 0;
}