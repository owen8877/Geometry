#include <math.h>
#include <stdio.h>
#include "element.h"

point::point():complex(0.0){}

point::point(double _x, double _y):complex(_x, _y){}

point::point(complex c):complex(c){}

point point::mobius(complex c){
    return point(((*this) - c)/(1.0 - (*this)*c.conj()));
}

point point::rotate(double theta){
    return point((*this)*unit(theta));
}

void point::print(){
    printf("Point: ");
    complex::print();
}

ideal::ideal(complex c){
    if (c.abs2() < 1e-6)
        throw "Error getting an ideal point by origin.\n";
    *((complex *)this) = c.normal();
}

ideal::ideal(double _x, double _y){
    if (_x*_x + _y*_y < 1e-6)
        throw "Error getting an ideal point by origin.\n";
    *((complex *)this) = complex(_x, _y).normal();
}

ideal ideal::mobius(complex c){
    return ideal( ((*this) - c) / (1.0 - (*this)*c.conj()) );
}

ideal ideal::rotate(double theta){
    return ideal((*this)*unit(theta));
}

void ideal::print(){
    printf("Ideal Point: ");
    complex::print();
}
