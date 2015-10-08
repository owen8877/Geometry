#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "element.h"
/*
    This function needs three arguments:
        point p : the original point;
        ideal q : the ideal point to specify the direction;
        double d : the distance between p and the return value;
*/

point getPointByDistance(point p, ideal q, double d){
    return point( q.mobius(p) * ((exp(d)-1) / (exp(d)+1)) ).mobius(-p);
}

point rotateByPoint(point p, point center, double phi){
    return p.mobius(center).rotate(phi).mobius(-center);
}

/*
    This function needs three arguments:
        point p : the original point;
        ideal q : the ideal point to specify the direction;
        double phi : the angle between the return line and direction q;
*/

line getLineByAngle(point p, ideal q, double phi){
    return line(q.mobius(p).rotate(phi), point(0.0)).mobius(-p);
}

double PoincareDistance(point p1, point p2){
    double d = (p2.mobius(p1)).abs();
    return log((1+d)/(1-d));
}

point randPoint(){ 
    double ran = (double) rand()/RAND_MAX*2 - 1;
    return point(ran, ((double)rand()/RAND_MAX*2-1)*sqrt(1-ran*ran));
}
