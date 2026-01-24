#pragma once
#include "types.h"

#ifndef _RAND_SEEDED
#define _RAND_SEEDED 0
#endif

#define _RAND_SEED() if (_RAND_SEEDED) srand(time(NULL));

/* Generates a random double from lower to upper. */
db drand(const db lower, const db upper);

/* Generates a random integer from lower to upper. */
int irand(const int lower, const int upper);