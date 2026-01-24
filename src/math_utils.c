#include "types.h"
#include "math_utils.h"
#include <stdlib.h>
#include <time.h>

db drand(const db lower, const db upper) {
    _RAND_SEED();
    db range = (upper - lower); 
    db div = RAND_MAX / range;
    return lower + (rand() / div);
}

int irand(const int lower, const int upper) {
    return (rand() % (upper - lower + 1)) + lower;
}