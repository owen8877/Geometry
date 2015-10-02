#include <math.h>
#include <stdio.h>
#include "element.h"

line::line(double _x, double _y):complex(_x, _y){}

line::line(complex c):complex(c){}

point line::getCenter(){ return point(x, y); }

double line::getRadius(){ return sqrt(abs2() - 1); }

double line::getStartArc(){
    double middle = atan2(y, x) + M_PI;
    double deflection = asin(1/abs());
    return (middle - deflection);
}
double line::getEndArc(){
    double middle = atan2(y, x) + M_PI;
    double deflection = asin(1/abs());
    return (middle + deflection);
}

line line::mobius(complex c){
    return line(
            ( (*this) - c*2 + conj()*c*c )
            /
            ( 1 + c.abs2() - (*this)*c.conj() - c*conj() )
            );
}

void line::print(){
    printf("Line: ");
    complex::print();
}
