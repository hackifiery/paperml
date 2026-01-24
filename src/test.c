#include "linreg.h"
#include "math_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    srand(time(NULL));
    Plane pl = initPlane();
    for (int i = 0; i <= 2000; i++) {
        addPoint(&pl, initPoint(i+drand(0, 10), i+drand(0, 10)));
    }
    LinReg lr = linreg(pl);
    printLinReg(lr);
    return 0;
}