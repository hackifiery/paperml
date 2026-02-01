# paperml
basic machine learning stuff that doesn't do much rly.

## Linear Regression w/noise
```c
#include <paperml/linreg.h>
#include <paperml/math_utils.h>
#include <paperml/plane.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    srand(time(NULL));
    Plane pl = initPlane();
    for (int i = 0; i <= 2000; i++) {
        addPoint(&pl, initPoint(i+randDouble(0, 10), i+randDouble(0, 10))); /* a bit of noise */
    }
    LinearRegression lr = linreg(pl);
    printLinearRegression(lr);
    return 0;
}
```

## K-Nearest Neighbors
This code demostrates classifying a 5-D query using Majority-vote KNN.
```c
#include <paperml/knn.h>
#include <paperml/vector.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    KNearestNeighborsDataset ds;
    Vector samples[10];
    Vector query1;
    Vector query2;
    Vector query3;
    db query1_a[5] = {0.5, 1.0, 1.5, 2.0, 2.5};
    db query2_a[5] = {2.5, 3.0, 3.5, 4.0, 4.5};
    db query3_a[5] = {4.0, 4.5, 5.0, 5.5, 6.0};
    int i;
    int k;
    double res;

    /* Initialize 5D dataset */
    ds = initKNearestNeighborsDataset(5);

    /* Add 10 samples with class labels (0.0, 1.0, 2.0) */
    for (i = 0; i < 10; i++) {
        int j;
        double label;
        samples[i] = initVector();
        
        /* Create varied sample features */
        for (j = 0; j < 5; j++) {
            appendVector(&samples[i], (double)(i + j) * 0.5);
        }
        
        /* Alternate class labels */
        label = (double)(i % 3);
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
    query1 = arrToVector(query1_a, 5);
    
    printf("=== Query 1: [0.5, 1.0, 1.5, 2.0, 2.5] ===\n");
    for (k = 3; k <= 7; k += 2) {
        res = findKNearestNeighbors(ds, query1, (unsigned int)k);
        printf("  k=%d: result=%f\n", k, res);
    }

    /* Test query 2: Should be close to middle samples */
    query2 = arrToVector(query2_a, 5);
    
    printf("\n=== Query 2: [2.5, 3.0, 3.5, 4.0, 4.5] ===\n");
    for (k = 3; k <= 7; k += 2) {
        res = findKNearestNeighbors(ds, query2, (unsigned int)k);
        printf("  k=%d: result=%f\n", k, res);
    }

    /* Test query 3: Should be close to higher samples */
    query3 = arrToVector(query3_a, 5);
    
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

```