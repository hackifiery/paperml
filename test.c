#include "linreg.h"
#include <stdio.h>

int main(void) {
    Plane pl = initPlane();
    for (int i = 0; i <= 10; i++) addPoint(&pl, initPoint(i,i));
    LinReg lr = linreg(pl);
    printLinReg(lr);
    return 0;
}