#include "point.h"
#include "types.h"
#include "helpers.h"
#include "linear.h"

Linear initLinear(const db slope, const db intercept) {
    Linear out;
    out.slope = slope;
    out.intercept = intercept;
    return out;
}

db getLinY(const Linear ln, const db x) { return ln.slope*x + ln.intercept; }

db getLinX(const Linear ln, const db y) {
    if (ln.slope == 0) return ln.intercept; /* cuz division by 0 is undefined */
    return (y-ln.slope)/ln.intercept;
}

int onLinear(const Linear ln, const Point pt) { return (getLinX(ln, pt.y) == getLinY(ln, pt.x)); }