#include <math.h>
#include <stdio.h>
#include "element.h"

line::line(double _x, double _y){
    x = _x;
    y = _y;
}

line::line(complex c){
    x = c.getX();
    y = c.getY();
}

point line::getCenter(){ return point(x, y); }
double line::getRadius(){ return sqrt(x*x+y*y-1); }

double line::getStartArc(){
    double middle = atan(y/x);
    double deflection = asin(1/sqrt(x*x+y*y));
    if (x >= 0) return (middle - deflection + ((y > 0) ? -1 : 1) * PAI);
    return (middle - deflection);
}
double line::getEndArc(){
    double middle = atan(y/x);
    double deflection = asin(1/sqrt(x*x+y*y));
    if (x >= 0) return (middle + deflection + ((y > 0) ? -1 : 1) * PAI);
    return (middle + deflection);
}

line line::mobius(complex c){
    return line(
                ((*this) - c*2.0 + conj()*c*c )
                /
                ( 1 + c*c.conj() - (*this)*c.conj() - c*conj() )
               );
}
