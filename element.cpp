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
    /*
    double A = (1.0-p.abs2()) * exp(d);
    double B = 1.0 + p.abs2();
    return point(
            ((A-B)*l.getLeft() + 2.0*p)
            /
            ((A+B) - 2.0*p.conj()*l.getLeft())
            );
    */
    return point(l.getLeft().mobius(p) * ((exp(d)-1) / (exp(d)+1))).mobius(-p);
}

/*
    To specify which side is the line going (in order to get the destination point), the function
    needs a second argument.
*/
point getPointByDistance(point origin, point direction, line l, double d){
    return point((direction.mobius(origin)).normal() * ((exp(d)-1) / (exp(d)+1))).mobius(-origin);
}

line getLineByAngle(point p, line l, double fai){
    return (line(l.getLeft().mobius(p)*unit(fai), complex(0.0))).mobius(-p);
}

line getLineByAngle(point origin, point from_direction, point to_direction, double fai){
    int flag = ((to_direction.mobius(origin)/from_direction.mobius(origin)).arg() > 0.0) ? 1 : -1;
    return (line(from_direction.mobius(origin).normal()*unit(flag * fai), complex(0.0))).mobius(-origin);
}
