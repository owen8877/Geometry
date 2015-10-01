#include <math.h>
#include "element.h"
/*
    This function needs four arguments:
        point p : the originaal point;
        line l : the line on which p and the return value lie;
        bool flag : true - anti-clockwise;
                    false - clockwise;
        double d : the distance between p and the return value;
*/

point getPointByDistance(point p, line l, bool flag, double d){
    d = (flag ? d : (-d));
    double A = (1.0-p.abs2()) * exp(d);
    double B = 1.0 + p.abs2();
    //complex mystery = complex(1.0, sqrt(l.getCenter().abs2()-1.0)) / l.getCenter().conj();
    complex mystery = l.getCenter() + l.getRadius() * unit(l.getStartArc());
    return point(
               ((A-B)*mystery + 2.0*p)
               /
               ((A+B) - 2.0*p.conj()*mystery)
           );
}
