#include "linreg.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    srand(time(NULL));
    Plane pl = initPlane();
    for (int i = 0; i <= 10; i++) {
        double r1 = (double)rand() / (double)RAND_MAX*1;
        double r2 = (double)rand() / (double)RAND_MAX*1;
        addPoint(&pl, initPoint(i + r1, i + r2));
    }
    LinReg lr = linreg(pl);
    printLinReg(lr);
    return 0;
}