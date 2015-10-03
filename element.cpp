#include <math.h>
#include <stdio.h>
#include "element.h"
/*
    This function needs three arguments:
        point p : the originaal point;
        line l : the line on which p and the return value lie;
        double d : the distance between p and the return value;
*/

point getPointByDistance(point p, line l, double d){
    double A = (1.0-p.abs2()) * exp(d);
    double B = 1.0 + p.abs2();
    return point(
            ((A-B)*l.getLeft() + 2.0*p)
            /
            ((A+B) - 2.0*p.conj()*l.getLeft())
            );
    //return (l.getLeft().mobius(p) * ((exp(d)-1) / (exp(d)+1))).mobius(-p);
}
